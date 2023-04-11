#include "ContaBancaria.h"
#include "ContaBancaria.cpp"
#include "ContaCorrente.h"
#include "ContaCorrente.cpp"
#include "ContaPoupanca.h"
#include "ContaPoupanca.cpp"
#include <memory>


int main(){
    // Cria um objeto da classe ContaBancaria
    std::unique_ptr<ContaBancaria> contaBancaria(new ContaBancaria("Titular1", 1000.0));

    // Cria um objeto da classe ContaPoupanca
    std::unique_ptr<ContaPoupanca> contaPoupanca(new ContaPoupanca("Titular2", 2000.0, 0.02));

    // Cria um objeto da classe ContaCorrente
    std::unique_ptr<ContaCorrente> contaCorrente(new ContaCorrente("Titular3", 3000.0, 1000.0));

    // Realiza operações nas contas
    contaBancaria->depositar(500.0);
    contaBancaria->sacar(200.0);
    contaBancaria->exibirSaldo();

    contaPoupanca->aplicarJuros();
    contaPoupanca->exibirSaldo();

    contaCorrente->sacar(4000.0);
    contaCorrente->exibirSaldo();

    return 0;
}