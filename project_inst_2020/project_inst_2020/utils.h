#pragma once

using namespace std;

// ������� �� �������� ��������� ���� ������
template <typename T>
T input_check(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "--- ������������ ����. ��������� ����: ";
	}

	return x;
}