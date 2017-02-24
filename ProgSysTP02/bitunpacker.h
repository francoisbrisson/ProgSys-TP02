#ifndef BITPACKER_H__
#define BITPACKER_H__

#include <vector>
#include <string>

class BitUnpacker
{
public:
	static bool Get(const unsigned char* caractere, const unsigned int& position)
	{
		int positionOctet = position / 8; 
		int positionBit = position % 8; 
		return (caractere[positionOctet] & (1 << positionBit)) != 0;
	}

};



#endif