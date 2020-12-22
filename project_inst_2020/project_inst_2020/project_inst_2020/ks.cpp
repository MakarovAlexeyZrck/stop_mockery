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

void ks::edit_ks()
{
	active_workshops = input_value("Введите кол-во цехов в работе: ", 0, count_workshops);
}

int ks::GetId() const
{
	return id;
}


std::istream& operator >> (std::istream& in, ks& cs)
{
	cout << "Введите наименование КС: ";
	cin.get();
	getline(cin, cs.ks_name);

	cs.count_workshops = input_value("Введите число цехов КС: ", 0, 100);
	cs.active_workshops = input_value("Введите число активных цехов КС: ", 0, cs.count_workshops);
	cs.efficiency = input_value("Введите эффективность КС: ", 0, 100);

	cout << "Новая КС создана" << endl << endl;

	return in;
}

std::ostream& operator << (std::ostream& out, const ks& cs)
{
	out << "КС: #" << cs.id << endl
		<< "Наименование КС: " << cs.ks_name << endl
		<< "Число цехов: " << cs.count_workshops << endl
		<< "Число цехов в работе: " << cs.active_workshops << endl
		<< "Эффективность КС: " << cs.efficiency << endl << endl;

	return out;

}
