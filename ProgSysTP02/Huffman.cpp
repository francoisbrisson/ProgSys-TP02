#include "Huffman.h"
#include "bitpacker.h"
#include <sstream>

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
		freq[s[i]]++;

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

	for (const auto& e : dictionnaire)
		std::cout << "'" << e.first << "':" << e.second << std::endl;

	BitPacker bp;
	for (char c : s)
		bp << dictionnaire[c];
	std::stringstream out;
	auto data = bp.Get();
	for (auto v : data)
		out << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(v);

	return out.str();
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


