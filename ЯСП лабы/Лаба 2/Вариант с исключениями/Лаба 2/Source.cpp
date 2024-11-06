/*
���������� ������ 9 ������
8. ������� ����� Time ��� ������ �� �������� � ������� ����:������:�������. �����
������ �������� � ���� �� ����� ������� �������� �������������: �������,
������� (��������, �23:59:59�), ���������, ��������. ������������� ����������
��������: ���������� �������� ����� ����� ��������� ������� � ��������,
�������� ������� � ��������� ���������� ������, ��������� �� ������� ���������
���������� ������, ��������� �������� �������, ������� � �������, �������
� ������ (� ����������� �� ����� ������).
*/

#include "UserInteraction.h"
#include "Time.h"
#include <Windows.h>
// TODO: finally ��� �������� ����� � ��������� � ������ ����� � ������������...

// �������� ��� �������� �������
void action(Time& time);

void console_output(Time& time);

void file_output(Time& time, std::ofstream& file);

// ����� ������� ������������� � �������������
int initialization(Time& time);

void read_file_nums(std::ifstream& file, uShort& hour, uShort& minute, uShort& second);
void read_file_str(std::ifstream& file, std::string& str);
void read_file_sec(std::ifstream& file, uShort& sec);

void read_console_nums(uShort& hour, uShort& minute, uShort& second);
void read_console_str(std::string& str);
void read_console_sec(uShort& sec);


int main()
{
	SetConsoleOutputCP(1251);
	int choice = 0;	
	do
	{
		Time time;
		choice = initialization(time);
		if (choice)
			action(time);
	} while (choice != 0);
	return 0;
}

int initialization(Time& time)
{
	int choice = initialization_menu();
 	switch (choice)
	{
	case 1: // �������
	{
		uShort hour, minute, second;
		switch(input_menu())
		{
		case 1:
			read_console_nums(hour, minute, second);
			time = Time(hour, minute, second);
			break;
		case 2:
		{
			std::string fname = choose_in_file_name();
			std::ifstream file(fname);
			read_file_nums(file, hour, minute, second);
			file.close();
			time = Time(hour, minute, second);
			console_output(time);
			break;
		}
		}	
		break;
	}
	case 2: // �������
	{
		std::string str;
		switch (input_menu())
		{
		case 1:
			read_console_str(str);
			time = Time(str);
			break;
		case 2:
		{
			std::string fname = choose_in_file_name();
			std::ifstream file(fname);
			read_file_str(file, str);
			file.close();
			time = Time(str);
			console_output(time);
			break;
		}
		}
		break;
	}
	case 3: // ���������
	{
		uShort sec;
		switch (input_menu())
		{
		case 1:
			read_console_sec(sec);
			time = Time(sec);
			break;
		case 2:
		{
			std::string fname = choose_in_file_name();
			std::ifstream file(fname);
			read_file_sec(file, sec);
			file.close();
			time = Time(sec);
			console_output(time);
			break;
		}
		}
		break;
	}
	case 4: // ��������
	{
		uShort hour, minute, second;
		switch (input_menu())
		{
		case 1:
		{
			read_console_nums(hour, minute, second);
			tm t{ second, minute, hour };
			time = Time(t);
			break;
		}
		case 2:
		{
			std::string fname = choose_in_file_name();
			std::ifstream file(fname);
			read_file_nums(file, hour, minute, second);
			file.close();
			tm t{ second, minute, hour };
			time = Time(t);
			console_output(time);
			break;
		}
		}
		break;
	}
	}
	return choice;
}

void read_file_nums(std::ifstream& file, uShort& hour, uShort& minute, uShort& second)
{
	while (!(file >> hour) || !(file >> minute) || !(file >> second) || hour >= 24 || minute >= 60 || second >= 60)
	{
		file.close();
		std::cout << "������, ������� ������ ��� �����: ";
		std::string fname;
		std::cin >> fname;
		while (!check_file(fname))
		{
			std::cout << "������, ������� ������ ��� �����: ";
			std::cin >> fname;
		}
		file.open(fname);
	}
}

void read_file_str(std::ifstream& file, std::string& str)
{
	
	while (!(file >> str) || !condition_string(str))
	{
		file.close();
		std::cout << "������, ������� ������ ��� �����: ";
		std::string fname;
		std::cin >> fname;
		while (!check_file(fname))
		{
			std::cout << "������, ������� ������ ��� �����: ";
			std::cin >> fname;
		}
		file.open(fname);
		//file >> str;
	}
}

void read_file_sec(std::ifstream& file, uShort& sec)
{
	while (!(file >> sec) || sec >= 86400)
	{
		file.close();
		std::cout << "������, ������� ������ ��� �����: ";
		std::string fname;
		std::cin >> fname;
		while (!check_file(fname))
		{
			std::cout << "������, ������� ������ ��� �����: ";
			std::cin >> fname;
		}	
		file.open(fname);
	}
}

void read_console_nums(uShort& hour, uShort& minute, uShort& second)
{
	read_and_check(hour, "������� ����: ", 0, 23);
	read_and_check(minute, "������� ������: ", 0, 59);
	read_and_check(second, "������� �������: ", 0, 59);
}

void read_console_str(std::string& str)
{
	read_and_check(str, "������� ����� � ��������� �������������: ");
}

void read_console_sec(uShort& sec)
{
	read_and_check(sec, "������� ���������� ������: ", 0, 85399);
}

void action(Time& time)
{
	int choice = 0;
	do
	{
		choice = action_menu();
		switch (choice)
		{
		case 1: // ������� �������
		{
			uShort sec;
			switch (input_menu())
			{
			case 1:
				read_and_check(sec, "������� ���������� ������: ", 0, 85399);
				break;
			case 2:
			{
				std::string fname = choose_in_file_name();
				std::ifstream file(fname);
				read_file_sec(file, sec);
				console_output(time);
				break;
			}
			}
			time.subtract_seconds(sec);
			break;
		}
		case 2: // �������� �������
		{
			uShort sec;
			switch (input_menu())
			{
			case 1:
				read_and_check(sec, "������� ���������� ������: ", 0, 85399);
				break;
			case 2:
			{
				std::string fname = choose_in_file_name();
				std::ifstream file(fname);
				read_file_sec(file, sec);
				console_output(time);
				break;
			}
			}
			time.add_seconds(sec);
			break;
		}
		case 3: // ��������� ����� � �������
			switch (output_menu())
			{
			case 1:
				std::cout << time.to_seconds() << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << time.to_seconds();
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		case 4: // ��������� ����� � ������
			switch (output_menu())
			{
			case 1:
				std::cout << time.to_minutes() << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << time.to_minutes();
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		case 5: // ������� ����� �� �������
			console_output(time);
			break;
		case 6: // ������� ����� � ����
		{
			std::string fname = choose_out_file_name();
			std::ofstream file(fname.c_str());
			std::cout << "���������� ���������� � ���� " << fname << '\n';
			file.close();
			break;
		}
		case 7: // ��������� ����� � ��������� �������������
			switch (output_menu())
			{
			case 1:
				std::cout << time.to_string() << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << time.to_seconds();
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		case 8: // �������� ���� �������� �������
		{
			Time new_time;
			initialization(new_time);
			Time res = time + new_time;
			std::cout << '\n';
			switch (output_menu())
			{
			case 1:
				console_output(res);
				std::cout << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file_output(res, file);
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 9: // �������� ������ � �������
		{
			uShort sec;
			switch (input_menu())
			{
			case 1:
				read_and_check(sec, "������� ���������� ������: ", 0, 85399);
				break;
			case 2:
			{
				std::string fname = choose_in_file_name();
				std::ifstream file(fname);
				read_file_sec(file, sec);
				console_output(time);
				break;
			}
			}
			Time res = time + sec;
			std::cout << '\n';
			switch (output_menu())
			{
			case 1:
				console_output(res);
				std::cout << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file_output(res, file);
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 10: // �������� ���� �������� �������
		{
			Time new_time;
			initialization(new_time);
			Time res = time - new_time;
			std::cout << '\n';
			switch (output_menu())
			{
			case 1:
				console_output(res);
				std::cout << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file_output(res, file);
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 11: // �������� ������� � ������
		{
			uShort sec;
			switch (input_menu())
			{
			case 1:
				read_and_check(sec, "������� ���������� ������: ", 0, 85399);
				break;
			case 2:
			{
				std::string fname = choose_in_file_name();
				std::ifstream file(fname);
				read_file_sec(file, sec);
				console_output(time);
				break;
			}
			}
			Time res = time - sec;
			std::cout << '\n';
			switch (output_menu())
			{
			case 1:
				console_output(res);
				std::cout << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file_output(res, file);
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 12: // �������� �� ���������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time == new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time == new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;			
		}
		case 13: // �������� �� �����������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time != new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time != new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 14: // ������ ������ �������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time > new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time > new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 15: // ������ ������ �������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time < new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time < new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 16: // ������ ������ ��� ����� �������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time >= new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time >= new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 17: // ������ ������ ��� ����� �������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << ((time <= new_time) ? "true" : "false") << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << ((time <= new_time) ? "true" : "false");
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		case 18: // ������� ����� ����� ��������� �������
		{
			Time new_time;
			initialization(new_time);
			switch (output_menu())
			{
			case 1:
				std::cout << time.difference(new_time) << '\n';
				break;
			case 2:
				std::string fname = choose_out_file_name();
				std::ofstream file(fname);
				file << time.difference(new_time);
				std::cout << "���������� ���������� � ���� " << fname << '\n';
				file.close();
				break;
			}
			break;
		}
		}
	} while (choice != 0);
}

void console_output(Time& time)
{
	std::cout << time.to_string() << '\n';
}

void file_output(Time& time, std::ofstream& file)
{
	file << time.to_string();
}
