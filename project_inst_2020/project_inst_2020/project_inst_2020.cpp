#include <iostream>
#include <unordered_map>

#include "utils.h"
#include "trumpet.h"

using namespace std;


// Печатаем главное меню в консоль
void print_menu() {

	cout << "1. Добавить трубу или КС" << endl
		 << "2. Просмотреть все объекты" << "\n"
		 << "3. Редактировать трубу/КС" << "\n"
		 << "4. Удалить трубу/КС" << "\n"
		 << "5. Фильтр для труб" << "\n"
		 << "6. Фильтр для КС" << "\n"
		 << "7. Редактировать трубы пакетно" << "\n"
		 << "8. Сохранить данные в файл" << "\n"
		 << "9. Загрузить данные из файла" << "\n"
		 << "0. Выйти" << endl;
}

// Печатаем вторичное меню в консоль
int print_additional_menu() {

	cout << "0. Главное меню" << endl
		 << "1. Труба" << endl
		 << "2. КС" << endl;

	int user_point;
	user_point = input_value("--- Введите действие: ", 0, 2);

	return user_point;
}

int main()
{

	// Хранение данных
	unordered_map<int, trumpet> trumpets;

	// Русский язык в консоли
	setlocale(LC_ALL, "Russian");

    // Управление программой
    while (1) {

		// Вывод меню действий
		print_menu();

		// Обработка ввода пользователя
		switch (input_value("--- Введите действие: ", 0, 9))
		{

		case 0: {
			cout << "Пока" << endl;
			return 0;
		}

		case 1: {
			int id = trumpet::MaxID;
			trumpets.emplace(id, trumpet());
			cin >> trumpets[id];
			break;
		}

		case 2: {
			break;
		}

		case 3: {
			break;
		}

		case 4: {
			break;
		}

		case 5: {
			break;
		}

		case 6: {
			break;
		}

		case 7: {
			break;
		}

		case 8: {
			break;
		}

		case 9: {
			break;
		}

		default:
			cout << "Действие не поддерживается" << endl;
		}
    }

}