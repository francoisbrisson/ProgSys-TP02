#pragma once

class Huffman
{
public:


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
};