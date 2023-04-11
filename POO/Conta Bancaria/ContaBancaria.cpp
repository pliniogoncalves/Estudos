#include "ContaBancaria.h"

ContaBancaria::ContaBancaria(const std::string& titular, double saldo)
        : titular_(titular), saldo_(saldo) {}

void ContaBancaria::depositar(double valor) {
    saldo_ += valor;
}

void ContaBancaria::sacar(double valor) {
    if (saldo_ >= valor) {
        saldo_ -= valor;
    } else {
        std::cout << "Saldo insuficiente." << std::endl;
    }
}

void ContaBancaria::exibirSaldo() const {
    std::cout << "Titular: " << titular_ << ", Saldo: R$ " << saldo_ << std::endl;
}