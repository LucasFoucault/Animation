#include <Animation/CyclicCoordinateDescent.h>

Animation::CyclicCoordinateDescent::CyclicCoordinateDescent(Animation::KinematicChain *kinematicChain, Animation::KinematicChain::StaticNode *lastNode):
	m_kinematicChain(kinematicChain),
	m_lastNode(lastNode)
{}

Animation::CyclicCoordinateDescent::~CyclicCoordinateDescent()
{}

void Animation::CyclicCoordinateDescent::convergeToward(Math::Vector3f finalPosition, float maxAngle)
{
	Math::Vector3f lastPosition;
	lastPosition[0] = m_lastNode->getLocalTransformation()(0, 3);
	lastPosition[1] = m_lastNode->getLocalTransformation()(1, 3);
	lastPosition[2] = m_lastNode->getLocalTransformation()(2, 3);

	Math::Vector3f constraint = finalPosition - lastPosition;

	std::vector<Animation::KinematicChain::DegreeOfFreedom> allDOf;
	m_lastNode->collectDegreesOfFreedom(allDOf);

	float epsilon = 0.0001;

	for (int i=0; i<allDOf.size(); i++)
	{
		Math::Vector3f jacobien = m_kinematicChain->derivate(m_lastNode, Math::makeVector(0.0f, 0.0f, 0.0f), allDOf[i], epsilon);

		float varAngle = 0.0f;

		if (jacobien.norm2() != 0)
			varAngle = (jacobien.inv() * constraint) / jacobien.norm2();

		if (varAngle > maxAngle) varAngle = maxAngle;

		allDOf[i] = allDOf[i] + varAngle;
	}
}