#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"

using namespace std;


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

bool CheckByIsBroken(const trumpet& p, bool param) {
	return p.is_broken == param;
}

bool CheckByName(const ks& cs, string param) {
	return cs.ks_name == param;
}

bool CheckByPercentOfWorkshops(const ks& cs, double param) {
	double percentage_of_number_workshops = 1.0 - cs.active_workshops / (double)cs.count_workshops;
	return (abs(percentage_of_number_workshops - param / 100.0) < 0.0001);
}



// Печатаем главное меню в консоль
void print_menu() {

	cout << "1. Добавить трубу или КС" << endl
		 << "2. Просмотреть все объекты" << "\n"
		 << "3. Редактировать трубу/КС" << "\n"
		 << "4. Удалить трубу/КС" << "\n"
		 << "5. Фильтр для труб" << "\n"
		 << "6. Фильтр для КС" << "\n"
		 << "7. Редактировать трубы пакетно" << "\n"
		 << "8. Сохранить данные в файл" << "\n"
		 << "9. Загрузить данные из файла" << "\n"
		 << "10. Cеть" << endl
		 << "0. Выйти" << endl;
}


// Печатаем вторичное меню в консоль
int print_additional_menu(string msg1, string msg2) {

	cout << "0. Главное меню" << endl
		 << "1. " << msg1 << endl
		 << "2. " << msg2 << endl;

	int user_point;
	user_point = input_value("--- Введите действие: ", 0, 2);

	return user_point;
}


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


// Просмотр всех элементов
template <typename T>
void show_elements(string object_name, const T data) {

	if (data.size() == 0) {
		cout << object_name << " ещё не добавлены" << endl;
	}
	else {
		for (const auto& item : data) {
			cout << item.second << endl;
		}
	}
}


// Контроллер для удаления элементов
void delete_controller(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f) {

	int small_choise = print_additional_menu("Труба", "КС");

	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}
	else if (small_choise == 1) {
		delete_object(trumpets_f);
	}
	else if (small_choise == 2) {
		delete_object(ks_s_f);
	}

}


// Редактирование трубы
void update_trumpet(unordered_map<int, trumpet>& trumpets_f) {

	int trumpet_id = input_value("Введите идентификатор трубы: ", 0, 1000);

	if (trumpets_f.count(trumpet_id) != 0) {
		trumpets_f[trumpet_id].trumpet_mode();
		cout << "Данные трубы обновлены ... " << endl << endl;
	}
	else {
		cout << "Трубы с данным идентификатором не существует ... " << endl << endl;
	}
}

// Редактирвоание КС
void update_ks(unordered_map<int, ks>& ks_f) {

	int ks_id = input_value("Введите идентификатор КС: ", 0, 1000);

	if (ks_f.count(ks_id) != 0) {
		ks_f[ks_id].edit_ks();
		cout << "Данные КС обновлены ... " << endl << endl;
	}
	else {
		cout << "КС с данным идентификатором не существует ... " << endl << endl;
	}

}

// Обновление и редактирование данных
void update_objects(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f) {

	int small_choise = print_additional_menu("Труба", "КС");

	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}
	else if (small_choise == 1) {
		update_trumpet(trumpets_f);
	}
	else if (small_choise == 2) {
		update_ks(ks_s_f);
	}
}


// Редактировать трубы с slice id
void edit_slice_id(unordered_map<int, trumpet>& c_t) {

	int begin_slice = input_value("Введите начальный элемент среза: ", 0, trumpet::MaxID);
	int end_slice = input_value("Введите конечный элемент среза: ", 0, trumpet::MaxID);

	int counter = 0;
	for (auto& item : c_t) {

		if (item.second.id >= begin_slice && item.second.id <= end_slice) {
			item.second.trumpet_mode();
		}
		counter++;
	}

}

// Пакетное редактирование труб
void batch_trumpets_editor(unordered_map<int, trumpet>& c_t) {

	int small_choise = print_additional_menu("Редактировать все", "Редактировать набор");


	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}
	else if (small_choise == 1) {

		for (auto& item : c_t) {
			item.second.trumpet_mode();
		}

		cout << "Все трубы отредактированы ... " << endl << endl;

	}
	else if (small_choise == 2) {
		edit_slice_id(c_t);

		cout << "Пакет труб отредактирован ... " << endl << endl;
	}

}


// Фильтр для труб
void trumpets_filter(const unordered_map<int, trumpet>& trumpets_f) {

	int small_choise = print_additional_menu("Поиск по id", "Поиск по статусу");

	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}

	else if (small_choise == 1) {
		int research_id = input_value("Введите id для поиска: ", 0, 1000);
		if (research_id > trumpet::MaxID) {
			cout << "Нет объектов, соответствующих заданным критериям поиска" << endl << endl;
		}
		else {
			for (int i : FindObjectsByFilter(trumpets_f, CheckByID, research_id)) {
				cout << trumpets_f.at(i) << endl;
			}
		}
	}

	else if (small_choise == 2) {
		bool is_broken_status_to_find;
		is_broken_status_to_find = input_value("Состояние трубы? [1 - сломана, 0 - работает]: ", false, true);
		bool was_found = false;
		for (int i : FindObjectsByFilter(trumpets_f, CheckByIsBroken, is_broken_status_to_find)) {
			cout << trumpets_f.at(i) << endl;
			was_found = true;
		}
		if (!was_found) cout << "Нет объектов, соответствующих заданным критериям поиска" << endl << endl;
	}

}


// Фильтр для КС
void trumpets_filter(const unordered_map<int, ks>& cs_set) {

	int small_choise = print_additional_menu("Поиск по имени", "Поиск по проценту задействованных цехов");

	if (small_choise == 0) {
		cout << "Выполнен выход в начальное меню ... " << endl << endl;
	}

	else if (small_choise == 1) {
		string name_to_find;
		cout << "Введите имя КС: ";
		cin.get();
		getline(cin, name_to_find);
		for (int i : FindObjectsByFilter(cs_set, CheckByName, name_to_find)) {
			cout << cs_set.at(i) << endl;
		}
	}

	else if (small_choise == 2) {
		double percentage_to_find;
		percentage_to_find = input_value("Введите искомый процесс (0-100%): ", 0.0, 100.0);
		bool was_found = false;
		for (int i : FindObjectsByFilter(cs_set, CheckByPercentOfWorkshops, percentage_to_find)) {
			cout << cs_set.at(i) << endl;
			was_found = true;
		}

		if (!was_found) cout << "Нет объектов, соответствующих заданным критериям поиска" << endl << endl;

	}
}


// Чтение данных из файла
void read_data(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f) {

	cout << "Введите наименование файла, из которого хотите читать:     ";
	string str;
	cin >> str;

	ifstream fin(string(str) + ".txt");
	if (!fin.is_open())
		cout << "Файл не может быть открыт!" << endl << endl;
	else {
		string buff;
		while (fin >> buff)
		{

			if (buff == "t")
			{
				trumpet t;
				fin >> t.length >> t.diameter >> t.is_broken;
				int id = trumpet::MaxID;
				trumpets_f.emplace(id, t);
			}

			else if (buff == "ks") {
				ks c_ks;
				fin >> c_ks.ks_name >> c_ks.count_workshops >> c_ks.active_workshops >> c_ks.efficiency;
				int id = ks::MaxID;
				ks_s_f.emplace(id, c_ks);
			}

		}
		cout << "Данные успешно прочитаны ..." << endl << endl;
	}

	fin.close();
}


// Сохранениие данных о трубах
void save_t(ofstream& fout, const trumpet& t) {
	fout << "t " << t.length << " " << t.diameter << " " << t.is_broken << endl;
}

// Сохранение данных о КС
void save_ks(ofstream& fout, const ks& cs) {
	fout << "ks " << cs.ks_name << " " << cs.count_workshops << " " << cs.active_workshops << " " << cs.efficiency << endl;
}

// Запись данных в файл
void write_data(const unordered_map<int, trumpet>& trumpets_f, const unordered_map<int, ks>& ks_s_f) {

	cout << "Введите наименование файла, в которых хотите записать данные:     ";
	string str;
	cin >> str;

	// Открываем файл с потоком на запись
	ofstream fout(string(str) + ".txt");
	if (!fout.is_open())
		cout << "Файл не может быть открыт!" << endl << endl;
	else {

		// Запись данных о трубах
		if (trumpets_f.size() != 0) {
			for (const auto& item : trumpets_f) {
				save_t(fout, item.second);
			}
		}

		// Запись данных о КС
		if (ks_s_f.size() != 0) {
			for (const auto& item : ks_s_f) {
				save_ks(fout, item.second);
			}
		}

		cout << "Данные отправлены в файл ... " << endl << endl;
	}
	fout.close();
}


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
			trumpets_filter(ks_s);
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
