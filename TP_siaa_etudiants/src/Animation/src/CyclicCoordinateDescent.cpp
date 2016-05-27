#include <Animation/CyclicCoordinateDescent.h>

Animation::CyclicCoordinateDescent::CyclicCoordinateDescent(Animation::KinematicChain *kinematicChain, Animation::KinematicChain::Node *lastNode):
	m_kinematicChain(kinematicChain),
	m_lastNode(lastNode)
{}

Animation::CyclicCoordinateDescent::~CyclicCoordinateDescent()
{}

void Animation::CyclicCoordinateDescent::convergeToward(Math::Vector3f target, float maxAngle)
{
	Math::Vector3f lastNodePosition(0.0f);
	lastNodePosition[0] = m_lastNode->getGlobalTransformation()(0, 3);
	lastNodePosition[1] = m_lastNode->getGlobalTransformation()(1, 3);
	lastNodePosition[2] = m_lastNode->getGlobalTransformation()(2, 3);

	Math::Vector3f constraint = target - lastNodePosition;

	ccd(constraint, maxAngle);
}

bool Animation::CyclicCoordinateDescent::solve(Math::Vector3f target, float maxAngle)
{
	Math::Vector3f constraint;
	Math::Vector3f lastPosition(0.0f);
	Math::Vector3f lastNodePosition(0.0f);

	do
	{
		lastNodePosition[0] = m_lastNode->getGlobalTransformation()(0, 3);
		lastNodePosition[1] = m_lastNode->getGlobalTransformation()(1, 3);
		lastNodePosition[2] = m_lastNode->getGlobalTransformation()(2, 3);
	
		if ((lastPosition-lastNodePosition).norm() < 0.001f)
			return false;

		lastPosition = lastNodePosition;
		constraint = target - lastNodePosition;

		ccd(constraint, maxAngle);
	} while(constraint.norm() > 0.1f);

	return true;
}

void Animation::CyclicCoordinateDescent::ccd(Math::Vector3f constraint, float maxAngle)
{
	std::vector<Animation::KinematicChain::DegreeOfFreedom> allDOf;
	m_lastNode->collectDegreesOfFreedom(allDOf);

	float epsilon = 0.000001;

	for (int i = 0; i<allDOf.size(); i++)
	{
		Math::Vector3f jacobien = m_kinematicChain->derivate(m_lastNode, Math::makeVector(0.0f, 0.0f, 0.0f), allDOf[i], epsilon);

		float varAngle = 0.0f;

		if (jacobien.norm2() != 0)
			varAngle = (jacobien.inv() * constraint) / jacobien.norm2();

		if (varAngle > maxAngle)
			varAngle = maxAngle;

		allDOf[i] = allDOf[i] + varAngle;
	}
}
