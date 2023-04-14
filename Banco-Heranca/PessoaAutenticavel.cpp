#include "PessoaAutenticavel.hpp"

PessoaAutenticavel::PessoaAutenticavel(std::string senha):
senha(senha)
{

}

bool PessoaAutenticavel::autentica(std::string senha) const {
    return senha == this->senha;
}