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

trumpet::~trumpet() {
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