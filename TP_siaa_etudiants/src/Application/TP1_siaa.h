#ifndef _Application_TP1_siaa_H
#define _Application_TP1_siaa_H

#include <HelperGl/Camera.h>
#include <HelperGl/LightServer.h>
#include <HelperGl/Material.h>
#include <HelperGl/Color.h>

#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>

#include <Animation/Interpolation.h>

#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Rotate.h>
#include <SceneGraph/Translate.h>
#include <SceneGraph/Scale.h>
#include <SceneGraph/DragonFly.h>

#include <GL/compatibility.h>

namespace Application
{
	class TP1_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;
		SceneGraph::Group m_root;
		SceneGraph::DragonFly * dragonFly;

		SceneGraph::Translate * dragonFlyTranslation;
		SceneGraph::Rotate * dragonFlyRotation;

		double t;
		float u;

		virtual void handleKeys() 
		{
			// The camera translation speed
			float cameraSpeed = 5.0f;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi/2.0);

			// quit
			if(m_keyboard.isPressed('q')) { quit(); }
			// Go front
			if(m_keyboard.isPressed('+')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,-cameraSpeed*(float)getDt())); } 
			// Go back
			if(m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,(float)cameraSpeed*(float)getDt())); } 
			// Go left
			if(m_keyboard.isPressed('1')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed*(float)getDt(),0.0f,0.0f)); }
			// Go right
			if(m_keyboard.isPressed('3')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(),0.0f,0.0f)); }
			// Go down
			if(m_keyboard.isPressed('2')) { m_camera.translateLocal(Math::makeVector(0.0f,-cameraSpeed*(float)getDt(),0.0f)); }
			// Go up
			if(m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f,(float)cameraSpeed*(float)getDt(),0.0f)); }
			// Rotation left
			if(m_keyboard.isPressed('4')) { m_camera.rotateLocal(Math::makeVector(0.0f,1.0f,0.0f), -1.0f*Math::pi/180.0f); }
			// Rotation right
			if(m_keyboard.isPressed('6')) { m_camera.rotateLocal(Math::makeVector(0.0f,1.0f,0.0f), 1.0f*Math::pi/180.0f); }
		}

	public:
		TP1_siaa():
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
			dragonFlyRotation = new SceneGraph::Rotate(0,Math::makeVector(0,0,0));

			// SceneGraph
			m_root.addSon(dragonFlyTranslation);
				dragonFlyTranslation->addSon(dragonFlyRotation);
					dragonFlyRotation->addSon(dragonFly);
		}

		virtual void render(double dt)
		{
			t += dt;
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());
			dragonFly->animate(t);
		}
	};
}

#endif