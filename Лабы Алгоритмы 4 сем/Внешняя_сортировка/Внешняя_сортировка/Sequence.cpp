#include "Sequence.h"

void Sequence::ReadNext()
{
	eof = file.eof();
	eor = eof;
	if (!eof)
		file.read((char*)&elem, sizeof(Elem));
}

void Sequence::StartRead(std::string filename)
{
	file.open(filename, std::ios::in | std::ios::binary);
	ReadNext();
	eor = eof;
}

void Sequence::StartWrite(std::string filename)
{
	file.open(filename, std::ios::out | std::ios::binary);
}

void Sequence::Close()
{
	file.close();
}

void Sequence::Copy(Sequence& x)
{
	elem = x.elem;
	x.ReadNext();
	if (!x.eof)
		file.write((char*)&elem, sizeof(Elem));
	x.eor = x.eof || x.elem < elem;
}

void Sequence::CopyRun(Sequence& x)
{
	do
	{
		Copy(x);
	} while (!x.eor);
}
