#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Time.h"

class Record
{
public:
	enum class Specialization : size_t
	{
		Therapist = 0,
		Optometrist = 1,
		Surgeon = 2,
		Dentist = 3,
		ENT_Doctor = 4,
		Other
	};
	enum class WeekDay
	{
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday,
		Sunday,
	};

public:
	std::unordered_map<Specialization, std::string> Specializations = {
		{Specialization::Therapist,   "��������"},
		{Specialization::Optometrist, "�������"},
		{Specialization::Surgeon,     "������"},
		{Specialization::Dentist,     "����������"},
		{Specialization::ENT_Doctor,  "���"},
	};
	std::unordered_map<WeekDay, std::string> Days = {
		{WeekDay::Monday,	  "�����������"},
		{WeekDay::Tuesday,	  "�������"},
		{WeekDay::Wednesday, "�����"},
		{WeekDay::Thursday,  "�������"},
		{WeekDay::Friday,	  "�������"},
		{WeekDay::Saturday,  "�������"},
		{WeekDay::Sunday,	  "�����������"},
	};

public:
	Record() {}
	explicit Record(std::string& line) {
		const char delimiter = '=';
		std::vector<std::string> fields;

		line = line.substr(1, line.size() - 1);

		//��������� ������ �� ����
		size_t ind = 0;
		do {
			ind = line.find(delimiter);
			std::string part = line.substr(0, ind);
			trim(part);

			fields.push_back(part);
			line = line.substr(ind+1, line.size());
		} while (!line.empty());

		//�������� ���� ������ �� �����
		FIO = fields[0];
		specialization = fields[1];
		cabinet_number = std::stoi(fields[2]);
		work_start = Time(fields[3]);
		for (auto it = Days.begin(); it != Days.end(); ++it)
			if (it->second == fields[4])
				day = it->first;
	}

public:
	std::string FIO = "�.�. �������";
	std::string specialization = Specializations[Specialization::Dentist];
	uint32_t cabinet_number = 0;
	Time work_start = Time::_MIN_TIME();
	WeekDay day = WeekDay::Monday;

public:
	std::string to_string()
	{
		auto resize = [&](std::string s, size_t size) {
			size_t prev = s.size();
			for (size_t i = prev; i < size; ++i)
				s.push_back(' ');
			return s;
		};
		// -------15------ -------15------ ----11----- -------15------ -----12-----
		std::string result =
			"=" + resize(FIO, 15) +
			"=" + resize(specialization, 15) +
			"=" + resize(std::to_string(cabinet_number), 11) +
			"=" + resize(work_start.to_string(), 15) +
			"=" + resize(Days[day], 12) + "=\n";
		return result;
	}

	void set_specialization()
	{
		std::cout << "�������� ���� �� �������������� �����: \n";

		size_t i = 0;
		for (auto it = Specializations.begin(); it != Specializations.end(); ++i, ++it)
		{
			std::cout << static_cast<size_t>(it->first) + 1 << " - " << it->second << std::endl;
		}

		int input_i = 0;
		Specialization input = Specialization::Other;
		std::cin >> input_i;
		if (input_i >= 1 && input_i <= 5) {
			input = static_cast<Specialization>(input_i - 1);
			specialization = Specializations[input];
			return;
		}



		std::cout << "������� ������������� �������������� \n";
		std::cin >> specialization;
	}

	void set_day()
	{
		std::cout << "�������� ����: \n";

		size_t i = 0;
		for (auto it = Days.begin(); it != Days.end(); ++i, ++it)
		{
			std::cout << i + 1 << " - " << it->second << std::endl;
		}

		int input_i = 0;
		WeekDay input = WeekDay::Monday;
		std::cin >> input_i;
		input = static_cast<WeekDay>(input_i - 1);

		day = input;
	}

	void set_time() {
		int hours, minutes;

		std::cout << "������� ����� ������ ������ \n";
		std::cout << "(���� �� 0 �� 23, ������ �� 0 �� 59) \n";

		do {
			std::cout << "������� ����: \n";
			std::cin >> hours;
		} while (!work_start.setHours(hours));

		do {
			std::cout << "������� �����: \n";
			std::cin >> minutes;
		} while (!work_start.setMinutes(minutes));
	}

private:
	static inline void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	// trim from end (in place)
	static inline void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string& s) {
		rtrim(s);
		ltrim(s);
	}
};


