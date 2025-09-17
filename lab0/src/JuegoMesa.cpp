#include <string>
#include <iostream>
#include "../include/JuegoMesa.h"

//constructores
JuegoMesa::JuegoMesa():Objeto(){
    edadRecomendada=0;
    cantJugadores=0;
}

JuegoMesa::JuegoMesa(string n,int a,Estado e,int er,int c):Objeto(n,a,e){
    edadRecomendada=er;
    cantJugadores=c;       
}

//destructor
JuegoMesa::~JuegoMesa(){
}


//setters
void JuegoMesa::setEdadRecomendada(int er){
    edadRecomendada=er;
}

void JuegoMesa::setCantJugadores(int c){
    cantJugadores=c;
}



//getters
int JuegoMesa::getEdadRecomendada(){
    return edadRecomendada;
}

int JuegoMesa::getCantJugadores(){
    return cantJugadores;
}

string JuegoMesa::toString(){
     string nombreE;
    Estado estado=this->getEstado();
    switch(estado) {

        case  Nuevo:
            nombreE="Nuevo";
            break;
        case BienConservado:
            nombreE="BienConservado";
            break;
        case Roto:
            nombreE="Roto";
            break;
    }
    return "Juego: " + getNombre() +", " + to_string(getAnioComprado())+ ", " + nombreE + ", " 
            + to_string(getEdadRecomendada()) + ", " + to_string(getCantJugadores());   //posible error en estado, esperar hasta implementar objeto.
}
