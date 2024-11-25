#ifndef MEDICO_H
#define MEDICO_H

#include <string>

// Classe Medico representa um médico no hospital.
class Medico {

private:
    int id; 
    std::string nome; 
    std::string especialidade; 
    int horasTrabalhadas;
public:
    

    // Construtor da classe Medico (somente declaração)
    Medico(int id, const std::string& nome, const std::string& especialidade);

    Medico();
    
    // Método para exibir os dados do médico
    void exibirDados() const;

    int getId() const;
    std::string getNome() const;
    std::string getEspecialidade() const;
    int getHorastrabalhadas() const;

    void atendimentoCompleto();
};
#endif