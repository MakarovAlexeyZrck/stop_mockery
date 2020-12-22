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
#include "filters.h"

using namespace std;

int main()
{

	unordered_map<int, trumpet> trumpets;
	unordered_map<int, ks> ks_s;
	unordered_map<int, gas_network> Networks;


	// Русский язык в консоли
	setlocale(LC_ALL, "Russian");

    // Управление программой
    while (1) {

		// Вывод меню действий
		print_menu();

		// Обработка ввода пользователя
		switch (input_value("--- Введите действие: ", 0, 10))
		{

		case 0: {
			cout << "Пока" << endl;
			return 0;
		}

		case 1: {
			manual_add_elements(trumpets, ks_s);
			break;
		}

		case 2: {
			cout << endl << "Информация об объектах в программе" << endl << endl;
			show_elements("Трубы", trumpets);
			show_elements("КС", ks_s);
			break;
		}

		case 3: {
			update_objects(trumpets, ks_s);
			break;
		}

		case 4: {
			delete_controller(trumpets, ks_s);
			break;
		}

		case 5: {
			trumpets_filter(trumpets);
			break;
		}

		case 6: {
			ks_filter(ks_s);
			break;
		}

		case 7: {
			batch_trumpets_editor(trumpets);
			break;
		}

		case 8: {
			write_data(trumpets, ks_s);
			break;
		}

		case 9: {
			read_data(trumpets, ks_s);
			break;
		}

		case 10: {
			bool is_network_created = true;
			while (true) {
				network_menu();
				int choice10 = input_value("Введите действие (0-5): ", 0, 5);
				if (choice10 == 1) {
					int id = gas_network::MaxID + 1;
					Networks.emplace(id, gas_network());
				}
				else if (choice10 == 2) {
					if (is_network_created) {
						int selected_id = id_availability(Networks, "Введите id сети (0 - выйти): ");
						Networks[selected_id].disassemble_pipes(trumpets, ks_s);
					}
					else {
						cout << "Такой сети еще нет" << endl;
					}
				}
				else if (choice10 == 3) {
					if (is_network_created) {
						int selected_id = id_availability(Networks, "Введите id сети (0 - выйти): ");
						Networks[selected_id].delete_trumpet(trumpets);
					}
					else {
						cout << "Такой сети еще нет" << endl;
					}
				}
				else if (choice10 == 4) {
					int selected_id = id_availability(Networks, "Введите id сети (0 - выйти): ");
					Networks[selected_id].sorted_matrix(trumpets);
				}
				else if (choice10 == 5) {
					int selected_id = id_availability(Networks, "Введите id сети (0 - выйти): ");
					Networks[selected_id].Print_network();
				}
				else {
					break;
				}
			}

			break;
		}

		default:
			cout << "Действие не поддерживается" << endl;
		}
    }

}
