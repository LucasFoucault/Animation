#ifndef _Animation_Interpolation_H
#define _Animation_Interpolation_H

#include <Math/Matrix4x4f.h>
#include <Math/Vectorf.h>

namespace Animation
{
	class Interpolation
	{
	private:
		Math::Matrix4x4f m_coeffScalaire;

	public:
		Interpolation();
		~Interpolation();

		Math::Vector4f ComputeHermite(float u, 
										 Math::Vector3f P0, 
										 Math::Vector3f P1, 
										 Math::Vector3f D0, 
										 Math::Vector3f D1);
	};
}

#endif 
