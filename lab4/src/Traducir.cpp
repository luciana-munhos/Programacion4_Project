#include "../include/Traducir.h"

Traducir::Traducir():Ejercicio(){}

Traducir::Traducir(string& desc,string& fra,list<string> s):Ejercicio(desc,fra){
    Solucion = *s.begin();
};

string Traducir::getSolucion(){
    return Solucion;
}

void Traducir::setSolucion(string s){
    Solucion = s;
}

bool Traducir::corregirResp(list<string> resp){
    return getSolucion() == resp.front();
}