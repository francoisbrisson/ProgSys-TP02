#include "RLE.h"

std::string RLE::Compresser(const std::string& data)
{
	std::string out;
	int indexRepetition = 1;

	for (int i = 0; i < data.length(); i++)
	{
		while (data[i] == data[i + 1])
		{
			if (indexRepetition == 9)
			{
				out += std::to_string(indexRepetition) + data[i];
				indexRepetition = 0;
			}

			indexRepetition++;
			i++;
		}
		out += std::to_string(indexRepetition) + data[i];
		indexRepetition = 1;
	}

	return out;
}

std::string RLE::Decompresser(const std::string& data)
{
	std::string out;
	int nbrRepetition;

	for (int i = 0; i < data.length(); i++)
	{
		if (!(i%2))
			nbrRepetition = data[i] - '0';
		else
			for (int i2 = 0; i2 < nbrRepetition; i2++)
				out += data[i];
	}

	return out;
}