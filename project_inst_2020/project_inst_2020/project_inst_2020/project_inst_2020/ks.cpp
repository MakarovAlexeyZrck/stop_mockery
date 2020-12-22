#include "ks.h"
#include "utils.h"
#include <limits>

using namespace std;


int ks::MaxID = 0;


ks::ks() {
	id = ++MaxID;
	string ks_name = "Name";
	count_workshops = 0;
	active_workshops = 0;
	efficiency = 0;
}

void ks::edit_ks()
{
	active_workshops = input_value("������� ���-�� ����� � ������: ", 0, count_workshops);
}

int ks::GetId() const
{
	return id;
}


std::istream& operator >> (std::istream& in, ks& cs)
{
	cout << "������� ������������ ��: ";
	cin.get();
	getline(cin, cs.ks_name);

	cs.count_workshops = input_value("������� ����� ����� ��: ", 0, 100);
	cs.active_workshops = input_value("������� ����� �������� ����� ��: ", 0, cs.count_workshops);
	cs.efficiency = input_value("������� ������������� ��: ", 0, 100);

	cout << "����� �� �������" << endl << endl;

	return in;
}

std::ostream& operator << (std::ostream& out, const ks& cs)
{
	out << "��: #" << cs.id << endl
		<< "������������ ��: " << cs.ks_name << endl
		<< "����� �����: " << cs.count_workshops << endl
		<< "����� ����� � ������: " << cs.active_workshops << endl
		<< "������������� ��: " << cs.efficiency << endl << endl;

	return out;

}


ofstream& operator<<(ofstream& fout, const ks& k)
{
	fout << k.id << endl << k.ks_name << endl << k.count_workshops << endl << k.active_workshops << endl << k.efficiency << endl;
	return fout;
}

ifstream& operator>>(ifstream& fin, ks& k)
{
	fin >> k.id;
	fin.ignore(1, '\n');
	getline(fin, k.ks_name);
	fin >> k.count_workshops >> k.active_workshops >> k.efficiency;
	return fin;
}