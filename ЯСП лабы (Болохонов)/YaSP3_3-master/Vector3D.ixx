module;

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

export module Vector3D;

export class vector3D
{
private:
	double x;
	double y;
	double z;
public:
	vector3D() {}
	vector3D(const double x, const double y, const double z) : x(x), y(y), z(z) {}
	vector3D(std::ifstream& file);
	void print(std::ostream& stream = std::cout);
	std::string to_string() const;
	vector3D operator+(const vector3D& other) const;
	vector3D operator-(const vector3D& other) const;
	vector3D operator*(const double scalar) const;
	vector3D& operator=(const vector3D& other);
	friend vector3D dot(const vector3D& a, const vector3D& b); // scalar mult
	friend vector3D cross(const vector3D& a, const vector3D& b); // vector mult
	double len() const;
	bool operator==(const vector3D& other) const; // by length
	bool operator<(const vector3D& other) const;
	std::partial_ordering operator<=>(const vector3D& other) const;
	int compare(const vector3D& other) const;
	friend bool equal_by_coord(const vector3D& a, const vector3D& b);
	friend std::istream& operator>>(std::istream& is, vector3D& vector);
	friend std::ostream& operator<<(std::ostream& os, const vector3D& vector);
};

vector3D::vector3D(std::ifstream& file)
{
	file >> x >> y >> z;
}

void vector3D::print(std::ostream& stream)
{
	stream << '(' << x << ' ' << y << ' ' << z << ')' << '\n';
}

std::string vector3D::to_string() const
{
	return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
}

vector3D vector3D::operator+(const vector3D& other) const
{
	return vector3D(x + other.x, y + other.y, z + other.z);
}

vector3D vector3D::operator-(const vector3D& other) const
{
	return vector3D(x - other.x, y - other.y, z - other.z);
}

vector3D vector3D::operator*(const double scalar) const
{
	return vector3D(x * scalar, y * scalar, z * scalar);
}

vector3D& vector3D::operator=(const vector3D& other) 
{
	if (this != &other) 
	{ 
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this; 
}

double vector3D::len() const
{
	return sqrt(x * x + y * y + z * z);
}

bool vector3D::operator==(const vector3D& other) const
{
	return len() == other.len();
}

bool vector3D::operator<(const vector3D& other) const
{
	return len() < other.len();
}

int vector3D::compare(const vector3D& other) const
{
	int res{ -1 };
	std::partial_ordering id{ (*this) <=> other };
	if (id == std::partial_ordering::greater)
		res = 1;
	else
		if (id == std::partial_ordering::equivalent)
			res = 0;
	return res;
}

std::partial_ordering vector3D::operator<=>(const vector3D& other) const
{
	return len() <=> other.len();
}

export vector3D dot(const vector3D& a, const vector3D& b)
{
	return vector3D(a.x * b.x, a.y * b.y, a.z * b.z);
}

export vector3D cross(const vector3D& a, const vector3D& b)
{
	return vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

export bool equal_by_coord(const vector3D& a, const vector3D& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

export std::istream& operator>>(std::istream& is, vector3D& vector)
{
	is >> vector.x >> vector.y >> vector.z;
	return is;
}

export std::ostream& operator<<(std::ostream& os, const vector3D& vector)
{
	os << '(' << vector.x << ' ' << vector.y << ' ' << vector.z << ')';
	return os;
}
