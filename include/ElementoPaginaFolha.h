#ifndef ELEMENTOPAGINAFOLHA_H
#define ELEMENTOPAGINAFOLHA_H

#include "ElementoPagina.h"
#include "Paciente.h"
#include "Pagina.h"

class ElementoPaginaFolha : public ElementoPagina
{
    private:
        Paciente* chave; // Armazena o ponteiro para o paciente

    public:
        // Construtor com parâmetros padrão e inicialização de chave
        ElementoPaginaFolha(int prioridade = 0, Pagina* prox = nullptr, Pagina* ant = nullptr, Paciente* chave = nullptr)
        : ElementoPagina(prioridade, prox, ant), chave(chave){}

        // Getter para chave
        Paciente* getChave() const ;

        // Setter para chave
        void setChave(Paciente* novaChave);
};
#endif