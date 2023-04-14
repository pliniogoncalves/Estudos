#include <iostream>
#include <string>
#include "Conta.hpp"
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
#include "Autenticavel.hpp"
#include "Autenticavel.cpp"
#include "Gerente.hpp"
#include "Gerente.cpp"

using namespace std;

void ExibeSaldo(const Conta& conta)
{
    cout << "O saldo da conta é: " << conta.getSaldo() << endl;
}

void RealizaSaque(Conta& conta)
{
    conta -= 200;
}

void FazLogin(Autenticavel& alguem, string senha)
{
    if (alguem.autentica(senha)) {
        cout << "Login realizado com sucesso" << endl;
    } else {
        cout << "Senha inválida" << endl;
    }
}

ostream& operator<<(ostream& cout, const Conta& conta){

    cout << "O saldo da conta é : " << conta.getSaldo() << endl;
    cout << "O titular da conta é: " << conta.titular.getNome() << endl;

    return cout;
}

template <typename T>
T Menor(T a, T b){
    return a < b? a:b;
}

int main()
{
    Titular titular(Cpf("123.456.789-10"), "Plinio", "umasenha");

    ContaPoupanca umaConta("123456", titular);
    umaConta += 500;
    RealizaSaque(umaConta);

    //ExibeSaldo(umaConta);
    //cout << umaConta ;

    Titular outro(Cpf("098.765.432-10"), "Plinio Ricardo", "outrasenha");
    ContaCorrente umaOutraConta("654321", titular);
    umaOutraConta += 300;
    
    ContaCorrente outraContaCorrente("546312", titular);
    
    umaOutraConta.transferePara(umaConta, 250);

    //ExibeSaldo(umaOutraConta);
    //ExibeSaldo(outraContaCorrente);

    //cout << "Número de contas: " << Conta::getNumeroDeContas() << endl;

    Gerente umGerente(Cpf("000.000.000-00"), "Nome Do Gerente", 1500, DiaDaSemana::Terca, "123456");

    cout << Menor<Conta&>(umaConta, umaOutraConta);

    return 0;
}