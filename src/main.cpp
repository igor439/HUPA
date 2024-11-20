#include "..\include\Paciente.h"
#include "..\include\Medico.h"
#include "..\include\Especialidade.h"
#include "..\include\Sala.h"
#include "..\include\Controller.h"
#include "..\include\Pagina.h"
#include "..\include\ElementoPaginaFolha.h"
#include "..\include\ElementoPagina.h"

int main() {

    int tamanhoPagina = 10;
    std::string nomeArquivo = "pacientes.csv";
    Controller controller;
    controller.exportarPacientesCSV(nomeArquivo);



    Especialidade especialidade =  Especialidade("Cardiologia");
    

    std::vector<Paciente> pacientes = especialidade.carregarPacientesDoCSV(nomeArquivo);






    if(!pacientes.empty()){

        
       // std::cin.get();

        Pagina * raiz = new  Pagina(tamanhoPagina,0);

        Pagina * auxdisplay = raiz;
        

        int tam = pacientes.size();
       
        Pagina * raizAncora = raiz;

        for (int i = 0; i < tam; i++)
        {

            
            while (raiz->getTipo() != 0)
            {
                
                

                ElementoPagina * elementoDecida = raiz->buscarPorPrioridade(pacientes[i].prioridade);

            
                
                
                if (elementoDecida->getPrioridade() <= pacientes[i].prioridade)
                {
                    

                    raiz = elementoDecida->getAnt();
                }
                else
                {
                    
                    raiz = elementoDecida->getProx();
                }

                
                
                
                
            }
            
          


            ElementoPaginaFolha * novoElemento = new ElementoPaginaFolha( pacientes[i].prioridade,   nullptr,   nullptr, &pacientes[i]);

            if (raiz->addelemento(novoElemento)) 
            {
                std::cout << "Elemento adicionado com sucesso!" << std::endl;
            } else {
                std::cout << "Página cheia! Cisão nescessária." << std::endl;

                

                Pagina * novaPaginaFolha = raiz->split();
                Pagina * pagPai = raiz->getPagPai();

                novaPaginaFolha->setProxPag(raiz->getProxPag());
                raiz->setProxPag(novaPaginaFolha);


                
                
                if (pagPai == nullptr)
                {
                
                    
                    Pagina * navaPaginaIndices = new  Pagina(tamanhoPagina,1);

                    ElementoPagina* elementoMeio = novoElemento;

                    elementoMeio->setProx(novaPaginaFolha);
                    elementoMeio->setAnt(raiz);

                    novaPaginaFolha->setPagPai(navaPaginaIndices);
                    raiz->setPagPai(navaPaginaIndices);

                    navaPaginaIndices->addelementoIndice(elementoMeio);
                    

                    raizAncora = navaPaginaIndices;
                }
                else{

                    
                    

                    ElementoPagina* elementoMeio = novoElemento;
                    elementoMeio->setProx(novaPaginaFolha);
                    elementoMeio->setAnt(raiz);

                   


                    

                    while (!pagPai->addelementoIndice(elementoMeio))
                    {
                         

                        Pagina *splitPagPai = pagPai->split();
                        Pagina * avo = pagPai->getPagPai();

                        elementoMeio->setProx(splitPagPai);
                        elementoMeio->setAnt(pagPai);

                        if (avo == nullptr)
                        {

                            Pagina * navaPaginaIndices = new  Pagina(tamanhoPagina,1);
                            pagPai->setPagPai(navaPaginaIndices);
                            splitPagPai->setPagPai(navaPaginaIndices);

                            pagPai = navaPaginaIndices;


                        }
                        else{
                           

                            pagPai = avo;
                            

                        }
                        

                        
                    // ajustar pra voltar pro topo
                        
                    }
                    
                    raizAncora = pagPai;

        
                }
               
 

            }
            

            raiz = raizAncora;


            
        }

        
/*
int count = 0;
        while (auxdisplay->getProxPag() != nullptr)
        {
            count++;
            std::cout<< "++++++++++++++++++++++++++++"<< std::endl;

            std::cout<< "PAGINA: "<< count << " tamanho: "<< auxdisplay->getTamanho() - auxdisplay->getTamanhoLivre()  << std::endl;

            std::cout<< "++++++++++++++++++++++++++++"<< std::endl;
            Pagina * aux = auxdisplay->getProxPag();

            auxdisplay->exibirChaves();

            auxdisplay = aux;


        }

*/
        //AS PAGINAS ESTAM COM TAMANHO 6, INVESTIGAR AMANHÃ
        
        


        
    


        
    }


    



   
    

}





