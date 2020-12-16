#include "ks.h"
#include "utils.h"

using namespace std;


int ks::MaxID = 0;


ks::ks() {
	id = ++MaxID;
	string ks_name = "Name";
	count_workshops = 0;
	active_workshops = 0;
	efficiency = 0;
}


std::istream& operator>>(std::istream& in, ks& cs)
{
	cout << "������� ������������ ��: ";
	cin.get();
	getline(cin, cs.ks_name);

	cs.count_workshops = input_value("������� ����� ����� ��: ", 0, 100);
	cs.active_workshops = input_value("������� ����� �������� ����� ��: ", 0, cs.count_workshops);
	cs.efficiency = input_value("������� ������������� ��: ", 0, 100);

	return in;
}

std::ostream& operator<<(std::ostream& out, const ks& cs)
{
	out << "��: #" << cs.id << endl
		<< "������������ ��: " << cs.ks_name << endl
		<< "����� �����: " << cs.count_workshops << endl
		<< "����� ����� � ������: " << cs.active_workshops << endl
		<< "������������� ��: " << cs.efficiency << endl << endl;

	return out;
	// TODO: �������� ����� �������� return
}
