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


// Управление ручным добавлением
void manual_add_elements(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f) {

	int small_choise = print_additional_menu("Труба", "КС");

	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}
	else if (small_choise == 1) {
		int id = trumpet::MaxID;
		trumpets_f.emplace(id, trumpet());
		cin >> trumpets_f[id];
	}
	else if (small_choise == 2) {
		int id = ks::MaxID;
		ks_s_f.emplace(id, ks());
		cin >> ks_s_f[id];
	}

}
