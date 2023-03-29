#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> ler_arquivo(){

    std::ifstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open()){
        int quantidade_palavras;
        arquivo >> quantidade_palavras;

        std::vector<std::string> palavras_do_arquivo;

        for(int i=0; i<quantidade_palavras; i++){
            std::string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
        }

        arquivo.close();

        return palavras_do_arquivo;
    
    }
    else{
        std::cout << "Não foi possivel acessar o arquivo" << std::endl;
        exit(0);
    }

}