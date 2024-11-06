#pragma once
#include <iostream>
#include <fstream>
#include <string>


// ������� �������� ������������ �������� ������
void read_and_check(unsigned short& input, const char* message, int a, int b);
void read_and_check(std::string& str, const char* message);


// �������� ������������ ����� �����. 1, ���� ���� ��������, -1, ���� ���� �� ������, 0, ���� ���� ����
bool check_file(std::string& fname);

// ����� ������� ������������� ������� ������ "Time"
int initialization_menu();

//����� �������� ��� �������� �������
int action_menu();

int input_menu();

int output_menu();

std::string choose_out_file_name();

std::string choose_in_file_name();
