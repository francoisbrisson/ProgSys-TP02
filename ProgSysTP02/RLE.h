#ifndef RLE_H__
#define RLE_H__
#include <string>
#include <sstream>
#include <iostream>

class RLE
{
public:
	static std::string Compresser(const std::string& data);
	static std::string Decompresser(const std::string& data);
};

#endif