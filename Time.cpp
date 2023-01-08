#include "Time.h"

Time::Time(std::string& str) {
	auto pos = str.find(':');
	if (!pos) return; //Если нет разделителя - нельзя
	//Если представление часов не соответствует формату 'hh:mm' - нельзя
	if (pos > 2) return;  //Проверка, что часы занимают не более двух символов. Запись '6:00' валидна, запись '06:00' валидна, запись '006:00' не валидна
	if (str.length() - pos - 1 != 2) return; //Минуты обязаны занимать два символа 

	remove(str.begin(), str.end(), ' ');

	int hoursPart = atoi(&str[0]);
	int minutesPart = atoi(&str[pos + 1]);

	setValid(hoursPart, minutesPart);
}

Time::Time(int hours_, int minutes_) {
	setValid(hours_, minutes_);
}

Time::Time(std::string& hours_, std::string& minutes_) {
	if (hours_.length() > 2) return;
	if (minutes_.length() != 2) return;

	int hoursPart = atoi(&hours_[0]);
	int minutesPart = atoi(&minutes_[0]);

	setValid(hoursPart, minutesPart);
}

Time::Time() {
	valid = false;
}

void Time::setValid(int hours_, int minutes_) {
	valid = setHours(hours_) && setMinutes(minutes_) && (minutes + hours != 0);
}

std::string Time::format(int num) const
{
	std::string result = std::to_string(num);
	if (result.size() < 2) result = "0" + result;
	return result;
}

bool Time::setHours(int num_) {
	if (num_ < 0 || num_ >= 24) return false;

	hours = num_;
	return true;
}
int Time::getHours() {
	return hours;
}

bool Time::setMinutes(int num_) {
	if (num_ < 0 || num_ >= 60) return false;

	minutes = num_;
	return true;
}
int Time::getMinutes() {
	return minutes;
}

bool Time::isValid() {
	return valid;
}

std::string Time::to_string() const
{
	std::string result = format(hours) + ":" + format(minutes);
	return result;
}
