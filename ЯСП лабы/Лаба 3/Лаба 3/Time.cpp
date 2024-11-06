#include "Time.h"


void Time::from_string(std::string str)
{
	hour = std::stoi(str.substr(0, 2));
	minute = std::stoi(str.substr(3, 5));
	second = std::stoi(str.substr(6, 8));
}

void Time::from_seconds(short seconds)
{
	if (seconds < 0)
		throw std::invalid_argument("„исло секунд должно быть неотрицательным\n");
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

Time::Time(short hour, short minute, short second)
{
	if (hour >= 24 || hour < 0 || minute >= 60 || minute < 0 || second >= 60 || second < 0)
		throw std::invalid_argument("„исло часов не должно превышать 24, а минут и секунд Ч 60\n");
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

Time::Time(std::string str_time)
{
	from_string(str_time);
}

Time::Time(short seconds)
{
	from_seconds(seconds);
}

Time::Time(tm& time)
{
	hour = time.tm_hour;
	minute = time.tm_min;
	second = time.tm_sec;
}

short Time::difference(Time time2)
{
	short t1 = this->to_seconds();
	short t2 = time2.to_seconds();
	return t1 >= t2 ? t1 - t2 : t2 - t1;
}

void Time::subtract_seconds(short seconds)
{
	short time = this->to_seconds();
	if (time < seconds)
		this->from_seconds(0);
	else
		this->from_seconds(time - seconds);
}

void Time::add_seconds(short seconds)
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
	return result;
}

Time Time::operator+(const short sec)
{
	Time time = *this;
	Time result = Time(time.to_seconds() + sec);
	result.hour %= 24;
	return result;
}

Time Time::operator-(const Time& time2)
{
	Time t1 = *this;
	Time t2 = time2;
	t1.subtract_seconds(t2.to_seconds());
	return t1;
}

Time Time::operator-(const short sec)
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

short Time::to_seconds()
{
	return hour * 3600 + minute * 60 + second;
}

short Time::to_minutes()
{
	return hour * 60 + minute + (second > 0 ? 1 : 0);
}

std::ostream& operator<<(std::ostream& out, const Time& time)
{
	out << time.hour << ' ' << time.minute << ' ' << time.second << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, Time& time)
{
	short hour, minute, second;
	if (in >> hour >> minute >> second)
	{
		if (hour >= 24 || hour < 0 || minute >= 60 || minute < 0 || second >= 60 || second < 0)
			throw std::invalid_argument("„исло часов не должно превышать 24, а минут и секунд Ч 60\n");
		time.hour = hour;
		time.minute = minute;
		time.second = second;
	}
	return in;
}
