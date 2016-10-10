#include "Parque.h"
#include <vector>

using namespace std;

//================= PERGUNTA a) =================
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,
		unsigned int nMaxCli) :
		lotacao(lot), numMaximoClientes(nMaxCli) {
	lot = 0;
	vagas = numMaximoClientes;
}

//Devolve a lotacao do parque
unsigned int ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}

//Devolve o numero máximo de clientes
unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
	return numMaximoClientes;
}

//================= PERGUNTA b) =================
//Devolve a posicao do cliente no vetor InfoCartao
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i].nome == nome)
			return i;
	}
	return -1;
}

//Verifica se adicionou/registou corretamente o registo do cliente ao parque (Cliente está fora do parque)
bool ParqueEstacionamento::adicionaCliente(const string & nome) {
	InfoCartao novoCliente;
	novoCliente.nome = nome;
	novoCliente.presente = false;
	if (clientes.size() != getNumMaximoClientes()) {
		clientes.push_back(novoCliente);
		vagas--;
		return true;
	}
	return false;
}

//================= PERGUNTA c) =================
//Verifica se o cliente pode entrar no parque. Tem de estar registado, a viatura nao estar presente no parque e o parque ter vagas
bool ParqueEstacionamento::entrar(const string & nome) {
	if (adicionaCliente(nome)
			&& (clientes[posicaoCliente(nome)].presente == false)) {
		clientes[posicaoCliente(nome)].presente = true;
		return true;
	}
	return false;
}

//================= PERGUNTA d) =================
//Verifica a remocao do registo do cliente. Este tem de estar fora do parque e o cliente tem de existir.
bool ParqueEstacionamento::retiraCliente(const string & nome) {
	if ((clientes[posicaoCliente(nome)].presente == false)
			&& posicaoCliente(nome) != -1) {
		clientes.erase(clientes.begin() + posicaoCliente(nome));
		vagas++;
		return true;
	}
	return false;
}

//================= PERGUNTA e) =================
//Verifica se o cliente pode sair, tem de estar registado e a viatura estar dentro do parque.
bool ParqueEstacionamento::sair(const string & nome) {
	if ((posicaoCliente(nome) != -1)
			&& (clientes[posicaoCliente(nome)].presente == true)) {
		clientes[posicaoCliente(nome)].presente = false;
		return true;
	}
	return false;
}

//================= PERGUNTA f) =================
//Devolve numero de lugares ocupados no parque
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
	int nrLugaresOcupados = 0;
	for (unsigned int i = 0; i < clientes.size(); i++) {
		if (clientes[i].presente == true)
			nrLugaresOcupados++;
	}
	return nrLugaresOcupados;

}

//Devolve numero de clientes registados
unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
	return numMaximoClientes - getNumLugaresOcupados();
}

//================= PERGUNTA g) =================
const ParqueEstacionamento & ParqueEstacionamento::operator +=(
		const ParqueEstacionamento & p2) {
	for (vector<InfoCartao>::const_iterator it = p2.clientes.begin();
			it != p2.clientes.end(); it++) {
		adicionaCliente(it->nome);
		if (clientes.size() == numMaximoClientes)
			break;
	}
	return *this;
}
