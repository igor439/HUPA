#include "..\include\Pagina.h"
#include "..\include\ElementoPaginaFolha.h"
#include <iostream>


Pagina::Pagina(int tamanho, int tipo){
    this->elementos = new ElementoPaginaFolha[tamanho + 1];
    this->tamanhoLivre = tamanho;
    this->tamanho = tamanho;
    this->tipo = tipo;
}

Pagina::~Pagina()
{
    delete[] elementos;
}

ElementoPaginaFolha *Pagina::getElementos() const { return elementos; }

void Pagina::setElementos(ElementoPaginaFolha *elementos) { this->elementos = elementos; }


ElementoPaginaFolha * Pagina::getElemento(int indice) const
{
    if (indice >= 0 && indice < tamanho) 
        return &elementos[indice];
    return nullptr;  // Retorna nulo se o índice for inválido
}

bool Pagina::addelemento(ElementoPaginaFolha *&elemento)
{

    ElementoPaginaFolha * novoElemento = new ElementoPaginaFolha(elemento->getPrioridade(), elemento->getProx(), elemento->getAnt(), elemento->getChave());
    
    // Verifica se ainda há espaço livre
    
    if (tamanhoLivre <= 0) {

        
        
        elementos[tamanho - tamanhoLivre] = *novoElemento;
        
        this->oredenarArray(tamanho + 1);

        int meio = tamanho / 2;

        elemento = &elementos[meio];


        
        return false;
    }
    else{

        

        // Insere o novo elemento na última posição disponível
        elementos[tamanho - tamanhoLivre] = *novoElemento;
        tamanhoLivre--;
        



        this->oredenarArray(tamanho - tamanhoLivre);

        return true;


    }

    
    
}




int Pagina::getTamanhoLivre(){
    return this->tamanhoLivre;

}
void Pagina::oredenarArray(int indexOrdencao)
{

    
    
    // Realiza uma ordenação decrescente para manter o array ordenado


    for (int i = 0; i < indexOrdencao; ++i) {

        if (indexOrdencao == 10)
        {
            std::cout << "Paciente: "<< i << std::endl;

            elementos[i].getChave()->exibirDados();

            std::cout << "================================= "<< std::endl;

        }
        
        

        for (int j = i + 1; j < indexOrdencao; ++j) {



            if (elementos[i].getChave()->prioridade < elementos[j].getChave()->prioridade) { // Ordena por chave decrescente
                // Troca os elementos
                ElementoPaginaFolha temp = elementos[i];
                elementos[i] = elementos[j];
                elementos[j] = temp;
            }

            
        }
    }


}

Pagina *Pagina::getProxPag()
{
    return this->proxPag;
}

void Pagina::setProxPag(Pagina& apontarPara) // Note o uso de & aqui
{
    this->proxPag = &apontarPara;
}

int Pagina::getElementosAdicionados()
{
    return this->tamanho - this->tamanhoLivre;
}

int Pagina::getTipo()
{
    return this->tipo;
}

ElementoPaginaFolha *Pagina::buscarPorPrioridade(int prioridade)
{

   for (int i = 0; i < tamanho - tamanhoLivre; ++i) { // Itera pelos elementos adicionados
        if (elementos[i].getPrioridade() == prioridade) {
            return &elementos[i]; // Retorna o endereço do elemento encontrado
        }
        else if(elementos[i].getPrioridade() > prioridade){
            return &elementos[i];
        }
    }
    return  &elementos[tamanho]; // Retorna nullptr se não encontrar
}

bool Pagina::addelementoIndice(ElementoPagina *&elemento)
{

    
    
    // Verifica se ainda há espaço livre
    
    if (tamanhoLivre <= 0) {
        
        elementos[tamanho - tamanhoLivre] = *dynamic_cast<ElementoPaginaFolha*>(elemento);
        
        
        this->oredenarArray(tamanho);

        int meio = tamanho / 2;

        elemento = &elementos[meio];


        
        return false;
    }

    // Insere o novo elemento na última posição disponível
    elementos[tamanho - tamanhoLivre - 1] = *dynamic_cast<ElementoPaginaFolha*>(elemento);
    tamanhoLivre--;
    



    this->oredenarArray(tamanho - tamanhoLivre - 1);

    return true;
}

Pagina* Pagina::split() {
    // Calcula o índice do meio
    int meio = tamanho / 2;

    // Cria a nova página que representará a parte direita
    Pagina* novaPagina = new Pagina(tamanho, this->tipo); // A nova página tem o mesmo tamanho que a original

    // Copia os elementos do meio até o final para a nova página
    for (int i = meio; i < tamanho + 1 - tamanhoLivre ; ++i) {
         ElementoPaginaFolha * novoElemento = &elementos[i];
        novaPagina->addelemento(novoElemento);  // Adiciona os elementos da segunda metade
    }

    // Atualiza a página original para remover os elementos da segunda metade
    tamanhoLivre += (tamanho - meio);  // Aumenta o espaço livre, pois os elementos foram movidos para a nova página

    // Limpa os elementos que foram movidos para a nova página
    for (int i = meio; i < tamanho; ++i) {
        elementos[i] = ElementoPaginaFolha();  // Deleta os elementos que foram movidos
    }

    // Retorna a nova página
    return novaPagina;
}
