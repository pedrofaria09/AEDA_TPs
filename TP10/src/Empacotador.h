/*
 * Empacotador.h
 */

#ifndef EMPACOTADOR_H_
#define EMPACOTADOR_H_

#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include "Caixa.h"
using namespace std;

typedef priority_queue<Objeto> HEAP_OBJS;
typedef priority_queue<Caixa> HEAP_CAIXAS;

class MaquinaEmpacotar {
	HEAP_OBJS objetos;
	HEAP_CAIXAS caixas;
	unsigned capacidadeCaixas;
public:
	MaquinaEmpacotar(int capCaixas = 10);
	unsigned numCaixasUsadas();
	unsigned addCaixa(Caixa& cx);

	unsigned carregaPaletaObjetos(vector<Objeto> &objs);
	Caixa procuraCaixa(Objeto& obj);
	unsigned empacotaObjetos();
	string imprimeObjetosPorEmpacotar() const;
	Caixa caixaMaisObjetos() const;
	class MaquinaSemCaixas{};
};

#endif /* EMPACOTADOR_H_ */
