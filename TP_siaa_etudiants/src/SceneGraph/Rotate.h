#ifndef _SceneGraph_Rotate_H
#define _SceneGraph_Rotate_H

#include <SceneGraph/Transform.h>
#include <Math/Vectorf.h>

namespace SceneGraph
{
	class Rotate : public Transform
	{
	protected:
		GLfloat m_angle;
		Math::Vector3f m_axis;

	public:
		Rotate(GLfloat angle, const Math::Vector3f & axis)
			: m_angle(angle), m_axis(axis)
		{}

		void setAngle(GLfloat angle)
		{
			m_angle = angle;
		}

		GLfloat getAngle() const
		{
			return m_angle;
		}

		void setAxis(const Math::Vector3f & axis)
		{
			m_axis = axis;
		}

		virtual void draw() 
		{
			storeMatrix();
			glRotatef((float)(m_angle*180.0/Math::pi), m_axis[0], m_axis[1], m_axis[2]);
			Group::draw();
			restoreMatrix();
		}
	};
}

#endif