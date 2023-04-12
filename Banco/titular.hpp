#pragma once
#include <string>

class Titular {
private:
    std::string nome;
    std::string cpf;
public:
    Titular(std::string nome, std::string cpf);
    std::string getNome() const;
    std::string getCpf() const;
private:
    void verificaTamanhoDoNome();
};



