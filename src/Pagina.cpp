#include "..\include\Pagina.h"
#include "..\include\ElementoPaginaFolha.h"
#include <iostream>


Pagina::Pagina(int tamanho, int tipo){
    this->elementos = new ElementoPaginaFolha[tamanho + 1];
    this->tamanhoLivre = tamanho;
    this->tamanho = tamanho;
    this->tipo = tipo;
    this->pagPai = nullptr;
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

        
        
        

        for (int j = i + 1; j < indexOrdencao; ++j) {



            if (elementos[i].getPrioridade() < elementos[j].getPrioridade()) { // Ordena por chave decrescente
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

void Pagina::setProxPag(Pagina* apontarPara) // Note o uso de & aqui
{
    this->proxPag = apontarPara;
}

Pagina *Pagina::getPagPai()
{
    return this->pagPai;
}
void Pagina::setPagPai(Pagina *apontarPara)
{
    this->pagPai = apontarPara;
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

   for (int i = 0; i < tamanho - tamanhoLivre; i++)
   {
        if (prioridade < elementos[i].getPrioridade())
        {
            return &elementos[i];
        }
        
   }

   
    return  &elementos[tamanho - tamanhoLivre - 1]; 
}

bool Pagina::addelementoIndice(ElementoPagina *&elemento)
{

    ElementoPaginaFolha * novoElemento = new ElementoPaginaFolha(elemento->getPrioridade(), elemento->getProx(), elemento->getAnt(), nullptr);
    
    // Verifica se ainda há espaço livre
     std::cout<<tamanho - tamanhoLivre<<std::endl;
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
     

    // Limpa os elementos que foram movidos para a nova página
    for (int i = meio; i < tamanho + 1 - tamanhoLivre; ++i) {
        elementos[i] = ElementoPaginaFolha();  // Deleta os elementos que foram movidos
    }

    tamanhoLivre = (tamanho - meio); 

   // novaPagina->exibirChaves();


    // Retorna a nova página
    return novaPagina;
}

void Pagina::exibirChaves()
{

    int tam  = tamanho - tamanhoLivre;

    for (int i = 0; i < tam; i++)
    {
        elementos[i].getChave()->exibirDados();
    }
    
}
