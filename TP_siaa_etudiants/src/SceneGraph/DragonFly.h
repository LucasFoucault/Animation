#ifndef _SceneGraph_DragonFly_H
#define _SceneGraph_DragonFly_H

#include <GL/glew.h>

#include <HelperGl/Material.h>
#include <HelperGl/Color.h>

#include <Application/BaseWithKeyboard.h>

#include <SceneGraph/Group.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Rotate.h>
#include <SceneGraph/Translate.h>
#include <SceneGraph/Scale.h>

#define WINGS_ANGLE_LIMIT 30

namespace SceneGraph
{
	class DragonFly : public Group
	{
	private:
		//Geometries
			// Body
			SceneGraph::Sphere * m_body;
			SceneGraph::Sphere * m_tail;

			// Chicken Wings
			SceneGraph::Sphere * m_leftUpWing;
			SceneGraph::Sphere * m_rightUpWing;
			SceneGraph::Sphere * m_leftDownWing;
			SceneGraph::Sphere * m_rightDownWing;

			// Eyes
			SceneGraph::Sphere * m_leftEye;
			SceneGraph::Sphere * m_rightEye;

			// Pupils
			SceneGraph::Sphere * m_leftPupil;
			SceneGraph::Sphere * m_rightPupil;

		// Transformations
			// Rotations
			SceneGraph::Rotate * m_leftArticulation;
			SceneGraph::Rotate * m_rightArticulation;
			SceneGraph::Rotate * m_leftWingsRotation;
			SceneGraph::Rotate * m_rightWingsRotation;

			// Translations
			SceneGraph::Translate * m_tailTranslation;

			SceneGraph::Translate * m_leftUpWingTranslation;
			SceneGraph::Translate * m_rightUpWingTranslation;
			SceneGraph::Translate * m_leftDownWingTranslation;
			SceneGraph::Translate * m_rightDownWingTranslation;

			SceneGraph::Translate * m_leftEyeTranslation;
			SceneGraph::Translate * m_rightEyeTranslation;

			SceneGraph::Translate * m_pupilsTranslation;

			// Scales
			SceneGraph::Scale * m_scaleBody;
			SceneGraph::Scale * m_scaleTail;
			SceneGraph::Scale * m_scaleWings;

		// Animation
		float m_wingsSpeed;

	public:
		DragonFly();

		virtual ~DragonFly();

		void animate(double dt);

	private:
		void buildSkeleton();
	};
}

#endif 