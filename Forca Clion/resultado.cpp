#include <iostream>
#include <string>
#include "nao_acertou.hpp"
#include "adciona_palavra.hpp"

extern std::string palavra_secreta;

void resultado(){
    
    std::cout << "Fim de Jogo!" << std::endl;
    std::cout << "A palavra secreta era: " << palavra_secreta << std::endl;
    
    if(nao_acertou()){
        std::cout << "Você perdeu! Tente Novamente!" << std::endl;
    }
    else{
        std::cout << "Parabens! Você acertou!" << std::endl;
        std::cout << std::endl;
        
        std::cout << "Você quer adcionar uma palavra ao banco? (S/N) ";
        char resposta;
        std::cin >> resposta;

        if(resposta == 'S'){
            adciona_palavra();
        }

    }

}