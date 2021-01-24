#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "ModulePlayer.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = LightMaroon;

	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube carShape(info.carShape_size.x, info.carShape_size.y, info.carShape_size.z);

	carShape.color = info.color;

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&carShape.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.carShape_offset.x, info.carShape_offset.y, info.carShape_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	carShape.transform.M[12] += offset.getX();
	carShape.transform.M[13] += offset.getY();
	carShape.transform.M[14] += offset.getZ();

	Cube driver(0.5f, 1.0f, 0.5f);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&driver.transform);
	btVector3 d_offset(info.carShape_offset.x + 0.5f, info.carShape_offset.y + 0.5f, info.carShape_offset.z);
	d_offset = d_offset.rotate(q.getAxis(), q.getAngle());
	driver.transform.M[12] += d_offset.getX();
	driver.transform.M[13] += d_offset.getY();
	driver.transform.M[14] += d_offset.getZ();
	driver.color = Skin;

	carShape.Render();
	driver.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for (int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if (info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}

void PhysVehicle3D::Rotate(float angle)
{
	// Counter clock-wise rotation around the y axis

	float mat[16];
	memset(mat, 0.0f, sizeof(mat));

	// Position
	vec3 p = GetPos();
	mat[12] = p.x;
	mat[13] = p.y;
	mat[14] = p.z;
	mat[15] = 1;

	// Rotation
	mat[0] = cos(angle);
	mat[2] = -sin(angle);
	mat[5] = 1;
	mat[8] = sin(angle);
	mat[10] = cos(angle);

	SetTransform(mat);

}