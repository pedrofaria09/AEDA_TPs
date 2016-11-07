/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"

using namespace std;

unsigned Jogo::numPalavras(string frase) {
	if (frase.length() == 0)
		return 0;
	int n = 1;
	unsigned int pos = frase.find(' ');
	while (pos != string::npos) {
		frase = frase.substr(pos + 1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}

Jogo::Jogo() {
	// a alterar
}

Jogo::Jogo(list<Crianca>& lc2) {
	list<Crianca>::iterator it;
	for (it = lc2.begin(); it != lc2.end(); it++) {
		criancas.push_back(*it);
	}
}

void Jogo::insereCrianca(const Crianca &c1) {
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const {
	return criancas;
}

string Jogo::escreve() const {
	stringstream ss;
	list<Crianca>::const_iterator it;
	for (it = criancas.begin(); it != criancas.end(); it++) {
		ss << it->escreve() << "\n";
	}
	return ss.str();
}

Crianca& Jogo::perdeJogo(string frase) {
	int nrPalavras = numPalavras(frase);

	list<Crianca> criancasBack;
	list<Crianca>::iterator it;
	int j = 0;
	criancasBack = criancas;
	while (criancasBack.size() > 1) {
		int numeroCriancas = criancasBack.size();
		int posicaoAEliminar = (((nrPalavras - 1) % numeroCriancas) + 1);
		for (it = criancasBack.begin(); it != criancasBack.end(); it++) {
			j++;
			if (j == posicaoAEliminar) {
				criancasBack.erase(it);
				j = 0;
				break;
			}
		}
	}
	Crianca *c1 = new Crianca(criancasBack.front());
	return *c1;
}

list<Crianca>& Jogo::inverte() {
	//criancas.reverse(); //EASY WAY

	list<Crianca> criancasBack = criancas;
	list<Crianca>::iterator it1 = criancasBack.begin();
	list<Crianca>::iterator it2 = criancas.end();
	it2--;
	for (; it1 != criancasBack.end(); it1++, it2--) {
		(*it2) = (*it1);
	}
	return criancas;
}

list<Crianca> Jogo::divide(unsigned id) {

	list<Crianca> criancasBack;
	list<Crianca>::const_iterator it;
	for (it = criancas.begin(); it != criancas.end(); it++) {
		if (it->getIdade() > id) {
			criancasBack.push_back(*it);
		}
	}
	return criancasBack;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	criancas = l1;
}

bool Jogo::operator==(Jogo& j2) {
	list<Crianca>::const_iterator it1 = criancas.begin();
	list<Crianca>::const_iterator it2 = j2.criancas.begin();

	if (criancas.size() != j2.criancas.size())
		return false;

	for (; it1 != criancas.end(); it1++, it2++) {
		if (!(*it1 == *it2))
			return false;
	}
	return true;
}

bool searchNumberInVector(vector<int> auxVector, int aux){
	for(unsigned int i = 0; i <auxVector.size(); i++){
		if(aux == auxVector[i])
			return false;
	}
	return true;
}
list<Crianca> Jogo::baralha() const {
	srand (time(NULL));
	list<Crianca> res;
	int aux = 0;
	int i = 0;
	vector<int> auxVector;
	list<Crianca>::const_iterator it1 = criancas.begin();

	while (auxVector.size() != criancas.size()) {
		do{
			i = (rand()%criancas.size()+1);
		}while (!searchNumberInVector(auxVector, i));
		auxVector.push_back(i);

		for (; it1 != criancas.end(); it1++) {
			aux++;
			if(aux == i){
				res.push_back(*it1);
				aux = 0;
				it1 = criancas.begin();
				break;
			}
		}
	}

	return res;
}
