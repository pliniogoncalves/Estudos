#include <iostream>
#include "conta.hpp"
#include "conta.cpp"
#include "titular.hpp"
#include "titular.cpp"

using namespace std;

int main()
{
    Conta umaConta(Titular("Plinio", "123-456-789-10"),"7777");

    umaConta.depositar(500);
    umaConta.sacar(200);

    //cout << "Nome: " << umaConta(.getNome()) << endl;
    //cout << "CPF: " << umaConta.getCpf() << endl;
    cout << "Numero: " << umaConta.getNumeroConta() << endl;
    cout << "Saldo : " << umaConta.getSaldo() << endl;

    cout << "Número de Contas: " << Conta::getNumeroDeContas() << endl;

    Conta umaOutraConta(Titular("Ric", "987-654-321-10"),"6666");
    
    return 0;
}
