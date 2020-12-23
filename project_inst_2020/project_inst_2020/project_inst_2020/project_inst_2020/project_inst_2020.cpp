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
	gas_network n;

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
			update_objects(trumpets, ks_s, n);
			break;
		}

		case 4: {
			delete_controller(trumpets, ks_s, n);
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
			bool running = true;
			while (running) {
				network_menu();
				switch (input_value("--- --- Введите действие: ", 0, 6))
				{

				case 0: {
					running = false;
					cout << endl << endl;
					break;
				}

				case 1: {
					n.create_connection(trumpets, ks_s);
					break;
				}

				case 2: {
					n.create_network(trumpets);
					break;
				}

				case 3: {
					n.show_network();
					break;
				}

				case 4: {
					n.topological_sort(trumpets);
					break;
				}

				case 5: {
					n.load_data(trumpets, ks_s);
					n.create_network(trumpets);
					break;
				}

				case 6: {
					n.save_data(trumpets, ks_s);
				}

				}
			}
		}
		default:
			cout << "Действие не поддерживается" << endl;
		}
	}
}
