#pragma once
#include <string>
#include "Titular.hpp"

class Conta
{
private:
    static int numeroDeContas;

public:
    static int getNumeroDeContas();

private:
    std::string numero;
    Titular titular;
    
protected:
    float saldo;

public:
    Conta(std::string numero, Titular titular);
    virtual ~Conta();
    void sacar(float valorASacar);
    void depositar(float valorADepositar);
    float getSaldo() const;
    virtual float taxaDeSaque() const = 0;
};
