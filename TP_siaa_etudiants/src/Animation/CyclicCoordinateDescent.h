#ifndef _Animation_CyclicCoordinateDescent_H
#define _Animation_CyclicCoordinateDescent_H

#include <Math/Matrix4x4f.h>
#include <Math/Vectorf.h>
#include <Animation/KinematicChain.h>

namespace Animation
{
	class CyclicCoordinateDescent
	{
	private:
		Animation::KinematicChain *m_kinematicChain;
		Animation::KinematicChain::Node *m_lastNode;

	public:
		CyclicCoordinateDescent(Animation::KinematicChain *kinematicChain, Animation::KinematicChain::Node *lastNode);
		~CyclicCoordinateDescent();

		void convergeToward(Math::Vector3f target, float maxAngle);
		bool solve(Math::Vector3f target, float maxAngle);
		void ccd(Math::Vector3f constraint, float maxAngle);
	};
}

#endif 

