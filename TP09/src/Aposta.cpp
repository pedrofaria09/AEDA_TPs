#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const {
	for (auto n : numeros) {
		if (num == n)
			return true;
	}
	return false;
}

bool Aposta::verificaValor(unsigned valor) {
	for (auto n : numeros) {
		if (valor == n)
			return false;
	}
	return true;
}

void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n) {
	unsigned int aux = 0;

	for (auto v : valores) {
		if (verificaValor(v) && aux < n) {
			numeros.insert(v);
			aux++;
		}
	}

}

unsigned Aposta::calculaCertos(const tabHInt & sorteio) const {
	unsigned certos = 0;
	for (auto s : sorteio){
		if(contem(s))
			certos++;
	}
	return certos;
}

