#include <iostream>
#include <unordered_map>
#include <fstream>

#include "utils.h"
#include "trumpet.h"
#include "ks.h"
#include "gas_network.h"
#include "with_files_tasks.h"
#include "editor.h"
#include "another_features.h"
#include "filters.h"

using namespace std;


// Инициализация сети
gas_network::gas_network() {
	NetworkExist = false;
	cycle_found = false;
}


// Создаем соединения
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


// Создаем сеть
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


// Вывод созданной сети
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


// Алгоритм поиска в глубину
void gas_network::DFS(int start, vector<int>& color, stack <int>& answer_stack)
{
	color[start] = 1;
	for (const auto& ver : mGtsKs)
	{
		if (network[make_pair(start, ver.first)] != 0 && (color[ver.first] == 0))
		{
			DFS(ver.first, color, answer_stack);
		}
		else if (network[make_pair(start, ver.first)] != 0 && ((color[ver.first] == 1) || (color[ver.first] == 2)))
			cycle_found = true;
	}
	color[start] = 2;
	answer_stack.push(start);
}


// Топологическая сортировка графа
void gas_network::topological_sort(const unordered_map<int, trumpet>& Pipeline_s)
{
	if (NetworkExist)
	{
		stack <int> answer_stack;
		vector<int> color;
		unordered_map<int, int> answer;
		color.clear();
		answer.clear();
		color.resize(GtsKs.size());
		for (const auto& ver : mGtsKs)
			(color[ver.first] == 0);
		while (!answer_stack.empty())
			answer_stack.pop();
		int koren = -1;
		for (const auto& line : mGtsKs)
		{
			int summa = 0;
			for (const auto& column : mGtsKs)
			{
				summa += network[make_pair(column.first, line.first)];
			}
			bool not_isolated = false;
			for (const auto& p : Pipeline_s)
			{
				if ((p.second.to == line.second) || (p.second.from == line.second))
					not_isolated = true;
			}
			if ((summa == 0) && (not_isolated == true))
			{
				koren = line.first;
				break;
			}
		}
		if (koren == -1)
		{
			cout << "\nТопологическая сортировка невозможна, тк граф содержит цикл.\n";
			return;
		}
		else
		{
			DFS(koren, color, answer_stack);
			if (cycle_found)
			{
				cout << "\nТопологическая сортировка невозможна, тк граф содержит цикл.\n";
				return;
			}
			else
			{
				int numeric = 1;
				while (!answer_stack.empty())
				{
					auto iter = mGtsKs.find(answer_stack.top());
					answer.insert(pair<int, int>(numeric, iter->second));
					answer_stack.pop();
					numeric++;
				}
				cout << "\nТопологическая сортировка выполнена:\n";
				for (const auto& sort : answer)
					cout << sort.first << " - " << sort.second << endl;
			}
		}
	}
	else cout << "Сеть еще не была создана.\n";
}


void gas_network::save_data(const unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s)
{
	if (NetworkExist)
	{
		cout << "Введите наименование файла, в которых хотите записать данные:     ";
		string str;
		cin >> str;

		ofstream fout;
		fout.open(string(str) + ".txt", ios::out);
		if (fout.is_open())
		{
			fout << GtsPipe.size() << endl;
			fout << GtsKs.size() << endl;
			for (const auto& pipe : GtsPipe)
				fout << pipe << endl;
			for (const auto& ks : GtsKs)
				fout << ks << endl;
			for (const auto& pipe : GtsPipe)
			{
				auto IterPipe = Pipeline_s.find(pipe);
				fout << IterPipe->second;
			}
			for (const auto& ks : GtsKs)
			{
				auto IterKs = Ks_s.find(ks);
				fout << IterKs->second;
			}
			fout.close();
			cout << "Данные сохранены ...\n";
		}
		else cout << "Проверьте наименование файла, открыть не удалось ...\n";
	}
	else cout << "Для начала создайте ГТС ...\n";
}

void gas_network::load_data(unordered_map<int, trumpet>& Pipeline_s, unordered_map<int, ks>& Ks_s)
{
	cout << "Введите наименование файла, из которого хотите извлечь данные:     ";
	string str;
	cin >> str;

	ifstream fin;
	fin.open(string(str) + ".txt", ios::in);
	if (fin.is_open())
	{
		Pipeline_s.erase(Pipeline_s.begin(), Pipeline_s.end());
		Ks_s.erase(Ks_s.begin(), Ks_s.end());
		int numKs, numPipes;
		fin >> numPipes;
		fin >> numKs;
		for (int i = 1; i <= numPipes; i++)
		{
			int prom;
			fin >> prom;
			GtsPipe.emplace(prom);
		}
		for (int i = 1; i <= numKs; i++)
		{
			int prom;
			fin >> prom;
			GtsKs.emplace(prom);
		}
		while (numPipes--)
		{
			trumpet p;
			fin >> p;
			Pipeline_s.insert(pair<int, trumpet>(p.GetId(), p));
		}
		while (numKs--)
		{
			ks k;
			fin >> k;
			Ks_s.insert(pair<int, ks>(k.GetId(), k));
		}
		fin.close();
		cout << "Данные загружены ...\n";
	}
	else cout << "Проверьте наименование файла, открыть не удалось ...\n";
}


void gas_network::KsDelChanges(int id, unordered_map <int, trumpet>& Pipeline_s)
{
	for (auto IterKs = GtsKs.begin(); IterKs != GtsKs.end();)
	{
		if (*IterKs == id)
		{
			GtsKs.erase(IterKs++);
			for (auto& p : Pipeline_s)
			{
				if ((p.second.from == id) || (p.second.to == id))
				{
					p.second.to = 0;
					p.second.from = 0;
					for (auto IterPipe = GtsPipe.begin(); IterPipe != GtsPipe.end();)
					{
						if (*IterPipe == p.second.GetId())
							GtsPipe.erase(IterPipe++);
						else
							IterPipe++;

					}
				}
			}
		}
		else
			IterKs++;
	}
}

void gas_network::PipeDelChanges(int id)
{
	for (auto IterPipe = GtsPipe.begin(); IterPipe != GtsPipe.end();)
	{
		if (*IterPipe == id)
			GtsPipe.erase(IterPipe++);
		else
			IterPipe++;
	}
}


void gas_network::way_founder(int vertex, stack<int>& way, const vector <int>& distance)
{
	way.push(vertex);
	if (distance[vertex] == 0)
	{
		return;
	}
	else
		for (int i = 0; i <= (int)GtsKs.size() - 1; i++)
		{
			if (distance[vertex] == network[make_pair(i, vertex)])
			{
				way.push(i);
				return;
			}
			else if ((distance[vertex] - network[make_pair(i, vertex)] == distance[i]) && i != vertex)
				way_founder(i, way, distance);
		}
}

void gas_network::short_dist()
{
	if (NetworkExist)
	{
		int start = vertex_founder("\nВведите от какой КС ищем путь: ");
		int end = vertex_founder("\nВведите к которой КС ищем путь: ");
		if ((start == -1) || (end == -1))
		{
			cout << "Введенное число недействительно.\n";
			return;
		}
		else
		{
			vector <int> distance;
			vector <int> visited;
			stack <int> way;
			while (!way.empty())
				way.pop();
			distance.reserve(GtsKs.size());
			visited.reserve(GtsKs.size());
			for (int i = 0; i <= (int)GtsKs.size() - 1; i++)
			{
				distance.push_back(INT_MAX);
				visited.push_back(0);
			}
			int indexstart = 0;
			int indexend = 0;
			for (const auto& m : mGtsKs)
			{
				if (m.second == start)
					indexstart = m.first;
				if (m.second == end)
					indexend = m.first;
			}
			distance[indexstart] = 0;
			int index = 0;
			for (int count = 0; count < (int)GtsKs.size() - 1; count++)
			{
				int min = INT_MAX;
				for (int i = 0; i < (int)GtsKs.size(); i++)
					if (!visited[i] && distance[i] <= min)
					{
						min = distance[i];
						index = i;
					}
				visited[index] = 1;
				for (int i = 0; i < (int)GtsKs.size(); i++)
					if (!visited[i] && network[make_pair(index, i)] && distance[index] != INT_MAX &&
						distance[index] + network[make_pair(index, i)] < distance[i])
						distance[i] = distance[index] + network[make_pair(index, i)];
			}
			cout << "\nВычисленный кратчайший путь:\n\n";
			if (distance[indexend] != INT_MAX)
			{
				cout << start << " > " << end << " = " << distance[indexend];
				cout << endl;
				if (distance[indexend] != 0)
				{
					cout << "Путь: ";
					way_founder(indexend, way, distance);
					auto iter = mGtsKs.find(way.top());
					way.pop();
					cout << iter->second;
					while (!way.empty())
					{
						iter = mGtsKs.find(way.top());
						way.pop();
						cout << "->" << iter->second;
					}
					cout << endl;
				}
				cout << endl;
			}
			else cout << start << " > " << end << " = " << "Пути не существует" << endl << endl;
		}
	}
	else cout << "Для начала создается ГТС.\n";
}

int gas_network::vertex_founder(string str)
{
	vector <int> vershina;
	vershina.reserve(GtsKs.size());
	for (const auto& v : GtsKs)
		vershina.push_back(v);
	int vertex = input_value(str, 1, ks::MaxID);
	auto got = find(vershina.begin(), vershina.end(), vertex);
	if (got == vershina.end())
	{
		return -1;
	}
	return vertex;
}