#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"
#include "with_files_tasks.h"
#include "editor.h"


// ���������� ��� �������� ���������
void delete_controller(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f, gas_network& n) {

	int small_choise = print_additional_menu("�����", "��");

	if (small_choise == 0) {
		cout << "�������� ����� � ��������� ���� ... " << endl << endl;
	}
	else if (small_choise == 1) {
		DelPipe(trumpets_f, n);
	}
	else if (small_choise == 2) {
		DelKs(ks_s_f, trumpets_f, n);
	}

}


// �������������� �����
void update_trumpet(unordered_map<int, trumpet>& trumpets_f, gas_network& n) {

	int trumpet_id = input_value("������� ������������� �����: ", 0, 1000);

	if (trumpets_f.count(trumpet_id) != 0) {
		trumpets_f[trumpet_id].trumpet_mode();
		n.PipeDelChanges(trumpet_id);
		cout << "������ ����� ��������� ... " << endl << endl;
	}
	else {
		cout << "����� � ������ ��������������� �� ���������� ... " << endl << endl;
	}
}

// �������������� ��
void update_ks(unordered_map<int, ks>& ks_f) {

	int ks_id = input_value("������� ������������� ��: ", 0, 1000);

	if (ks_f.count(ks_id) != 0) {
		ks_f[ks_id].edit_ks();
		cout << "������ �� ��������� ... " << endl << endl;
	}
	else {
		cout << "�� � ������ ��������������� �� ���������� ... " << endl << endl;
	}

}

// ���������� � �������������� ������
void update_objects(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f, gas_network &n) {

	int small_choise = print_additional_menu("�����", "��");

	if (small_choise == 0) {
		cout << "�������� ����� � ��������� ���� ... " << endl << endl;
	}
	else if (small_choise == 1) {
		update_trumpet(trumpets_f, n);
	}
	else if (small_choise == 2) {
		update_ks(ks_s_f);
	}
}


// ������������� ����� � slice id
void edit_slice_id(unordered_map<int, trumpet>& c_t) {

	int begin_slice = input_value("������� ��������� ������� �����: ", 0, trumpet::MaxID);
	int end_slice = input_value("������� �������� ������� �����: ", 0, trumpet::MaxID);

	int counter = 0;
	for (auto& item : c_t) {

		if (item.second.GetId() >= begin_slice && item.second.GetId() <= end_slice) {
			item.second.trumpet_mode();
		}
		counter++;
	}

}

// �������� �������������� ����
void batch_trumpets_editor(unordered_map<int, trumpet>& c_t) {

	int small_choise = print_additional_menu("������������� ���", "������������� �����");


	if (small_choise == 0) {
		cout << "�������� ����� � ��������� ���� ... " << endl << endl;
	}
	else if (small_choise == 1) {

		for (auto& item : c_t) {
			item.second.trumpet_mode();
		}

		cout << "��� ����� ��������������� ... " << endl << endl;

	}
	else if (small_choise == 2) {
		edit_slice_id(c_t);

		cout << "����� ���� �������������� ... " << endl << endl;
	}

}


void DelPipe(unordered_map<int, trumpet>& Pipeline_s, gas_network& n)
{

	int IdDel = input_value("\n������� id �������, ������� ������ �������: ", 0, trumpet::MaxID);
	auto IdToDelete = Pipeline_s.find(IdDel);
	if (IdToDelete == Pipeline_s.end())
		cout << "������� �� ������ ...\n";
	else
	{
		n.PipeDelChanges(IdDel);
		Pipeline_s.erase(IdToDelete->first);
		cout << "��������� ...\n";
	}
}

void DelKs(unordered_map<int, ks>& Ks_s, unordered_map <int, trumpet>& Pipeline_s, gas_network& n)
{
	int IdDel = input_value("\n������� id �������, ������� ������ �������: ", 0, ks::MaxID);
	auto IdToDelete = Ks_s.find(IdDel);
	if (IdToDelete == Ks_s.end())
		cout << "������� �� ������ ...\n";
	else
	{
		n.KsDelChanges(IdDel, Pipeline_s);
		Ks_s.erase(IdToDelete->first);
		cout << "��������� ...\n";
	}
}
