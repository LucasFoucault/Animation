#include <Animation/Interpolation.h>

Animation::Interpolation::Interpolation():
	m_coeffScalaire(Math::makeVector(2,-2,1,1),
					Math::makeVector(-3,3,-2,-1),
					Math::makeVector(0,0,1,0),
					Math::makeVector(1,0,0,0)
				   )
{}

Animation::Interpolation::~Interpolation()
{}

Math::Vector3f Animation::Interpolation::ComputeHermite(float u, 
										 Math::Vector3f P0, 
										 Math::Vector3f P1, 
										 Math::Vector3f D0, 
										 Math::Vector3f D1)
{
	Math::Vector4f uVector = Math::makeVector(pow(u,3),pow(u,2),u,1.0f);
	Math::Vector3f resultHermite = Math::makeVector(0.0f,0.0f,0.0f);

	for(int i=0; i<3; i++)
	{
		Math::Vector4f pdVector = Math::makeVector(P0[i],P1[i],D0[i],D1[i]);
		Math::Vector4f rowMatrix = m_coeffScalaire.getRow(i);
		
		for (int j=0; j<4; j++)
			resultHermite[i] += uVector[j] * rowMatrix[j] * pdVector[j];
	}

	return resultHermite;
}