#ifndef _SceneGraph_Cylinder_H
#define _SceneGraph_Cylinder_H

#include <GL/glew.h>
#include <HelperGl/Material.h>
#include <HelperGl/PhongShader.h>
#include <HelperGl/Draw.h>
#include <HelperGl/LightServer.h>
#include <SceneGraph/NodeInterface.h>

namespace SceneGraph
{
	class Cylinder : public NodeInterface
	{
	protected:
		HelperGl::Material m_material ;
		GLUquadric * m_quadric ;
		float m_baseRadius ;
		float m_topRadius ;
		float m_height ;
		int m_slices ;
		int m_stacks ; 

	public:
		Cylinder(const HelperGl::Material & material, float baseRadius=1.0, float topRadius=1.0, float height=1.0, int slices=20, int stacks=1);

		virtual void draw();

		virtual ~Cylinder();
	};
}

#endif