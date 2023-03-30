#include <vector>
#include <iostream>
#include <string>
#include "ler_arquivo.hpp"
#include "salva_arquivo.hpp"

void adciona_palavra(){

    std::cout << "Digite a nova palavra, usando letras MAIÚSCULAS: " ;
    std::string nova_palavra;
    std::cin >> nova_palavra;

    std::vector<std::string> lista_palavras = ler_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}