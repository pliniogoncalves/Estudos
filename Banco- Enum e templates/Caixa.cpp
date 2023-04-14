#include "Caixa.hpp"

Caixa::Caixa(Cpf cpf, std::string nome, float salario, DiaDaSemana diaDoPagamento):
Funcionario(cpf, nome, salario, diaDoPagamento)
{
}

float Caixa::bonificacao() const
{
    return getSalario() * 0.1;
}

