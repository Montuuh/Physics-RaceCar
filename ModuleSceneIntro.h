#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

struct PhysBody3D;
struct PhysMotor3D;

#define TRACK_WIDTH 20.0f

struct Cubes
{
	p2DynArray<PhysBody3D*>		physic_bodies;
	p2DynArray<Cube>			primitive_bodies;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateLine(const vec3 iniPos, const vec3 finalPos, uint numCubes, bool isDouble);
	void CreateClients();
	void Restart();

	void ChangeGoal(int num);

public:

	Cubes cube_pieces;
	Cylinder goalPoint;
	vec3 goalPos;
	Line arrowPoint;
	
	p2DynArray<Cube> clients;
	int clientsDone;

	uint winFx;
	uint looseFx;
	uint clientPickedFx;
	uint clientDestinationFx;

	Timer game_timer;
};
