#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube()
	{
		this->vertices =
		{
			{ Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(0,0,0), Vector3D(0,1,0) },
			{ Vector3D(-0.5f,  0.5f, -0.5f),    Vector3D(1,1,0), Vector3D(0,1,1) },
			{ Vector3D( 0.5f,  0.5f, -0.5f),    Vector3D(0,0,1), Vector3D(1,0,0) },
			{ Vector3D( 0.5f, -0.5f, -0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) },

			{ Vector3D( 0.5f, -0.5f,  0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) },
			{ Vector3D( 0.5f,  0.5f,  0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) },
			{ Vector3D(-0.5f,  0.5f,  0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) },
			{ Vector3D(-0.5f, -0.5f,  0.5f),    Vector3D(1,1,1), Vector3D(0,0,1) }
		};

		this->index_list =
		{
			0,1,2,
			2,3,0,

			4,5,6,
			6,7,4,

			1,6,5,
			5,2,1,

			7,0,3,
			3,4,7,

			3,2,5,
			5,4,3,

			7,6,1,
			1,0,7,
		};
	}

	~Cube() {}
};

