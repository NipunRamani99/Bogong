#pragma once
#include "../VertexArray.hpp"
#include "Mesh.hpp"
namespace bogong {
	class ShapeMesh : public Mesh
	{
	public:
		ShapeMesh() = default;
		ShapeMesh(std::vector<Vertex<float>> & p_Vertices)
		{
		
		}
		ShapeMesh(std::vector<Vertex<float>> & p_Vertices, std::vector<unsigned int> & p_Indices)
		{
			
		}

	};
}
