#include <string>
#include <map>
#include <vector>

extern std::map<char, bool> chutou;
extern std::string palavra_secreta;

bool nao_acertou(){
    
    for(char letra: palavra_secreta){
        if(!chutou[letra]){
            return true;
        }
    }

    return false;
}