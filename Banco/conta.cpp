#include "conta.hpp"
#include <iostream>

int Conta::numeroDeContas = 0;

Conta::Conta(Titular titular, std::string numeroConta):
    titular(titular),
    numeroConta(numeroConta),
    saldo(0)
{
    numeroDeContas++;
}

Conta::~Conta(){
    numeroDeContas --;
};

void Conta::sacar(float valorASacar){
    if (valorASacar < 0) {
        std::cout << "Não pode sacar valor negativo" << std::endl;
        return;
    }

    if (valorASacar > saldo) {
        std::cout << "Saldo insuficiente" << std::endl;
        return;
    }

    saldo -= valorASacar;
}

void Conta::depositar(float valorADepositar) {
    if (valorADepositar < 0) {
        std::cout << "Não pode sacar valor negativo" << std::endl;
        return;
    }

    saldo += valorADepositar;
}

float Conta::getSaldo() const{
    return saldo;
}

std::string Conta::getNumeroConta() const{
    return numeroConta;
}
/*
void Conta::setNomeTitular(std::string nome) {
    nomeTitular = nome;
}

void Conta::setCpfTitular(std::string cpf) {
    cpfTitular = cpf;
}

void Conta::setNumeroConta(std::string numero) {
    numeroConta = numero;
}
*/

int Conta::getNumeroDeContas(){
    return numeroDeContas;
}