#include <iostream>
#include "resultado.hpp"
#include "nao_acertou.hpp"
#include "adciona_palavra.hpp"

void resultado(std::string palavra_secreta, std::map<char, bool> chutou){
    
    std::cout << "Fim de Jogo!" << std::endl;
    std::cout << "A palavra secreta era: " << palavra_secreta << std::endl;
    
    if(nao_acertou(palavra_secreta,chutou)){
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