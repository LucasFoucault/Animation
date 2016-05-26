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
		Animation::KinematicChain::StaticNode *m_lastNode;

	public:
		CyclicCoordinateDescent(Animation::KinematicChain *kinematicChain, Animation::KinematicChain::StaticNode *lastNode);
		~CyclicCoordinateDescent();

		void convergeToward(Math::Vector3f finalPosition, float angle);
	};
}

#endif 

