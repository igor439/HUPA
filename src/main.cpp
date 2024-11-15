#include "..\include\Paciente.h"
#include "..\include\Medico.h"
#include "..\include\Especialidade.h"
#include "..\include\Sala.h"
#include "..\include\Controller.h"
#include "..\include\Pagina.h"
#include "..\include\ElementoPaginaFolha.h"


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

        int tam = pacientes.size();

        for (int i = 0; i < tam; i++)
        {

            while (raiz->getTipo() != 0)
            {
                ElementoPaginaFolha * elementoDecida = raiz->buscarPorPrioridade(pacientes[i].prioridade);

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

                Pagina * navaPaginaIndices = new  Pagina(tamanhoPagina,1);

                ElementoPagina* elementoMeio = novoElemento;

                elementoMeio->setProx(novaPaginaFolha);
                elementoMeio->setAnt(raiz);


                navaPaginaIndices->addelementoIndice(elementoMeio);

                raiz = navaPaginaIndices;

            
                

                
                



            }
            
            

            
            

            


            
        }
        
    }



   
    

}