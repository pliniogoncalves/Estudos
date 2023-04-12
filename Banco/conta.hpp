#pragma once
#include <string>
#include "titular.hpp"

class Conta {
private:
    Titular titular;
    std::string numeroConta;
    float saldo;
    static int numeroDeContas;

public:
    Conta(Titular titular, std::string numeroConta);
    ~Conta();
    void sacar(float valorASacar);
    void depositar(float valorADepositar);
    float getSaldo() const;
    std::string getNumeroConta() const;
    static int getNumeroDeContas();
    //void setNomeTitular(std::string nome);
    //void setCpfTitular(std::string cpf);
    //void setNumeroConta(std::string numero);
};