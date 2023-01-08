#pragma once

#include <string>

class Time {
private:
	int hours = -1;
	int minutes = -1;
	bool valid = false;
	
private:
	void setValid(int hours_, int minutes_);
	std::string format(int num) const;

public:
	Time(std::string& str);
	Time(int hours_, int minutes_);
	Time(std::string& hours_, std::string& minutes_);
	Time();

public:
	bool setHours(int num_);
	int getHours();
	bool setMinutes(int num_);
	int getMinutes();
	bool isValid();

public:
	std::string to_string() const;

public:
    auto operator<=>(const Time& other) const = default;

public:
	static Time&& MAX_TIME_() {
		return Time(23, 59);
	}

	static Time&& MIN_TIME_(){
		return Time(00, 00);
	}
};
