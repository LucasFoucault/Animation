#ifndef _SceneGraph_Scale_H
#define _SceneGraph_Scale_H

#include <SceneGraph/Transform.h>

namespace SceneGraph
{
	class Scale : public Transform
	{
	protected:
		Math::Vector3f m_scale ;

	public:
		Scale(const Math::Vector3f & scale)
			: m_scale(scale)
		{}

		const Math::Vector3f & getScale() const
		{
			return m_scale ;
		}

		void setScale(const Math::Vector3f & scale)
		{
			m_scale = scale ;
		}

		virtual void draw()
		{
			storeMatrix() ;
			glScalef(m_scale[0], m_scale[1], m_scale[2]) ;
			Group::draw() ;
			restoreMatrix();
		}
	};
}

#endif