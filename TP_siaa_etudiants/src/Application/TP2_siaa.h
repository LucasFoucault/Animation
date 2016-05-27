#ifndef _Application_TP2_siaa_H
#define _Application_TP2_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <HelperGl/Material.h>
#include <HelperGl/Color.h>

#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>

#include <Animation/KinematicChain.h>
#include <Animation/CyclicCoordinateDescent.h>

#include <SceneGraph/Group.h>
#include <SceneGraph/Transform.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Cylinder.h>
#include <SceneGraph/Rotate.h>
#include <SceneGraph/Translate.h>

#include <GL/compatibility.h>

#define PI 3.14159265
#define CYLINDER_RADIUS 0.1f
#define CYLINDER_HEIGHT 0.5f
#define SPHERE_RADIUS	0.2f

typedef Animation::KinematicChain::StaticNode StaticNode;
typedef Animation::KinematicChain::DynamicNode DynamicNode;
typedef Animation::KinematicChain KinematicChain;

namespace Application
{
	class TP2_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;
		SceneGraph::Group m_root;
		Animation::KinematicChain m_kinematicChain;
		Animation::Journey * TheJourney;
		Animation::CyclicCoordinateDescent * CCD;
		KinematicChain::Node * m_lastKinematicNode;

		std::vector<std::pair<SceneGraph::Rotate *, Animation::KinematicChain::Node *> > m_mapDoF;

		SceneGraph::Sphere * m_target;
		SceneGraph::Translate * m_targetTranslation;

		double t;
		float u;

		virtual void handleKeys()
		{
			// The camera translation speed
			float cameraSpeed = 5.0f;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi / 2.0);

			// quit
			if (m_keyboard.isPressed('q')) { quit(); }
			// Go front
			if (m_keyboard.isPressed('+')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, -cameraSpeed*(float)getDt())); }
			// Go back
			if (m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, (float)cameraSpeed*(float)getDt())); }
			// Go left
			if (m_keyboard.isPressed('1')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed*(float)getDt(), 0.0f, 0.0f)); }
			// Go right
			if (m_keyboard.isPressed('3')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(), 0.0f, 0.0f)); }
			// Go down
			if (m_keyboard.isPressed('2')) { m_camera.translateLocal(Math::makeVector(0.0f, -cameraSpeed*(float)getDt(), 0.0f)); }
			// Go up
			if (m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f, (float)cameraSpeed*(float)getDt(), 0.0f)); }
			// Rotation left
			if (m_keyboard.isPressed('4')) { m_camera.rotateLocal(Math::makeVector(0.0f, 1.0f, 0.0f), -1.0f*Math::pi / 180.0f); }
			// Rotation right
			if (m_keyboard.isPressed('6')) { m_camera.rotateLocal(Math::makeVector(0.0f, 1.0f, 0.0f), 1.0f*Math::pi / 180.0f); }
			if (m_keyboard.isPressed(32)){
				Math::Vector3f target = Math::makeVector((float)(std::rand() % 20 - 10), (float)(std::rand() % 20 - 10), (float)(std::rand() % 20 - 10));
				m_targetTranslation->setTranslation(target);
			}
		}

	public:
		TP2_siaa() :
			t(0),
			u(0.0f)
		{
			m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, 10.0f));
		}

		virtual void initializeRendering()
		{
			// Light
			HelperGl::Color lightColor(1.0,1.0,1.0);
			HelperGl::Color lightAmbiant(0.0,0.0,0.0,0.0);
			Math::Vector4f lightPosition = Math::makeVector(0.0f,0.0f,10000.0f,1.0f); // Point light centered in 0,0,0
			HelperGl::LightServer::Light * light = HelperGl::LightServer::getSingleton()->createLight(lightPosition.popBack(), lightColor, lightColor, lightColor);
			light->enable();	

			// Target
			HelperGl::Color targetColor(1.0, 0.0, 0.0);
			HelperGl::Material targetMaterial;
			targetMaterial.setDiffuse(targetColor);
			m_target = new SceneGraph::Sphere(targetMaterial, SPHERE_RADIUS);
			m_targetTranslation = new SceneGraph::Translate(Math::makeVector(4.0f, 4.0f, 0.0f));

			m_root.addSon(m_targetTranslation);
			m_targetTranslation->addSon(m_target);



			int chainSize = 12;
			//std::cout << "Enter the size of the chain: " << std::endl;
			//std::cin >> chainSize;

			// SceneGraph
			m_root.addSon(buildChain(chainSize));
			//m_lastKinematicNode = polyArticulatedChain(&m_root,m_kinematicChain.getRoot(),chainSize);

			// Interpolation
			//vector<Math::Vector3f> *v = new vector<Math::Vector3f>();
			//v->push_back(Math::makeVector(lastKinematicNode->getGlobalTransformation()(0, 3), lastKinematicNode->getGlobalTransformation()(1, 3), lastKinematicNode->getGlobalTransformation()(2, 3)));
			//v->push_back(Math::makeVector(0, 1, 0));
			//v->push_back(Math::makeVector(10, 10, 3));
			//v->push_back(Math::makeVector(0, 1, 0));
			//TheJourney = new Animation::Journey(v);

			CCD = new Animation::CyclicCoordinateDescent(&m_kinematicChain,m_lastKinematicNode);
		}

		SceneGraph::Group * buildChain(int chainSize)
		{
			SceneGraph::Group * root = new SceneGraph::Group();

			HelperGl::Color chainDiffuseColor(0.0f,0.0f,1.0f);
			HelperGl::Material chainMaterial;
			chainMaterial.setDiffuse(chainDiffuseColor);

			HelperGl::Color articulationDiffuseColor(0.7f,0.7f,0.0f);
			HelperGl::Material articulationMaterial;
			articulationMaterial.setDiffuse(articulationDiffuseColor);



			SceneGraph::Translate * firstTranslate = new SceneGraph::Translate(Math::makeVector(0.0f,0.0f,0.0f));
			SceneGraph::Rotate * firstRotate = new SceneGraph::Rotate(90.0f*Math::pi/180.0f, Math::makeVector(0,1,0));
			SceneGraph::Cylinder * firstCylinder = new SceneGraph::Cylinder(chainMaterial, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT);
						
			root->addSon(firstTranslate);
				firstTranslate->addSon(firstRotate);
					firstRotate->addSon(firstCylinder);
			SceneGraph::Transform * lastNode = firstTranslate;


			m_lastKinematicNode = m_kinematicChain.addStaticTranslation(m_kinematicChain.getRoot(),firstTranslate->getTranslation());


			for(int i=0; i<chainSize-1; i++)
			{
				SceneGraph::Translate * t1 = new SceneGraph::Translate(Math::makeVector(CYLINDER_HEIGHT + SPHERE_RADIUS/2,0.0f,0.0f)); // 2 + SPHERE_RADIUS/2 - 0.04f
				SceneGraph::Rotate * firstLibertyDegree  = new SceneGraph::Rotate(0,Math::makeVector(1,0,0));
				SceneGraph::Rotate * secondLibertyDegree = new SceneGraph::Rotate(0,Math::makeVector(0,0,1));

				SceneGraph::Translate * t2 = new SceneGraph::Translate(Math::makeVector(SPHERE_RADIUS/2,0.0f,0.0f));
				SceneGraph::Rotate * r2 = new SceneGraph::Rotate(90.0f*Math::pi/180.0f, Math::makeVector(0,1,0));

				lastNode->addSon(t1);
					t1->addSon(firstLibertyDegree);
						firstLibertyDegree->addSon(secondLibertyDegree);
							secondLibertyDegree->addSon(new SceneGraph::Sphere(articulationMaterial, SPHERE_RADIUS));				
								secondLibertyDegree->addSon(t2);
									t2->addSon(r2);
										r2->addSon(new SceneGraph::Cylinder(chainMaterial,CYLINDER_RADIUS,CYLINDER_RADIUS,CYLINDER_HEIGHT));
				lastNode = t2;



				DynamicNode * dn1 = m_kinematicChain.addDynamicRotation(m_lastKinematicNode, Math::makeVector(1, 0, 0), Math::makeInterval((float)-Math::pi / 2, (float)Math::pi / 2), 0.0f);
				DynamicNode * dn2 = m_kinematicChain.addDynamicRotation(dn1, Math::makeVector(0, 0, 1), Math::makeInterval((float)-Math::pi / 2, (float)Math::pi / 2), 0.0f);
				StaticNode  * st1 = m_kinematicChain.addStaticTranslation(dn2, Math::makeVector(CYLINDER_HEIGHT + SPHERE_RADIUS,0.0f,0.0f));
				m_lastKinematicNode = st1;

				m_mapDoF.push_back(pair<SceneGraph::Rotate *, Animation::KinematicChain::Node *>(firstLibertyDegree, dn1));
				m_mapDoF.push_back(pair<SceneGraph::Rotate *, Animation::KinematicChain::Node *>(secondLibertyDegree, dn2));
			}

			return root;
		}


		Animation::KinematicChain::Node * polyArticulatedChain(SceneGraph::Group * rootGraph, Animation::KinematicChain::Node * rootChain, int segments)
		{
			// End condition for recursive function
			if (segments == 0)
				return rootChain;


			// Init materials
			HelperGl::Material matArticulation;
			matArticulation.setDiffuse(HelperGl::Color(0.0f, 0.8f, 0.0f));

			HelperGl::Material matBone;
			matBone.setDiffuse(HelperGl::Color(0.0f, 0.0f, 0.7f));


			// Init poly-articulated chain in scene graph
			SceneGraph::Sphere * articulation = new SceneGraph::Sphere(matArticulation, 0.2);

			SceneGraph::Cylinder * bone = new SceneGraph::Cylinder(matBone, 0.1, 0.1, 0.5);

			SceneGraph::Rotate * articulationRotationX = new SceneGraph::Rotate(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f));
			SceneGraph::Rotate * articulationRotationZ = new SceneGraph::Rotate(0.0f, Math::makeVector(0.0f, 0.0f, 1.0f));

			SceneGraph::Translate * boneTranslation = new SceneGraph::Translate(Math::makeVector(0.20f, 0.0f, 0.0f));
			SceneGraph::Rotate * boneRotation = new SceneGraph::Rotate(Math::piDiv2, Math::makeVector(0.0f, 1.0f, 0.0f));

			SceneGraph::Translate * rootTranslation = new SceneGraph::Translate(Math::makeVector(0.70f, 0.0f, 0.0f));


			// Init poly-articulated chain in kinematic chain
			Animation::KinematicChain *kineChain = new Animation::KinematicChain();
			Animation::KinematicChain::DynamicNode *nodeArticulationX = kineChain->addDynamicRotation(rootChain, Math::makeVector(1.0f, 0.0f, 0.0f), Math::makeInterval((float)-Math::piDiv2, (float)Math::piDiv2), 0.0f);
			Animation::KinematicChain::DynamicNode *nodeArticulationZ = kineChain->addDynamicRotation(nodeArticulationX, Math::makeVector(0.0f, 0.0f, 1.0f), Math::makeInterval((float)-Math::piDiv2, (float)Math::piDiv2), 0.0f);
			Animation::KinematicChain::StaticNode *nodeBone = kineChain->addStaticTranslation(nodeArticulationZ, Math::makeVector(0.90f, 0.0f, 0.0f));

			m_mapDoF.push_back(std::pair<SceneGraph::Rotate*, Animation::KinematicChain::Node*>(articulationRotationX, nodeArticulationX));
			m_mapDoF.push_back(std::pair<SceneGraph::Rotate*, Animation::KinematicChain::Node*>(articulationRotationZ, nodeArticulationZ));


			// Init Scene Graph
			rootGraph->addSon(articulationRotationX);
			articulationRotationX->addSon(articulationRotationZ);
			articulationRotationZ->addSon(articulation);
			articulationRotationZ->addSon(boneTranslation);
			boneTranslation->addSon(boneRotation);
			boneRotation->addSon(bone);
			boneTranslation->addSon(rootTranslation);

			return polyArticulatedChain(rootTranslation, nodeBone, segments - 1);
		}

		virtual void render(double dt)  
		{
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());

			CCD->convergeToward(m_targetTranslation->getTranslation(),45.0f*Math::pi/180.0f);
			//bool result = CCD->solve(m_targetTranslation->getTranslation(), 45.0f*Math::pi / 180.0f);
			//std::cout << result << std::endl;
			
			for (int i = 0; i < m_mapDoF.size(); i++)
				m_mapDoF[i].first->setAngle(m_mapDoF[i].second->getDOF()[0]);

			m_root.draw();
		}
	};
}

#endif
