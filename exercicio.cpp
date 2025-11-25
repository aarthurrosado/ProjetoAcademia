#include "Exercicio.h"


int Exercicio::proximoId = 1;


Exercicio::Exercicio(std::string nome) {
    this->id = proximoId++;
    this->nome = nome;
    this->ativo = true;
}


Exercicio::Exercicio(int id, std::string nome, bool ativo) {
    this->id = id;
    this->nome = nome;
    this->ativo = ativo;
   
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

int Exercicio::getId() const { 
    return id; 
}

std::string Exercicio::getNome() const { 
    return nome; 
}

bool Exercicio::isAtivo() const { return ativo; }

void Exercicio::setAtivo(bool status) { 
    this->ativo = status; 
}
