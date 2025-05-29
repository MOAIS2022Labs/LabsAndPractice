module;

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <list>
#include <random>
#include <set>

export import Library;
export import Manuscript;
export import Temple;

export module TempleList;

constexpr const char* SAVE_FILE_NAME = "StateData.txt";

export class TempleList
{
private:

	std::list<Temple> temples{};

	uint random100()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, 100);
		return dist(gen);
	}

	void load_state()
	{
		std::fstream file(SAVE_FILE_NAME, std::ios::out | std::ios::in);

		if (!file.is_open()) // if file is not exists
			file.open(SAVE_FILE_NAME, std::ios::out);
		else
			file >> *this;

		file.close();
	}

	void save_state()
	{
		std::ofstream file(SAVE_FILE_NAME);
		file << *this;
	}

public:

	TempleList() 
	{
		load_state();
	}

	~TempleList() 
	{
		save_state();
	}

	void add(const Temple& other) { return temples.push_back(other); }

	int size() { return temples.size(); }

	std::list<Temple>::iterator get_temple_val(const std::string& temple_name)
	{
		auto it = std::find_if(temples.begin(), temples.end(),
			[temple_name](const Temple& t) { return t.get_temple_name() == temple_name; });
		if (it == temples.end())
			throw std::runtime_error("Отсутствует храм с таким именем");
		else
			return it;
	}

	Temple& get_temple_ref(const std::string& temple_name)
	{
		auto it = std::find_if(temples.begin(), temples.end(),
			[temple_name](const Temple& t) { return t.get_temple_name() == temple_name; });
		if (it == temples.end())
			throw std::runtime_error("Отсутствует храм с таким именем");
		else
			return *it;
	}

	// generates runtime error
	void remove(const std::string& temple_name) 
	{
		temples.erase(get_temple_val(temple_name));
	}

	// generates runtime error
	// monk changing
	void change(const std::string& temple_name, const std::string& new_monk_name, const uint new_diligence)
	{
		Temple& t = get_temple_ref(temple_name);
		t.set_monk_name(new_monk_name);
		t.set_diligence(new_diligence);
	}

	// generates runtime error
	// temple name changing
	void change(const std::string& temple_name, const std::string& new_temple_name)
	{
		Temple& t = get_temple_ref(temple_name);
		t.set_temple_name(new_temple_name);
	}

	// generates runtime error
	// generates out_of_range exception
	// side: false = left, true = right
	void move(const std::string& from_temple_name, const bool from_side, const std::string& to_temple_name, const bool to_side)
	{
		Temple& from_temple = get_temple_ref(from_temple_name);
		Manuscript manuscript_to_move = from_side ? from_temple.get_library().get_right() : from_temple.get_library().get_left();
		Temple& to_temple = get_temple_ref(to_temple_name);
		to_side ? to_temple.get_library().add_right(manuscript_to_move) : to_temple.get_library().add_left(manuscript_to_move);

		if (from_temple.get_diligence() < random100())
			from_side ? from_temple.get_library().remove_right() : from_temple.get_library().remove_left();
	}

	void read(std::istream_iterator<Temple> it)
	{
		temples.clear();
		std::istream_iterator<Temple> eos;
		std::copy(it, eos, std::back_inserter(temples));
	}

	void print(std::ostream_iterator<Temple> it) const { std::copy(temples.begin(), temples.end(), it); }

	friend std::ostream& operator<<(std::ostream& out, TempleList& list)
	{
		std::ostream_iterator<Temple> it(out, "\n");
		list.print(it);
		return out;
	}

	friend std::istream& operator>>(std::istream& in, TempleList& lib)
	{
		std::istream_iterator<Temple> it(in);
		lib.read(it);
		return in;
	}

    void about(std::ostream& out)
    {
		uint sum_size{};
		uint sum_count_table{}, sum_count_parchment{}, sum_count_scroll{}, sum_count_book{};
		std::set<Manuscript> set;

		out << "=== Информация о храмах и рукописях ===\n\n";

		for (auto t : temples)
		{
			out << "Храм: " << t.get_temple_name() << "\n"
				<< "Количество рукописей: " << t.get_library().size() << " шт.\n"
				<< "--------------------------------------\n";
			sum_size += t.get_library().size();
			for (size_t i{}; i < t.get_library().size(); ++i)
			{
				switch (t.get_library()[i].get_type())
				{
				case Tablet:
					sum_count_table++;
					break;
				case Parchment:
					sum_count_parchment++;
					break;
				case Scroll:
					sum_count_scroll++;
					break;
				case Book:
					sum_count_book++;
					break;
				}
				set.insert(t.get_library()[i]);
			}
		}

		out << "\n=== Сводная информация ===\n"
			<< "Общее число храмов: " << size() << "\n"
			<< "Общее число рукописей: " << sum_size << "\n"
			<< "Уникальных рукописей: " << set.size() << "\n"
			<< "--------------------------------------\n"
			<< "Типы рукописей:\n"
			<< "* Табличек: " << sum_count_table << "\n"
			<< "* Пергаментов: " << sum_count_parchment << "\n"
			<< "* Свитков: " << sum_count_scroll << "\n"
			<< "* Книг: " << sum_count_book << "\n"
			<< "======================================\n";
    }
};