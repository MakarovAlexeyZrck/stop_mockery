#pragma once

#include <iostream>
#include <string>

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