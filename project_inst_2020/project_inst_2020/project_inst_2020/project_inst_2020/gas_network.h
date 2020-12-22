#pragma once

#include "utils.h"
#include "trumpet.h"
#include "ks.h"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>


class gas_network
{
private:
	unordered_map <int, int> mGtsKs;
	unordered_map <int, trumpet> mGtsPipe;
	map<pair<int, int>, int> network;
	void DFS(int start, vector<int>& color, stack <int>& temp);

	bool cycle_found;

public:
	set <int> GtsPipe;
	set <int> GtsKs;
	bool NetworkExist;

	gas_network();
	void create_connection(unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s);
	void create_network(const unordered_map<int, trumpet>& Pipeline_s);
	void topological_sort(const unordered_map<int, trumpet>& Pipeline_s);

	void save_data(const unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s);
	void load_data(unordered_map<int, trumpet>& Pipeline_s, unordered_map<int, ks>& Ks_s);

	void show_network();

};

