#include "gas_network.h"

#include <iostream>
#include <string>

using namespace std;

int gas_network::MaxID = 0;

gas_network::gas_network() {
	id = ++MaxID;
	network_name = "Unset";
	cout << "Введите имя вашей сети: " << endl;
	cin.get();
	getline(cin, network_name);
}

void gas_network::assign_name(const string& user_name)
{
	network_name = user_name;
}

void gas_network::assign_id(int network_id)
{
	id = network_id;
}

string gas_network::get_name()
{
	return network_name;
}

int gas_network::get_id()
{
	return id;
}

void gas_network::disassemble_pipes(std::unordered_map<int, trumpet>& trumpet_data, std::unordered_map<int, ks>& ks_data)
{
	int cs_from = id_availability(ks_data, "Введите id КС от которого проколадываем трубу: ");
	int cs_to = id_availability(ks_data, "Введите id КС к которому  прокладываем трубу: ");
	int used_trumpet_id = id_availability(trumpet_data, "Введите id используемой трубы: ");

	if (cs_from != -1 && cs_to != -1 && used_trumpet_id != -1) {
		if (trumpet_data[used_trumpet_id].from == 0 && trumpet_data[used_trumpet_id].to == 0) {

			trumpet_data[used_trumpet_id].from = cs_from;
			trumpet_data[used_trumpet_id].to = cs_to;

			used_trumpets.insert(used_trumpet_id);
			used_kss.insert(cs_from);
			used_kss.insert(cs_to);

		}
		else {
			cout << "Труба уже занята" << endl << endl;
		}
	}
	else {
		cout << "Объектов с введенными id не найдено" << endl << endl;
	}


}

void gas_network::delete_trumpet(std::unordered_map<int, trumpet>& trumpet_data)
{
	int trumpets_id_for_delete = id_availability(trumpet_data, "Введите id трубы, которую хотите отключить: ");

	// Поиск трубы 
	bool was_found = false;
	for (auto i : used_trumpets) {
		if (trumpets_id_for_delete == i) {
			was_found = true;
			break;
		}
	}

	if (trumpets_id_for_delete != -1 && was_found) {
		for (int i = 0; i < topo_matrix.size(); i++) {
			for (int j = 0; j < topo_matrix[i].size(); j++) {
				if (cs_matr_pos[i] == trumpet_data[trumpets_id_for_delete].from && cs_matr_pos[j] == trumpet_data[trumpets_id_for_delete].to) {
					topo_matrix[i][j] = 0;
					used_trumpets.erase(trumpets_id_for_delete);
				}
			}
		}
	}
	else {
		cout << "Нет соединений для трубы с данным id";
	}
}

void gas_network::sorted_matrix(unordered_map<int, trumpet>& trumpet_data)
{
	for (auto i : used_kss) {
		cs_matr_pos.push_back(i);
	}

	const int m_size = cs_matr_pos.size();
	topo_matrix.resize(m_size);

	for (int i = 0; i < m_size; i++) {
		topo_matrix[i].resize(m_size);

		for (int j = 0; j < m_size; j++) {
			for (auto p_id : used_trumpets) {
				topo_matrix[i][j] = (cs_matr_pos[i] && trumpet_data[p_id].to == cs_matr_pos[j]) ? trumpet_data[p_id].get_weight() : 0;
			}
		}
	}
}


void gas_network::Print_network() {
	cout << "Трубы: " << endl;
	for (auto p : used_trumpets) {
		cout << p << endl;
	}
	cout << "\nКомпрессорные станции: " << endl;

	for (auto cs : used_kss) {
		cout << cs << endl;
	}

	cout << "-------------------" << endl;
	cout << "После сортировки:" << endl;
	cout << "  ";
	for (int i = 0; i <= cs_matr_pos.size() - 1; i++) {
		cout << cs_matr_pos[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < cs_matr_pos.size(); i++) {
		cout << cs_matr_pos[i] << " ";
		for (int j = 0; j < cs_matr_pos.size(); j++) {
			cout << topo_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
