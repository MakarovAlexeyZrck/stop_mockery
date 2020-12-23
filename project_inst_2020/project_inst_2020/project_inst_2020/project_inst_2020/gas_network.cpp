#include "gas_network.h"
#include "utils.h"
#include <algorithm> 

gas_network::gas_network()
{
	NetworkExist = false;
	cycle_found = false;
}

void gas_network::CreateConnection(unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s)
{
	if ((!Pipeline_s.size()) or (Ks_s.size() < 2))
		cout << "Добавьте элементы для создания ГТС.\n ";
	else
	{
		auto IterObj1 = Ks_s.find(input_value(
			"\n1. Введите id КС от которого протягиваем связь: ", 1, ks::MaxID));
		auto IterObj2 = Pipeline_s.find(input_value(
			"\n2. Введите id трубы: ", 1, trumpet::MaxID));
		auto IterObj3 = Ks_s.find(input_value(
			"\n3. Введите id КС к которой протягиваем связь: ", 1, ks::MaxID));
		if (IterObj1 == Ks_s.end())
		{
			cout << "КС с данным идентификатором не существует.\n";
			return;
		}
		if ((IterObj2->second.is_broken == true) or (IterObj2 == Pipeline_s.end()))
		{
			cout << "Труба недоступна для связи.\n";
			return;
		}
		if (IterObj2->second.from != 0)
		{
			cout << "Эта труба уже занята.\n";
			return;
		}
		if ((IterObj1->second.GetId() == IterObj3->second.GetId()) or (IterObj3 == Ks_s.end()))
		{
			cout << "КС недоступно.\n";
			return;
		}
		GtsKs.insert(IterObj1->second.GetId());
		GtsPipe.insert(IterObj2->second.GetId());
		GtsKs.insert(IterObj3->second.GetId());
		IterObj2->second.from = IterObj1->second.GetId();
		IterObj2->second.to = IterObj3->second.GetId();
	}
}

void gas_network::CreateNetwork(const unordered_map<int, trumpet>& Pipeline_s)
{
	if (!GtsKs.size() && !GtsPipe.size())
	{
		cout << "Для начала создайте соединения.\n";
		return;
	}
	int numKs = 0;
	int numPipes = 0;
	mGtsKs.clear();
	mGtsPipe.clear();
	network.clear();
	throughputs.clear();

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
			throughputs.emplace(make_pair(line.first, column.first), 0);
		}
	}
	for (const auto& obj : mGtsPipe)
	{
		int line = 0;
		int column = 0;
		for (const auto& matr : mGtsKs)
		{
			if (matr.second == obj.second.from)
				line = matr.first;
			if (matr.second == obj.second.to)
				column = matr.first;
		}
		network.erase(network.find(make_pair(line, column)));
		throughputs.erase(throughputs.find(make_pair(line, column)));
		network.emplace(make_pair(line, column), obj.second.Weight);
		throughputs.emplace(make_pair(line, column), obj.second.Throughput);
	}
	NetworkExist = true;
	cout << "ГТС обнослена/добалена\n";
}

void gas_network::PrintTable(map<pair<int, int>, int>& table)
{
	cout << "\n ";
	for (const auto& column : mGtsKs)
		cout << "\t" << column.second;
	for (const auto& line : mGtsKs)
	{
		cout << endl << line.second;
		for (const auto& column : mGtsKs)
		{
			cout << "\t" << table[make_pair(line.first, column.first)];
		}
	}
	cout << "\n\n";
}

void gas_network::PrintNetwork()
{
	if (NetworkExist)
	{
		cout << "\nСмежная матрица весов:\n";
		PrintTable(network);
		cout << "\nСмежная матрица пропускных способностей:\n";
		PrintTable(throughputs);
	}
	else cout << "Для начала создайте ГТС.\n";
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
				if ((p.second.to == id) || (p.second.from == id))
				{
					p.second.from = 0;
					p.second.to = 0;
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

void gas_network::SaveNetwork(const unordered_map<int, trumpet>& Pipeline_s, const unordered_map<int, ks>& Ks_s)
{
	if (NetworkExist)
	{
		ofstream fout;
		fout.open("flow2.txt", ios::out);
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
			cout << "Выполнено.\n";
		}
		else cout << "Ошибка.";
	}
	else cout << "Для начала создайте ГТС.\n";
}

void gas_network::LoadNetwork(unordered_map<int, trumpet>& Pipeline_s, unordered_map<int, ks>& Ks_s)
{
	ifstream fin;
	fin.open("flow2.txt", ios::in);
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
		cout << "Выполнено.\n";
	}
	else cout << "Ошибка.\n";
}

void gas_network::DFS(int start, vector<int>& color, stack <int>& answer_stack)
{
	color[start] = 1;
	for (const auto& ver : mGtsKs)
	{
		if (network[make_pair(start, ver.first)] != 0 && (color[ver.first] == 0))
		{
			DFS(ver.first, color, answer_stack);
		}
		else if (network[make_pair(start, ver.first)] != 0 && (color[ver.first] == 1))
			cycle_found = true;
	}
	color[start] = 2;
	answer_stack.push(start);
}

void gas_network::TopolSort(const unordered_map<int, trumpet>& Pipeline_s)
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
			cout << "\nНевозможно выполнить оопологическую сортировку\n";
			return;
		}
		else
		{
			DFS(koren, color, answer_stack);
			if (cycle_found)
			{
				cout << "\nНевозможно выполнить оопологическую сортировку.\n";
				return;
			}
			else
			{
				int i = 1;
				while (!answer_stack.empty())
				{
					auto iter = mGtsKs.find(answer_stack.top());
					answer.insert(pair<int, int>(i, iter->second));
					answer_stack.pop();
					i++;
				}
				cout << "\nТопрологическая сортировка выполнена:\n";
				for (const auto& sort : answer)
					cout << sort.first << " - " << sort.second << endl;
			}
		}
	}
	else cout << "TДля начала создайте Гтс.\n";
}

void gas_network::FindWay(int vertex, stack<int>& way, const vector <int>& distance)
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
				FindWay(i, way, distance);
		}
}

void gas_network::ShortDist()
{
	if (NetworkExist)
	{
		int start = FindVertex("\nВведите стартовую КС: ");
		int end = FindVertex("\nведите финальную КС: ");
		if ((start == -1) || (end == -1))
		{
			cout << "Вершина задана неверно.\n";
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
			cout << "\nКратчайший путь:\n\n";
			if (distance[indexend] != INT_MAX)
			{
				cout << start << " > " << end << " = " << distance[indexend];
				cout << endl;
				if (distance[indexend] != 0)
				{
					cout << "Путь: ";
					FindWay(indexend, way, distance);
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
			else cout << start << " > " << end << " = " << "построить путь невозможно" << endl << endl;
		}
	}
	else cout << "Для начала постройте ГТС.\n";
}

int gas_network::FindVertex(string str)
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

int gas_network::BFS(int stvertex, int endvertex, vector <int>& way, map <pair<int, int>, int>& flow)
{
	vector<int> color;
	color.clear();
	color.resize(GtsKs.size());
	for (int i = 0; i <= (int)GtsKs.size() - 1; i++)
		color[i] = 0;
	queue<int> q;
	q.push(stvertex);
	color[stvertex] = 1;
	way[stvertex] = -1;
	while (!q.empty())
	{
		int prom = q.front();
		color[prom] = 2;
		q.pop();
		for (int vershina = 0; vershina <= (int)GtsKs.size() - 1; vershina++)
		{
			if (color[vershina] == 0 && (throughputs[make_pair(prom, vershina)] - flow[make_pair(prom, vershina)]) > 0)
			{
				q.push(vershina);
				color[vershina] = 1;
				way[vershina] = prom;
			}
		}
	}
	if (color[endvertex] == 2)
		return 0;
	else
		return 1;
}

void gas_network::MaxFlow()
{
	if (NetworkExist)
	{
		int source = FindVertex("\nВведите стартовую КС: ");
		int stock = FindVertex("\nВведите стартовую КС: ");
		if ((source == -1) || (stock == -1) || (stock == source))
			cout << "Вершина введена некоректно.\n";
		else
		{
			int maxflow = 0;
			vector <int> way;
			way.clear();
			way.resize(GtsKs.size());
			map <pair<int, int>, int> flow;
			for (const auto& line : mGtsKs)
			{
				for (const auto& column : mGtsKs)
				{
					flow.emplace(make_pair(line.first, column.first), 0);
				}
			}
			int indexsource = 0;
			int indexstock = 0;
			for (const auto& m : mGtsKs)
			{
				if (m.second == source)
					indexsource = m.first;
				if (m.second == stock)
					indexstock = m.first;
			}
			while (!BFS(indexsource, indexstock, way, flow))
			{
				int lyambda = INT_MAX;
				int vershina = indexstock;
				while (way[vershina] != -1)
				{
					lyambda = min(lyambda, throughputs[make_pair(way[vershina], vershina)] - flow[make_pair(way[vershina], vershina)]);
					vershina = way[vershina];
				}
				vershina = indexstock;
				while (way[vershina] != -1)
				{
					flow[make_pair(vershina, way[vershina])] -= lyambda;
					flow[make_pair(way[vershina], vershina)] += lyambda;
					vershina = way[vershina];
				}
				maxflow += lyambda;
			}
			cout << "\nМаксимальный поток между " << source << " и " << stock << " равен: " << maxflow << endl;
		}
	}
	else cout << "Для начала создайте ГТС.\n";
}
