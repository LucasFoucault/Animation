#ifndef _SceneGraph_Translate_H
#define _SceneGraph_Translate_H

#include <SceneGraph/Transform.h>
#include <Math/Vectorf.h>

namespace SceneGraph
{
	class Translate : public Transform
	{
	protected:
		Math::Vector3f m_translation ;

	public:
		Translate(const Math::Vector3f & translation = Math::makeVector(0.0,0.0,0.0))
			: m_translation(translation)
		{}

		void setTranslation(const Math::Vector3f & translation)
		{
			m_translation = translation ;
		}

		const Math::Vector3f & getTranslation() const
		{
			return m_translation ;
		}

		virtual void draw()
		{
			storeMatrix() ;
			glTranslatef(m_translation[0], m_translation[1], m_translation[2]) ;
			Group::draw();
			restoreMatrix() ;			
		}
	};
}

#endif