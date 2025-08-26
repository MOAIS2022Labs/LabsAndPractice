#pragma once
#include <iostream>

struct Error //класс ошибки
{
private:
	int code; //код ошибки
	const char* description; //описание ошибки
public:
	Error(int code = 101, const char* description = "FATAL UNINITIALIZED ERROR!\n") : code(code), description(description) {}; //инициализация ошибки по умолчанию и через аргументы
	void print_Error() const { std::cout << "Error code: " << code << '\n' << description << "\n"; }; //печать ошибки в консоль
	~Error() { code = -1; description = nullptr; }
};