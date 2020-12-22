#pragma once

void manual_add_elements(unordered_map<int, trumpet>& trumpets_f, unordered_map<int, ks>& ks_s_f);

// Просмотр всех элементов
template <typename T>
void show_elements(string object_name, const T data) {

	if (data.size() == 0) {
		cout << object_name << " ещё не добавлены" << endl;
	}
	else {
		for (const auto& item : data) {
			cout << item.second << endl;
		}
	}
}

class another_features
{
};

