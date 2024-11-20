
#ifndef ELEMENTOPAGINA_H
#define ELEMENTOPAGINA_H


#include "Paciente.h"
#include "Pagina.h"

class ElementoPagina
{
private:
    int  prioridade;
    Pagina * prox;
    Pagina *ant;
   

public:

ElementoPagina(int prioridade = 0, Pagina* prox = nullptr, Pagina* ant = nullptr) 
        : prioridade(prioridade), prox(prox), ant(ant) {}

    // Getters
    int getPrioridade() const ;
    Pagina* getProx() const ;
    Pagina* getAnt() const ;
    

    // Setters
    void setPrioridade(int prioridade);
    void setProx(Pagina* prox);
    void setAnt(Pagina* ant);
    

    virtual ~ElementoPagina();
    
   
};



#endif