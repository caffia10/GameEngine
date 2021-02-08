#include "Mesh.h"

inline void SetTriangleData(std::vector<Vertex>& vertices, std::vector<u32>& indices)
{
	vertices.clear();
	indices.clear();

	vertices = {
		{ { 0.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },
	};

	indices = { 0, 1, 2, };
}

inline void SetQuadData(std::vector<Vertex>& vertices, std::vector<u32>& indices)
{
	vertices.clear();
	indices.clear();

	vertices = {

		{ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },
		{ { 1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }
	};

	indices = {

		0, 1, 2,
		0, 2, 3
	};
}

inline void SetCubeData(std::vector<Vertex>& vertices, std::vector<u32>& indices)
{
	vertices.clear();
	indices.clear();

	vertices = {

		//front
		{ { -1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } },
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },
		{ { 1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } },

		// back 
		{ { 1.0, -1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 1.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //4
		{ { 1.0f, 1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 0.0f, 1.0f, 1.0 },{ 0.0, 0.0 } }, //5
		{ { -1.0, 1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 0.0f, 1.0f, 1.0 },{ 1.0, 0.0 } }, //6
		{ { -1.0, -1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //7

		//left
		{ { -1.0, -1.0, -1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //8
		{ { -1.0f, 1.0, -1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //9
		{ { -1.0, 1.0, 1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },   //10
		{ { -1.0, -1.0, 1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //11

		//right
		{ { 1.0, -1.0, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, // 12
		{ { 1.0f, 1.0, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //13
		{ { 1.0, 1.0, -1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } }, //14
		{ { 1.0, -1.0, -1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //15

		//top
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //16
		{ { -1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //17
		{ { 1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } }, //18
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //19

		//bottom 
		{ { -1.0f, -1.0, -1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //20
		{ { -1.0, -1.0, 1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //21
		{ { 1.0, -1.0, 1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },  //22
		{ { 1.0, -1.0, -1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //23

	};

	indices = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23

	};
}

void CreateSphereMesh(Mesh* mesh)
{
	mesh->position = Vector3(0.0f);
	mesh->scale = Vector3(1.0f);

	u32 const latitudeBands = 20;
	u32 const longitudeBands = 20;

	{
		mesh->vertexCount = 441;
		u32 const size = mesh->vertexCount * sizeof(Vertex);
		mesh->vertices = (Vertex*) malloc(size);
		f32 const radius = 1.0f;

		u32 index = 0;

		for (f32 latNumber = 0; latNumber <= latitudeBands; latNumber++) {

			f32 const theta = latNumber * 3.14f / latitudeBands;
			f32 const sinTheta = sinf(theta);
			f32 const cosTheta = cosf(theta);

			for (f32 longNumber = 0; longNumber <= longitudeBands; longNumber++) {

				f32 const phi = longNumber * 2.0f * 3.147f / longitudeBands;
				f32 const sinPhi = sinf(phi);
				f32 const cosPhi = cosf(phi);

				Vertex vs;

				vs.texCoords.x = (longNumber / longitudeBands); // u
				vs.texCoords.y = (latNumber / latitudeBands);   // v

				vs.normal.x = cosPhi * sinTheta;   // normal x
				vs.normal.y = cosTheta;            // normal y
				vs.normal.z = sinPhi * sinTheta;   // normal z

				vs.color.r = vs.normal.x;
				vs.color.g = vs.normal.y;
				vs.color.b = vs.normal.z;

				vs.position.x = radius * vs.normal.x; // x
				vs.position.y = radius * vs.normal.y; // y
				vs.position.z = radius * vs.normal.z; // z

				//vertices.push_back(vs);
				mesh->vertices[index] = vs;
				index++;
			}
		}
	}

	{
		
		mesh->indexCount = 2400;
		u32 const size = mesh->indexCount * sizeof(GLuint);
		mesh->indices = (GLuint*) malloc(size);

		u32 index = 0;
		for (u32 latNumber = 0; latNumber < latitudeBands; latNumber++)
		{
			for (u32 longNumber = 0; longNumber < longitudeBands; longNumber++) {

				const u32 first = (latNumber * (longitudeBands + 1)) + longNumber;
				const u32 second = first + longitudeBands + 1;

				mesh->indices[index] = first;
				index++;

				mesh->indices[index] = second;
				index++;

				mesh->indices[index] = first + 1;
				index++;

				mesh->indices[index] = second;
				index++;

				mesh->indices[index] = second + 1;
				index++;

				mesh->indices[index] = first + 1;
				index++;
			}
		}
	}

}