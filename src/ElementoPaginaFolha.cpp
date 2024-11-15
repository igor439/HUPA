#include "../include/ElementoPaginaFolha.h"
#include "../include/Paciente.h"
#include "../include/Pagina.h"


Paciente *ElementoPaginaFolha::getChave() const{ return chave; }
void ElementoPaginaFolha::setChave(Paciente *novaChave){ chave = novaChave; }