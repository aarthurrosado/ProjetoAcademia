#include "Cardio.h"
#include <iostream>
#include <iostream>
using namespace std;

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome) {
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
    // check
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo) {
    // check
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {
    cout << "Tipo: Cardio" << endl;
    cout << "ID: " << id << endl;
    cout << "Cardio: " << nome << endl;
    cout << "Status: " << (ativo ? "Ativo" : "Inativo ")<< endl;
    cout << "Duracao " << duracao << endl;
    cout << "CaloriasPorMinuto: " << caloriasPorMinuto << endl;
} // check

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    return duracao; // check
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto; // check
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 1; 
}

// Getter de duração
int Cardio::getDuracao() const {
    return duracao; // check
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto; 
}
