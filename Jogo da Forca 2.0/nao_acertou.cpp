#include <string>
#include <map>
#include <vector>

std::map<char, bool> chutou;
std::string palavra_secreta;

bool nao_acertou(){
    
    for(char letra: palavra_secreta){
        if(!chutou[letra]){
            return true;
        }
    }

    return false;
}