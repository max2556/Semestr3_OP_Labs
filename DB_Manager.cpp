#include <iostream>
#include <algorithm>

#include "DB_Manager.h"
#include "Sort.hpp"

constexpr auto _READ_WRITE = std::fstream::out | std::fstream::in;
constexpr auto _WRITE = std::fstream::out;

DB_Manager* DB_Manager::instance = 0;

void DB_Manager::open_database() {
	open_database(DATABASE);
}

void DB_Manager::open_database(const std::string& file_name)
{
	file_stream.open(file_name, _WRITE);

	if (file_stream.fail())
	{
		std::cout << "Cannot open or create file: " << file_name << ";" << std::endl;
		std::cout << "Try again with other file! \n ";

		return;
	}
}

bool DB_Manager::YN_Dialog()
{
	std::cout << "Y - yes |  N - no" << std::endl;

	char result;
	std::cin >> result;

	return std::tolower(result) == 'y';
}

std::vector<std::string> DB_Manager::read_all()
{
	std::vector<std::string> result;
	file_stream.open(DATABASE, _READ_WRITE);
	if (file_stream.fail()) std::cout << "Something went wrong! \n";


	std::string line;
	while(std::getline(file_stream, line))
		result.push_back(line);
	

	file_stream.close();
	return result;
}

std::vector<std::string> DB_Manager::search(Record::WeekDay target) {
	auto lines = read_all();
	std::vector<Record> records;
	std::vector<std::string> result;

	for (auto& line : lines) {
		auto rec = Record(line);
		if (rec.day == target)
			result.push_back(rec.to_string());
	}

	std::fstream fs(SEARCHBASE);
	if (fs.good())
		for (auto& line : result)
			fs.write(line.c_str(), line.size());

	return result;
}

void DB_Manager::add_record(Record&& record)
{
	auto s = record.to_string();

	file_stream.open(DATABASE, std::fstream::app);
	if (file_stream.fail()) std::cout << "Something went wrong! \n";

	file_stream << s;
	file_stream.close();
}

Record DB_Manager::create_record()
{
	Record new_record;
	std::cout << "Последовательно введите ФИО, специальность, кабинет, время и день работы \n";
	
	
	std::cout << "Введите ФИО: ";
	std::getline(std::cin, new_record.FIO);
	std::getline(std::cin, new_record.FIO);
	new_record.set_specialization();

	std::cout << "Введите номер кабинета: ";
	std::cin >> new_record.cabinet_number;
	new_record.set_time();
	new_record.set_day();

	return new_record;
}

void DB_Manager::remove_line(size_t index)
{
	std::string result;
	auto all = read_all();
	auto it = all.begin();
	it += (index - 1u);
	all.erase(it);

	for (auto line : all)
		result.append(line + '\n');

	file_stream.open(DATABASE, _WRITE);
	file_stream.write(result.c_str(), result.size());
	file_stream.close();
}

size_t DB_Manager::size_of_base()
{
	std::ifstream f(DATABASE);
	std::string unuse;
	size_t count = 0;
	
	while (std::getline(f, unuse))
		count++;
		
	f.close();
	return count;
}

Record DB_Manager::get_record(size_t index)
{
	file_stream.open(DATABASE, std::fstream::in);
	GotoLine(index);

	std::string line;
	std::getline(file_stream, line);

	file_stream.close();
	return Record(line);
}

void DB_Manager::change_line(size_t index, const std::string& line)
{
	std::string result;
	auto all = read_all();
	std::replace(all.begin(), all.end(), all[index-1], line+'\n');

	for (auto l : all)
		result.append(l);

	file_stream.open(DATABASE, _WRITE);
	file_stream.write(result.c_str(), result.size());
	file_stream.close();
}

void DB_Manager::sort_name()
{
	auto lines = read_all();
	std::vector<Record> records;

	for (auto l : lines)
		records.push_back(Record(l));

	recordsSort(
		records,
		[&](Record& a, Record& b)->bool {
			return a.FIO < b.FIO;
		}
	);

	std::string result;

	for (auto r : records)
		result.append(r.to_string());

	file_stream.open(DATABASE, _WRITE);
	file_stream.write(result.c_str(), result.size());
	file_stream.close();
}



