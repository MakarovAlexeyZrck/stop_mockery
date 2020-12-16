#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"

using namespace std;


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
		 << "0. Выйти" << endl;
}


// Печатаем вторичное меню в консоль
int print_additional_menu(string msg1, string msg2) {

	cout << "0. Главное меню" << endl
		 << "1." << msg1 << endl
		 << "2." << msg2 << endl;

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

	// Русский язык в консоли
	setlocale(LC_ALL, "Russian");

    // Управление программой
    while (1) {

		// Вывод меню действий
		print_menu();

		// Обработка ввода пользователя
		switch (input_value("--- Введите действие: ", 0, 9))
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
			break;
		}

		case 6: {
			break;
		}

		case 7: {
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

		default:
			cout << "Действие не поддерживается" << endl;
		}
    }

}
