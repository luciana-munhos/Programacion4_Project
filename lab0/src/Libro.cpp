#include <string>
#include <iostream>

#include "../include/Libro.h"

//constructores
Libro::Libro():Objeto(){
    autor = string();
    cantPaginas = 0;
}

Libro::Libro(string nombre, int anio, Estado e, string aut, int cant):Objeto(nombre, anio, e){
    autor = aut;
    cantPaginas = cant;
}

Libro::~Libro(){
}

//operaciones
void Libro::set_autor(string nombre){
    autor = nombre;
}

void Libro::set_cantPaginas(int cant){
    cantPaginas = cant;
}

string Libro::get_autor(){
    return autor;
}

int Libro::get_cantPaginas(){
    return cantPaginas;
}

string Libro::toString(){
    Estado estado = getEstado();
    string nEstado;
    switch(estado) { 
        case  Nuevo:
            nEstado = "Nuevo";
            break;
        case BienConservado:
            nEstado = "BienConservado";
            break;
        case Roto:
            nEstado = "Roto";
            break;
    }
    return "Libro: " + getNombre() + ", " + to_string(getAnioComprado()) + ", " + nEstado + ", " + get_autor() + ", " + to_string(get_cantPaginas());
}
