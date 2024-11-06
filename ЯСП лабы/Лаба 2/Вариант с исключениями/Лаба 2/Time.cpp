#include "Time.h"


void Time::from_string(std::string str)
{
	if (!condition_string(str))
		throw std::exception("Неверное строковое представление! Строка должна быть вида hh:mm:ss\n");
	hour = std::stoi(str.substr(0, 2));
	minute = std::stoi(str.substr(3, 5));
	second = std::stoi(str.substr(6, 8));
}

void Time::from_seconds(uShort seconds)
{
	hour = seconds / 3600;
	minute = (seconds % 3600) / 60;
	second = (seconds % 3600) % 60;
}

Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(std::string str_time)
{
	from_string(str_time);
}

Time::Time(uShort seconds)
{
	from_seconds(seconds);
}

Time::Time(tm& time)
{
	hour = time.tm_hour;
	minute = time.tm_min;
	second = time.tm_sec;
}

uShort Time::difference(Time time2)
{
	uShort t1 = this->to_seconds();
	uShort t2 = time2.to_seconds();
	return t1 >= t2 ? t1 - t2 : t2 - t1;
}

void Time::subtract_seconds(uShort seconds) 
{
	uShort time = this->to_seconds();
	if (time < seconds)
		this->from_seconds(0);
	else
		this->from_seconds(time - seconds);
}

void Time::add_seconds(uShort seconds)
{
	this->from_seconds(this->to_seconds() + seconds);
	hour %= 24;
	minute %= 60;
	second %= 60;
}

bool Time::operator==(const Time& time2)
{
	return this->hour == time2.hour && this->minute == time2.minute && this->second == time2.second;
}

bool Time::operator!=(const Time& time2)
{
	return !(*this == time2);
}

bool Time::operator>(const Time& time2)
{
	if (this->hour < time2.hour)
		return false;
	if (this->hour == time2.hour)		
	{
		if (this->minute < time2.minute)
			return false;
		if (this->minute == time2.minute)
			return this->second > time2.second;
	}	
	return true;
}

bool Time::operator<(const Time& time2)
{
	return !(*this > time2) && *this != time2;
}

bool Time::operator>=(const Time& time2)
{
	return *this > time2 || *this == time2;
}

bool Time::operator<=(const Time& time2)
{
	return *this < time2 || *this == time2;
}

Time Time::operator+(const Time& time2)
{
	Time t1 = *this;
	Time t2 = time2;
	Time result = Time(t1.to_seconds() + t2.to_seconds());
	result.hour %= 24;
	result.minute %= 60;
	result.minute %= 60;
	return result;
}

Time Time::operator+(const uShort sec)
{
	Time time = *this;
	Time result = Time(time.to_seconds() + sec);
	result.hour %= 24;
	result.minute %= 60;
	result.minute %= 60;
	return result;
}

Time Time::operator-(const Time& time2)
{
	Time t1 = *this;
	Time t2 = time2;
	t1.subtract_seconds(t2.to_seconds());
	return t1;
}

Time Time::operator-(const uShort sec)
{
	Time time = *this;
	time.subtract_seconds(sec);
	return time;
}

std::string Time::to_string()
{
	std::string _hour = hour < 10 ? "0" + std::to_string(hour) : std::to_string(hour);
	std::string _minute = minute < 10 ? "0" + std::to_string(minute) : std::to_string(minute);
	std::string _second = second < 10 ? "0" + std::to_string(second) : std::to_string(second);
	return _hour + ":" + _minute + ":" + _second;
}

uShort Time::to_seconds()
{
	return hour * 3600 + minute * 60 + second;
}

uShort Time::to_minutes()
{
	return hour * 60 + minute + (second > 0 ? 1 : 0);
}

bool check_symbol(char chr)
{
	return chr >= '0' && chr <= '9';
}


bool Time::condition_string(std::string& str)
{
	return str.length() == 8 && check_symbol(str[0]) && check_symbol(str[1]) && check_symbol(str[3])
		&& check_symbol(str[4]) && check_symbol(str[6])
		&& check_symbol(str[7]) && str[2] == ':' && str[5] == ':' && std::stoi(str.substr(0, 2)) <= 23
		&& std::stoi(str.substr(3, 5)) <= 59 && std::stoi(str.substr(6, 8)) <= 59;
}
