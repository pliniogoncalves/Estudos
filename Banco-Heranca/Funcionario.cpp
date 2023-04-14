#include "Funcionario.hpp"
#include <iostream>

Funcionario::Funcionario(Cpf cpf, std::string nome, float salario)
    : Pessoa(cpf, nome), salario(salario)
{
}

std::string Funcionario::getNome() const
{
    return nome;
}

float Funcionario::getSalario() const {
    return salario;
}