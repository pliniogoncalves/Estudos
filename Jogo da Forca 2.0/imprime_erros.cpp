#include <iostream>
#include <vector>

std::vector<char> chutes_errados;

void imprime_erros(){
    
    std::cout << "Chutes Errados: ";
        for(char letra: chutes_errados){
            std::cout << letra << " ";
        }
        std::cout << std::endl;

}