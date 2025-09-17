#include "../include/Progreso.h"

Progreso::Progreso(){
    Aprobado = false;
    MiEjercicio = NULL;
}

Progreso::Progreso(bool aprob){
    Aprobado = aprob;
    MiEjercicio = NULL;
}

Progreso::~Progreso(){
    // No hay nada para destruir
}

// Getters
bool Progreso::getAprobado(){
    return Aprobado;
}

Ejercicio* Progreso::getMiEjercicio(){
    return MiEjercicio;
}

// Setters
void Progreso::setAprobado(bool aprob){
    Aprobado = aprob;
}

void Progreso::setMiEjercicio(Ejercicio* ej){
    MiEjercicio = ej;
}

bool Progreso::esProgresoBuscado(string fraseEj){
    return MiEjercicio->getFrase() == fraseEj;
}