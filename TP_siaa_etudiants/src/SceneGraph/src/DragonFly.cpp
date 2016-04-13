#include <SceneGraph/DragonFly.h>

SceneGraph::DragonFly::DragonFly():
	SceneGraph::Group(),

	// Transformations
		// Rotations
		m_leftArticulation 			(new SceneGraph::Rotate(0.0f,Math::makeVector(1.0f,0.0f,0.0f))),
		m_rightArticulation 		(new SceneGraph::Rotate(0.0f, Math::makeVector(1.0f,0.0f,0.0f))),
		
		m_leftUpWingRotation 		(new SceneGraph::Rotate(0.0f, Math::makeVector(0.0f,0.0f,1.0f))),
		m_rightUpWingRotation 		(new SceneGraph::Rotate(180.0f*Math::pi/180.0f, Math::makeVector(0.0f,0.0f,1.0f))),
		m_leftDownWingRotation		(new SceneGraph::Rotate(-5.0f*Math::pi/180.0f, Math::makeVector(0.0f,0.0f,1.0f))),
		m_rightDownWingRotation		(new SceneGraph::Rotate(185.0f*Math::pi/180.0f, Math::makeVector(0.0f,0.0f,1.0f))),

		// Translations	
		m_headTranslation			(new SceneGraph::Translate(Math::makeVector(0.7f,0.0f,0.0f))),
		m_tailTranslation			(new SceneGraph::Translate(Math::makeVector(-0.8f,0.0f,0.0f))),
		
		m_leftUpWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.0f,-0.6f,0.0f))),
		m_rightUpWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.0f,-0.6f,0.0f))),
		m_leftDownWingTranslation 	(new SceneGraph::Translate(Math::makeVector(-0.5f,-0.6f,0.0f))),
		m_rightDownWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.5f,-0.6f,0.0f))),

		m_leftEyeTranslation 		(new SceneGraph::Translate(Math::makeVector(0.05f,0.07f,0.05f))),
		m_rightEyeTranslation		(new SceneGraph::Translate(Math::makeVector(0.05f,-0.07f,0.05f))),
		m_pupilsTranslation 		(new SceneGraph::Translate(Math::makeVector(0.0f,0.0f,0.04f))),
		
		// Scales
		m_scaleBody 				(new SceneGraph::Scale(Math::makeVector(0.7f,0.2f,0.2f))),
		m_scaleHead					(new SceneGraph::Scale(Math::makeVector(2.0f,0.9f,0.9f))),
		m_scaleTail					(new SceneGraph::Scale(Math::makeVector(1.5f,0.1f,0.1f))),
		m_scaleWings 				(new SceneGraph::Scale(Math::makeVector(0.3f,0.6f,0.05f))),
	
	// Animation
	m_wingsSpeed(100000.0f)

{
	//Geometries
		// Body
		HelperGl::Color bodyDiffuseColor(0.07f,0.5f,0.07f);
		HelperGl::Material bodyMaterial;
		bodyMaterial.setDiffuse(bodyDiffuseColor);
		m_body 					= new SceneGraph::Sphere(bodyMaterial);

		// Head
		HelperGl::Color headDiffuseColor(0.07f,0.5f,0.07f);
		HelperGl::Material headMaterial;
		headMaterial.setDiffuse(headDiffuseColor);
		m_head					= new SceneGraph::Sphere(headMaterial,0.1f);

		// Tail
		HelperGl::Color tailDiffuseColor(0.07f,0.5f,0.07f);
		HelperGl::Material tailMaterial;
		tailMaterial.setDiffuse(tailDiffuseColor);
		m_tail					= new SceneGraph::Sphere(tailMaterial);

		// Wings
		HelperGl::Color wingsDiffuseColor(0.7f,0.7f,0.7f,0.0f);
		HelperGl::Material wingsMaterial;
		wingsMaterial.setDiffuse(wingsDiffuseColor);
		m_leftUpWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_rightUpWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_leftDownWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_rightDownWing 		= new SceneGraph::Sphere(wingsMaterial);

		// Eyes
		HelperGl::Color eyesDiffuseColor(0.2f,0.2f,0.0f);
		HelperGl::Material eyesMaterial;
		eyesMaterial.setDiffuse(eyesDiffuseColor);
		m_leftEye 				= new SceneGraph::Sphere(eyesMaterial,0.1f);
	 	m_rightEye 				= new SceneGraph::Sphere(eyesMaterial,0.1f);

		// Pupils
		HelperGl::Color pupilsDiffuseColor(0.0f,0.0f,0.0f);
		HelperGl::Material pupilsMaterial;
		pupilsMaterial.setDiffuse(pupilsDiffuseColor);
	 	m_leftPupil 			= new SceneGraph::Sphere(pupilsMaterial,0.02f);
		m_rightPupil 			= new SceneGraph::Sphere(pupilsMaterial,0.02f);

	buildSkeleton();
}

SceneGraph::DragonFly::~DragonFly()
{}

void SceneGraph::DragonFly::buildSkeleton()
{
	this->addSon(m_scaleBody);
		m_scaleBody->addSon(m_body);

	this->addSon(m_scaleTail);
		m_scaleTail->addSon(m_tailTranslation);
			m_tailTranslation->addSon(m_tail);

	this->addSon(m_headTranslation);
		m_headTranslation->addSon(m_scaleHead);
			m_scaleHead->addSon(m_head);
		m_headTranslation->addSon(m_leftEyeTranslation);
			m_leftEyeTranslation->addSon(m_leftEye);
			//m_leftEyeTranslation->addSon(m_pupilsTranslation);
				//m_pupilsTranslation->addSon(m_leftPupil);
		m_headTranslation->addSon(m_rightEyeTranslation);
			m_rightEyeTranslation->addSon(m_rightEye);
			//m_rightEyeTranslation->addSon(m_pupilsTranslation);
				//m_pupilsTranslation->addSon(m_rightPupil);
	
	this->addSon(m_leftArticulation);
		m_leftArticulation->addSon(m_leftUpWingRotation);
			m_leftUpWingRotation->addSon(m_leftUpWingTranslation);
				m_leftUpWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_leftUpWing);
		m_leftArticulation->addSon(m_leftDownWingRotation);
			m_leftDownWingRotation->addSon(m_leftDownWingTranslation);
				m_leftDownWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_leftDownWing); 
	this->addSon(m_rightArticulation);
		m_rightArticulation->addSon(m_rightUpWingRotation);
			m_rightUpWingRotation->addSon(m_rightUpWingTranslation);
				m_rightUpWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_rightUpWing);
		m_rightArticulation->addSon(m_rightDownWingRotation);
			m_rightDownWingRotation->addSon(m_rightDownWingTranslation);
				m_rightDownWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_rightDownWing);
}

void SceneGraph::DragonFly::animate(double t)
{
	float m_wingsAngle = WINGS_ANGLE_LIMIT*std::cos(m_wingsSpeed*t);
	m_leftArticulation->setAngle(m_wingsAngle*Math::pi/180.0f);
	m_rightArticulation->setAngle(-m_wingsAngle*Math::pi/180.0f);
}
