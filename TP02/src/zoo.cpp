#include "zoo.h"

string Animal::getNome() const {
	return nome;
}

string Veterinario::getNome() const {
	return nome;
}

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

//=============== Pergunta a) ===============
Veterinario::Veterinario(string nome, long codOrdem) {
	this->nome = nome;
	this->codOrdem = codOrdem;
}

int Animal::maisJovem = 1000;
Animal::Animal(string nome, int idade) {
	this->nome = nome;
	this->idade = idade;

	if (idade < maisJovem)
		maisJovem = idade;
}

Cao::Cao(string nome, int idade, string raca) :
		Animal(nome, idade) {
	this->raca = raca;
}

Voador::Voador(int vmax, int amax) {
	velocidade_max = vmax;
	altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) :
		Animal(nome, idade), Voador(vmax, amax) {

}

int Animal::getMaisJovem() {
	return maisJovem;
}

bool Cao::eJovem() const {
	if (this->idade < 5)
		return true;
	else
		return false;
}

bool Morcego::eJovem() const {
	if (this->idade < 4)
		return true;
	else
		return false;
}

//=============== Pergunta b) ===============
void Zoo::adicionaAnimal(Animal *a1) {
	animais.push_back(a1);
}

//=============== Pergunta c) ===============
int Animal::getIdade() const {
	return idade;
}
string Zoo::getInformacao() const {
	stringstream nome;
	for (unsigned int i = 0; i < animais.size(); i++) {
		nome << animais[i]->getInformacao() << "\n";
	}
	return nome.str();
}

string Animal::getInformacao() const {
	stringstream stm;
	stm << getNome() << ", " << getIdade();
	return stm.str();
}

long Veterinario::getCodOrdem() const {
	return codOrdem;
}

string Cao::getInformacao() const {
	stringstream stm;
	if (this->vet == NULL)
		stm << Animal::getInformacao() << ", " << raca;
	else
		stm << Animal::getInformacao() << ", " << vet->getNome() << ", "
				<< vet->getCodOrdem() << ", " << raca;
	return stm.str();
}

int Voador::getVelocidadeMaxima() {
	return this->velocidade_max;
}
int Voador::getAlturaMaxima() {
	return this->altura_max;
}

string Voador::getInformacao() const {
	stringstream stm;
	stm << velocidade_max << ", " << altura_max;
	return stm.str();
}

string Morcego::getInformacao() const {
	stringstream stm;
	stm << Animal::getInformacao() << ", " << Voador::getInformacao();
	return stm.str();
}

//=============== Pergunta d) ===============
bool Zoo::animalJovem(string nomeA) {
	for (unsigned int i = 0; i < animais.size(); i++) {
		if ((animais[i]->getNome() == nomeA) && animais[i]->eJovem())
			return true;
	}
	return false;
}

//=============== Pergunta e) ===============
void Animal::setVetirinario(Veterinario *vet) {
	this->vet = vet;
}

Veterinario* Animal::getVetirinario() {
	return this->vet;
}

void Zoo::alocaVeterinarios(istream &isV) {
	string nome, codigoS;
	int codigoI = 0;
	while (getline(isV, nome)) {
		//If we put getline again we can get a new line!! COOL!!!
		getline(isV, codigoS);
		//convert from string to int
		codigoI = atoi(codigoS.c_str());
		Veterinario *veterinario = new Veterinario(nome, codigoI);
		veterinarios.push_back(veterinario);
	}

	for (unsigned int i = 0; i < animais.size(); i++) {
		animais[i]->setVetirinario(veterinarios[i]);
	}
}

//=============== Pergunta f) ===============
bool Zoo::removeVeterinario(string nomeV) {
	for (unsigned int i = 0; i < veterinarios.size(); i++) {
		for (unsigned int j = 0; j < animais.size(); j++){
			if((veterinarios[i]->getNome()==nomeV) && (animais[j]->getVetirinario()->getNome()==nomeV)){
				veterinarios.erase(veterinarios.begin() + i);
				//We dont need to increment i because vector veterinarios already decremented 1 with erase!!!!
				animais[j]->setVetirinario(veterinarios[i]);
				return true;
			}
		}
	}
	return false;
}

//=============== Pergunta h) ===============
bool Zoo::operator < (Zoo& zoo2) const{
	int soma1 = 0;
	int soma2 = 0;

	for(int i = 0; i < animais.size(); i++){
		soma1 += animais[i]->getIdade();
	}

	for(int i = 0; i < zoo2.animais.size(); i++){
		soma2 += zoo2.animais[i]->getIdade();
	}

	if(soma1<soma2)
		return true;
	return false;
	
}
