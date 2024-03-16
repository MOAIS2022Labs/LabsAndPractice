#pragma once
#include <set>
#include <iostream>
#include <fstream>


using TInfo = int;

class MathSet
{

//private:
	
	

public:

	std::set<TInfo> mset;
	MathSet() {}
	MathSet(const std::set<TInfo>& source)
	{
		mset = source;
	}
	MathSet union_set(const MathSet& other);
	MathSet difference(const MathSet& other);
	MathSet intersection(const MathSet& other);
	void print(std::ostream& stream = std::cout)
	{
		if (mset.empty())
			std::cout << "EMPTY!\n";
		else
		{
			for (TInfo x : mset)
				std::cout << x << ' ';
			std::cout << '\n';
		}
	}
};

