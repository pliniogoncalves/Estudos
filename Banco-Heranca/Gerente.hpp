#pragma once
#include "Funcionario.hpp"
#include "PessoaAutenticavel.hpp"

class Gerente final: public Funcionario, public PessoaAutenticavel {
public:
    Gerente(Cpf cpf, std::string nome, float salario, std::string senha);
    float bonificacao() const override;
};



