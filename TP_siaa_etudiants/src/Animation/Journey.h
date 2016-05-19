#ifndef _Animation_Journey_H
#define _Animation_Journey_H

#include <vector>
#include <Animation/Interpolation.h>

using namespace std;

namespace Animation
{
	class Journey
	{
	private:
		vector<Math::Vector3f> *m_v;
		vector<Animation::Interpolation*> m_Interpolations;

	public:
		Journey(vector<Math::Vector3f> *v);
		~Journey();

		Math::Vector3f compute(int t, float u);

		Math::Vector3f interpolationSpeed(int t, float u);
 	};
}

#endif 