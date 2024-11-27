#include "..\include\Paciente.h" // Inclui a classe Paciente para manipulação de objetos Paciente.
#include "..\include\Medico.h" // Inclui a classe Medico para manipulação de objetos Médico.
#include "..\include\Especialidade.h" // Inclui a classe Especialidade para gerenciar áreas médicas específicas.
#include "..\include\Sala.h" // Inclui a classe Sala para gerenciar salas no hospital.
#include "..\include\Controller.h" // Inclui a classe Controller para operações relacionadas ao controle de pacientes.
#include "..\include\Pagina.h" // Inclui a classe Pagina para a implementação da árvore B+.
#include "..\include\ElementoPaginaFolha.h" // Inclui a classe ElementoPaginaFolha para elementos das folhas da árvore B+.
#include "..\include\ElementoPagina.h" // Inclui a classe ElementoPagina para elementos de índice na árvore B+.
#include <algorithm>  // Para usar std::swap
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

std::string getFormattedDateAndWeekday(int diasUteis) {
    // Data inicial
    std::tm dataInicial = {};
    dataInicial.tm_year = 2024 - 1900; // Ano ajustado para struct tm
    dataInicial.tm_mon = 10;          // Novembro (meses começam do 0)
    dataInicial.tm_mday = 26;         // Dia inicial

    int diasTotais = 0;

    while (diasUteis > 0) {
        // Adicionar um dia
        dataInicial.tm_mday++;
        std::mktime(&dataInicial); // Atualiza a data automaticamente

        // Verificar se o dia é útil (não sábado ou domingo)
        if (dataInicial.tm_wday != 0 && dataInicial.tm_wday != 6) { // 0 = Domingo, 6 = Sábado
            diasUteis--;
        }

        diasTotais++;
    }

    // Array com os dias da semana
    const char* diasSemana[] = {"Domingo", "Segunda-Feira", "Terça-Feira", "Quarta-Feira", 
                                "Quinta-Feira", "Sexta-Feira", "Sábado"};

    // Formatar a data
    std::ostringstream oss;
    oss << std::put_time(&dataInicial, "%d/%m/%Y") << " - " << diasSemana[dataInicial.tm_wday];

    return oss.str();
}

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


int tamanhoPagina = 8;

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


Pagina* processarPacientes(std::vector<Paciente>& pacientes) {
    // Ordena os pacientes por prioridade usando heapsort
    ordenaHeap(pacientes);

    for (const auto& paciente : pacientes) {
        std::cout << "Paciente: " << paciente.nome << ", Prioridade: " << paciente.prioridade << std::endl;
    }

    if (!pacientes.empty()) { // Verifica se existem pacientes carregados na lista.
        Pagina* raiz = new Pagina(tamanhoPagina, 0); // Inicializa a página raiz como uma folha da árvore B+.
        Pagina* auxdisplay = raiz; // Variável auxiliar para exibir as páginas.
        Pagina* raizAncora = raiz; // Mantém uma referência fixa para a raiz da árvore.

        int tam = pacientes.size(); // Armazena o número de pacientes carregados.
        std::cout << "==============================" << std::endl;
        std::cout << "Tamanho: " << tam << std::endl;
        std::cout << "==============================" << std::endl;

        for (int i = 0; i < tam; i++) { // Loop para inserir todos os pacientes na árvore B+.
            while (raiz->getTipo() != 0) { // Navega pela árvore até alcançar uma folha.
                ElementoPagina* elementoDecida = raiz->buscarPorPrioridade(pacientes[i].prioridade);
                if (elementoDecida->getPrioridade() < pacientes[i].prioridade) {
                    raiz = elementoDecida->getAnt(); // Vai para o ramo à esquerda.
                } else {
                    raiz = elementoDecida->getProx(); // Vai para o ramo à direita.
                }
            }

            ElementoPaginaFolha* novoElemento = new ElementoPaginaFolha(
                pacientes[i].prioridade, nullptr, nullptr, &pacientes[i]
            );

            if (!raiz->addelemento(novoElemento)) { // Se a página estiver cheia, realiza uma cisão (split).
                Pagina* novaPagina = raiz->split();

                if (raiz->getProxPag()) {
                    novaPagina->setProxPag(raiz->getProxPag());
                }
                raiz->setProxPag(novaPagina);

                Pagina* pagPai = raiz->getPagPai();
                if (pagPai == nullptr) {
                    Pagina* novaPagIndices = new Pagina(tamanhoPagina, 1);
                    ElementoPagina* novoElementoIndice = new ElementoPagina(
                        novaPagina->getElementos()[0].getPrioridade(), novaPagina, raiz
                    );
                    novaPagina->setPagPai(novaPagIndices);
                    raiz->setPagPai(novaPagIndices);
                    novaPagIndices->addelementoIndice(novoElementoIndice);
                    raizAncora = novaPagIndices;
                } else {
                    ElementoPagina* novoElementoIndice = new ElementoPagina(
                        novaPagina->getElementos()[0].getPrioridade(), novaPagina, raiz
                    );
                    raizAncora = AdcionarNaArvore(pagPai, novoElementoIndice);
                }
            }

            raiz = raizAncora;
        }

        Pagina * paginaRetorno = auxdisplay;

        int count = 0;
        while (auxdisplay->getProxPag() != nullptr) { // Loop para exibir informações das páginas.
            count++;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            std::cout << "PÁGINA: " << count
                      << " tamanho: " << auxdisplay->getTamanho() - auxdisplay->getTamanhoLivre() << std::endl;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            Pagina* aux = auxdisplay->getProxPag();
            auxdisplay->exibirChaves();
            auxdisplay = aux;
        }

        if (auxdisplay->getProxPag() == nullptr) {
            count++;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            std::cout << "PÁGINA: " << count
                      << " tamanho: " << auxdisplay->getTamanho() - auxdisplay->getTamanhoLivre() << std::endl;
            std::cout << "++++++++++++++++++++++++++++" << std::endl;
            auxdisplay->exibirChaves();
        }

        paginaRetorno->setNumeroPaginasAssociadas(count);
        return paginaRetorno; // Retorna o ponteiro auxiliar.
    }

    return nullptr; // Retorna nulo se o vetor de pacientes estiver vazio.
}



void gerarCronograma(Pagina* pagina, std::vector<Medico> medicos) {


    int tam = medicos.size();

    if (tam == 1)
    {

        std::string nomeArquivo = "Agendamentos_" + medicos[0].getEspecialidade() + ".txt";
        std::ofstream arquivo(nomeArquivo);

        // Verifica se o arquivo foi aberto com sucesso
        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para escrita.\n";
            return;
        }

        int dias = 0;
        int semanas = 1;
        int horas = 0;
        bool diaplayMedico = true;
        Medico medico = medicos[0];
        Pagina * raizAncora = pagina;


        int diasUteis = 0;

        while (pagina->getProxPag() != nullptr) { // Loop para exibir informações das páginas.
            diasUteis++;
            horas = 8;

            // Obter a data formatada ignorando fins de semana
            std::string dataFormatada = getFormattedDateAndWeekday(diasUteis);

            // Cabeçalho por semana
            if (diasUteis % 5 == 1 || diasUteis == 1) {
                arquivo << "====================== SEMANA: " << semanas 
                        << " / " << dataFormatada << " ======================\n";
                semanas++;
            } else {
                arquivo << "====================== DIA: " << dataFormatada 
                        << " ======================\n";
            }            

            if (diaplayMedico)
            {
                diaplayMedico = false;
                arquivo << "====================== Médico Resposável: ====================== \n";
                arquivo << "Nome: " << medico.getNome() << "\n";
                arquivo << "Identificação: " << medico.getId() << "\n";
                arquivo << "Especialidade: " << medico.getEspecialidade() << "\n";
                arquivo << "================================================================= \n";

            }
            
            arquivo << '\n';
            arquivo << "====================== Pacientes: ====================== \n";
            Pagina* aux = pagina->getProxPag();
            for (int i = 0; i < pagina->getTamanho() - pagina->getTamanhoLivre(); i++)
            {

                
                arquivo << "Nome: " << pagina->getElementos()[i].getChave()->nome << "\n";
                arquivo << "Identificação: " << pagina->getElementos()[i].getChave()->id << "\n";
                arquivo << "Especialidade: " << pagina->getElementos()[i].getChave()->especialidade << "\n";
                arquivo << "Horario: " << horas << ":00 h\n";
                arquivo << "================================================================= \n";
                horas++;
                medico.atendimentoCompleto();
                
            }
            
            pagina = aux;

        }

        if (pagina->getProxPag() == nullptr) {
            
            pagina->exibirChaves();
        }

        pagina->getNumeroPaginasAssociadas();

        diaplayMedico = false;
        arquivo << "====================== Relatório Horas Trabalhadas: ====================== \n";
        arquivo << "Nome: " << medico.getNome() << "\n";
        arquivo << "Identificação: " << medico.getId() << "\n";
        arquivo << "Especialidade: " << medico.getEspecialidade() << "\n";
        arquivo << "Horas Trabalhadas: " << medico.getHorastrabalhadas();
        arquivo << "\n================================================================= \n";

        arquivo << "\n\n====================== NÚMERO DE SEMANAS NESCESSÁRIAS: " << semanas - 1<< " ====================== \n";
  


        arquivo.close();

    }
    else
    {



        std::string nomeArquivo = "Agendamentos_" + medicos[0].getEspecialidade() + ".txt";
        std::ofstream arquivo(nomeArquivo);

        // Verifica se o arquivo foi aberto com sucesso
        if (!arquivo.is_open()) {
            std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << " para escrita.\n";
            return;
        }

        int dias = 0;
        int semanas = 1;
        int horas = 0;
        int horasTrabalhadas = 0;
        bool diaplayMedico = true;
        Pagina * raizAncora = pagina;
        int alternador = 0;
        int diasUteis = 0;


        while (pagina->getProxPag() != nullptr) { // Loop para exibir informações das páginas.
            diasUteis++;
            dias++;
            diaplayMedico = true;
            horas = 8;

            // Obter a data formatada ignorando fins de semana
            std::string dataFormatada = getFormattedDateAndWeekday(diasUteis);

            // Cabeçalho por semana
            if (diasUteis % 5 == 1 || diasUteis == 1) {
                arquivo << "====================== SEMANA: " << semanas 
                        << " / " << dataFormatada << " ======================\n";
                semanas++;
            } else {
                arquivo << "====================== DIA: " << dataFormatada 
                        << " ======================\n";
            }
            
            

            if (diaplayMedico)
            {
                diaplayMedico = false;
                arquivo << "====================== Médico Resposável: ====================== \n";
                arquivo << "Nome: " << medicos[alternador].getNome() << "\n";
                arquivo << "Identificação: " << medicos[alternador].getId() << "\n";
                arquivo << "Especialidade: " << medicos[alternador].getEspecialidade() << "\n";
                arquivo << "================================================================= \n";
                
                alternador = !alternador;
            }
            
            arquivo << '\n';
            arquivo << "====================== Pacientes: ====================== \n";
            Pagina* aux = pagina->getProxPag();
            for (int i = 0; i < pagina->getTamanho() - pagina->getTamanhoLivre(); i++)
            {

                
                arquivo << "Nome: " << pagina->getElementos()[i].getChave()->nome << "\n";
                arquivo << "Identificação: " << pagina->getElementos()[i].getChave()->id << "\n";
                arquivo << "Especialidade: " << pagina->getElementos()[i].getChave()->especialidade << "\n";
                arquivo << "Horario: " << horas << ":00 h\n";
                arquivo << "================================================================= \n";
                horas++;
                medicos[alternador].atendimentoCompleto();
                
            }
            
            pagina = aux;

        }

        if (pagina->getProxPag() == nullptr) {
            
            pagina->exibirChaves();
        }

        pagina->getNumeroPaginasAssociadas();

        diaplayMedico = false;
        arquivo << "====================== Relatório Horas Trabalhadas: ====================== \n";
        arquivo << "Nome: " << medicos[0].getNome() << "\n";
        arquivo << "Identificação: " << medicos[0].getId() << "\n";
        arquivo << "Especialidade: " << medicos[0].getEspecialidade() << "\n";
        arquivo << "Horas Trabalhadas: " << medicos[0].getHorastrabalhadas();
        arquivo << "\n================================================================= \n";

        arquivo << "====================== Relatório Horas Trabalhadas: ====================== \n";
        arquivo << "Nome: " << medicos[1].getNome() << "\n";
        arquivo << "Identificação: " << medicos[1].getId() << "\n";
        arquivo << "Especialidade: " << medicos[1].getEspecialidade() << "\n";
        arquivo << "Horas Trabalhadas: " << medicos[1].getHorastrabalhadas();
        arquivo << "\n================================================================= \n";

        arquivo << "\n\n====================== NÚMERO DE SEMANAS NESCESSÁRIAS: " << semanas - 1<< " ====================== \n";
  


        arquivo.close();

        


    }
    
        
    
    
    






}











int main() {
     // Define o tamanho máximo permitido para uma página na árvore B+.
    
    std::string nomeArquivo = "pacientes.csv"; // Nome do arquivo CSV para armazenar os dados dos pacientes.
    
    Controller controller; // Cria uma instância da classe Controller.
    
    controller.exportarPacientesCSV(nomeArquivo,200); // Exporta os dados dos pacientes para o arquivo CSV especificado.
    
    

    Especialidade cardiologia = Especialidade("Cardiologia"); 
    Especialidade pediatria = Especialidade("Pediatria"); 
    Especialidade ortopedia = Especialidade("Ortopedia"); 
    Especialidade neorologia = Especialidade("Neurologia"); 
    Especialidade dermatologia = Especialidade("Dermatologia"); 
    
    std::vector<Paciente> pacientesCardiologia = cardiologia.carregarPacientesDoCSV(nomeArquivo); // Carrega os dados dos pacientes a partir do arquivo CSV.
    std::vector<Paciente> pacientesPediatria = pediatria.carregarPacientesDoCSV(nomeArquivo);
    std::vector<Paciente> pacientesOrtopedia = ortopedia.carregarPacientesDoCSV(nomeArquivo);
    std::vector<Paciente> pacientesNeorologia = neorologia.carregarPacientesDoCSV(nomeArquivo);
    std::vector<Paciente> pacientesDermatologia = dermatologia.carregarPacientesDoCSV(nomeArquivo);


    controller.gerarMedicosAleatorios("medicos.csv",pacientesCardiologia,pacientesPediatria,pacientesOrtopedia,pacientesNeorologia, pacientesDermatologia);

    std::vector<Medico> cardiologiaMedicos = cardiologia.carregarMedicosDoCSV("medicos.csv");
    std::vector<Medico> pediatriaMedicos = pediatria.carregarMedicosDoCSV("medicos.csv");
    std::vector<Medico> ortopediaMedicos = ortopedia.carregarMedicosDoCSV("medicos.csv");
    std::vector<Medico> neorologiaMedicos = neorologia.carregarMedicosDoCSV("medicos.csv");
    std::vector<Medico> dermatologiaMedicos = dermatologia.carregarMedicosDoCSV("medicos.csv");




    Pagina* auxCardiologia = processarPacientes(pacientesCardiologia);
    Pagina* auxPediatria = processarPacientes(pacientesPediatria);
    Pagina* auxOrtopedia = processarPacientes(pacientesOrtopedia);
    Pagina* auxNeurologia = processarPacientes(pacientesNeorologia);
    Pagina* auxDermatologia = processarPacientes(pacientesDermatologia);


    gerarCronograma(auxCardiologia,cardiologiaMedicos);
    gerarCronograma(auxPediatria,pediatriaMedicos);
    gerarCronograma(auxOrtopedia,ortopediaMedicos);
    gerarCronograma(auxNeurologia,neorologiaMedicos);
    gerarCronograma(auxDermatologia,dermatologiaMedicos);







}


