#pragma once

#include "utils.h"
#include "trumpet.h"
#include "ks.h"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>



using namespace std;

class gas_network
{

public:

	gas_network();
	static int MaxID;

	void assign_name(const string& user_name);
	void assign_id(int network_id);
	string get_name();
	int get_id();

	void disassemble_pipes(
		std::unordered_map<int, trumpet>& trumpet_data, std::unordered_map<int, ks>& ks_data);
	void delete_trumpet(std::unordered_map<int, trumpet>& trumpet_data);

	void sorted_matrix(unordered_map<int, trumpet>& trumpet_data);

	void Print_network();

private:

	int id;
	string network_name;

	set<int> used_trumpets;
	set<int> used_kss;

	vector<std::vector<int>> topo_matrix;
	vector<int> cs_matr_pos;
};

