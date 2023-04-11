#ifndef POO_CONTACORRENTE_H
#define POO_CONTACORRENTE_H

#include "ContaBancaria.h"

class ContaCorrente : public ContaBancaria {
public:
    ContaCorrente(const std::string& titular, double saldo, double limite);
    void sacar(double valor) override;

private:
    double limite_;
};

#endif //POO_CONTACORRENTE_H
