#include <iostream>
#include <map>
#include <vector>
#include "letra_existe.cpp"

std::map<char, bool> chutou;
std::vector<char> chutes_errados;

void chuta(){
    
    char chute;
    std::cout << std::endl;
    std::cout <<"Digite uma letra: ";
    std::cin >> chute;

    chutou[chute] = true;

    if(letra_existe(chute)){
        std::cout << "Sua letra está na palavra" << std::endl;
    }
    else{
        std::cout << "Sua letra não está na palavra" << std::endl;
        chutes_errados.push_back(chute);
    }
    std::cout << std::endl;

}