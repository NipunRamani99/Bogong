#include "Rendering/ShapeMesh.hpp"
#include "Rendering/Renderer.hpp"
namespace bogong {
	class Plane
	{
		std::shared_ptr<ShapeMesh> mesh;
		std::shared_ptr<Renderer> renderer;
		std::vector<Vertex<float>> vertices;
		VertexBufferLayout vbl;
	public:
		Plane()
		{
			Vertex<float> a;
			Vertex<float> b;
			Vertex<float> c;
			Vertex<float> d;
			a.x = 0.20f;
			a.z = 0.0f;
			a.y = 0.20f;
			a.r = 1.0f;
			a.a = 1.0f;
			
			b.y = -0.20f;
			b.x = 0.20f;
			b.z = 0.0f;
			b.r = 1.0f;
			b.a = 1.0f;
			
		    c.x = -0.20f;
			c.y = -0.20f;
			c.z = 0.0f;
			c.r = 1.0f;
			c.a = 1.0f;

			d.y = 0.20f;
			d.x = -0.20f;
			d.z = 0.0f;
			d.r = 1.0f;
			d.a = 1.0f;
			vertices.push_back(a);
			vertices.push_back(b);
			vertices.push_back(c);
			vertices.push_back(d);
			mesh = std::make_shared<ShapeMesh>(vertices);
			assert(!error());

			renderer = std::make_shared<Renderer>();
			assert(!error());

			vbl.AddElement<float>(3);
			vbl.AddElement<float>(4);
			renderer->SetDrawMode(GL_QUADS);
			assert(!error());

			renderer->SetLayout(vbl);
			assert(!error());

			renderer->BindBuffer(mesh);
			assert(!error());

		}
		void setShader(Shader shader)
		{
			renderer->SetShader(shader);
			assert(!error());

		}
		void Draw() const
		{
			assert(!error());
			renderer->RenderMesh(mesh);
			assert(!error());

		}
	};
}