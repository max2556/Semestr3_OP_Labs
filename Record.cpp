#include "Record.h"


std::istream& operator>>(std::istream& is, Record::Specialization& i)
{
	int tmp;
	if (is >> tmp)
		i = static_cast<Record::Specialization>(tmp);
	return is;
}

std::istream& operator>>(std::istream& is, Record::WeekDay& i)
{
	int tmp;
	if (is >> tmp)
		i = static_cast<Record::WeekDay>(tmp);
	return is;
}
