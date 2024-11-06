#include "MathSet.h"

MathSet MathSet::union_set(const MathSet& other)
{
	/*auto it1 = mset.begin();
	auto it2 = other.mset.begin();
	MathSet result;
	while (it1 != mset.end() || it2 != other.mset.end())
	{
		if (it1 != mset.end() && it2 != other.mset.end())
		{

		}
	}*/

	MathSet result = other;
	for (TInfo x : mset)
		result.mset.insert(x);
	return result;
}

MathSet MathSet::difference(const MathSet& other)
{
	MathSet result;
	for (TInfo x : mset)
		if (!(other.mset.count(x)))
			result.mset.insert(x);
	return result;;
}

MathSet MathSet::intersection(const MathSet& other)
{
	MathSet result;
	for (TInfo x : mset)
		if (other.mset.count(x))
			result.mset.insert(x);
	return result;
}
