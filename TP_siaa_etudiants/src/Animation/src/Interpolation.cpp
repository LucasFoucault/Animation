#include <Animation/Interpolation.h>

Animation::Interpolation::Interpolation(Math::Vector3f P0,
										Math::Vector3f D0,
										Math::Vector3f P1,
										Math::Vector3f D1):
	m_P0(P0),
	m_D0(D0),
	m_P1(P1),
	m_D1(D1),
	m_coeffScalaire(Math::makeVector(2,-2,1,1),
					Math::makeVector(-3,3,-2,-1),
					Math::makeVector(0,0,1,0),
					Math::makeVector(1,0,0,0)
				   )
{}

Animation::Interpolation::~Interpolation()
{}

Math::Vector3f Animation::Interpolation::ComputeHermite(float u)
{
	Math::Vector4f uVector = Math::makeVector(pow(u,3),pow(u,2),u,1.0f);
	Math::Vector3f hermiteResult = Math::makeVector(0.0f,0.0f,0.0f);
	Math::Vector4f tempResult = Math::makeVector(0.0f,0.0f,0.0f,0.0f);

	/*for(int i=0; i<3; i++)
	{
		Math::Vector4f pdVector = Math::makeVector(m_P0[i],m_P1[i],m_D0[i],m_D1[i]);
		Math::Vector4f rowMatrix = m_coeffScalaire.getRow(i);
		
		for (int j=0; j<4; j++)
			resultHermite[i] += uVector[j] * rowMatrix[j] * pdVector[j];
	}*/

	for(int i=0; i<4; i++)
	{
		Math::Vector4f rowMatrix = m_coeffScalaire.getRow(i);

		for (int j=0; j<4; j++)
			tempResult[i] += uVector[j] * rowMatrix[j];
	}

	for(int i=0; i<3; i++)
	{
		Math::Vector4f pdVector = Math::makeVector(m_P0[i],m_P1[i],m_D0[i],m_D1[i]);

		for (int j=0; j<4; j++)
			hermiteResult[i] = tempResult[j] * pdVector[j];
	}

	return hermiteResult;
}

float Animation::Interpolation::ComputeSpeed(float u)
{
	Math::Vector4f duVector = Math::makeVector(3*pow(u,2), 2*pow(u,1), u, 0.0f);
	Math::Vector3f resultHermite = Math::makeVector(0.0f, 0.0f, 0.0f);

	for (int i = 0; i<3; i++)
	{
		Math::Vector4f pdVector = Math::makeVector(m_P0[i], m_P1[i], m_D0[i], m_D1[i]);
		Math::Vector4f rowMatrix = m_coeffScalaire.getRow(i);

		for (int j = 0; j<4; j++)
			resultHermite[i] += duVector[j] * rowMatrix[j] * pdVector[j];
	}

	return 0.0f;
}