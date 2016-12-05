#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;
	for(auto ap : apostas)
		if(ap.contem(num))
			count++;

	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	for(auto aps : apostas){
		int aux = 0;
		for(auto sr : sorteio){
			if(aps.contem(sr))
				aux++;
		}
		if(aux > 3)
			money.insert(aps);
	}

	return money;
}
