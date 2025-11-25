#ifndef EXERCICIO_H
#define EXERCICIO_H

#include <string>
#include <iostream>

class Exercicio {
protected:
    int id;
    std::string nome;
    bool ativo;
    static int proximoId; 
public:

    Exercicio(std::string nome);

    
    Exercicio(int id, std::string nome, bool ativo);

    virtual ~Exercicio() {}

    
    virtual void exibirDetalhes() const = 0;
    virtual double calcularTempoEstimado() const = 0;
    virtual double calcularCaloriasGastas() const = 0;
    virtual int getTipo() const = 0; 

   
    int getId() const;
    std::string getNome() const;
    bool isAtivo() const;
    void setAtivo(bool status);
};

#endif
