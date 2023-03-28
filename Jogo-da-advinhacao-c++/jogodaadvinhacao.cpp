#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;;

int main(){
    
    cout << "***********************" << endl;
    cout << "* Jogo Da Advinhação! *" << endl;
    cout << "***********************" << endl;

    cout << "Escolha o seu nível de dificuldade: " << endl;
    cout << "Fácil(F), Médio(M) ou Difícil(D)" << endl;

    char dificuldade;

    cin >> dificuldade;

    int numero_de_tentativas;

    if(dificuldade == 'F' || dificuldade == 'f' ){
        numero_de_tentativas = 15;
    }
    else if(dificuldade == 'M' || dificuldade == 'm'){
        numero_de_tentativas = 10;
    }
    else if(dificuldade == 'D' || dificuldade == 'd'){
        numero_de_tentativas = 5;
    }

    srand(time(NULL));
    const int NUMERO_SECRETO = rand() % 100;
    
    bool nao_acertou = true;

    int tentativas = 0;

    double pontos = 1000.0;

    while(nao_acertou && (numero_de_tentativas > 0)){

        tentativas++;
        numero_de_tentativas --;
        
        int chute;

        cout << "Você está na " << tentativas << "ª tentativa" << endl;

        cout << "Qual o seu chute?" << endl;
        cin >> chute;
        cout << "O Valor do seu chute é: " << chute << endl;

        pontos = pontos - (abs (chute - NUMERO_SECRETO)/2.0);

        bool acertou = chute == NUMERO_SECRETO;
        bool maior = chute > NUMERO_SECRETO;

        if(acertou){
            cout << "Parabéns, você acertou o chute!" << endl;
            nao_acertou = false;
        }
        else if(maior){
            cout << "Seu chute foi maior que o número secreto!" << endl;
        }
        else{
            cout << "Seu chute foi menor que o número secreto!" << endl;
        }

   }
    
    cout << "Fim de Jogo!" << endl;
    
    if(nao_acertou){
        cout << "Você perdeu! Tente novamente!" << endl;
    }
    else{
        cout << "Você acertou o número secreto em " << tentativas << " tentativas" << endl;
    
        cout.precision(2);
        cout << fixed;
        cout << "Sua pontuação é de: " << pontos << " pontos!" << endl;

    }
    
}
