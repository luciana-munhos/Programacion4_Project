#include "../include/Fabrica.h"

using namespace std;

IUsuario* Fabrica::getIUsuario(){
    return ContUsuario::getInstance();
}

ICurso* Fabrica::getICurso(){
    return ContCurso::getInstance();
}

void Fabrica::deleteIUsuario(){
    ContUsuario::deleteInstance();
}

void Fabrica::deleteICurso(){
    ContCurso::deleteInstance();
}

