#include "Jogo.h"
#include <sstream>
BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}

ostream &operator <<(ostream &os, Circulo &c1) {
	// a alterar
	return os;
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados) {
	jogo = iniciaJogo(0, niv, pontos, estados);
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos,
		vector<bool> &estados) {
	Circulo c1(pontos[pos], estados[pos]);
	if (niv == 0)
		return BinaryTree<Circulo>(c1);

	BinaryTree<Circulo> filhoEsquerdo = iniciaJogo(2 * pos + 1, niv - 1, pontos,
			estados);
	BinaryTree<Circulo> filhoDireito = iniciaJogo(2 * pos + 2, niv - 1, pontos,
			estados);

	return BinaryTree<Circulo>(c1, filhoEsquerdo, filhoDireito);
}

string Jogo::escreveJogo() {
	BTItrLevel<Circulo> it(jogo);
	stringstream ss;
	while(!it.isAtEnd()){
		if(it.retrieve().getEstado())
			ss << it.retrieve().getPontuacao() << "-true-" << it.retrieve().getNVisitas() << "\n";
		else
			ss << it.retrieve().getPontuacao() << "-false-" << it.retrieve().getNVisitas() << "\n";
		it.advance();
	}
	return ss.str();
}

int Jogo::jogada() {
// a alterar
	return 0;
}

int Jogo::maisVisitado() {
// a alterar
	return 0;
}

