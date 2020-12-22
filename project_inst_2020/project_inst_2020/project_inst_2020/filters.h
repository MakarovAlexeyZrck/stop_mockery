#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"
#include "with_files_tasks.h"
#include "editor.h"
#include "another_features.h"

class filters
{
};

// Поиск по заданному параметру
template<class T, typename T_param>
using Filter = bool(*)(const T& obj, T_param param);

template<class T, typename T_param>
vector<int> FindObjectsByFilter(const unordered_map<int, T>& m, Filter<T, T_param> f, T_param param) {

	vector <int> result;
	for (const auto& item : m) {
		if (f(item.second, param))
			result.push_back(item.first);
	}
	return result;
}


template <class T>
bool CheckByID(const T& p, int param) {
	return p.id == param;
}

bool CheckByIsBroken(const trumpet& p, bool param);
bool CheckByName(const ks& cs, string param);
bool CheckByPercentOfWorkshops(const ks& cs, double param);

void trumpets_filter(const unordered_map<int, trumpet>& trumpets_f);
void ks_filter(const unordered_map<int, ks>& cs_set);