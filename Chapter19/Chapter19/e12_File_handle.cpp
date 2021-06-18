
/*	A File_handle class with a constructor that takes a string argument as the file name, opens
	the file in the constructor, and closes it in the destructor 
	*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>



class File_handle {
private:
	std::fstream fs;

public:
	explicit File_handle(std::string name = "")
	{
		fs.exceptions(fs.exceptions() | std::ios_base::badbit);
		fs.open(name, std::fstream::in | std::fstream::out | std::fstream::app);
		std::cerr << this << "File_handle object successfully opened a " << name << " file" << std::endl;
	}

	~File_handle()
	{
		fs.close();
		std::cerr << this << "File_handle object successfully closed a file";
	}

	void write(std::string text) { fs << text; };
	void read(std::string& str) { fs >> str; }
};


int main()
{
	File_handle fh{ "test.txt" };
	//fh.write(" check");

	std::string text;
	fh.read(text);

	std::cout << text << std::endl;
}
