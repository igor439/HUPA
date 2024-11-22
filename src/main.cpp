#include "..\include\Paciente.h" // Inclui a classe Paciente para manipulação de objetos Paciente.
#include "..\include\Medico.h" // Inclui a classe Medico para manipulação de objetos Médico.
#include "..\include\Especialidade.h" // Inclui a classe Especialidade para gerenciar áreas médicas específicas.
#include "..\include\Sala.h" // Inclui a classe Sala para gerenciar salas no hospital.
#include "..\include\Controller.h" // Inclui a classe Controller para operações relacionadas ao controle de pacientes.
#include "..\include\Pagina.h" // Inclui a classe Pagina para a implementação da árvore B+.
#include "..\include\ElementoPaginaFolha.h" // Inclui a classe ElementoPaginaFolha para elementos das folhas da árvore B+.
#include "..\include\ElementoPagina.h" // Inclui a classe ElementoPagina para elementos de índice na árvore B+.
#include <algorithm>  // Para usar std::swap

// Função auxiliar para ajustar o heap
void ajusteHeap(std::vector<Paciente>& vec, int n, int i) {
    int maior = i;  // Maior elemento como a raiz
    int esquerda = 2 * i + 1;  // Filho à esquerda
    int direita = 2 * i + 2;  // Filho à direita

    // Se o filho à esquerda for maior que a raiz
    if (esquerda < n && vec[esquerda].prioridade > vec[maior].prioridade)
        maior = esquerda;

    // Se o filho à direita for maior que o maior até agora
    if (direita < n && vec[direita].prioridade > vec[maior].prioridade)
        maior = direita;

    // Se o maior não for a raiz
    if (maior != i) {
        std::swap(vec[i], vec[maior]); // Usada para trocar os valores de duas variáveis.

        // Recursivamente, ajusta o sub-heap afetado
        ajusteHeap(vec, n, maior);
    }
}

// Função para ordenar o vetor de pacientes usando heapsort
void ordenaHeap(std::vector<Paciente>& pacientes) {
    int n = pacientes.size();

    // Constrói o heap (reorganiza o vetor)
    for (int i = n / 2 - 1; i >= 0; i--)
        ajusteHeap(pacientes, n, i);

    // Extrai um elemento do heap de cada vez
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final
        std::swap(pacientes[0], pacientes[i]);

        // Chama ajusteHeap no heap reduzido
        ajusteHeap(pacientes, i, 0);
    }
}

int main() {
    int tamanhoPagina = 10; // Define o tamanho máximo permitido para uma página na árvore B+.
    
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
        
        Pagina* raizAncora = raiz; // Mantém uma referência fixa para a raiz da árvore.

        for (int i = 0; i < tam; i++) { // Loop para inserir todos os pacientes na árvore B+.
            
            while (raiz->getTipo() != 0) { // Navega pela árvore até alcançar uma folha.
                
                ElementoPagina* elementoDecida = raiz->buscarPorPrioridade(pacientes[i].prioridade); // Busca o índice apropriado com base na prioridade.
                
                if (elementoDecida->getPrioridade() <= pacientes[i].prioridade) {
                    raiz = elementoDecida->getAnt(); // Vai para o ramo à esquerda.
                } else {
                    raiz = elementoDecida->getProx(); // Vai para o ramo à direita.
                }
            }

            ElementoPaginaFolha* novoElemento = new ElementoPaginaFolha( // Cria um novo elemento folha para o paciente.
                pacientes[i].prioridade, nullptr, nullptr, &pacientes[i]
            );

            if (raiz->addelemento(novoElemento)) { // Tenta adicionar o elemento na folha atual.
                std::cout << "Elemento adicionado com sucesso!" << std::endl; // Mensagem de sucesso.
            } else { // Se a página estiver cheia, realiza uma cisão (split).
                std::cout << "Página cheia! Cisão necessária." << std::endl;

                Pagina* novaPaginaFolha = raiz->split(); // Divide a página em duas.
                
                Pagina* pagPai = raiz->getPagPai(); // Obtém a página pai.

                novaPaginaFolha->setProxPag(raiz->getProxPag()); // Atualiza o ponteiro da próxima página da nova folha.
                
                raiz->setProxPag(novaPaginaFolha); // Atualiza o ponteiro da próxima página na página atual.

                if (pagPai == nullptr) { // Se não houver uma página pai, cria uma nova raiz.
                    
                    Pagina* navaPaginaIndices = new Pagina(tamanhoPagina, 1); // Cria uma nova página de índice.
                    
                    ElementoPagina* elementoMeio = novoElemento; // O elemento do meio se torna o índice.
                    
                    elementoMeio->setProx(novaPaginaFolha); // Configura o próximo elemento para a nova folha.
                    
                    elementoMeio->setAnt(raiz); // Configura o elemento anterior para a raiz.
                   
                    novaPaginaFolha->setPagPai(navaPaginaIndices); // Atualiza o pai da nova folha.
                    
                    raiz->setPagPai(navaPaginaIndices); // Atualiza o pai da raiz.
                    
                    navaPaginaIndices->addelementoIndice(elementoMeio); // Adiciona o índice à nova raiz.
                                   
                    raizAncora = navaPaginaIndices; // Atualiza a referência para a nova raiz.
                } else { // Se houver uma página pai.
                    ElementoPagina* elementoMeio = novoElemento; // Configura o elemento do meio como índice.
                    
                    elementoMeio->setProx(novaPaginaFolha); // Define o próximo como a nova folha.
                    
                    elementoMeio->setAnt(raiz); // Define o anterior como a página atual.

                    while (!pagPai->addelementoIndice(elementoMeio)) { // Continua tentando adicionar o índice na página pai.
                        
                        Pagina* splitPagPai = pagPai->split(); // Divide a página pai.
                        
                        Pagina* avo = pagPai->getPagPai(); // Obtém o "avô" da página atual.

                        elementoMeio->setProx(splitPagPai); // Configura o próximo como a página dividida.
                        elementoMeio->setAnt(pagPai); // Configura o anterior como a página original.

                        if (avo == nullptr) { // Se não houver um avô, cria uma nova raiz.
                            Pagina* navaPaginaIndices = new Pagina(tamanhoPagina, 1); // Nova raiz.
                            
                            pagPai->setPagPai(navaPaginaIndices); // Atualiza o pai da página original.
                            
                            splitPagPai->setPagPai(navaPaginaIndices); // Atualiza o pai da página dividida.
                                                       
                            pagPai = navaPaginaIndices; // Atualiza a referência para a nova raiz.
                        } else {
                            pagPai = avo; // Continua subindo na árvore.
                        }
                    }
                    raizAncora = pagPai; // Atualiza a referência para a raiz da árvore.
                }
            }
            raiz = raizAncora; // Retorna para a raiz após cada inserção.
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
        

        // AS PAGINAS ESTAM COM TAMANHO 6, INVESTIGAR AMANHÃ
    }
}


