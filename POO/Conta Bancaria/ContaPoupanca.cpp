#include "ContaPoupanca.h"

ContaPoupanca::ContaPoupanca(const std::string& titular, double saldo, double taxa)
        : ContaBancaria(titular, saldo), taxa_(taxa) {}

void ContaPoupanca::aplicarJuros() {
    saldo_ += saldo_ * taxa_;
}
