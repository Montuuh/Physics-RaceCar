#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turning = accelerating = braking = 0.0f;
	startPosition.Set(10, 2, 20);
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.carShape_size.Set(2.2f, 0.5f, 5.0f);
	car.carShape_offset.Set(0.0f, 1.0f, 0.0f);
	car.mass = 500.0f;
	car.suspensionStiffness = 14.5f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.95f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;
	car.color = LightGrey;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.25f;
	float wheel_width = 0.2f;
	float suspensionRestLength = 0.7f;

	// Don't change anything below this line ------------------

	float half_width = car.carShape_size.x * 0.5f;
	float half_length = car.carShape_size.z * 0.5f;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);

	vehicle->SetPos(startPosition.x, startPosition.y, startPosition.z);
	vehicle->Rotate(3.14f);
	vehicle->GetTransform(startMatrix);
	player_state = state::EMPTY;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	braking = 0.0f;
	turning = 0.0f;
	accelerating = 0.0f;


	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LEFT) != KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RIGHT) != KEY_REPEAT)
	{
		accelerating = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		accelerating = MAX_ACCELERATION;

		if (turning < MAX_TURN)
			turning += MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		accelerating = MAX_ACCELERATION;

		if (turning > -MAX_TURN)
			turning -= MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (turning < MAX_TURN)
			turning += MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT)
	{
		accelerating = -MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		accelerating = -MAX_ACCELERATION;

		if (turning < MAX_TURN)
			turning += MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		accelerating = -MAX_ACCELERATION;

		if (turning > -MAX_TURN)
			turning -= MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (turning > -MAX_TURN)
			turning -= MAX_TURN;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		braking = MAX_BRAKE;
	}

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
	{
		accelerating = MAX_ACCELERATION * 5;
	}



	vehicle->Brake(braking);
	vehicle->ApplyEngineForce(accelerating);
	vehicle->Turn(turning);

	vehicle->Render();

	char title[100];
	sprintf_s(title,"Current Velocity: %.1f Km/h, Countdown: %ds left, Clients: %d/5 satisfied", vehicle->GetKmh(), 180 - App->scene_intro->game_timer.Read() / 1000, App->scene_intro->clientsDone);
	App->window->SetTitle(title);

	pos = vehicle->GetPos();

	return UPDATE_CONTINUE;
}



