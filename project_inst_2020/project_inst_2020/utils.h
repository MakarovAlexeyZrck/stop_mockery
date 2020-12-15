#pragma once

using namespace std;

// Функция по проверке вводимого типа данных
template <typename T>
T input_check(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "--- Некорректный ввод. Повторите ввод: ";
	}

	return x;
}