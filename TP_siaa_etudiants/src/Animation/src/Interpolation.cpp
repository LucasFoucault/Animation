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

Math::Vector3f Animation::Interpolation::HermiteCompute(float u, int d)
{
	Math::Vector4f uVector;

	if(d==0)		// Aucune dérivée appliquée
		uVector = Math::makeVector(pow(u,3),pow(u,2),u,1.0f);
	else if(d==1)	// Dérivée du premier degré
		uVector = Math::makeVector(3*pow(u,2),2*u,1.0f,0.0f);
	else if(d==2)	// Dérivée du second degré
		uVector = Math::makeVector(6*u,2.0f,0.0f,0.0f);

	Math::Vector3f hermiteResult = Math::makeVector(0.0f,0.0f,0.0f);
	Math::Vector4f tempResult = Math::makeVector(0.0f,0.0f,0.0f,0.0f);

	for(int i=0; i<4; i++)
	{
		Math::Vector4f matrixColumn = m_coeffScalaire.getColumn(i);

		for (int j=0; j<4; j++)
			tempResult[i] += uVector[j] * matrixColumn[j];
	}

	for(int i=0; i<3; i++)
	{
		Math::Vector4f pdVector = Math::makeVector(m_P0[i],m_P1[i],m_D0[i],m_D1[i]);

		for (int j=0; j<4; j++)
			hermiteResult[i] += tempResult[j] * pdVector[j];
	}

	return hermiteResult;
}

float Animation::Interpolation::speedCompute(float u)
{
	Math::Vector3f hermiteResult = HermiteCompute(u, 1);
	return sqrt(pow(hermiteResult[0],2) + pow(hermiteResult[1],2) + pow(hermiteResult[2],2));
}

float Animation::Interpolation::accelerationCompute(float u)
{
	Math::Vector3f hermiteResult = HermiteCompute(u, 2);
	return sqrt(pow(hermiteResult[0], 2) + pow(hermiteResult[1], 2) + pow(hermiteResult[2], 2));
}