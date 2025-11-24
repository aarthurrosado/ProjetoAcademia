#include "Forca.h"
#include <iostream>
using namespace std;
// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
    this-> carga = carga;
    this-> series = series;
    this-> repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
    this-> carga = carga;
    this-> series = series;
    this-> repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    cout << "Tipo: Força" << endl;
    cout << "ID: " << id << endl;
    cout << "Nome: " << nome << endl;
    cout << "Status: " << (ativo ? "Ativo" : "Inativo ")<< endl;
    cout << "Carga: " << carga << endl;
    cout << "Series: " << series << endl;
    cout << "Repeticoes: " << repeticoes << endl;
    cout << "Tempo de descanso " << tempoDescanso << endl;
}

// Calcular tempo estimado minutos
double Forca::calcularTempoEstimado() const {
    long tempoTotalSegundos = (long)(series * repeticoes * 3) + (long)(series * tempoDescanso);
    return (double)tempoTotalSegundos / 60.0;
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    return series * repeticoes * carga * 0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga; 
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
