#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"
#include "with_files_tasks.h"

void delete_controller(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f);
void update_trumpet(unordered_map<int, trumpet>& trumpets_f);
void update_ks(unordered_map<int, ks>& ks_f);
void update_objects(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f);
void edit_slice_id(unordered_map<int, trumpet>& c_t);
void batch_trumpets_editor(unordered_map<int, trumpet>& c_t);

class editor
{
};

