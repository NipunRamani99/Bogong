#include "Gerstener.hpp"
namespace bogong
{
	namespace cuda {
		GerstnerWave::GerstnerWave(int mesh_width,int mesh_height)
		{
			gerstener_mesh = std::make_shared<GerstnerWaveMesh>(mesh_width,mesh_height);
			renderer = std::make_shared<CudaRenderer>();
			renderer->BindBuffer(gerstener_mesh);
			renderer->SetDrawMode(GL_POINTS);

			
		}
		void GerstnerWave::Draw()
		{
			renderer->RenderMesh(gerstener_mesh);
		}
		void GerstnerWave::Update(float deltime)
		{
			gerstener_mesh->Update(deltime);
		}
		void GerstnerWave::SetShader(Shader p_Shader)
		{
			renderer->SetShader(p_Shader);
		}

		GerstnerWaveMesh::GerstnerWaveMesh(int width, int height)
		{
			mesh_prop.mesh_height = height;
			mesh_prop.mesh_width = width;
			cvbo_vertex = std::make_shared<CudaVBO<float3>>(width*height * sizeof(float3));
			cvbo_colours = std::make_shared<CudaVBO<float4>>(width*height * sizeof(float4));
			VertexBufferLayout vbl_pos;
			VertexBufferLayout vbl_colours;
			vbl_pos.AddElement<float>(3);
			vbl_colours.AddElement<float>(4);
			Buffer pos_buff;
			pos_buff.first = cvbo_vertex;
			pos_buff.second = vbl_pos;
			Buffer pos_colours;
			pos_colours.first = cvbo_colours;
			pos_colours.second = vbl_colours;
			m_BufferVertex.push_back(pos_buff);
			m_BufferVertex.push_back(pos_colours);
			count = mesh_prop.mesh_height * mesh_prop.mesh_width;
			props.resize(4);
			props[0].amplitude = 0.001f;
			props[1].amplitude = 0.004f;
			props[2].amplitude = 0.004f;
			props[3].amplitude = 0.002f;
			props[0].isCircular = 0;
			props[1].isCircular = 0xFF;
			props[2].isCircular = 0xFF;
			props[3].isCircular = 0;
			props[0].dirx = 1.0f / sqrtf(2);
			props[0].diry = 1.0f / sqrtf(2);
			props[1].x = 0.5f;
			props[1].y = 0.1f;
			props[2].x = 0.1f;
			props[2].y = 0.3f;
			props[3].dirx = 0.0f;
			props[3].diry = 1.0f;
			props[0].w = props[1].w = props[2].w = props[3].w = 1.0f;
			props[3].q = 1.0f;
			n = 4;
			counter = 0.0f;
		}

		void GerstnerWaveMesh::Update(float deltime)
		{
			counter += deltime;
			cvbo_vertex->Map();
			cvbo_vertex->GetMappedPointer();
			float3 * data = cvbo_vertex->GetData();
			GerstnerTest2(data, props.data(), mesh_prop, props.size(), counter);
			cvbo_vertex->UnMap();
			cvbo_colours->Map();
			cvbo_colours->GetMappedPointer();
			float4 * colour_data = cvbo_colours->GetData();
			UpdateColors2(colour_data, mesh_prop.mesh_width, mesh_prop.mesh_height, counter);
			cvbo_colours->UnMap();
		}
	}
}