#ifndef POO_CONTAPOUPANCA_H
#define POO_CONTAPOUPANCA_H

#include "ContaBancaria.h"

class ContaPoupanca : public ContaBancaria {
public:
    ContaPoupanca(const std::string& titular, double saldo, double taxa);
    void aplicarJuros();

private:
    double taxa_;
};

#endif //POO_CONTAPOUPANCA_H
