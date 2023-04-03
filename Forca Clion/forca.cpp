#include <string>
#include <map>
#include <vector>
#include "nao_acertou.hpp"
#include "imprime_cabecalho.hpp"
#include "imprime_erros.hpp"
#include "imprime_palavra.hpp"
#include "chuta.hpp"
#include "sorteia_palavra.hpp"
#include "resultado.hpp"

using namespace std;

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

int main(){
    
    imprime_cabecalho();

    palavra_secreta = sorteia_palavra();

    while(nao_acertou(palavra_secreta, chutou) && chutes_errados.size() < 5){

        imprime_erros(chutes_errados);

        imprime_palavra(palavra_secreta, chutou);

        chuta(&chutou, &chutes_errados);
    }

    resultado(palavra_secreta, chutou);

}