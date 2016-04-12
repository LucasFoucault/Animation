#include <SceneGraph/DragonFly.h>

SceneGraph::DragonFly::DragonFly():
	SceneGraph::Group(),

	// Transformations
		// Rotations
		m_leftArticulation 			(new SceneGraph::Rotate(0.0f,Math::makeVector(1.0f,0.0f,0.0f))),
		m_rightArticulation 		(new SceneGraph::Rotate(0.0f, Math::makeVector(1.0f,0.0f,0.0f))),
		m_leftWingsRotation 		(new SceneGraph::Rotate(0.0f, Math::makeVector(0.0f,0.0f,0.0f))),
		m_rightWingsRotation 		(new SceneGraph::Rotate(180.0f*Math::pi/180.0f, Math::makeVector(0.0f,0.0f,1.0f))),

		// Translations	
		m_tailTranslation			(new SceneGraph::Translate(Math::makeVector(-0.7f,0.0f,0.0f))),
		m_leftUpWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.0f,-0.6f,0.0f))),
		m_rightUpWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.0f,-0.6f,0.0f))),
		m_leftDownWingTranslation 	(new SceneGraph::Translate(Math::makeVector(-0.7f,-0.6f,0.0f))),
		m_rightDownWingTranslation 	(new SceneGraph::Translate(Math::makeVector(0.7f,-0.6f,0.0f))),

		m_leftEyeTranslation 		(new SceneGraph::Translate(Math::makeVector(0.7f,0.2f,0.2f))),
		m_rightEyeTranslation		(new SceneGraph::Translate(Math::makeVector(0.7f,-0.2f,0.2f))),
		m_pupilsTranslation 		(new SceneGraph::Translate(Math::makeVector(0.0f,0.0f,0.04f))),
		
		// Scales
		m_scaleBody 				(new SceneGraph::Scale(Math::makeVector(1.0f,0.3f,0.3f))),
		m_scaleTail					(new SceneGraph::Scale(Math::makeVector(3.0f, 0.1f, 0.1f))),
		m_scaleWings 				(new SceneGraph::Scale(Math::makeVector(0.3f,0.6f,0.05f))),
	
	// Animation
	m_wingsSpeed(100000.0f)

{
	//Geometries
		// Body
		HelperGl::Color bodyDiffuseColor(1.0f,1.0f,0.0f);
		HelperGl::Material bodyMaterial;
		bodyMaterial.setDiffuse(bodyDiffuseColor);
		m_body 					= new SceneGraph::Sphere(bodyMaterial);

		// Tail
		HelperGl::Color tailDiffuseColor(1.0f,1.0f,0.0f);
		HelperGl::Material tailMaterial;
		tailMaterial.setDiffuse(tailDiffuseColor);
		m_tail					= new SceneGraph::Sphere(tailMaterial);

		// Wings
		HelperGl::Color wingsDiffuseColor(1.0,1.0,1.0,0.0);
		HelperGl::Material wingsMaterial;
		wingsMaterial.setDiffuse(wingsDiffuseColor);
		m_leftUpWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_rightUpWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_leftDownWing 			= new SceneGraph::Sphere(wingsMaterial);
		m_rightDownWing 		= new SceneGraph::Sphere(wingsMaterial);

		// Eyes
		HelperGl::Color eyesDiffuseColor(1.0,1.0,1.0);
		HelperGl::Material eyesMaterial;
		eyesMaterial.setDiffuse(eyesDiffuseColor);
		m_leftEye 				= new SceneGraph::Sphere(eyesMaterial,0.05f);
	 	m_rightEye 				= new SceneGraph::Sphere(eyesMaterial,0.05f);

		// Pupils
		HelperGl::Color pupilsDiffuseColor(0.0,0.0,0.0);
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

	this->addSon(m_leftArticulation);
		m_leftArticulation->addSon(m_leftWingsRotation);
			m_leftWingsRotation->addSon(m_leftUpWingTranslation);
				m_leftUpWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_leftUpWing); 
			m_leftWingsRotation->addSon(m_leftDownWingTranslation);
				m_leftDownWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_leftDownWing); 
	this->addSon(m_rightArticulation);
		m_rightArticulation->addSon(m_rightWingsRotation);
			m_rightWingsRotation->addSon(m_rightUpWingTranslation);
				m_rightUpWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_rightUpWing);
			m_rightWingsRotation->addSon(m_rightDownWingTranslation);
				m_rightDownWingTranslation->addSon(m_scaleWings);
					m_scaleWings->addSon(m_rightDownWing);

	this->addSon(m_leftEyeTranslation);
		m_leftEyeTranslation->addSon(m_leftEye);
		m_leftEyeTranslation->addSon(m_pupilsTranslation);
			m_pupilsTranslation->addSon(m_leftPupil);
	this->addSon(m_rightEyeTranslation);
		m_rightEyeTranslation->addSon(m_rightEye);
		m_rightEyeTranslation->addSon(m_pupilsTranslation);
			m_pupilsTranslation->addSon(m_rightPupil);	
}

void SceneGraph::DragonFly::animate(double t)
{
	float m_wingsAngle = WINGS_ANGLE_LIMIT*std::cos(m_wingsSpeed*t);
	m_leftArticulation->setAngle(m_wingsAngle*Math::pi/180.0f);
	m_rightArticulation->setAngle(-m_wingsAngle*Math::pi/180.0f);
}
