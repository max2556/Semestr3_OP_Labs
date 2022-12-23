#pragma once
#include <string>

class Time {
private:
	int hours = -1;
	int minutes = -1;
	bool valid = false;

public:
	Time(std::string& str);
	Time(int _hours, int _minutes);
	Time(std::string& _hours, std::string& _minutes);
	Time();

private:
	void setValid(int _hours, int _minutes);
	std::string format(int num);

public:
	bool setHours(int _num);
	int getHours();
	bool setMinutes(int _num);
	int getMinutes();
	bool isValid();

public:
	std::string to_string();

public:
	bool operator<(const Time& other) {
		return hours < other.hours || (hours == other.hours && minutes < other.minutes);
	}
	bool operator>(const Time& other) {
		return hours > other.hours || (hours == other.hours && minutes > other.minutes);
	}
	bool operator==(const Time& other) {
		return hours == other.hours && minutes == other.minutes;
	}
	bool operator<=(const Time& other) {
		if (this != nullptr)
			return *this < other || *this == other;
	}
	bool operator>=(const Time& other) {
		if (this != nullptr)
			return *this > other || *this == other;
	}


public:
	static Time&& _MAX_TIME() {
		return Time(23, 59);
	}

	static Time&& _MIN_TIME(){
		return Time(00, 00);
	}
};

