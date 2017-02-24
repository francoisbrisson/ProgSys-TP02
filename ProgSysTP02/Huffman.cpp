#include "Huffman.h"
#include "bitpacker.h"
#include <sstream>
#include <random>

void Huffman::GenererDictionnaire(Noeud* n, std::string code, Dictionnaire& dictionnaire)
{
	if (!n)
		return;

	GenererDictionnaire(n->gauche, code + "0", dictionnaire);
	GenererDictionnaire(n->droite, code + "1", dictionnaire);

	if (!n->gauche && !n->droite)
		dictionnaire[n->c] = code;
}

Huffman::Noeud* Huffman::GenererArbre(std::string s)
{
	int freq[256] = { 0 };

	// Calculer la frequence des caracteres
	for (size_t i = 0; i < s.length(); ++i)
		freq[static_cast<unsigned char>(s[i])]++;

	std::priority_queue<Noeud*, std::vector<Noeud*>, Comparateur> q;
	for (int i = 0; i < 256; ++i)
		if (freq[i] != 0)
			q.push(new Noeud(i, freq[i]));

	while (q.size() > 1)
	{
		Noeud* gauche = q.top();
		q.pop();

		Noeud* droite = q.top();
		q.pop();

		q.push(new Noeud(0, gauche->freq + droite->freq, gauche, droite));
	}

	Noeud* racine = q.top();

	return racine;
}

std::string Huffman::Compresser(std::string s)
{
	Dictionnaire dictionnaire;
	GenererDictionnaire(GenererArbre(s), "", dictionnaire);

	std::stringstream out;
	for (char c : s)
		out << dictionnaire[c];
	/*BitPacker bp;
	auto data = bp.Get();
	for (auto v : data)
		out << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(v);*/

	std::stringstream outAvecDictionnaire;
	outAvecDictionnaire << std::setw(3) << std::setfill('0') << dictionnaire.size();
	for (const auto& e : dictionnaire)
		outAvecDictionnaire << e.second + e.first;
	outAvecDictionnaire << out.str();
	return outAvecDictionnaire.str();
}

std::string Huffman::Decompresser(std::string s)
{
	Dictionnaire dictionnaire;
	std::string out;
	int nbrCle = 0;
	int i = 3;

	for (std::string code = ""; nbrCle < std::stoi(s.substr(0, 3)); i++)
	{
		if ((s[i]) == '1' || (s[i]) == '0')
			code += s[i];
		else
		{
			dictionnaire[s[i]] = code;
			++nbrCle;
			code = "";
		}
	}


	for (std::string code; i < s.size(); i++)
	{
		code += s[i];
		for (const auto& e : dictionnaire)
		{
			if (e.second == code)
			{
				out += e.first;
				code = "";
				break;
			}
		}
	}

	return out;
}

void Huffman::AfficherArbre(Noeud* n, int level = 0)
{
	if (!n)
		return;

	AfficherArbre(n->droite, level + 1);
	std::cout << std::string(level * 4, ' ');

	if (n->c == 0)
		std::cout << "[" << n->freq << "]" << std::endl;
	else
		std::cout << "[" << n->c << "]" << std::endl;
	AfficherArbre(n->gauche, level + 1);
}