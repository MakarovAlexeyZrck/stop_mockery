#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "trumpet.h"
#include "ks.h"

using namespace std;

// ���� ��� ������������ �� � �����
void network_menu();

// ������� �� �������� ��������� ���� ������
template <typename T>
T input_value(string msg, T min, T max)
{
	T x;
	cout << msg;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << msg;
	}

	return x;
}


// ������� �� ��������� ���������
template <typename T1>
void delete_object(unordered_map<int, T1>& active_element) {

	int id = input_value("������������� ���������� �������: ", 0, 1000);

	if (active_element.count(id) == 0) {
		cout << "��������� �������������, ������� � �������� ��������������� �� ����������" << endl << endl;
	}
	else {
		active_element.erase(id);
		cout << "������ ������� ������ ... " << endl << endl;
	}

}


// �������� �� ������� ������� � ���������������
template <typename T>
int id_availability(std::unordered_map<int, T> data, std::string user_msg) {

	while (true) {

		int research_id = input_value(user_msg, 0, 1000);

		if (research_id == 0) {
			break;
		}

		if (data.count(research_id) != 0) {
			return research_id;
		}
	}
	return -1;
}

class utils
{
};

