#pragma once
#include <vector>
#include "..\..\Math\Vector2.h"
#include "..\..\Math\Vector3.h"
#include "..\..\Math\Vector4.h"

namespace GatesEngine
{
	namespace MyDirectX
	{
		namespace VertexInfo
		{
			struct Vertex
			{
				GatesEngine::Math::Vector3 point;
			};

			struct Vertex_UV
			{
				GatesEngine::Math::Vector3 point;
				GatesEngine::Math::Vector2 uv;
			};

			struct Vertex_Normal
			{
				GatesEngine::Math::Vector3 point;
				GatesEngine::Math::Vector3 normal;
			};

			struct Vertex_UV_Normal
			{
				GatesEngine::Math::Vector3 point;
				GatesEngine::Math::Vector2 uv;
				GatesEngine::Math::Vector3 normal;
			};

			struct Vertex_UV_Normal_Color
			{
				GatesEngine::Math::Vector3 point;
				GatesEngine::Math::Vector2 uv;
				GatesEngine::Math::Vector3 normal;
				GatesEngine::Math::Vector4 color;
			};
		}
	}
}
