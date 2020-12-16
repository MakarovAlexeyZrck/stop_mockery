#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "trumpet.h"
#include "ks.h"

using namespace std;

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

