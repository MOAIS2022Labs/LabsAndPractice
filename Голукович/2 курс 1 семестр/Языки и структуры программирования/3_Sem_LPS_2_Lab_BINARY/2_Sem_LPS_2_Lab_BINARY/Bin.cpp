#include "Bin.h"

Binary Binary::plus(const Binary& num_r)
{
	Binary result(0);
	char sur = '0', t;
	int i, max;
	if (size <= num_r.size)
		max = num_r.size;
	else
		max = size;
	for (i = 0; i < max; ++i)
	{
		if (bin[i] == num_r.bin[i])
			t = '0';
		else
			t = '1';
		if (t == sur)
			result.bin[i] = '0';
		else
			result.bin[i] = '1';
		if (bin[i] == num_r.bin[i] && num_r.bin[i] == '1' || bin[i] == sur && sur == '1' || num_r.bin[i] == sur && sur == '1')
			sur = '1';
		else
			sur = '0';
		result.size += 1;
	}
	if (i != MAX)
	{
		result.bin[i] = sur;
		if (sur == '1')
			result.size = i + 1;
	}
	else
	{
		int res_size = 1;
		for (int j = MAX - 1; j >= 0 && res_size == 1; --j)
			if (result.bin[j] == '1')
				res_size = j + 1;
		result.size = res_size;
	}
	return result;
}

Binary Binary::minus(const Binary& num_r)
{
	Binary result(0);
	char sur = '0';
	for (int i = 0; i < size; ++i)
	{
		if (bin[i] == num_r.bin[i])
		{
			if (sur == '1')
				result.bin[i] = '1';
			else
				result.bin[i] = '0';
		}
		else
			if (bin[i] > num_r.bin[i])
			{
				if (sur != '0')
					result.bin[i] = '0';
				else
					result.bin[i] = '1';
				sur = '0';
			}
			else
			{
				if (sur == '0')
					result.bin[i] = '1';
				else
					result.bin[i] = '0';
				sur = '1';
			}
		result.size += 1;
	}
	while (result.bin[result.size - 1] != '1')
		result.size--;
	return result;
}

Binary Binary::multiplication(const Binary& num_r)
{
	Binary result(0);
	if (*this != Binary(0) && num_r != Binary(0))
	{
		Binary summand(*this);
		for (int i = 0; i < num_r.size; ++i)
		{
			if (num_r.bin[i] == '1')
				result += summand;
			for (int j = MAX - 1; j > 0; --j)
				summand.bin[j] = summand.bin[j - 1];
			summand.bin[0] = '0';
			int summand_size = MAX - 1;
			while (summand.bin[summand_size] != '1')
				summand_size -= 1;
			summand.size = summand_size + 1;
		}
	}
	return result;
}

Binary Binary::division(const Binary& num_r)
{
	Binary result(0);
	Binary num_l(*this);
	while (num_l >= num_r)
	{
		num_l -= num_r;
		result += Binary("1");
	}
	return result;
}

Binary Binary::another_division(const Binary& num_r)
{
	Binary result(0);
	result = Binary(*this);
	while (result >= num_r)
		result -= num_r;
	return result;
}

Binary::Binary()
{
	*this = Binary(0);
}

Binary::Binary(const Binary& num)
{
	*this = num;
}

Binary::Binary(const int SIZE)
{
	if (SIZE > MAX || SIZE < 0)
		throw Error(10, "Initialization error!");
	else
	{
		try
		{
			size = SIZE;
			char* num = new char[MAX + 1];
			num[MAX] = '\0';
			for (int i = 0; i < MAX - size; ++i)
				num[i] = '0';
			if (size > 0)
			{
				std::cout << "¬ведите число >> ";
				for (int i = MAX - size; i < MAX; ++i)
					std::cin >> num[i];
				std::cout << '\n';
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
			}
			*this = Binary(num);
		}
		catch (const Error error) { throw error; }
	}
}

Binary::Binary(const char* num)
{
	int i, j;
	int count = strlen(num);
	for (i = count - 1, j = 0; i >= 0 && j < MAX; ++j, --i)
	{
		if (num[i] == '0' || num[i] == '1')
			bin[j] = num[i];
		else
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			throw Error(11, "Initialization error!");
		}
	}
	if (j < MAX)
		for (i = MAX - 1; i >= j; --i)
			bin[i] = '0';
	j = MAX - 1;
	while (bin[j] == '0')
		--j;
	++j;
	size = j;
}

Binary::Binary(std::istream& in)
{
	char* num = new char[MAX + 1];
	in.getline(num, MAX + 1);
	*this = Binary(num);
	delete[] num;
	num = nullptr;
}

char* Binary::to_cstring()
{
	char* result;
	if (size != 0)
	{
		result = new char[size + 1];
		for (int i = 0, j = size - 1; i < size; ++i, --j)
			result[j] = bin[i];
		result[size] = '\0';
	}
	else
	{
		result = new char[2];
		result[0] = '0';
		result[1] = '\0';
	}	
	return result;
}

std::ostream& operator<<(std::ostream& out, const Binary& num)
{
	if (num.size == 0)
		out << '0';
	for (int i = num.size - 1; i >= 0; --i)
		out << num.bin[i];
	return out;
}

Binary& Binary::operator=(const Binary& num)
{
	for (int i = 0; i < num.size; ++i)
		bin[i] = num.bin[i];
	for (int i = num.size; i < MAX; ++i)
		bin[i] = '0';
	size = num.size;
	return *this;
}

Binary& Binary::operator+=(const Binary& num_r)
{
	*this = this->plus(num_r);
	return *this;
}

Binary& Binary::operator-=(const Binary& num)
{
	if (*this != num)
	{
		Binary num_l(0), num_r(0);
		bool flag = false;
		if (*this > num)
		{
			num_l = *this;
			num_r = num;
			flag = true;
		}
		else
		{
			num_l = num;
			num_r = *this;
		}
		*this = num_l.minus(num_r);
		if (!flag)
			*this = Binary(MAXBIN) - *this + Binary("1");
	}
	else
		*this = Binary(0);
	return *this;
}

Binary& Binary::operator*=(const Binary& num)
{
	*this = multiplication(num);
	return *this;
}

Binary& Binary::operator/=(const Binary& num_r)
{
	if (num_r != Binary(0))
		*this = division(num_r);
	else
		throw Error(0, "Binary division by zero!");
	return *this;
}

Binary& Binary::operator%=(const Binary& num_r)
{
	if (num_r != Binary(0))
		*this = another_division(num_r);
	else
		throw Error(0, "Binary division by zero!");
	return *this;
}

Binary& Binary::operator++()
{
	if (*this == Binary(MAXBIN))
		*this = Binary(0);
	else
		*this += Binary("1");
	return *this;
}

Binary& Binary::operator--()
{
	if (*this == Binary(0))
		*this = Binary(MAXBIN);
	else
		*this -= Binary("1");
	return *this;
}

/*Binary& Binary::operator++(int rud)
{
	if (*this == Binary(MAX_bin))
		*this = Binary(0);
	else
		*this += Binary("1");
	return *this;
}

Binary& Binary::operator--(int rud)
{
	if (*this == Binary(0))
		*this = Binary("11111111");
	else
		*this -= Binary("1");
	return *this;
}*/

const Binary operator+(const Binary& num_l, const Binary& num_r)
{
	Binary result = num_l;
	result = result.plus(num_r);
	return result;
}

const Binary operator-(const Binary& num_1, const Binary& num_2)
{
	Binary result(0);
	if (num_1 != num_2)
	{
		Binary num_l(0), num_r(0);
		bool flag = false;
		if (num_1 > num_2)
		{
			num_l = num_1;
			num_r = num_2;
			flag = true;
		}
		else
		{
			num_l = num_2;
			num_r = num_1;
		}
		result = num_l.minus(num_r);
		if (!flag)
			result = Binary(MAXBIN) - result + Binary("1");
	}
	return result;
}

const Binary operator*(const Binary& num_l, const Binary& num_r)
{
	Binary result(num_l);
	result = result.multiplication(num_r);
	return result;
}

const Binary operator/(const Binary& num_l, const Binary& num_r)
{
	if (num_r != Binary(0))
	{
		Binary result(num_l);
		result = result.division(num_r);
		return result;
	}
	else
		throw Error(0, "Binary division by zero!");
}

const Binary operator%(const Binary& num_l, const Binary& num_r)
{
	if (num_r != Binary(0))
	{
		Binary result(num_l);
		result = result.another_division(num_r);
		return result;
	}
	else
		throw Error(0, "Binary division by zero!");
}

Binary::operator bool()
{
	return *this == Binary(0) ? false : true;
}

const bool operator!(const Binary& num)
{
	return num == Binary(0) ? true : false;
}

const bool operator==(const Binary& num_l, const Binary& num_r)
{
	bool result = true;
	if (num_l.size != num_r.size)
		result = false;
	else
		for (int i = 0; i < num_l.size && result; ++i)
			if (num_l.bin[i] != num_r.bin[i])
				result = false;
	return result;
}

const bool operator!=(const Binary& num_l, const Binary& num_r)
{
	bool result = false;
	if (num_l.size != num_r.size)
		result = true;
	else
		for (int i = 0; i < num_l.size && !result; ++i)
			if (num_l.bin[i] != num_r.bin[i])
				result = true;
	return result;
}

const bool operator<=(const Binary& num_l, const Binary& num_r)
{
	bool result = false;
	if (num_l.size < num_r.size)
		result = true;
	else
		if (num_l.size == num_r.size)
		{
			int i = num_l.size;
			while (i >= 0 && num_l.bin[i] == num_r.bin[i])
				i--;
			if (i != -1 && num_l.bin[i] < num_r.bin[i] || i == -1)
				result = true;
		}
	return result;
}

const bool operator>=(const Binary& num_l, const Binary& num_r)
{
	bool result = false;
	if (num_l.size > num_r.size)
		result = true;
	else
		if (num_l.size == num_r.size)
		{
			int i = num_l.size;
			while (i >= 0 && num_l.bin[i] == num_r.bin[i])
				i--;
			if (i != -1 && num_l.bin[i] > num_r.bin[i] || i == -1)
				result = true;
		}
	return result;
}

const bool operator<(const Binary& num_l, const Binary& num_r)
{
	bool result = true;
	if (num_l.size > num_r.size)
		result = false;
	else
		if (num_l.size == num_r.size)
		{
			int i = num_l.size;
			while (i >= 0 && num_l.bin[i] == num_r.bin[i])
				i--;
			if (i != -1 && num_l.bin[i] > num_r.bin[i] || i == -1)
				result = false;
		}
	return result;
}

const bool operator>(const Binary& num_l, const Binary& num_r)
{
	bool result = true;
	if (num_l.size < num_r.size)
		result = false;
	else
		if (num_l.size == num_r.size)
		{
			int i = num_l.size;
			while (i >= 0 && num_l.bin[i] == num_r.bin[i])
				i--;
			if (i != -1 && num_l.bin[i] < num_r.bin[i] || i == -1)
				result = false;
		}
	return result;
}

//int Binary::get_size() { return size; }