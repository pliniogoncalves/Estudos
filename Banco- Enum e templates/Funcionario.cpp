#include "Funcionario.hpp"
#include <iostream>

Funcionario::Funcionario(Cpf cpf, std::string nome, float salario,DiaDaSemana diaDoPagamento)
    : Pessoa(cpf, nome), salario(salario), diaDoPagamento(diaDoPagamento)
{
}

std::string Funcionario::getNome() const
{
    return nome;
}

float Funcionario::getSalario() const
{
    return salario;
}