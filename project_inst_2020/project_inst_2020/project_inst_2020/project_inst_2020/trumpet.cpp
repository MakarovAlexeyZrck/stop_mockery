#include "trumpet.h"
#include "utils.h"


using namespace std;
int trumpet::MaxID = 0;


trumpet::trumpet() {
	id = ++MaxID;
	length = 0;
	diameter = 0;
	is_broken = false;

	from = 0;
	to = 0;
}


void trumpet::trumpet_mode()
{
	is_broken = !is_broken;
}

ostream& operator << (ostream& out, const trumpet& t)
{
	out << "�����: #" << t.id << endl
		<< "����� �����: " << t.length << endl
		<< "������� �����: " << t.diameter << endl
		<< "������ �����: " << (t.is_broken ? "� �������!" : "� ������!") << endl;

	return out;
}


istream& operator >> (istream& in, trumpet& t) {

	cout << endl;

	t.length = input_value("������� ����� �����: ", 0.0, 10000.0);
	t.diameter = input_value("������� ������� �����: ", 0.0, 100.0);
	t.is_broken = false;

	cout << "����� ����� �������" << endl << endl;
	
	return in;
}


int trumpet::get_weight() {
	return length;
}

int trumpet::GetId() const
{
	return id;
}


ofstream& operator<<(ofstream& fout, const trumpet& p)
{
	fout << p.id << endl << p.length << endl << p.diameter << endl << p.is_broken << endl << p.to << endl << p.from << endl;
	return fout;
}

ifstream& operator>>(std::ifstream& fin, trumpet& p)
{
	fin >> p.id >> p.length >> p.diameter >> p.is_broken >> p.to >> p.from;
	return fin;
}