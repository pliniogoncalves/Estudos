#include "ContaCorrente.h"

ContaCorrente::ContaCorrente(const std::string& titular, double saldo, double limite)
        : ContaBancaria(titular, saldo), limite_(limite) {}

void ContaCorrente::sacar(double valor) {
    if (saldo_ + limite_ >= valor) {
        saldo_ -= valor;
    } else {
        std::cout << "Saldo insuficiente." << std::endl;
    }
}