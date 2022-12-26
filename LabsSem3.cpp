#include <string>
#include <fstream>
#include <iostream>

#include "DB_Manager.h"

int pick_result() {
	int res;
	bool complete = false;
	while (!complete) {
		try {
			std::cin >> res;
			complete = true;
		}
		catch (const std::exception&) {
			complete = false;
		}
	}
	return res;
}

void sort_db() {
	std::cout << "Сортировать по имени? \n";

	std::cout << "Y - yes |  N - no" << std::endl;
	char result;
	std::cin >> result;
	bool res = std::tolower(result) == 'y';
	
	if (!res) return;

	DB_Manager::Instance()->sort_name();
}

void show_db(std::vector<std::string>&& lines) {
	if (lines.size() == 0) {
		std::cout << "База пуста \n";
		return;
	}
	std::string result =
		"==========================================================================\n"
		"=      ФИО      = Специализация =  Кабинет  =     Время     =    День    =\n"
		"=     Врача     =               =           = начала приёма =   недели   =\n"
		"==========================================================================\n";
	//    -------15------ -------15------ ----11----- -------15------ -----12-----
	for (std::string& record : lines)
		result.append(record + '\n');

	result.append("==========================================================================\n");
	std::cout << result;
}

void remove_line() {
	size_t max = DB_Manager::Instance()->size_of_base();
	if (max == 0) {
		std::cout << "База пуста! \n";
		return;
	}
	std::cout << "Выберите строку для удаления от 1 до " << max << std::endl;


	size_t index = 0;
	while (index > max || index < 1)
		index = pick_result();

	DB_Manager::Instance()->remove_line(index);
}

void modify_line() {
	size_t max = DB_Manager::Instance()->size_of_base();
	if (max == 0) {
		std::cout << "База пуста! \n";
		return;
	}
	std::cout << "Выберите строку для изменения от 1 до " << max << std::endl;
	size_t line_index = 0;
	while (line_index > max || line_index < 1)
		line_index = pick_result();


	std::cout << "Выберите поле для изменения: \n";
	std::cout << "0 - ФИО: \n";
	std::cout << "1 - Специальность: \n";
	std::cout << "2 - Кабинет: \n";
	std::cout << "3 - Время: \n";
	std::cout << "4 - День: \n";

	size_t index = -1;
	while (index > 4 || index < 0)
		index = pick_result();

	Record record = DB_Manager::Instance()->get_record(line_index);

	switch (index) {
	case 0:
		std::cout << "Старое значение: " << record.FIO << std::endl;
		std::cout << "Введите новое: ";
		std::cin >> record.FIO;
		break;
	case 1:
		std::cout << "Старое значение: " << record.specialization << std::endl;
		std::cout << "Введите новое: ";
		record.set_specialization();
		break;
	case 2:
		std::cout << "Старое значение: " << record.cabinet_number << std::endl;
		std::cout << "Введите новое: ";
		std::cin >> record.cabinet_number;
		break;
	case 3:
		std::cout << "Старое значение: " << record.work_start.to_string() << std::endl;
		std::cout << "Введите новое: ";
		record.set_time();
		break;
	case 4:
	default:
		std::cout << "Старое значение: " << record.Days[record.day] << std::endl;
		std::cout << "Введите новое: ";
		record.set_day();
		break;
	}

	DB_Manager::Instance()->change_line(line_index, record.to_string());
}

void search() {
	std::cout << "Выберите день недели: \n";

	Record r;
	size_t i = 0;
	for (auto it = r.Days.begin(); it != r.Days.end(); ++i, ++it)
	{
		std::cout << i + 1 << " - " << it->second << std::endl;
	}

	int input_i = 0;
	Record::WeekDay input = Record::WeekDay::Monday;
	std::cin >> input_i;
	input = static_cast<Record::WeekDay>(input_i);

	show_db(DB_Manager::Instance()->search(input));
}

void choose_workflow(int res) {
	switch (res)
	{
	case 1:
		DB_Manager::Instance()->open_database();
		break;
	case 2:
		show_db(DB_Manager::Instance()->read_all());
		break;
	case 3:
		DB_Manager::Instance()->add_record(DB_Manager::Instance()->create_record());
		break;
	case 4:
		remove_line();
		break;
	case 5:
		modify_line();
		break;
	case 6:
		sort_db();
		break;
	case 7:
		search();
		break;

	default:
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	int result = -1;
	while (result != 0)
	{
		std::cout <<
			"Выберите действие: \n"
			"1 - Открыть базу \n"
			"2 - Прочитать базу\n"
			"3 - Добавить запись в базу\n"
			"4 - Убрать строку из базы \n"
			"5 - Изменить строку в базе \n"
			"6 - Отсортировать по имени \n"
			"7 - Поиск по дню недели \n"
			"0 - Выход\n";

		result = pick_result();
		choose_workflow(result);
	}
}
