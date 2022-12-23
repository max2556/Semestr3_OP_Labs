#include "Time.h"

Time::Time(std::string& str) {
	auto pos = str.find(':');
	if (!pos) return; //���� ��� ����������� - ������
	//���� ������������� ����� �� ������������� ������� 'hh:mm' - ������
	if (pos > 2) return;  //��������, ��� ���� �������� �� ����� ���� ��������. ������ '6:00' �������, ������ '06:00' �������, ������ '006:00' �� �������
	if (str.length() - pos - 1 != 2) return; //������ ������� �������� ��� ������� 


	remove(str.begin(), str.end(), ' ');


	int hoursPart = atoi(&str[0]);
	int minutesPart = atoi(&str[pos + 1]);

	setValid(hoursPart, minutesPart);
}

Time::Time(int _hours, int _minutes) {
	setValid(_hours, _minutes);
}

Time::Time(std::string& _hours, std::string& _minutes) {
	if (_hours.length() > 2) return;
	if (_minutes.length() != 2) return;

	int hoursPart = atoi(&_hours[0]);
	int minutesPart = atoi(&_minutes[0]);

	setValid(hoursPart, minutesPart);
}

Time::Time() {
	valid = false;
}



void Time::setValid(int _hours, int _minutes) {
	valid = setHours(_hours) && setMinutes(_minutes) && (minutes + hours != 0);
}

std::string Time::format(int num) {
	std::string result = std::to_string(num);
	if (result.size() < 2) result = "0" + result;
	return result;
}



bool Time::setHours(int _num) {
	if (_num < 0 || _num >= 24) return false;

	hours = _num;
	return true;
}
int Time::getHours() {
	return hours;
}

bool Time::setMinutes(int _num) {
	if (_num < 0 || _num >= 60) return false;

	minutes = _num;
	return true;
}
int Time::getMinutes() {
	return minutes;
}

bool Time::isValid() {
	return valid;
}

std::string Time::to_string() {
	std::string result = format(hours) + ":" + format(minutes);
	return result;
}