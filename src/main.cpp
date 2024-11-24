#include "..\include\Paciente.h" // Inclui a classe Paciente para manipulação de objetos Paciente.
#include "..\include\Medico.h" // Inclui a classe Medico para manipulação de objetos Médico.
#include "..\include\Especialidade.h" // Inclui a classe Especialidade para gerenciar áreas médicas específicas.
#include "..\include\Sala.h" // Inclui a classe Sala para gerenciar salas no hospital.
#include "..\include\Controller.h" // Inclui a classe Controller para operações relacionadas ao controle de pacientes.
#include "..\include\Pagina.h" // Inclui a classe Pagina para a implementação da árvore B+.
#include "..\include\ElementoPaginaFolha.h" // Inclui a classe ElementoPaginaFolha para elementos das folhas da árvore B+.
#include "..\include\ElementoPagina.h" // Inclui a classe ElementoPagina para elementos de índice na árvore B+.
#include <algorithm>  // Para usar std::swap

// Função auxiliar para ajustar o heap máximo
void ajusteHeap(std::vector<Paciente>& vec, int n, int i) {
    int maior = i;  // Inicialmente, a raiz é o maior
    int esquerda = 2 * i + 1;  // Filho à esquerda
    int direita = 2 * i + 2;  // Filho à direita

    // Verifica se o filho à esquerda é maior que a raiz
    if (esquerda < n && vec[esquerda].prioridade > vec[maior].prioridade)
        maior = esquerda;

    // Verifica se o filho à direita é maior que o maior até agora
    if (direita < n && vec[direita].prioridade > vec[maior].prioridade)
        maior = direita;

    // Se o maior não for a raiz
    if (maior != i) {
        std::swap(vec[i], vec[maior]); // Troca a raiz com o maior

        // Ajusta recursivamente o sub-heap afetado
        ajusteHeap(vec, n, maior);
    }
}

// Função para ordenar o vetor usando heapsort em ordem decrescente
void ordenaHeap(std::vector<Paciente>& pacientes) {
    int n = pacientes.size();

    // Constrói o heap máximo (reorganiza o vetor)
    for (int i = n / 2 - 1; i >= 0; i--)
        ajusteHeap(pacientes, n, i);

    // Extrai o maior elemento do heap de cada vez
    for (int i = n - 1; i > 0; i--) {
        // Move o maior (raiz) para o final
        std::swap(pacientes[0], pacientes[i]);

        // Ajusta o heap reduzido para manter a propriedade de heap máximo
        ajusteHeap(pacientes, i, 0);
    }

    // Como o heapsort padrão gera ordem crescente, invertendo aqui,
    // obteremos a ordem decrescente.
    std::reverse(pacientes.begin(), pacientes.end());
}


int tamanhoPagina = 10;

Pagina * AdcionarNaArvore(Pagina * pagPai, ElementoPagina *novoElementoIndice){

    if (!pagPai->addelementoIndice(novoElementoIndice))
    {
        Pagina * novaPagIndices = pagPai->split();

        novaPagIndices->migrarPai();

        ElementoPagina * novoElemento = new ElementoPagina(novaPagIndices->getElementos()[0].getPrioridade(),novaPagIndices,pagPai);

        if (pagPai->getPagPai())
        {
            pagPai = AdcionarNaArvore(pagPai->getPagPai(),novoElemento);
        }
        else
        {
            Pagina * novaRaiz = new Pagina(tamanhoPagina,1);

            novaRaiz->addelementoIndice(novoElemento);

            return novaRaiz;

        }

        
        


    }

    return pagPai;
    

}


int main() {
     // Define o tamanho máximo permitido para uma página na árvore B+.
    
    std::string nomeArquivo = "pacientes.csv"; // Nome do arquivo CSV para armazenar os dados dos pacientes.
    
    Controller controller; // Cria uma instância da classe Controller.
    
    controller.exportarPacientesCSV(nomeArquivo); // Exporta os dados dos pacientes para o arquivo CSV especificado.
    
    Especialidade especialidade = Especialidade("Cardiologia"); // Cria uma especialidade médica chamada "Cardiologia".
    
    std::vector<Paciente> pacientes = especialidade.carregarPacientesDoCSV(nomeArquivo); // Carrega os dados dos pacientes a partir do arquivo CSV.
    
    // Ordena os pacientes por prioridade usando heapsort
    ordenaHeap(pacientes);

    for (const auto& paciente : pacientes) {
    std::cout << "Paciente: " << paciente.nome << ", Prioridade: " << paciente.prioridade << std::endl;
    }


    if (!pacientes.empty()) { // Verifica se existem pacientes carregados na lista.        
        Pagina* raiz = new Pagina(tamanhoPagina, 0); // Inicializa a página raiz como uma folha da árvore B+.
        
        Pagina* auxdisplay = raiz; // Variável auxiliar para exibir as páginas.
        
        int tam = pacientes.size(); // Armazena o número de pacientes carregados.

        std::cout << "==============================" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << tam << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "==============================" << std::endl;
        
        Pagina* raizAncora = raiz; // Mantém uma referência fixa para a raiz da árvore.

        for (int i = 0; i < tam; i++) { // Loop para inserir todos os pacientes na árvore B+.
            
            while (raiz->getTipo() != 0) { // Navega pela árvore até alcançar uma folha.
                ElementoPagina* elementoDecida = raiz->buscarPorPrioridade(pacientes[i].prioridade); // Busca o índice apropriado com base na prioridade.
                
                if (elementoDecida->getPrioridade() < pacientes[i].prioridade) {

                    std::cout << "Esquerda: "<< elementoDecida->getPrioridade()<< " " <<   pacientes[i].prioridade << std::endl;
                    raiz = elementoDecida->getAnt(); // Vai para o ramo à esquerda.
                } else {
                    raiz = elementoDecida->getProx(); // Vai para o ramo à direita.
                    std::cout << "Direita: "<< elementoDecida->getPrioridade()<< " " <<   pacientes[i].prioridade << std::endl;

                }
                
            }

            ElementoPaginaFolha* novoElemento = new ElementoPaginaFolha( // Cria um novo elemento folha para o paciente.
                pacientes[i].prioridade, nullptr, nullptr, &pacientes[i]
            );

            if (raiz->addelemento(novoElemento)) { // Tenta adicionar o elemento na folha atual.
                std::cout << "Elemento adicionado com sucesso!" << std::endl; // Mensagem de sucesso.
            } else { // Se a página estiver cheia, realiza uma cisão (split).
                std::cout << "Página cheia! Cisão necessária." << std::endl;

             
                Pagina * novaPagina = raiz->split();

                if (raiz->getProxPag())
                {
                    novaPagina->setProxPag(raiz->getProxPag());
                }

            
                raiz->setProxPag(novaPagina);

                Pagina * pagPai = raiz->getPagPai();

                if (pagPai ==  nullptr)
                {
                    Pagina * novaPagIndices = new Pagina(tamanhoPagina, 1);

                    ElementoPagina * novoElementoIndice = new ElementoPagina(novaPagina->getElementos()[0].getPrioridade(),novaPagina,raiz);

                    novaPagina->setPagPai(novaPagIndices);
                    raiz->setPagPai(novaPagIndices);

                    novaPagIndices->addelementoIndice(novoElementoIndice);

                    raizAncora = novaPagIndices;
                    
                }
                else
                {

                    

                    ElementoPagina * novoElementoIndice = new ElementoPagina(novaPagina->getElementos()[0].getPrioridade(),novaPagina,raiz);

                    raizAncora =  AdcionarNaArvore(pagPai, novoElementoIndice);



                }
                
                

            }
            
            raiz = raizAncora;
        }

        
        int count = 0;
        while (auxdisplay->getProxPag() != nullptr) { // Loop para exibir informações das páginas.
            count++;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            std::cout << "PAGINA: " << count << " tamanho: " << auxdisplay->getTamanho() - auxdisplay->getTamanhoLivre() << std::endl;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            Pagina* aux = auxdisplay->getProxPag(); // Obtém a próxima página.
            auxdisplay->exibirChaves(); // Exibe as chaves da página atual.
            auxdisplay = aux; // Atualiza o ponteiro auxiliar para a próxima página.
        }
        
        if (auxdisplay->getProxPag() == nullptr)
        {
            count++;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            std::cout << "PAGINA: " << count << " tamanho: " << auxdisplay->getTamanho() - auxdisplay->getTamanhoLivre() << std::endl;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            auxdisplay->exibirChaves();
        }
        

        // AS PAGINAS ESTAM COM TAMANHO 6, INVESTIGAR AMANHÃ
    }
}


