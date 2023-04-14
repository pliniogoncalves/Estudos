#pragma once
#include "Pessoa.hpp"
#include "Cpf.hpp"
#include "DiaDaSemana.hpp"
#include <string>

class Funcionario : public Pessoa<Cpf>
{
private:
    float salario;
    DiaDaSemana diaDoPagamento; //0=Domingo,1=Segunda, etc

public:
    Funcionario(Cpf cpf, std::string nome, float salario, DiaDaSemana diaDoPagamento);
    std::string getNome() const;
    float getSalario() const;
    virtual float bonificacao() const = 0;
};
