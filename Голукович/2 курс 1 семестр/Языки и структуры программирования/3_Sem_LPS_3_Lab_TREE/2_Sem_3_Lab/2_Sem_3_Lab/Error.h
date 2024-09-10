#pragma once
#include <iostream>

struct Error //����� ������
{
private:
	int code; //��� ������
	const char* description; //�������� ������
public:
	Error(int code = 101, const char* description = "FATAL UNINITIALIZED ERROR!\n") : code(code), description(description) {}; //������������� ������ �� ��������� � ����� ���������
	void print_Error() const { std::cout << "Error code: " << code << '\n' << description << "\n"; }; //������ ������ � �������
	~Error() { code = -1; description = nullptr; }
};