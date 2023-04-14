#include "titular.hpp"
#include <iostream>

Titular::Titular(std::string nome, std::string cpf):
nome(nome),
cpf(cpf)
{
    verificaTamanhoDoNome();
    getNome();
    getCpf();
}

std::string Titular::getNome() const{
    return nome;
}

std::string Titular::getCpf() const{
    return cpf;
}

void Titular::verificaTamanhoDoNome() {
    if(nome.size() < 5){
        std::cout << "Nome muito Curto" << std::endl;
        exit(1);
    }
}
