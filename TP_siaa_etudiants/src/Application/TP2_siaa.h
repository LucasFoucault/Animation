#ifndef _Application_TP2_siaa_H
#define _Application_TP2_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <HelperGl/Material.h>
#include <HelperGl/Color.h>

#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>

#include <Animation/KinematicChain.h>

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
		SceneGraph::DragonFly * dragonFly;

		SceneGraph::Translate * dragonFlyTranslation;
		SceneGraph::Rotate * dragonFlyRotationX;
		SceneGraph::Rotate * dragonFlyRotationY;
		SceneGraph::Rotate * dragonFlyRotationZ;

		Animation::Interpolation * dragonFlyInterpolation;

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

			// DragonFly
			dragonFly = new SceneGraph::DragonFly();

			// Transformation
			dragonFlyTranslation = new SceneGraph::Translate();
			dragonFlyRotationX = new SceneGraph::Rotate(0,Math::makeVector(0,0,0));
			dragonFlyRotationY = new SceneGraph::Rotate(0, Math::makeVector(0,0,0));
			dragonFlyRotationZ = new SceneGraph::Rotate(0, Math::makeVector(0,0,0));

			// Interpolation
			dragonFlyInterpolation = new Animation::Interpolation(	
																	Math::makeVector(0,0,0),
																	Math::makeVector(-10,0,-20),
																	Math::makeVector(3,3,3),
																	Math::makeVector(10,0,20)
																 );

			int chainSize;
			std::cout << "Enter the size of the chain: " << std::endl;
			std::cin >> chainSize;

			// SceneGraph
			m_root.addSon(buildChain(chainSize));
		}

		SceneGraph::Group * buildChain(int chainSize)
		{
			SceneGraph::Group * root = new SceneGraph::Group();
			KinematicChain * chainRoot = new KinematicChain();
			StaticNode * firstNode = new StaticNode();

			HelperGl::Color chainDiffuseColor(0.0f,0.0f,1.0f);
			HelperGl::Material chainMaterial;
			chainMaterial.setDiffuse(chainDiffuseColor);

			HelperGl::Color articulationDiffuseColor(0.7f,0.7f,0.0f);
			HelperGl::Material articulationMaterial;
			articulationMaterial.setDiffuse(articulationDiffuseColor);

			SceneGraph::Translate * firstTranslate = new SceneGraph::Translate(Math::makeVector(0.0f,0.0f,0.0f));
			SceneGraph::Rotate * firstRotate = new SceneGraph::Rotate(90.0f*Math::pi/180.0f, Math::makeVector(0,1,0));
			SceneGraph::Cylinder * firstCylinder = new SceneGraph::Cylinder(chainMaterial, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT);
			
			StaticNode * secondNode = chainRoot->addStaticTranslation(firstNode,firstTranslate->getTranslation());
			StaticNode * thirdNode  = chainRoot->addStaticEulerRotation(secondNode,0,firstRotate->getAngle(),0);

			root->addSon(firstTranslate);
				firstTranslate->addSon(firstRotate);0
					firstRotate->addSon(firstCylinder);

			SceneGraph::Transform * lastNode = firstTranslate;

			for(int i=0; i<chainSize-1; i++)
			{
				SceneGraph::Translate * t1 = new SceneGraph::Translate(Math::makeVector(CYLINDER_HEIGHT + SPHERE_RADIUS/2,0.0f,0.0f)); // 2 + SPHERE_RADIUS/2 - 0.04f
				SceneGraph::Rotate * firstLibertyDegree  = new SceneGraph::Rotate(0,Math::makeVector(0,1,0));
				SceneGraph::Rotate * secondLibertyDegree = new SceneGraph::Rotate(0,Math::makeVector(0,0,1));

				StaticNode * sn1  = chainRoot->addStaticTranslation(firstNode,t1->getTranslation());
				DynamicNode * dn1 = chainRoot->addDynamicRotation(sn1,Math::makeVector(0,1,0),Math::makeInterval((float)-Math::pi/2,(float)Math::pi/2),0);
				DynamicNode * dn2 = chainRoot->addDynamicRotation(dn1,Math::makeVector(0,0,1),Math::makeInterval((float)-Math::pi/2,(float)Math::pi/2),0);

				lastNode->addSon(t1);
					t1->addSon(firstLibertyDegree);
						firstLibertyDegree->addSon(secondLibertyDegree);
							secondLibertyDegree->addSon(new SceneGraph::Sphere(articulationMaterial, SPHERE_RADIUS));
				lastNode = secondLibertyDegree;



				SceneGraph::Translate * t2 = new SceneGraph::Translate(Math::makeVector(SPHERE_RADIUS/2,0.0f,0.0f));
				SceneGraph::Rotate * r2 = new SceneGraph::Rotate(90.0f*Math::pi/180.0f, Math::makeVector(0,1,0));
				
				StaticNode * sn2 = chainRoot->addStaticTranslation(dn2,t2->getTranslation());
				StaticNode * sn3 = chainRoot->addStaticEulerRotation(sn2,0,r2->getAngle(),0);

				lastNode->addSon(t2);
					t2->addSon(r2);
						r2->addSon(new SceneGraph::Cylinder(chainMaterial,CYLINDER_RADIUS,CYLINDER_RADIUS,CYLINDER_HEIGHT));
				lastNode = t2;
			}

			return root;
		}

		virtual void render(double dt)
		{
			t += dt;
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());
			m_root.draw();
		}
	};
}

#endif
