#include <iostream>
#include <map>
#include <iomanip>
#include "bitpacker.h"
#include "Huffman.h"
#include "RLE.h"
#include <fstream>

std::string LoadFile(const std::string & filename)
{
	std::ifstream f(filename.c_str(), std::ios::binary);
	if (!f.is_open())
		return "";
	f.seekg(0, std::ios::end);
	unsigned int len = f.tellg();
	f.seekg(0, std::ios::beg);
	char * tmp = new char[len];
	f.read(tmp, len);
	f.close();
	std::string buffer(tmp, len);
	delete[] tmp;
	return buffer;
}

int main()
{ 

	std::string fileContent = LoadFile("03.bmp");
	std::cout << fileContent.length() / 100 << std::endl;

	std::cout << "---------------------" << std::endl;

	std::string s = Huffman::Compresser(fileContent);
	std::cout << s.length() / 100 << std::endl; 

	system("pause");
}