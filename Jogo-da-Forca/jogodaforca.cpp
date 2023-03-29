#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char chute){
    
    for(char letra : palavra_secreta){
        if(chute == letra){
            return true;
        }
    }

    return false;

}

bool nao_acertou(){
    
    for(char letra: palavra_secreta){
        if(!chutou[letra]){
            return true;
        }
    }

    return false;
}

bool nao_enforcou(){

    return chutes_errados.size() < 5;
}

void imprime_cabecalho(){
    
    cout << "*****************" << endl;
    cout << "* Jogo da Forca *" << endl;
    cout << "*****************" << endl;
    cout << endl;

}

void imprime_erros(){
    
    cout << "Chutes Errados: ";
        for(char letra: chutes_errados){
            cout << letra << " ";
        }
        cout << endl;

}

void imprime_palavra(){
    
    for(char letra : palavra_secreta){
        if(chutou[letra]){
            cout<< letra << " ";
        }
        else{
            cout <<"_ ";
        }
    }
    cout << endl;

}

void chuta(){
    
    char chute;
    cout << endl;
    cout <<"Digite uma letra: ";
    cin >> chute;

    chutou[chute] = true;

    if(letra_existe(chute)){
        cout << "Sua letra está na palavra" << endl;
    }
    else{
        cout << "Sua letra não está na palavra" << endl;
        chutes_errados.push_back(chute);
    }
    cout << endl;

}

vector<string> ler_arquivo(){

    ifstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open()){
        int quantidade_palavras;
        arquivo >> quantidade_palavras;

        vector<string> palavras_do_arquivo;

        for(int i=0; i<quantidade_palavras; i++){
            string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
        }

        arquivo.close();

        return palavras_do_arquivo;
    
    }
    else{
        cout << "Não foi possivel acessar o arquivo" << endl;
        exit(0);
    }

}

void sorteia_palavra(){
    
    vector<string> palavras = ler_arquivo();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];

}

void salva_arquivo(vector<string> nova_lista){

    ofstream arquivo;
    arquivo.open("palavras.txt");

    if(arquivo.is_open()){
        arquivo << nova_lista.size() << endl;

        for(string palavra : nova_lista){
            arquivo << palavra << endl;
        }
     
        arquivo.close();
    }
    else{
        cout << "Não foi possivel acessar o arquivo" << endl;
        exit(0);
    }

}

void adciona_palavra(){

    cout << "Digite a nova palavra, usando letras MAIÚSCULAS: " ;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = ler_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}

void resultado(){
    
    cout << "Fim de Jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;
    
    if(nao_acertou()){
        cout << "Você perdeu! Tente Novamente!" << endl;
    }
    else{
        cout << "Parabens! Você acertou!" << endl;
        cout << endl;
        
        cout << "Você quer adcionar uma palavra ao banco? (S/N) ";
        char resposta;
        cin >> resposta;

        if(resposta == 'S'){
            adciona_palavra();
        }

    }

}

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