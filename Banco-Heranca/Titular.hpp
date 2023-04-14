#pragma once
#include <string>
#include "Pessoa.hpp"
#include "Cpf.hpp"
#include "PessoaAutenticavel.hpp"

class Titular : public Pessoa, public PessoaAutenticavel
{
public:
    Titular(Cpf cpf, std::string nome, std::string senha);
};
