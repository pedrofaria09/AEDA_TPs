#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template<class N, class A> class Aresta;

template<class N, class A>
class No {
public:
	N info;
	vector<Aresta<N, A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template<class N, class A>
class Aresta {
public:
	A valor;
	No<N, A> *destino;
	Aresta(No<N, A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template<class N, class A>
class Grafo {
	vector<No<N, A> *> nos;
public:
	Grafo();
	~Grafo();
	Grafo & inserirNo(const N &dados);
	Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
	Grafo & eliminarAresta(const N &inicio, const N &fim);
	A & valorAresta(const N &inicio, const N &fim);
	int numArestas(void) const;
	int numNos(void) const;
	void imprimir(std::ostream &os) const;
};

template<class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N, A> &g);

// excecao  NoRepetido
template<class N>
class NoRepetido {
public:
	N info;
	NoRepetido(N inf) {
		info = inf;
	}
};
template<class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no) {
	out << "No repetido: " << no.info;
	return out;
}

// excecao NoInexistente
template<class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template<class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni) {
	out << "No inexistente: " << ni.info;
	return out;
}

//================== Pergunta a) ==================
template<class N, class A>
inline Grafo<N, A>::Grafo() {

}

template<class N, class A>
inline Grafo<N, A>::~Grafo() {

}

template<class N, class A>
inline int Grafo<N, A>::numArestas(void) const {
	int soma = 0;
	for (unsigned int i = 0; i < nos.size(); i++) {
		soma += nos[i]->arestas.size();
	}
	return soma;
}

template<class N, class A>
inline int Grafo<N, A>::numNos(void) const {
	return nos.size();
}

//================== Pergunta b) ==================
template<class N, class A>
inline Grafo<N, A>& Grafo<N, A>::inserirNo(const N& dados) {
	for (int i = 0; i < numNos(); i++) {
		if (nos[i]->info == dados)
			throw NoRepetido<N>(dados);
	}
	No<N, A> *novo = new No<N, A>(dados);
	nos.push_back(novo);
	return *this;
}

//================== Pergunta c) ==================
// excecao ArestaRepetida
template<class N>
class ArestaRepetida {
public:
	N noInicio;
	N noFim;
	ArestaRepetida(N noI, N noF) {
		noInicio = noI;
		noFim = noF;
	}
	;
};
template<class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar) {
	out << "Aresta repetida: " << ar.noInicio << " , " << ar.noFim;
	return out;
}

template<class N, class A>
inline Grafo<N, A>& Grafo<N, A>::inserirAresta(const N& inicio, const N& fim,
		const A& val) {
	bool flag = 0;
	bool encontra = 0;
	for (int i = 0; i < numNos(); i++) {
		if (nos[i]->info == inicio) {
			flag = 1;
			encontra = 1;
		}
		for (unsigned int j = 0; j < nos[i]->arestas.size(); j++) {
			if ((nos[i]->info == inicio)
					&& (nos[i]->arestas[j].destino->info == fim)) {
				throw ArestaRepetida<N>(inicio, fim);
				flag = 0;
			}
		}
		if (flag == 1) {
			for (unsigned int k = 0; k < nos.size(); k++) {
				if (nos[k]->info == fim) {
					Aresta<N, A> novaAresta(nos[k], val);
					nos[i]->arestas.push_back(novaAresta);
				}
			}
		}
		if (encontra == 0 && i == numNos() - 1)
			throw NoInexistente<N>(inicio);
		flag = 0;

	}
	return *this;
}

//================== Pergunta d) ==================
// excecao ArestaRepetida
template<class N>
class ArestaInexistente {
public:
	N noInicio;
	N noFim;
	ArestaInexistente(N noI, N noF) {
		noInicio = noI;
		noFim = noF;
	}

};
template<class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ar) {
	out << "Aresta inexistente: " << ar.noInicio << " , " << ar.noFim;
	return out;
}

template<class N, class A>
inline A& Grafo<N, A>::valorAresta(const N& inicio, const N& fim) {
	for (unsigned int i = 0; i < nos.size(); i++) {
		if (inicio == nos[i]->info) {
			for (unsigned int j = 0; j < nos[i]->arestas.size(); j++) {
				if (nos[i]->arestas[j].destino->info == fim) {
					return nos[i]->arestas[j].valor;
				}
				if (j == nos[i]->arestas.size() - 1) {
					throw ArestaInexistente<N>(inicio, fim);
				}
			}
		}
		throw NoInexistente<N>(inicio);
	}
}
//================== Pergunta e) ==================
template<class N, class A>
inline Grafo<N, A>& Grafo<N, A>::eliminarAresta(const N& inicio, const N& fim) {
	bool flag = 0;
	bool encontra = 0;
	for (unsigned int i = 0; i < nos.size(); i++) {
		if (inicio == nos[i]->info) {
			encontra = 1;
			for (unsigned int j = 0; j < nos[i]->arestas.size(); j++) {
				if (nos[i]->arestas[j].destino->info == fim) {
					nos[i]->arestas.erase(nos[i]->arestas.begin() + j);
					flag = 1;
				}
			}
		}
		if (encontra == 0 && (i == numNos() - 1))
			throw NoInexistente<N>(inicio);
	}
	if (flag == 0)
		throw ArestaInexistente<N>(inicio, fim);
	return *this;
}

//================== Pergunta f) ==================
template<class N, class A>
inline void Grafo<N, A>::imprimir(std::ostream& os) const {
	stringstream ss, s1;
	for (unsigned int i = 0; i < nos.size(); i++) {
		for (unsigned int j = 0; j < nos[i]->arestas.size(); j++) {
			ss << "[ " << nos[i]->arestas[j].destino->info << " "
					<< nos[i]->arestas[j].valor << "] ";
		}
		os << "( " << nos[i]->info << ss.str() << ") ";
		ss.str("");
	}
}

//================== Pergunta g) ==================
template<class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N, A> &g) {
	g.imprimir(out);
}
