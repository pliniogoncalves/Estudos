#include <iostream>
using namespace std;
#include <string>

const string PALAVRA_SECRETA = "MELANCIA";

bool letra_existe(char chute){
    for(int i = 0; i < PALAVRA_SECRETA.size(); i++){
        if(chute == PALAVRA_SECRETA[i]){
            return true;
        }
    }

    return false;
}

int main(){
    cout << "*****************" << endl;
    cout << "* Jogo da Forca *" << endl;
    cout << "*****************" << endl;

    bool nao_acertou = true;
    bool nao_enforcou = true;

    while(nao_acertou && nao_enforcou){
        char chute;
        cout <<"Digite uma letra" << endl;
        cin >> chute;

        if(letra_existe(chute)){
            cout << "Sua letra está na palavra" << endl;
        }
        else{
            cout << "Sua letra não está na palavra" << endl;
        }
    }

}