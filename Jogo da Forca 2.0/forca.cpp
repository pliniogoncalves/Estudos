#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "letra_existe.hpp"
#include "nao_acertou.hpp"
#include "nao_enforcou.hpp"
#include "imprime_cabecalho.hpp"
#include "imprime_erros.hpp"
#include "imprime_palavra.hpp"
#include "chuta.hpp"
#include "ler_arquivo.hpp"
#include "sorteia_palavra.hpp"
#include "salva_arquivo.hpp"
#include "adciona_palavra.hpp"
#include "resultado.hpp"

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