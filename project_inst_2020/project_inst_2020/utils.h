#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "trumpet.h"
#include "ks.h"

using namespace std;

// Меню для составляющей ЛР с сетью
void network_menu();

// Функция по проверке вводимого типа данных
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


// Функция по удалениию элементов
template <typename T1>
void delete_object(unordered_map<int, T1>& active_element) {

	int id = input_value("Идентификатор удаляемого объекта: ", 0, 1000);

	if (active_element.count(id) == 0) {
		cout << "Проверьте идентификатор, объекта с заданным идентификатором не существует" << endl << endl;
	}
	else {
		active_element.erase(id);
		cout << "Объект успешно удален ... " << endl << endl;
	}

}


// Проверка на наличие объекта с идентификатором
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

