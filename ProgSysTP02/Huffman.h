#ifndef HUFFMAN_H__
#define HUFFMAN_H__

#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <iomanip>

class Huffman
{
public:
	std::string Compresser(std::string s);
	std::string Decompresser(std::string s);
private:

	struct Noeud
	{
		char c;
		int freq;

		Noeud* gauche;
		Noeud* droite;

		Noeud(char c, int freq, Noeud* gauche = nullptr, Noeud* droite = nullptr) :
			c(c), freq(freq), gauche(gauche), droite(droite) {}
	};

	class Comparateur
	{
	public:
		bool operator()(const Noeud* gauche, const Noeud* droite) const
		{
			return gauche->freq > droite->freq;
		}
	};
	typedef std::map<char, std::string> Dictionnaire;

	static void AfficherArbre(Noeud* n, int level);
	static void GenererDictionnaire(Noeud* n, std::string code, Dictionnaire& dictionnaire);
	static Noeud* GenererArbre(std::string s);
};

#endif