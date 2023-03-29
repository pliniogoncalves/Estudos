#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "letra_existe.cpp"
#include "nao_acertou.cpp"
#include "nao_enforcou.cpp"
#include "imprime_cabecalho.cpp"
#include "imprime_erros.cpp"
#include "imprime_palavra.cpp"
#include "chuta.cpp"
#include "ler_arquivo.cpp"
#include "sorteia_palavra.cpp"
#include "salva_arquivo.cpp"
#include "adciona_palavra.cpp"
#include "resultado.cpp"

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

int main(){
    
    imprime_cabecalho();

    ler_arquivo();

    sorteia_palavra();

    while(nao_acertou() && nao_enforcou()){

        imprime_erros();

        imprime_palavra();

        chuta();
    }

    resultado();

}