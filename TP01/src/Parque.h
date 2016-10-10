#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCartao {
public:
	string nome;
	bool presente;
};

class ParqueEstacionamento {
	unsigned int vagas;						//N�mero de lugares vagos
	const unsigned int lotacao;				//N�mero de lugares ocupados no momento
	vector <InfoCartao> clientes;			//Vetor de clientes(Nome e presen�a)
	const unsigned int numMaximoClientes;	//N�mero M�ximo de clientes com acesso ao parque
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	bool adicionaCliente(const string & nome);
	bool retiraCliente(const string & nome);
	bool entrar(const string & nome);
	bool sair(const string & nome);
	int posicaoCliente(const string & nome) const;
	unsigned int getNumLugares() const;
	unsigned int getNumMaximoClientes() const;
	unsigned int getNumLugaresOcupados() const;
	unsigned int getNumClientesAtuais() const;
	const ParqueEstacionamento & operator += (const ParqueEstacionamento & p2);
};
