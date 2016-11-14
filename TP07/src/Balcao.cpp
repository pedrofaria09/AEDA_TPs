#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"
using namespace std;

Cliente::Cliente() {
	numPresentes = (rand() % 5 + 1);
}

int Cliente::getNumPresentes() const {
	return numPresentes;
}

Balcao::Balcao(int te) :
		tempo_embrulho(te) {
	tempo_atual = 0;
	prox_chegada = (rand() % 20 + 1);
	prox_saida = 0;
}

void Balcao::proximoEvento() {
	//Acho que está errado!!!
	if (!clientes.empty())
		if (prox_chegada < prox_saida){
			tempo_atual = tempo_atual + prox_chegada;
			saida();
		}
		else{
			tempo_atual = tempo_atual + prox_saida;
			saida();
		}
	else {
		tempo_atual = prox_chegada;
		chegada();
	}
}

void Balcao::chegada() {
	Cliente *cliente = new Cliente();
	if (clientes.empty()) {
		prox_saida = tempo_atual
				+ (cliente->getNumPresentes()) * tempo_embrulho;
	}
	clientes.push(*cliente);
	prox_chegada = (rand() % 20 + 1);
	cout << "Numero Presentes: " << cliente->getNumPresentes() << endl;
	cout << "Proxima chegada: " << prox_chegada << endl;
	cout << "Proxima saida: " << prox_saida << endl;

}

void Balcao::saida() {
	Cliente cliente = getProxCliente();
	clientes.pop();
	prox_saida = tempo_atual + (cliente.getNumPresentes()) * tempo_embrulho;
	cout << endl;
	cout << "Numero Presentes: " << cliente.getNumPresentes() << endl;
	cout << "Proxima saida: " << prox_saida << endl;
}

int Balcao::getTempoAtual() const {
	return tempo_atual;
}

int Balcao::getProxChegada() const {
	return prox_chegada;
}

int Balcao::getNrClientes() const{
	if (clientes.empty())
		return 0;
	return clientes.size();
}
ostream & operator <<(ostream & out, const Balcao & b1) {
	stringstream ss;
	ss << "\n" << b1.getClientesAtendidos() <<" - " << b1.getNrClientes() << "\n";
	out << ss.str();
	return out;
}

int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

int Balcao::getProxSaida() const {
	return prox_saida;
}

int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

Cliente & Balcao::getProxCliente() {
	if (clientes.empty()) {
		throw FilaVazia();
	}
	clientes_atendidos++;
	return clientes.front();
}

