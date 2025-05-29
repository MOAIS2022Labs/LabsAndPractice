module;

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

export import Library;
export import Manuscript;

export module Temple;

export using uint = unsigned int;

export class Temple
{
private:
	std::string monk_name{};
	std::string temple_name{};
	uint diligence{};
    Library<Manuscript> library{};
public:
    Temple() {};
	
    Temple(std::string monk_name, std::string temple_name, uint diligence, const Library<Manuscript>& library)
		: monk_name(monk_name), temple_name(temple_name), diligence(diligence), library(library)
	{}

    Library<Manuscript>& get_library() { return library; }
    
    const Library<Manuscript>& get_library() const { return library; }
    
    uint get_diligence() const { return diligence; }
    
    std::string get_temple_name() const { return temple_name; }
    
    std::string get_monk_name() const { return monk_name; }
    
    void set_monk_name(const std::string& monk_name) { this->monk_name = monk_name; }
    
    void set_temple_name(const std::string& temple_name) { this->temple_name = temple_name; }
    
    void set_diligence(const uint diligence) { this->diligence = diligence; }
	
    bool empty() const { return library.empty(); }
    
    friend std::ostream& operator<<(std::ostream& out, const Temple& temple)
    {
        out << temple.temple_name << '\n'
            << temple.monk_name << '\n'
            << temple.diligence << '\n' << '\n'
            << temple.library
            << "========================================";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Temple& temple)  
    {  
        Temple tmp;  
        std::string delim_line{};  

        std::getline(in, tmp.temple_name);  
        std::getline(in, tmp.monk_name);
        if (!(in >> tmp.diligence) && tmp.diligence > 100)  
            throw std::invalid_argument("Недопустимое значение усердности\n");  
        in.ignore(1, '\n');  
        std::getline(in, delim_line);
        try
        {
            in >> tmp.library;
        }
	    catch (const std::exception& e)
	    {
		    if (std::string(e.what()).find('=') == std::string::npos)
			    throw std::invalid_argument("Недопустимое значение манускрипта\n");
	    }
       
        temple = tmp;
        return in;  
    }
};