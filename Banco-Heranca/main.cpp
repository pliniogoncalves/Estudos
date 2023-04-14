#include <iostream>
#include <string>
#include "Conta.hpp"
#include "Conta.cpp"
#include "ContaCorrente.hpp"
#include "ContaCorrente.cpp"
#include "ContaPoupanca.hpp"
#include "ContaPoupanca.cpp"
#include "Titular.hpp"
#include "Titular.cpp"
#include "Cpf.hpp"
#include "Cpf.cpp"
#include "Funcionario.hpp"
#include "Funcionario.cpp"
#include "Pessoa.hpp"
#include "Pessoa.cpp"
#include "PessoaAutenticavel.hpp"
#include "PessoaAutenticavel.cpp"

using namespace std;

void ExibeSaldo(const Conta& conta)
{
    cout << "O saldo da conta é: " << conta.getSaldo() << endl;
}

void RealizaSaque(Conta& conta)
{
    conta.sacar(200);
}

void FazLogin(PessoaAutenticavel& pessoa, string senha){

    if(pessoa.autentica(senha)){
        cout << "Login realizad com sucesso" << endl;
    }else{
        cout << "Senha Inválida" << endl;
    }

}

int main()
{
    Titular titular(Cpf("123.456.789-10"), "Plinio","senha1");

    ContaPoupanca umaConta("123456", titular);
    umaConta.depositar(500);
    RealizaSaque(umaConta);

    ExibeSaldo(umaConta);


    Titular outro(Cpf("098.765.432-10"), "Ricardo Goncalves", "senha2");
    ContaCorrente umaOutraConta("654321", titular);
    umaOutraConta.depositar(300);
    umaOutraConta.transferePara(umaConta, 250);


    ExibeSaldo(umaOutraConta);
    ExibeSaldo(umaConta);

    cout << "Número de contas: " << Conta::getNumeroDeContas() << endl;

    return 0;

}
