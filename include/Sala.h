#ifndef SALA_H
#define SALA_H

// Classe Sala representa uma sala do hospital.
class Sala {
public:
    int numero; // Número da sala
    bool ocupada; // Indica se a sala está ocupada ou não

    // Construtor da classe Sala (somente declaração)
    Sala(int numero);

    // Método para marcar a sala como ocupada
    void ocupar();

    // Método para marcar a sala como livre
    void liberar();

    // Exibe o estado atual da sala
    void exibirStatus() const;
};

#endif
