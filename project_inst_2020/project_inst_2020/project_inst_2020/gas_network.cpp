#include "gas_network.h"

#include <iostream>
#include <string>

using namespace std;


gas_network::gas_network() {
	NetworkExist = false;
	cycle_found = false;
}

void gas_network::create_connection(unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s)
{
	if ((!Pipeline_s.size()) or (Ks_s.size() < 2))
		cout << "Для начала выберите объекты для создания сети.\n ";
	else
	{
		auto ks_to = Ks_s.find(input_value("Введите id КС от которой делаем связь: ", 1, ks::MaxID));
		auto ks_from = Ks_s.find(input_value("Введите id КС к которой делаем связь: ", 1, ks::MaxID));

		auto current_trumpet = Pipeline_s.find(input_value("Введите id трубы, котрой соединяем КС: ", 1, trumpet::MaxID));


		if (ks_from == Ks_s.end())
		{
			cout << "Такой КС не существует.\n";
			return;
		}

		if ((current_trumpet->second.is_broken == true) or (current_trumpet == Pipeline_s.end()))
		{
			cout << "Трубы с заданным id не существует.\n";
			return;
		}

		if (current_trumpet->second.from != 0)
		{
			cout << "Эта труба уже используется.\n";
			return;
		}

		if ((ks_from->second.GetId() == ks_to->second.GetId()) or (ks_to == Ks_s.end()))
		{
			cout << "Нет КС с заданным id или введены два одинаковых id.\n";
			return;
		}

		GtsKs.insert(ks_from->second.GetId());
		GtsKs.insert(ks_to->second.GetId());
		GtsPipe.insert(current_trumpet->second.GetId());
		current_trumpet->second.from = ks_from->second.GetId();
		current_trumpet->second.to = ks_to->second.GetId();
	}
}


void gas_network::create_network(const unordered_map<int, trumpet>& Pipeline_s)
{
	int numKs = 0;
	int numPipes = 0;
	mGtsKs.clear();
	mGtsPipe.clear();
	network.clear();
	if (!GtsKs.size() && !GtsPipe.size())
	{
		cout << "Для начала выберите объекты для создания сети.\n";
		return;
	}

	for (const auto& obj : GtsKs)
	{
		mGtsKs.insert(pair<int, int>(numKs, obj));
		numKs++;
	}
	for (const auto& obj : GtsPipe)
	{
		auto Iter = Pipeline_s.find(obj);
		mGtsPipe.insert(pair<int, trumpet>(numPipes, Iter->second));
		numPipes++;
	}
	for (const auto& line : mGtsKs)
	{
		for (const auto& column : mGtsKs)
		{
			network.emplace(make_pair(line.first, column.first), 0);
		}
	}
	for (const auto& obj : mGtsPipe)
	{
		int line = 0;
		int column = 0;
		for (const auto& matr : mGtsKs)
		{
			if (matr.second == obj.second.to)
				line = matr.first;
			if (matr.second == obj.second.from)
				column = matr.first;
		}
		network.erase(network.find(make_pair(line, column)));
		network.emplace(make_pair(line, column), 1);
	}
	NetworkExist = true;
	cout << "Сеть создана ... \n";
}


void gas_network::show_network()
{
	if (NetworkExist)
	{
		cout << "\n ";
		for (const auto& column : mGtsKs)
			cout << " " << column.second;
		for (const auto& line : mGtsKs)
		{
			cout << endl << line.second;
			for (const auto& column : mGtsKs)
			{
				cout << " " << network[make_pair(line.first, column.first)];
			}
		}
		cout << "\n\n";
	}
	else cout << "Для начала создайте ГТС ...\n";
}


