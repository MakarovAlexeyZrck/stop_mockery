#include "with_files_tasks.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

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
