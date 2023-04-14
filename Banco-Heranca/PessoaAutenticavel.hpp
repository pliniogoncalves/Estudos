#pragma once
#include <string>

class PessoaAutenticavel {
private:
    std::string senha;
public:
    PessoaAutenticavel(std::string senha);
    bool autentica(std::string senha)const;

};



