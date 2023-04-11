
#ifndef POO_CONTABANCARIA_H
#define POO_CONTABANCARIA_H

#include <iostream>
#include <memory>


class ContaBancaria {
protected:
    std::string titular_;
    double saldo_;

public:
    ContaBancaria(const std::string& titular, double saldo);

    void depositar(double valor);
    virtual void sacar(double valor);
    void exibirSaldo() const;

};

#endif //POO_CONTABANCARIA_H
