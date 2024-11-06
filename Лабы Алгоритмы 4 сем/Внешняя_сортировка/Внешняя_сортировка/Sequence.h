#pragma once
#include "Help.h"

struct Sequence
{
	std::fstream file;
	Elem elem;
	bool eof, eor;
	void ReadNext();
	void StartRead(std::string filename);
	void StartWrite(std::string filename);
	void Close();
	void Copy(Sequence& x);
	void CopyRun(Sequence& x);
};