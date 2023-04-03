#include <iostream>
#include "letra_existe.hpp"
#include "chuta.hpp"

void chuta(std::map<char, bool>* chutou, std::vector<char>* chutes_errados){
    
    char chute;
    std::cout << std::endl;
    std::cout <<"Digite uma letra: ";
    std::cin >> chute;

    (*chutou)[chute] = true;

    if(letra_existe(chute)){
        std::cout << "Sua letra está na palavra" << std::endl;
    }
    else{
        std::cout << "Sua letra não está na palavra" << std::endl;
        chutes_errados->push_back(chute);
    }
    std::cout << std::endl;

}