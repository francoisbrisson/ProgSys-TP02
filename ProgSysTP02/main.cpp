#include <iostream>
#include <map>
#include <iomanip>
#include "bitpacker.h"
#include "Huffman.h"

int main()
{
	std::string text = "salut sa sa sa sa sa sa sa sa sa";
	std::cout << text << std::endl;

	std::string textcompresser = Huffman::Compresser(text);
	std::cout << textcompresser << std::endl;

	std::cout << "-------------------------------------" << std::endl;

	std::string textdecompresser = Huffman::Decompresser(textcompresser);
	std::cout << textdecompresser << std::endl;

	system("pause");
}
