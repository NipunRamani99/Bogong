#pragma once
#include "../Rendering/CudaRenderer.hpp"
#include "../CudaVBO.h"

#include "RunKernels.h"
namespace bogong {
	namespace cuda {
		class GerstnerWaveMesh : public CudaMesh
		{
		private:
			std::vector<WaveProp> props;
			std::shared_ptr<CudaVBO<float3>> cvbo_vertex;
			std::shared_ptr<CudaVBO<float4>> cvbo_colours;
			float counter;
			MeshProp mesh_prop;
			int n = 0;
		public:
			GerstnerWaveMesh(int width,int height);
			void InputProp(int i);
			void Input();
			void Update(float delTime);
		};
		class GerstnerWave
		{
		private:
			std::shared_ptr<GerstnerWaveMesh> gerstener_mesh;
			std::shared_ptr<CudaRenderer> renderer;
		public:
			GerstnerWave(int mesh_width, int mesh_height);
			void Update(float deltime);
			void Draw();
			void SetShader(Shader p_Shader);
		};
	}
}