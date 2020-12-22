#include "with_files_tasks.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

// ������ ������ �� �����
void read_data(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f) {

	cout << "������� ������������ �����, �� �������� ������ ������:     ";
	string str;
	cin >> str;

	ifstream fin(string(str) + ".txt");
	if (!fin.is_open())
		cout << "���� �� ����� ���� ������!" << endl << endl;
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
		cout << "������ ������� ��������� ..." << endl << endl;
	}

	fin.close();
}


// ����������� ������ � ������
void save_t(ofstream& fout, const trumpet& t) {
	fout << "t " << t.length << " " << t.diameter << " " << t.is_broken << endl;
}

// ���������� ������ � ��
void save_ks(ofstream& fout, const ks& cs) {
	fout << "ks " << cs.ks_name << " " << cs.count_workshops << " " << cs.active_workshops << " " << cs.efficiency << endl;
}

// ������ ������ � ����
void write_data(const unordered_map<int, trumpet>& trumpets_f, const unordered_map<int, ks>& ks_s_f) {

	cout << "������� ������������ �����, � ������� ������ �������� ������:     ";
	string str;
	cin >> str;

	// ��������� ���� � ������� �� ������
	ofstream fout(string(str) + ".txt");
	if (!fout.is_open())
		cout << "���� �� ����� ���� ������!" << endl << endl;
	else {

		// ������ ������ � ������
		if (trumpets_f.size() != 0) {
			for (const auto& item : trumpets_f) {
				save_t(fout, item.second);
			}
		}

		// ������ ������ � ��
		if (ks_s_f.size() != 0) {
			for (const auto& item : ks_s_f) {
				save_ks(fout, item.second);
			}
		}

		cout << "������ ���������� � ���� ... " << endl << endl;
	}
	fout.close();
}
