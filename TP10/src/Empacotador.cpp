/*
 * Empacotador.cpp
 */

#include "Empacotador.h"

MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas) :
		capacidadeCaixas(capCaixas) {
}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	int conta = 0;
	vector<Objeto>::iterator it;

	for (it = objs.begin(); it != objs.end(); it++) {
		if ((*it).getPeso() <= capacidadeCaixas) {
			objetos.push((*it));
			objs.erase(it);
			conta++;
			it--;
		}
	}
	return conta;
}

Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
	bool found = 0;

	vector<Caixa> backup;

	while (!caixas.empty() && !found) {
		if (caixas.top().getCargaLivre() >= obj.getPeso()) {
			cx = caixas.top();
			found = 1;
		} else
			backup.push_back(caixas.top());
		caixas.pop();
	}

	for (auto ba : backup)
		caixas.push(ba);

	if (!found)
		return Caixa();
	else
		return cx;
}

unsigned MaquinaEmpacotar::empacotaObjetos() {
	unsigned conta = 0;

	while (!objetos.empty()) {
		Objeto ob = objetos.top();
		Caixa cx = procuraCaixa(ob);

		if (cx.getSize() == 0)
			conta++;

		cx.addObjeto(ob);
		caixas.push(cx);
		objetos.pop();
	}

	return conta;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	priority_queue<Objeto> backup = objetos;
	stringstream texto;

	if (objetos.empty()) {
		return "Nao ha objetos!\n";
	}

	while (!backup.empty()) {
		Objeto ob = backup.top();
		texto << ob << "\n";
		backup.pop();
	}

	return texto.str();
}

string Caixa::imprimeConteudo() const {
	stringstream texto;

	stack<Objeto> backup = objetos;
	if (objetos.empty()) {
		texto << "Caixa " << getID() << " vazia!\n";
		return texto.str();
	}

	texto << "C" << getID() << "[ ";
	while (!backup.empty()) {
		Objeto ob = backup.top();
		texto << ob << " ";
		backup.pop();
	}
	texto << "]";

	return texto.str();
}

Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	unsigned int nrObjetos = 0;

	priority_queue<Caixa> backupCaixa = caixas;

	if(caixas.empty()) {
		throw MaquinaSemCaixas();
	}

	while(!backupCaixa.empty()){

		if(backupCaixa.top().getSize() > nrObjetos){
			cx = backupCaixa.top();
			nrObjetos = cx.getSize();
		}
		backupCaixa.pop();
	}

	return cx;
}

