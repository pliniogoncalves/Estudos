#pragma once
#include <string>
#include "Titular.hpp"
#include <iostream>

template <int percentualTarifa>
class Conta
{
private:
    static int numeroDeContas;

public:
    static int getNumeroDeContas(){
        return numeroDeContas;
    }

private:
    std::string numero;
    Titular titular;
    
protected:
    float saldo;

public:

    Conta(std::string numero, Titular titular):
    numero(numero),titular(titular), saldo(0){
        numeroDeContas++;
    }

    virtual ~Conta(){
        numeroDeContas--;
    }

    void sacar(float valorASacar){
        if (valorASacar < 0) {
            std::cout << "Não pode sacar valor negativo" << std::endl;
            return;
        }

        float tarifaDeSaque = valorASacar * percentualTarifa/100;
        float valorDoSaque = valorASacar + tarifaDeSaque;

        if (valorDoSaque > saldo) {
            std::cout << "Saldo insuficiente" << std::endl;
            return;
        }

        saldo -= valorDoSaque;
    }

    void operator -=(float valorASacar){
        sacar(valorASacar);
    }

    void depositar(float valorADepositar){
        if (valorADepositar < 0) {
            std::cout << "Não pode sacar valor negativo" << std::endl;
            return;
        }

        saldo += valorADepositar;
    }

    void operator += (float valorADepositar){
        depositar(valorADepositar);
    }

    float getSaldo() const{
        return saldo;
    }
    bool operator < (const Conta& conta){
        return this-> saldo < conta.saldo;
    }

    friend std::ostream& operator<<(std::ostream& cout, const Conta& conta);
};
