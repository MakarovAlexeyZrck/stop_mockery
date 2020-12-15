#include <iostream>

#include "utils.h"

using namespace std;


// Печатаем меню в консоль
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
		 << "0. Выйти" << "\n"
		 << "--- Введите действие: ";
}

int main()
{
	// Русский язык в консоли
	setlocale(LC_ALL, "Russian");

    // Управление программой
    while (1) {

		// Вывод меню действий
		print_menu();

		// Обработка ввода пользователя
		switch (input_check(0, 9))
		{

		case 0: {
			cout << "Пока" << endl;
			return 0;
		}

		case 1: {
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