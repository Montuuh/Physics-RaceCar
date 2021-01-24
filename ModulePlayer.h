#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_BRAKE 300.0f
#define MAX_ACCELERATION 650.0f
#define MAX_TURN 16.0f * DEGTORAD

enum class state
{
	EMPTY,
	CARRYING
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turning;
	float accelerating;
	float braking;
	vec3 pos;
	vec3 startPosition;
	float startMatrix[16];
	float checkpointMatrix[16];
	state player_state;

	//Client being carried
	int client;
};