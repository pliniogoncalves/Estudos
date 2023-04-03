#include <vector>
#include <ctime>
#include <cstdlib>
#include "ler_arquivo.hpp"
#include "sorteia_palavra.hpp"



std::string sorteia_palavra(){
    
    std::vector<std::string> palavras = ler_arquivo();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

   return palavras[indice_sorteado];

}