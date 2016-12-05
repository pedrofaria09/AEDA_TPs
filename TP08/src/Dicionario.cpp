#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"
#include <sstream>

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

bool PalavraSignificado::operator <(const PalavraSignificado &ps1) const {
	if( palavra < ps1.palavra)
		return true;
	return false;
}

void Dicionario::lerDicionario(ifstream &fich) {
	string nome, significado;
	while (getline(fich, nome)) {
		getline(fich, significado);
		PalavraSignificado* palavra = new PalavraSignificado(nome, significado);
		palavras.insert(*palavra);
	}
	return;
}

string Dicionario::consulta(string palavra) const {
	BSTItrIn<PalavraSignificado> it(palavras);
	string aux;
	while(!it.isAtEnd()){
		if(it.retrieve().getPalavra() == palavra)
			aux = it.retrieve().getSignificado();
		it.advance();
	}
	if(aux.length() != 0)
		return aux;
}

bool Dicionario::corrige(string palavra, string significado) {
	BSTItrIn<PalavraSignificado> it(palavras);
	while(!it.isAtEnd()){
		if(it.retrieve().getPalavra() == palavra){
			it.retrieve().setSignificado(significado);
			return true;
		}

		it.advance();
	}
	PalavraSignificado* palavraNova = new PalavraSignificado(palavra, "");
	palavras.insert(*palavraNova);
	return false;
}

void Dicionario::imprime() const {
	BSTItrIn<PalavraSignificado> it(palavras);

	while(!it.isAtEnd()){
		cout << it.retrieve().getPalavra() << endl;
		cout << it.retrieve().getSignificado() << endl;
		it.advance();
	}
}
