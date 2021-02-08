#pragma once
#include <vector>
#include "..\..\Math\Vector2.h"
#include "..\..\Math\Vector3.h"
#include "..\..\Math\Vector4.h"

namespace GatesEngine
{
	namespace DirectX
	{
		//シェーダーに送るための頂点情報構造体
		template<typename T>
		class VertexData
		{
		private:
			unsigned int vertexDataSize;
			std::vector<T> vertices;
			std::vector<unsigned int> indices;
		public:
			VertexData();
			unsigned int GetVertexDataSize() { return vertexDataSize; }
			std::vector<T>* GetVertices() { return &vertices; }
			std::vector<unsigned int>* GetIndices() { return &indices; }
			void Clear()
			{
				vertices.clear();
				indices.clear();
			}

		};
		template<typename T>
		inline VertexData<T>::VertexData():vertexDataSize(sizeof(T))
		{
		}

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
