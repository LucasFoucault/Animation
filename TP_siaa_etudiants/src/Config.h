#ifndef _Config_H
#define _Config_H

#include <GL/freeglut.h>
#include <System/Path.h>

namespace Config
{
#ifdef WIN32
	/// \brief	The directory separator (for windows).
	static ::std::string directorySeparator = "\\";
#else
	/// \brief	The directory separator (for linux).
	static ::std::string directorySeparator = "/";
#endif

	/// \brief	Full pathname of the executable file.
	static ::std::string executablePath = System::Path::executable() ;

	/// \brief	Full pathname of the data directory.
	static ::std::string dataPath = System::Path::executable()+directorySeparator+".."+directorySeparator+".."+directorySeparator+"data" ; //"\\..\\..\\data" ;

	/// \brief	The Phong vertex shader file.
	static ::std::string PhongVertexShaderFile = dataPath + directorySeparator + "Shaders" + directorySeparator + "Phong" + directorySeparator + "Phong.vs" ; 

	/// \brief	The Phong fragment shader file.
	static ::std::string PhongFragmentShaderFile = dataPath + directorySeparator + "Shaders" + directorySeparator + "Phong" + directorySeparator + "Phong.fs" ; 

	/// \brief	The default openGL window width.
	static unsigned int defaultWindowWidth = 400 ;

	/// \brief	The default openGL window height.
	static unsigned int defaultWindowHeight = 400 ;

	/// \brief	The default near plane distance.
	static GLfloat defaultNearPlane = 0.01f ;

	/// \brief	The default far plane distance.
	static GLfloat defaultFarPlane = 1000.0f ;

	/// \brief	The default fovy.
	static GLfloat defaultFovy = 65.0f ;
}

#endif
