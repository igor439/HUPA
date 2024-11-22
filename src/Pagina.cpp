#include "..\include\Pagina.h" // Inclui o arquivo de cabeçalho da classe Pagina
#include "..\include\ElementoPaginaFolha.h" // Inclui o arquivo de cabeçalho da classe ElementoPaginaFolha
#include <iostream> // Biblioteca padrão para entrada e saída

// Construtor da classe Pagina
Pagina::Pagina(int tamanho, int tipo){
    this->elementos = new ElementoPaginaFolha[tamanho + 1]; // Cria um array de elementos com espaço adicional para inserções
    this->tamanhoLivre = tamanho; // Inicializa o espaço livre como o tamanho total
    this->tamanho = tamanho; // Define o tamanho total
    this->tipo = tipo; // Define o tipo da página (por exemplo, folha ou interna)
    this->pagPai = nullptr; // Inicializa o ponteiro para a página pai como nulo
}

// Destrutor da classe Pagina
Pagina::~Pagina() {
    delete[] elementos; // Libera a memória alocada para o array de elementos
}

// Método getter para retornar o array de elementos
ElementoPaginaFolha *Pagina::getElementos() const { return elementos; }

// Método setter para definir o array de elementos
void Pagina::setElementos(ElementoPaginaFolha *elementos) { this->elementos = elementos; }

// Método para obter um elemento específico pelo índice
ElementoPaginaFolha *Pagina::getElemento(int indice) const {
    if (indice >= 0 && indice < tamanho) // Verifica se o índice é válido
        return &elementos[indice]; // Retorna o elemento no índice especificado
    return nullptr; // Retorna nulo se o índice for inválido
}

// Método para adicionar um elemento à página
bool Pagina::addelemento(ElementoPaginaFolha *&elemento) {
    ElementoPaginaFolha *novoElemento = new ElementoPaginaFolha(
        elemento->getPrioridade(), elemento->getProx(), elemento->getAnt(), elemento->getChave()); 
        // Cria um novo elemento com os atributos do elemento fornecido

    if (tamanhoLivre <= 0) { // Verifica se não há espaço livre na página
        elementos[tamanho - tamanhoLivre] = *novoElemento; // Substitui o último elemento
        this->oredenarArray(tamanho + 1); // Ordena os elementos após a inserção
        int meio = tamanho / 2; // Calcula o índice do elemento do meio
        elemento = &elementos[meio]; // Retorna o elemento do meio
        return false; // Indica que a página está cheia
    } else {
        elementos[tamanho - tamanhoLivre] = *novoElemento; // Adiciona o novo elemento na última posição disponível
        tamanhoLivre--; // Diminui o espaço livre
        this->oredenarArray(tamanho - tamanhoLivre); // Ordena os elementos após a inserção
        return true; // Indica que o elemento foi adicionado com sucesso
    }
}

// Método para obter o tamanho livre restante na página
int Pagina::getTamanhoLivre() {
    return this->tamanhoLivre;
}

// Método para ordenar os elementos do array em ordem decrescente por prioridade
void Pagina::oredenarArray(int indexOrdencao) {
    for (int i = 0; i < indexOrdencao; ++i) {
        for (int j = i + 1; j < indexOrdencao; ++j) {
            if (elementos[i].getPrioridade() < elementos[j].getPrioridade()) { 
                // Troca os elementos se não estiverem em ordem decrescente
                ElementoPaginaFolha temp = elementos[i];
                elementos[i] = elementos[j];
                elementos[j] = temp;
            }
        }
    }
}

// Método getter para obter a página sucessora
Pagina *Pagina::getProxPag() {
    return this->proxPag;
}

// Método setter para definir a página sucessora
void Pagina::setProxPag(Pagina* apontarPara) {
    this->proxPag = apontarPara;
}

// Método getter para obter a página pai
Pagina *Pagina::getPagPai() {
    return this->pagPai;
}

// Método setter para definir a página pai
void Pagina::setPagPai(Pagina *apontarPara) {
    this->pagPai = apontarPara;
}

// Método para obter o número de elementos já adicionados à página
int Pagina::getElementosAdicionados() {
    return this->tamanho - this->tamanhoLivre;
}

// Método para obter o tipo da página
int Pagina::getTipo() {
    return this->tipo;
}

// Método para buscar um elemento pela prioridade
ElementoPaginaFolha *Pagina::buscarPorPrioridade(int prioridade) {
    for (int i = 0; i < tamanho - tamanhoLivre; i++) {
        if (prioridade < elementos[i].getPrioridade()) {
            return &elementos[i]; // Retorna o elemento com prioridade menor
        }
    }
    return &elementos[tamanho - tamanhoLivre - 1]; // Retorna o último elemento se não houver correspondência
}

// Método para adicionar um elemento do tipo ElementoPagina
bool Pagina::addelementoIndice(ElementoPagina *&elemento) {
    ElementoPaginaFolha *novoElemento = new ElementoPaginaFolha(
        elemento->getPrioridade(), elemento->getProx(), elemento->getAnt(), nullptr); 

    if (tamanhoLivre <= 0) { 
        elementos[tamanho - tamanhoLivre] = *novoElemento; 
        this->oredenarArray(tamanho + 1);
        int meio = tamanho / 2;
        elemento = &elementos[meio];
        return false; 
    } else {
        elementos[tamanho - tamanhoLivre] = *novoElemento;
        tamanhoLivre--;
        this->oredenarArray(tamanho - tamanhoLivre);
        return true;
    }
}

// Método para dividir a página em duas quando cheia
Pagina* Pagina::split() {
    int meio = tamanho / 2; // Calcula o índice do meio
    Pagina* novaPagina = new Pagina(tamanho, this->tipo); // Cria a nova página

    for (int i = meio; i < tamanho + 1 - tamanhoLivre; ++i) {
        ElementoPaginaFolha *novoElemento = &elementos[i];
        novaPagina->addelemento(novoElemento); // Move os elementos da segunda metade para a nova página
    }

    for (int i = meio; i < tamanho + 1 - tamanhoLivre; ++i) {
        elementos[i] = ElementoPaginaFolha(); // Limpa os elementos movidos
    }
    tamanhoLivre = (tamanho - meio); // Atualiza o espaço livre
    return novaPagina; // Retorna a nova página
}

// Método para exibir as chaves de todos os elementos da página
void Pagina::exibirChaves() {
    int tam = tamanho - tamanhoLivre;
    for (int i = 0; i < tam; i++) {
        elementos[i].getChave()->exibirDados(); // Exibe os dados associados à chave
    }
}