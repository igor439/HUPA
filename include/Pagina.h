

#ifndef PAGINA_H
#define PAGINA_H


class ElementoPaginaFolha;

class Pagina
{
    private:

    ElementoPaginaFolha * elementos;
    Pagina * proxPag;
    int tamanho;
    int tamanhoLivre;
    int  tipo; // 0 para folha e 1 para nó com filhos

        
    public:

      // Construtor e destrutor
    Pagina(int tamanho, int tipo);
    
    
    ~Pagina() ;

    // Getters
    ElementoPaginaFolha* getElementos() const ;
    int getTamanho() const { return tamanho; }

    // Setters
    void setElementos(ElementoPaginaFolha* elementos);
   

    // Método para acessar um elemento específico
    ElementoPaginaFolha* getElemento(int indice) const ;
    

    // Método para definir um elemento específico
    bool addelemento(ElementoPaginaFolha *&elemento);

    int getTamanhoLivre();

    void oredenarArray(int indexOrdencao);

    Pagina * getProxPag();

    void setProxPag(Pagina& apontarPara);

    int getElementosAdicionados();


    int getTipo();
    ElementoPaginaFolha* buscarPorPrioridade(int prioridade);

    bool addelementoIndice(ElementoPagina *&elemento);

    Pagina* split();
     
};




#endif