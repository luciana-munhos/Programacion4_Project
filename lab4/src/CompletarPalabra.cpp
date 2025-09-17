#include "../include/CompletarPalabra.h"

CompletarPalabra::CompletarPalabra():Ejercicio(){}

CompletarPalabra::CompletarPalabra(string& desc,string& fra,list<string> sol):Ejercicio(desc,fra){
    Solucion = sol;
}


list<string> CompletarPalabra::getSolucion(){
    return Solucion;
}

void CompletarPalabra::setSolucion(list<string> s){
    Solucion = s;
}

bool CompletarPalabra::corregirResp(list<string> resp){
    return resp == getSolucion();
}