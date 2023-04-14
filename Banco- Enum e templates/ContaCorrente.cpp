#include "ContaCorrente.hpp"
#include <iostream>

ContaCorrente::ContaCorrente(std::string numero, Titular titular): Conta(numero, titular)
{
}

void ContaCorrente::transferePara(Conta& destino, float valor)
{
    sacar(valor);
    destino.depositar(valor);
}