#pragma once
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "trumpet.h"
#include "ks.h"

using namespace std;

void read_data(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f);
void save_t(ofstream& fout, const trumpet& t);
void save_ks(ofstream& fout, const ks& cs);
void write_data(const unordered_map<int, trumpet>& trumpets_f, const unordered_map<int, ks>& ks_s_f);

class with_files_tasks
{
};

