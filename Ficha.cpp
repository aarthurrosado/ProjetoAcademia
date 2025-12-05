#include "Ficha.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) : nome(nome) {
    this-> id = proximoId + 1;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) {
    this-> id - proximoId++;
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if (exercicio != nullptr) {
        exercicios.push_back(exercicio);
    }
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    cout << "ID da Ficha: " << endl;
    cout << "Nome Aluno: " << endl;

    if (exercicios.empty()) {
        cout << "Nenhum Exercicio cadastrado." << endl;
    } else{
        cout << "Exercicios: " << endl;

        for ( size_t i = 0; i < exercicios.size(); i++ ) {
            exercicios[i]-> exibirDetalhes();
        }

        cout << "Resumo Final:" << endl;
        cout << "Total de treinos: " << exercicios.size() << endl;
        cout << "Tempo Total: " << calcularTempoTotal() << " minutos" << endl;
        cout << "Caloria Total: " << calcularCaloriasTotais() << " calorias" << endl;

    }
    

}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (const auto* ex : exercicios) {
        if (ex != nullptr) {
            total += ex->calcularTempoEstimado();
        }
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (const auto* ex : exercicios) {
        if (ex != nullptr) {
            total += ex->calcularCaloriasGastas();
        }
    }
    return total;
}

// Getters
int Ficha::getId() const { 
    return this->id; 
}

std::string Ficha::getNome() const { 
    return this->nome; 
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return this->exercicios;
}
// atualizar id
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}
