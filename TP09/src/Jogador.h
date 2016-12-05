#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>

using namespace std;


//A ALTERAR!!
struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
		int valor = 0;
		tabHInt aposta = ap.getNumeros();

		for(auto apo : aposta)
			valor += apo*3;

		return valor;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
		tabHInt aposta1 = ap1.getNumeros();
		for(auto valores1 : aposta1){
			if(!ap2.contem(valores1))
				return false;
		}
		return true;
	}
};

typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
