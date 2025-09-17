#include "../include/Ejercicio.h"

Ejercicio::Ejercicio(){
    Descripcion = "";
    Frase = "";
    MiLeccion = NULL;
}

Ejercicio::Ejercicio(string& d,string& f){
    Descripcion = d;
    Frase = f;
    MiLeccion = NULL;
}

Ejercicio::Ejercicio(DataEjercicioCompleto ej){
    Descripcion = ej.getDescripcion();
    Frase = ej.getFrase();
}

string Ejercicio::getDescripcion(){
    return Descripcion;
}

string Ejercicio::getFrase(){
    return Frase;
}

Leccion* Ejercicio::getLeccion(){
    return MiLeccion;
}

void Ejercicio::setDescripcion(string desc){
    Descripcion = desc;
}

void Ejercicio::setFrase(string f){
    Frase = f;
}

void Ejercicio::setLeccion(Leccion* l){
    MiLeccion = l;
}

string Ejercicio::getTemaLeccion(){
    return getLeccion()->getTema();
}

