#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <sstream>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,
		unsigned int nMaxCli) :
		lotacao(lot), numMaximoClientes(nMaxCli) {
	numClientes = 0;
	vagas = lot;
}

ParqueEstacionamento::~ParqueEstacionamento() {
}

vector<InfoCartao> ParqueEstacionamento::getClientes() const {
	return clientes;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
	if (numClientes == numMaximoClientes)
		return false;
	if (posicaoCliente(nome) != -1)
		return false;
	InfoCartao info;
	info.nome = nome;
	info.presente = false;
	info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
	for (vector<InfoCartao>::iterator it = clientes.begin();
			it != clientes.end(); it++)
		if (it->nome == nome) {
			if (it->presente == false) {
				clientes.erase(it);
				numClientes--;
				return true;
			} else
				return false;
		}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao - vagas;
}

bool ParqueEstacionamento::entrar(const string & nome) {
	if (vagas == 0)
		return false;
	int pos = posicaoCliente(nome);
	if (pos == -1)
		return false;
	if (clientes[pos].presente == true)
		return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome) {
	int pos = posicaoCliente(nome);
	if (pos == -1)
		return false;
	if (clientes[pos].presente == false)
		return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

// PERGUNTA a)
bool InfoCartao::operator ==(const InfoCartao &ic1) const {
	if (ic1.nome == nome)
		return true;
	return false;
}
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao cliente;
	cliente.nome = nome;

	int pos = sequentialSearch(clientes, cliente);

	return pos;
}

// Pergunta b)
int ParqueEstacionamento::getFrequencia(const string &nome) const {
	InfoCartao cliente;
	cliente.nome = nome;

	if (posicaoCliente(nome) == -1)
		throw ClienteNaoExistente(cliente);

	return getClientes()[posicaoCliente(nome)].frequencia;

}

// Pergunta c)
bool InfoCartao::operator <(const InfoCartao &ic1) const {
	if (ic1.frequencia == frequencia)
		return nome < ic1.nome;
	else if (ic1.frequencia < frequencia)
		return true;
	return false;
}
void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

// Pergunta d)
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	vector<string> cli;
	ordenaClientesPorFrequencia();
	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2) {
			cli.push_back(clientes[i].nome);
		}
	}
	return cli;
}

// Pergunta e)
void ParqueEstacionamento::ordenaClientesPorNome() {
	InfoCartao clienteTemp;

	for (unsigned int i = 0; i < clientes.size(); i++) {
		for (unsigned int j = i + 1; j < clientes.size(); j++) {
			if (clientes[i].nome > clientes[j].nome) {
				clienteTemp = clientes[i];
				clientes[i] = clientes[j];
				clientes[j] = clienteTemp;
			}
		}
	}
}

// Pergunta f)
InfoCartao ParqueEstacionamento::getClienteAtPos(
		vector<InfoCartao>::size_type p) const {

	if(p < clientes.size())
		return clientes[p];
	else
		throw PosicaoNaoExistente(p);
}

ostream & operator<<(ostream &os, const ParqueEstacionamento &pe) {
	stringstream ss;
	for (unsigned int i = 0; i < pe.getClientes().size(); i++) {
		ss << pe.getClientes()[i].nome << pe.getClientes()[i].presente
				<< pe.getClientes()[i].frequencia;
	}
	os << ss.str();
}
