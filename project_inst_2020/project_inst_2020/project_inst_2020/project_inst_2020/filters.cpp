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



// ������ ��� ����
void trumpets_filter(const unordered_map<int, trumpet>& trumpets_f) {

	int small_choise = print_additional_menu("����� �� id", "����� �� �������");

	if (small_choise == 0) {
		cout << "�������� ����� � ��������� ���� ... " << endl << endl;
	}

	else if (small_choise == 1) {
		int research_id = input_value("������� id ��� ������: ", 0, 1000);
		if (research_id > trumpet::MaxID) {
			cout << "��� ��������, ��������������� �������� ��������� ������" << endl << endl;
		}
		else {
			for (int i : FindObjectsByFilter(trumpets_f, CheckByID, research_id)) {
				cout << trumpets_f.at(i) << endl;
			}
		}
	}

	else if (small_choise == 2) {
		bool is_broken_status_to_find;
		is_broken_status_to_find = input_value("��������� �����? [1 - �������, 0 - ��������]: ", false, true);
		bool was_found = false;
		for (int i : FindObjectsByFilter(trumpets_f, CheckByIsBroken, is_broken_status_to_find)) {
			cout << trumpets_f.at(i) << endl;
			was_found = true;
		}
		if (!was_found) cout << "��� ��������, ��������������� �������� ��������� ������" << endl << endl;
	}

}


// ������ ��� ��
void ks_filter(const unordered_map<int, ks>& cs_set) {

	int small_choise = print_additional_menu("����� �� �����", "����� �� �������� ��������������� �����");

	if (small_choise == 0) {
		cout << "�������� ����� � ��������� ���� ... " << endl << endl;
	}

	else if (small_choise == 1) {
		string name_to_find;
		cout << "������� ��� ��: ";
		cin.get();
		getline(cin, name_to_find);
		for (int i : FindObjectsByFilter(cs_set, CheckByName, name_to_find)) {
			cout << cs_set.at(i) << endl;
		}
	}

	else if (small_choise == 2) {
		double percentage_to_find;
		percentage_to_find = input_value("������� ������� ������� (0-100%): ", 0.0, 100.0);
		bool was_found = false;
		for (int i : FindObjectsByFilter(cs_set, CheckByPercentOfWorkshops, percentage_to_find)) {
			cout << cs_set.at(i) << endl;
			was_found = true;
		}

		if (!was_found) cout << "��� ��������, ��������������� �������� ��������� ������" << endl << endl;

	}
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
