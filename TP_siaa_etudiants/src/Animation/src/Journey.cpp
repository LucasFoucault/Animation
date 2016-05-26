#include <Animation/Journey.h>

Animation::Journey::Journey(vector<Math::Vector3f> *v):
	m_v(v), 
	m_Interpolations()
{
	for(int i=0; i<m_v->size()-2; i+=2)
		m_Interpolations.push_back(new Animation::Interpolation((*m_v)[i],(*m_v)[i+1],(*m_v)[i+2],(*m_v)[i+3]));
}

Animation::Journey::~Journey()
{
	for(int i=0; i<m_Interpolations.size(); i++)
		delete m_Interpolations[i];
}

Math::Vector3f Animation::Journey::compute(int t, float u)
{
	int index = t%m_Interpolations.size();
	return m_Interpolations[index]->HermiteCompute(u);
}

Math::Vector3f Animation::Journey::interpolationSpeed(int t, float u)
{
	int index = t%m_Interpolations.size();
	return m_Interpolations[index]->HermiteCompute(u,1);
}
	