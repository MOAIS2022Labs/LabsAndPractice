#pragma once
#include"Sequence.h"


const size_t NFILES = 12;
//const size_t COUNT_ELEM = 1000000;

int distribute(Sequence f[NFILES], Sequence& f0, std::string filename);

int merge(Sequence f[NFILES], int t[NFILES], int count_sources);

//void shift_to_left(int t[NFILES]);

void sorting(std::string filename);