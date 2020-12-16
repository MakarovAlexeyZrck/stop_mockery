#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "trumpet.h"
#include "ks.h"

using namespace std;

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
bool CheckByID(const T& p, unsigned int param) {
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

