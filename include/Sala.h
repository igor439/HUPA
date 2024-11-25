#include <vector>
#include "Paciente.h"
#include <map>
#include "Medico.h"
#include "Pagina.h"
#include "ElementoPaginaFolha.h"
#ifndef SALA_H
#define SALA_H

// Classe Sala representa uma sala do hospital.
class Sala {

private:

    int numero; // Número da sala
    bool ocupada; // Indica se a sala está ocupada ou não 
    std::map<std::string,std::vector<Paciente>> atendimentos;
    Medico medico;
    int horasdiarias;

public:

    Sala(int numero, Medico medico) 
    : numero(numero), ocupada(false), atendimentos(), medico(medico), horasdiarias(0){}



    void ocupar(); 
    void liberar(); 
    void exibirStatus() const;

    // Métodos getters e setters
    int getNumero() const;
    void setNumero(int numero);

    bool isOcupada() const;
    void setOcupada(bool estado);

    const std::map<std::string, std::vector<Paciente>>& getAtendimentos() const;
    void setAtendimentos(const std::map<std::string, std::vector<Paciente>>& novosAtendimentos);

    const Medico getMedicos() const;
    void setMedicos(const Medico novosMedicos);

    int getHorasDiarias() const;
    void setHorasDiarias(int horas);

    void receberPacientes(Pagina* pacientesDoDia);
};
#endif