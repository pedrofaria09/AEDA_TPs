#ifndef PARQUE_H_
#define PARQUE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCartao {
public:
	string nome;
	bool presente;
	int frequencia;
	bool operator ==(const InfoCartao &ic1) const;
	bool operator <(const InfoCartao &ic1) const;
	int getFrequencia(const string &nome) const;
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	vector<InfoCartao> clientes;
	unsigned int numClientes;
	const unsigned int numMaximoClientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	~ParqueEstacionamento();
	vector<InfoCartao> getClientes() const;
	bool adicionaCliente(const string & nome);
	bool retiraCliente(const string & nome);
	bool entrar(const string & nome);
	bool sair(const string & nome);
	unsigned int getNumLugares() const;
	unsigned int getNumLugaresOcupados() const;
	int posicaoCliente(const string & nome) const;
	friend ostream & operator<<(ostream & os, const ParqueEstacionamento & pe);
	int getFrequencia(const string &nome) const;
	InfoCartao getClienteAtPos(vector<InfoCartao>::size_type p) const;
	void ordenaClientesPorFrequencia();
	void ordenaClientesPorNome();
	vector<string> clientesGamaUso(int n1, int n2);
	friend ostream & operator<<(ostream &os, const ParqueEstacionamento &pe);

};

class ClienteNaoExistente {
public:
	string nome;
	ClienteNaoExistente(InfoCartao &cliente){
		this->nome = cliente.nome;
	}
	string getNome(){
		return nome;
	}
};

class PosicaoNaoExistente {
public:
	int valor;
	PosicaoNaoExistente(int pos){
		valor = pos;
	}
	int getValor(){
		return valor;
	}
};

#endif /*PARQUE_H_*/
