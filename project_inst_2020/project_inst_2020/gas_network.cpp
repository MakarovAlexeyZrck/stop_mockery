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
	int cs_from = id_availability(ks_data, "Введите id КС от которого прокоадываем трубу: ");
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

	bool was_found = false;
	for (auto i : used_trumpets) {
		if (trumpets_id_for_delete == i) {
			was_found = true;
			break;
		}
	}
}
