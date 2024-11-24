#include "../include/ElementoPaginaFolha.h"
#include "../include/Paciente.h"
#include "../include/Pagina.h"


void ElementoPaginaFolha::setChave(Paciente *novaChave) { chave = novaChave; }

Paciente *ElementoPaginaFolha::getChave() const
{
    return this->chave;
}