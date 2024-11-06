#include "Sort.h"

int distribute(Sequence f[NFILES], Sequence& f0, std::string filename)
{
	f0.StartRead(filename);
	for (int i = 0; i < NFILES / 2 + 1; ++i)
		f[i].StartWrite(std::to_string(i) + ".bin");
	int count_sources = 0, i_dest = 0;
	while (!f0.eof)
	{
		f[i_dest].CopyRun(f0);
		if (f0.elem < f[i_dest].elem || f[i_dest].elem == Elem())
		{
			i_dest = (i_dest + 1) % (NFILES / 2 + 1);
			++count_sources;
		}
	}
	if (count_sources > NFILES / 2 + 1)
		count_sources = NFILES / 2 + 1;
	for (size_t i = 0; i < NFILES / 2 + 1; ++i)
		f[i].Close();
	f0.Close();
	return count_sources;
}

int merge(Sequence f[NFILES], int t[NFILES], int count_sources)
{
	for (size_t i = 0; i < count_sources; ++i)
		f[t[i]].StartRead(std::to_string(t[i]) + ".bin");
	for (size_t i = count_sources; i < NFILES; ++i)
		f[t[i]].StartWrite(std::to_string(t[i]) + ".bin");
	int count{};
	int i_t = count_sources;
	int first_dest = count_sources;
	while (count_sources > 1)
	{
		int count_series = count_sources;
		while (count_series > 1)
		{
			int i_min = 0;
			for (int i = 1; i < count_series; ++i)
				if (f[t[i_min]].elem > f[t[i]].elem)
					i_min = i;
			f[t[i_t]].Copy(f[t[i_min]]);
			if (f[t[i_min]].eor)
			{
				--count_series;
				std::swap(t[i_min], t[count_series]);
			}
		}
		f[t[i_t]].CopyRun(f[t[0]]);
		if (i_t < NFILES - 1)
			++i_t;
		else
			i_t = first_dest;
		int i = 0;
		while (i < count_sources)
		{
			if (f[t[i]].eof)
			{
				std::swap(t[i], t[count_sources - 1]);
				--count_sources;
			}
			else
				++i;
		}
		++count;
	}
	while (!f[t[0]].eof)
	{
		f[t[i_t]].CopyRun(f[t[0]]);
		++count;
	}
	for (size_t i = 0; i < NFILES; ++i)
		f[i].Close();
	return count;
}

void shift_to_left(int t[NFILES], int step)
{
	int* tmp = new int[step];
	for (int i = 0; i < step; ++i)
		tmp[i] = t[i];
	for (int i = 0; i < NFILES - step; ++i) 
		t[i] = t[i + step];
	for (int i = NFILES - step; i < NFILES; ++i) 
		t[i] = tmp[i - (NFILES - step)];
	delete[] tmp;
}


void sorting(std::string filename)
{
	Sequence f0;
	Sequence f[NFILES];
	int t[NFILES];
	for (int i = 0; i < NFILES; ++i)
		t[i] = i;
	int count_sources = distribute(f, f0, filename);
	if (count_sources > 1)
	{
		int count = 0;
		do
		{
			count = merge(f, t, count_sources);
			shift_to_left(t, count_sources);

			count_sources = NFILES - count_sources;
			if (count < count_sources)
				count_sources = count;

		} while (count > 1);
	}
	f0.StartWrite(filename);
	f[t[0]].StartRead(std::to_string(t[0]) + ".bin");
	f0.CopyRun(f[t[0]]);
	f[t[0]].Close();
	for (size_t i = 0; i < NFILES; ++i)
	{
		std::string fname = std::to_string(t[i]) + ".bin";
		remove(fname.c_str());
	}
	f0.Close();
}
