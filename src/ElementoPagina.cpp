#include "..\include\ElementoPagina.h"

int ElementoPagina::getPrioridade() const { return prioridade; }

Pagina *ElementoPagina::getProx() const { return prox; }

Pagina *ElementoPagina::getAnt() const { return ant; }

void ElementoPagina::setPrioridade(int prioridade) { this->prioridade = prioridade; }

void ElementoPagina::setProx(Pagina *prox) { this->prox = prox; }

void ElementoPagina::setAnt(Pagina *ant) { this->ant = ant; }

ElementoPagina::~ElementoPagina(){}