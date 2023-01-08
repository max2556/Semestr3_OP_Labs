#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <optional>
#include <filesystem>
#include "Record.hpp"


std::optional<std::string> current_db_filename = std::nullopt;
std::filesystem::path search_db_path = "search.db";


void print_db();
void create_record();
void sort_by_name();
void sort_by_cabinet();
void search();

//Пытается получить значение с клавиатуры от left до right, включая обе границы
int pick_in_range(int left, int right)
{
	size_t index = 0;
	do {
		index = pick_result();
	} while (index > right || index < left);
	return index;
}

//Пытается получить число из консоли
int pick_result() {
	int res;
	do {
		std::cin >> res;
	} while (std::cin.fail());
	std::cin.ignore();
	std::cin.clear();
	return res;
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

void search() {
	std::cout << "Выберите день недели: \n";

	std::ifstream in_stream(current_db_filename.value(), std::ios::binary);
	std::ofstream out_stream(search_db_path, std::ios::binary);


	size_t i = 0;
	for (auto it = Record::Days.begin(); it != Record::Days.end(); ++i, ++it)
	{
		std::cout << i + 1 << " - " << it->second << std::endl;
	}

	int input_i = 0;
	Record::WeekDay input = Record::WeekDay::Monday;
	std::cin >> input_i;
	input = static_cast<Record::WeekDay>(input_i);

	Record* temp = nullptr;
	while (in_stream.read(reinterpret_cast<char*>(temp), sizeof(Record)))
	{
		if (temp->day == input) {
			out_stream.write(reinterpret_cast<char*>(temp), sizeof(Record));
		}
	}
}

void sort_by_name()
{
	std::fstream io_stream(current_db_filename.value(), std::ofstream::binary);

	std::size_t records_count = std::filesystem::file_size(current_db_filename.value()) / sizeof(Record);
	Record* temp1;
	Record* temp2;
	for (std::size_t i = 0; i < records_count - 1; i++)
	{
		for (std::size_t j = 0; j + 1 < records_count - i; j++)
		{
			io_stream.seekg(j * sizeof(Record));
			io_stream.read(reinterpret_cast<char*>(temp1), sizeof(Record));
			io_stream.read(reinterpret_cast<char*>(temp2), sizeof(Record));

			if (temp1->FIO > temp2->FIO) {
				io_stream.seekp(j * sizeof(Record));
				io_stream.write(reinterpret_cast<char*>(temp2), sizeof(Record));
				io_stream.write(reinterpret_cast<char*>(temp1), sizeof(Record));
			}
		}
	}
}

void sort_by_cabinet()
{
	std::fstream io_stream(current_db_filename.value(), std::ofstream::binary);

	std::size_t records_count = std::filesystem::file_size(current_db_filename.value()) / sizeof(Record);
	Record* temp1;
	Record* temp2;
	for (std::size_t i = 0; i < records_count - 1; i++)
	{
		for (std::size_t j = 0; j + 1 < records_count - i; j++)
		{
			io_stream.seekg(j * sizeof(Record));
			io_stream.read(reinterpret_cast<char*>(temp1), sizeof(Record));
			io_stream.read(reinterpret_cast<char*>(temp2), sizeof(Record));

			if (temp1->cabinet_number > temp2->cabinet_number) {
				io_stream.seekp(j * sizeof(Record));
				io_stream.write(reinterpret_cast<char*>(temp2), sizeof(Record));
				io_stream.write(reinterpret_cast<char*>(temp1), sizeof(Record));
			}
		}
	}
}

void choose_workflow(int res) {
	static const std::unordered_map<int, void(*)()> workflows =
	{
		{1, print_db},
		{2, create_record},
		{3, sort_by_name},
		{4, sort_by_cabinet},
		{5, search}
	};

	workflows.at(res)();
}

void print_db()
{
	if (!current_db_filename.has_value()) {
		std::cout << "Нельзя" << std::endl;
		return;
	}

	std::ifstream in_stream(current_db_filename.value());
	std::string line;
	while (std::getline(in_stream, line))
	{
		std::cout << line;
	}
}

void create_record()
{
	if (!current_db_filename.has_value()) {
		std::cout << "Нельзя" << std::endl;
		return;
	}

	std::ofstream out_stream(current_db_filename.value(), std::ofstream::binary);

	Record new_record;
	out_stream << reinterpret_cast<char*>(&new_record);
}

int main()
{
	setlocale(LC_ALL, "ru");

	std::string db_filename = "default_base.txt";
	std::cout << "Введите файл базы" << std::endl;
	std::cin >> db_filename;
	current_db_filename = db_filename;

	if (!std::filesystem::exists(db_filename))
		std::ofstream{ db_filename };

	int result = -1;
	while (result != 0)
	{
		std::cout <<
			"Выберите действие: \n"
			"1 - Прочитать базу\n"
			"2 - Добавить запись в базу\n"
			"3 - Отсортировать по имени \n"
			"4 - Отсортировать по кабинету \n"
			"5 - Поиск по дню недели \n"
			"0 - Выход\n";

		result = pick_in_range(0, 6);
		choose_workflow(result);
	}
}
