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
		Math::Vector3f m_P0;
		Math::Vector3f m_D0;
		Math::Vector3f m_P1;
		Math::Vector3f m_D1;

	public:
		Interpolation(Math::Vector3f P0,
					  Math::Vector3f D0,
					  Math::Vector3f P1,
					  Math::Vector3f D1);
		~Interpolation();

		Math::Vector3f ComputeHermite(float u);

		float ComputeSpeed(float u);
	};
}

#endif 
