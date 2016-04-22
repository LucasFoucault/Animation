#include <Application/ApplicationSelection.h>

#include <Application/TP1_siaa.h>
#include <Application/TP2_siaa.h>


int main(int argc, char ** argv)
{
	// Registers the application 
	Application::ApplicationSelection::registerFactory<Application::TP1_siaa>("TP 1") ;
	// Registers the application 
	Application::ApplicationSelection::registerFactory<Application::TP2_siaa>("TP 2");
	// Initializes GLUT and GLEW
	Application::Base::initializeGLUT(argc, argv) ;
	// Selection of the application and run
	Application::ApplicationSelection::selectAndRun() ;
}