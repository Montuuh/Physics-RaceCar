#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "ModuleAudio.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("Audio/Music/background_song.ogg");
	winFx = App->audio->LoadFx("Audio/Fx/win.ogg");
	clientDestinationFx = App->audio->LoadFx("Audio/Fx/coin.ogg");
	clientPickedFx = App->audio->LoadFx("Audio/Fx/pick_client.ogg");
	looseFx = App->audio->LoadFx("Audio/Fx/loose.ogg");

	//Double lines
	CreateLine({ 20.0f, 0.0f, 10.0f }, { 80.0f, 0.0f, 10.0f }, 30, true);
	CreateLine({ 10.0f, 0.0f, 20.0f }, { 10.0f, 0.0f, 80.0f }, 30, true);
	CreateLine({ 90.0f, 0.0f, 20.0f }, { 90.0f, 0.0f, 80.0f }, 30, true);
	CreateLine({ 20.0f, 0.0f, 90.0f }, { 80.0f, 0.0f, 90.0f }, 30, true);

	CreateLine({ 100.0f, 0.0f, 10.0f }, { 160.0f, 0.0f, 10.0f }, 30, true);
	CreateLine({ 170.0f, 0.0f, 20.0f }, { 170.0f, 0.0f, 80.0f }, 30, true);
	CreateLine({ 170.0f, 0.0f, 100.0f }, { 170.0f, 0.0f, 160.0f }, 30, true);
	CreateLine({ 160.0f, 0.0f, 170.0f }, { 100.0f, 0.0f, 170.0f }, 30, true);
	CreateLine({ 90.0f, 0.0f, 100.0f }, { 90.0f, 0.0f, 160.0f }, 30, true);

	CreateLine({ 180.0f, 0.0f, 10.0f }, { 230.0f, 0.0f, 10.0f }, 25, true);
	CreateLine({ 240.0f, 0.0f, 20.0f }, { 240.0f, 0.0f, 80.0f }, 30, true);
	CreateLine({ 180.0f, 0.0f, 90.0f }, { 230.0f, 0.0f, 90.0f }, 25, true);

	CreateLine({ 180.0f, 0.0f, 170.0f }, { 230.0f, 0.0f, 170.0f }, 30, true);
	CreateLine({ 240.0f, 0.0f, 100.0f }, { 240.0f, 0.0f, 160.0f }, 30, true);

	CreateLine({ 240.0f, 0.0f, 180.0f }, { 240.0f, 0.0f, 240.0f }, 30, true);
	CreateLine({ 230.0f, 0.0f, 250.0f }, { 100.0f, 0.0f, 250.0f }, 65, true);

	CreateLine({ 90.0f, 0.0f, 180.0f }, { 90.0f, 0.0f, 240.0f }, 30, true);
	CreateLine({ 10.0f, 0.0f, 100.0f }, { 10.0f, 0.0f, 240.0f }, 70, true);

	CreateLine({ 20.0f, 0.0f, 250.0f }, { 80.0f, 0.0f, 250.0f }, 30, true);

	//Single lines
	CreateLine({ 0.0f, 0.0f, 10.0f }, { 20.0f, 0.0f, 10.0f }, 10, false);
	CreateLine({ -10.0f, 0.0f, 0.0f }, { -10.0, 0.0f, 20.0f }, 10, false);

	CreateLine({ 80.0f, 0.0f, 10.0f }, { 100.0f, 0.0f, 10.0f }, 10, false);

	CreateLine({ 160.0f, 0.0f, 10.0f }, { 180.0f, 0.0f, 10.0f }, 10, false);

	CreateLine({ 230.0f, 0.0f, 10.0f }, { 250.0f, 0.0f, 10.0f }, 10, false);
	CreateLine({ 240.0f, 0.0f, 0.0f }, { 240.0f, 0.0f, 20.0f }, 10, false);

	CreateLine({ -10.0f, 0.0f, 80.0f }, { -10.0f, 0.0f, 100.0f }, 10, false);
	CreateLine({ 90.0f, 0.0f, 80.0f }, { 90.0f, 0.0f, 100.0f }, 10, false);

	CreateLine({ 150.0f, 0.0f, 80.0f }, { 150.0f, 0.0f, 100.0f }, 10, false);
	CreateLine({ 240.0f, 0.0f, 80.0f }, { 240.0f, 0.0f, 100.0f }, 10, false);

	CreateLine({ 70.0f, 0.0f, 160.0f }, { 70.0f, 0.0f, 180.0f }, 10, false);
	CreateLine({ 240.0f, 0.0f, 160.0f }, { 240.0f, 0.0f, 180.0f }, 10, false);

	CreateLine({ 160.0f, 0.0f, 190.0f }, { 180.0f, 0.0f, 190.0f }, 10, false);

	CreateLine({ 240.0f, 0.0f, 240.0f }, { 240.0f, 0.0f, 260.0f }, 10, false);
	CreateLine({ 230.0f, 0.0f, 270.0f }, { 250.0f, 0.0f, 270.0f }, 10, false);

	CreateLine({ 80.0f, 0.0f, 270.0f }, { 110.0f, 0.0f, 270.0f }, 15, false);

	CreateLine({ 0.0f, 0.0f, 270.0f }, { 20.0f, 0.0f, 270.0f }, 10, false);
	CreateLine({ -10.0f, 0.0f, 240.0f }, { -10.0f, 0.0f, 260.0f }, 10, false);

	goalPos = vec3(50.0f, 5.0f, 20.0f);
	CreateClients();

	Cylinder destination(3.0f, 100.0f);
	destination.color = TransparentGreen;
	destination.SetRotation(90.0f, vec3(0.0f, 0.0f, 1.0f));
	goalPoint = destination;

	Line arrow(goalPos.x, 1.5f, goalPos.z);
	arrow.origin = App->player->pos;
	arrow.destination = vec3(arrow.destination.x / 10.0f, arrow.destination.y / 10.0f, arrow.destination.z / 10.0f);
	arrow.color = TransparentGreen;
	arrowPoint = arrow;

	clientsDone = 0;
	game_timer.Start();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	clients.Clear();
	cube_pieces.physic_bodies.Clear();
	cube_pieces.primitive_bodies.Clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0.0f, 1.0f, 0.0f, 0.0f);
	Cube floor(900.0f, 0.01f, 900.0f);

	Cube building1(50.0f, 50.0f, 50.0f);
	building1.SetPos(50.0f, 0.0f, 50.0f);
	Cube building2(50.0f, 80.0f, 130.0f);
	building2.SetPos(130.0f, 0.0f, 90.0f);
	Cube building3(40.0f, 100.0f, 50.0f);
	building3.SetPos(205.0f, 15.0f, 50.0f);
	Cube building4(40.0f, 100.0f, 50.0f);
	building4.SetPos(205.0f, 40.0f, 130.0f);
	Cube building5(50.0f, 60.0f, 130.0f);
	building5.SetPos(50.0f, 20.0f, 170.0f);
	Cube building6(120.0f, 35.0f, 50.0f);
	building6.SetPos(165.0f, 0.0f, 210.0f);

	floor.color = LightBlue;
	building1.color = LightBlue;
	building1.Render();
	building2.color = Blue;
	building2.Render();
	building3.color = Red;
	building3.Render();
	building4.color = Skin;
	building4.Render();
	building5.color = Yellow;
	building5.Render();
	building6.color = Green;
	building6.Render();
	floor.Render();

	for (int i = 0; i < cube_pieces.primitive_bodies.Count(); i++)
		cube_pieces.primitive_bodies[i].Render();

	// Restart condition
	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		App->player->turning = 0;
		App->player->accelerating = 0;
		App->player->braking = 0;

		App->player->vehicle->SetTransform(App->player->startMatrix);

		App->player->vehicle->info.color = LightGrey;
	}
	// Win condition
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		App->player->turning = 0;
		App->player->accelerating = 0;
		App->player->braking = 0;
		
		App->player->vehicle->info.color = Green;
		App->audio->PlayFx(winFx);

		Restart();
	}

	// Loose condition
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		App->player->vehicle->info.color = Red;
		App->audio->PlayFx(looseFx);

		Restart();
	}

	if (game_timer.Read() > 200000)
	{
		Restart();
		App->audio->PlayFx(looseFx);
		App->player->vehicle->info.color = Red;
	}

	for (int i = 0; i < clients.Count(); i++)
	{

		if ((abs(App->player->pos.x - clients[i].transform[12]) < 3 && abs(App->player->pos.z - clients[i].transform[14]) < 3) && App->player->braking == MAX_BRAKE && App->player->player_state == state::EMPTY && clients[i].color.g == 0.86f)
		{
			App->player->player_state = state::CARRYING;
			App->player->client = i;

			App->audio->PlayFx(clientPickedFx);

			ChangeGoal(App->player->client);
			goalPoint.SetPos(goalPos.x, goalPos.y, goalPos.z);
		}

		if (App->player->player_state == state::CARRYING)
		{
			btQuaternion q = App->player->vehicle->vehicle->getChassisWorldTransform().getRotation();
			App->player->vehicle->vehicle->getChassisWorldTransform().getOpenGLMatrix(&clients[App->player->client].transform);
			btVector3 lw_offset(App->player->vehicle->info.carShape_offset.x - 0.5f, App->player->vehicle->info.carShape_offset.y + 0.5f, App->player->vehicle->info.carShape_offset.z - 0.6f);
			lw_offset = lw_offset.rotate(q.getAxis(), q.getAngle());
			clients[App->player->client].transform.M[12] += lw_offset.getX();
			clients[App->player->client].transform.M[13] += lw_offset.getY();
			clients[App->player->client].transform.M[14] += lw_offset.getZ();
			arrowPoint.destination = vec3(App->player->pos.x + (goalPoint.transform.M[12] - App->player->pos.x) / 50.0f, App->player->pos.y + 3, App->player->pos.z + (goalPoint.transform.M[14] - App->player->pos.z) / 50.0f);
			arrowPoint.origin = vec3(App->player->pos.x, App->player->pos.y + 3.0f, App->player->pos.z);
			goalPoint.Render();
			arrowPoint.Render();

			if (abs(App->player->pos.x - goalPoint.transform[12]) < 3 && abs(App->player->pos.z - goalPoint.transform[14]) < 3 && App->player->braking == MAX_BRAKE)
			{
				App->player->player_state = state::EMPTY;

				App->audio->PlayFx(clientDestinationFx);

				clients[App->player->client].color = Green;
				clients[App->player->client].SetPos(App->player->pos.x, App->player->pos.y, App->player->pos.z);
				clients[App->player->client].transform.M[12] += 2.0f;
				clients[App->player->client].transform.M[13] = 0.25f;
				clientsDone++;
				App->player->vehicle->GetTransform(App->player->checkpointMatrix);
				if (clientsDone == 5)
				{
					App->audio->PlayFx(winFx);
					App->player->vehicle->info.color = Green;
					Restart();
				}
			}
		}

		clients[i].Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateLine(const vec3 initialPos, const vec3 finalPos, uint numCubes, bool isDouble)
{

	float distance = sqrt(pow(finalPos.x - initialPos.x, 2.0f) + pow(finalPos.y - initialPos.y, 2.0f) + pow(finalPos.z - initialPos.z, 2.0f));
	float distanceSeg = distance / numCubes;

	vec3 dir_v = finalPos - initialPos;
	float dir_v_mod = sqrt((dir_v.x * dir_v.x) + (dir_v.y * dir_v.y) + (dir_v.z * dir_v.z));
	dir_v /= dir_v_mod;
	vec3 perp_v = { -dir_v.z, 0, dir_v.x };
	float perp_v_mod = sqrt((perp_v.x * perp_v.x) + (perp_v.y * perp_v.y) + (perp_v.z * perp_v.z));
	perp_v /= perp_v_mod;

	vec3 pos;
	vec3 dim(0.5f, 50.0f, 0.5f);

	Cube wall;
	wall.color = LightMaroon;
	wall.size = { dim.x, dim.y, dim.z };

	for (uint j = 0; j < numCubes; j++)
	{
		if (isDouble)
		{
			pos = (initialPos + (dir_v * j * distanceSeg)) + ((TRACK_WIDTH / 2.0f) * perp_v);
			wall.SetPos(pos.x, pos.y + 1.0f, pos.z);
			cube_pieces.primitive_bodies.PushBack(wall);
			cube_pieces.physic_bodies.PushBack(App->physics->AddBody(wall, 0.0f));
		}

		pos = (initialPos + (dir_v * j * distanceSeg)) + ((TRACK_WIDTH / 2.0f) * -perp_v);
		wall.SetPos(pos.x, pos.y + 1.0f, pos.z);
		cube_pieces.primitive_bodies.PushBack(wall);
		cube_pieces.physic_bodies.PushBack(App->physics->AddBody(wall, 0.0f));
	}
}

void ModuleSceneIntro::CreateClients()
{
	Cube cl(0.4f, 1.2f, 0.4f);
	cl.color = Skin;

	for (uint j = 0; j < 5; j++)
	{
		clients.PushBack(cl);
	}

	//Placing clients
	clients[0].SetPos(120.0f, 0.25f, 10.0f);
	clients[1].SetPos(210.f, 0.25f, 170.0f);
	clients[2].SetPos(110.0f, 0.25f, 170.0f);
	clients[3].SetPos(10.0f, 0.25f, 60.0f);
	clients[4].SetPos(240.0f, 0.25f, 240.0f);
}

// Client goals
void ModuleSceneIntro::ChangeGoal(int dest)
{
	switch (dest)
	{
	case 0:
		goalPos = vec3(60.0f, 2.0f, 250.0f);
		break;
	case 1:
		goalPos = vec3(130.0f, 2.0f, 250.0f);
		break;
	case 2:
		goalPos = vec3(200.0f, 2.0f, 10.0f);
		break;
	case 3:
		goalPos = vec3(170.0f, 2.0f, 90.0f);
		break;
	case 4:
		goalPos = vec3(90.0f, 2.0f, 130.0f);
		break;
	}
}

//Restarting game
void ModuleSceneIntro::Restart()
{
	App->audio->PlayMusic("Audio/Music/background_song.ogg");

	game_timer.Start();
	App->player->player_state = state::EMPTY;
	App->player->vehicle->SetTransform(App->player->startMatrix);

	for (uint j = 0; j < 5; j++)
	{
		clients[j].color = Skin;
	}
	clients[0].SetPos(120.0f, 0.25f, 10.0f);
	clients[1].SetPos(210.f, 0.25f, 170.0f);
	clients[2].SetPos(110.0f, 0.25f, 170.0f);
	clients[3].SetPos(10.0f, 0.25f, 60.0f);
	clients[4].SetPos(240.0f, 0.25f, 240.0f);

	App->player->turning = 0;
	App->player->accelerating = 0;
	App->player->braking = 0;
}

