#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Object : public Model
{
	VertexArray  m_VAO;
	VertexBuffer m_VBO;
	IndexBuffer  m_IBO;
	Texture      m_Tex;
	
public:

	Object() = default;
	Object(std::string p_Path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(p_Path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);
		if (!scene)
		{
			std::cout<<(importer.GetErrorString());
			
		}
		
	}
};