#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"
#include "with_files_tasks.h"

void delete_controller(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f, gas_network& n);
void update_ks(unordered_map<int, ks>& ks_f);
void update_objects(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f, gas_network& n);
void edit_slice_id(unordered_map<int, trumpet>& c_t);
void batch_trumpets_editor(unordered_map<int, trumpet>& c_t);
void DelKs(unordered_map<int, ks>& Ks_s, unordered_map <int, trumpet>& Pipeline_s, gas_network& n);
void DelPipe(unordered_map<int, trumpet>& Pipeline_s, gas_network& n);

class editor
{
};

