#include "../include/InscriptoLeccion.h"

InscriptoLeccion::InscriptoLeccion(){
    Aprobado = false;
    
    MiLeccion = NULL;
    MisProgresos = set<Progreso*>();
}

InscriptoLeccion::InscriptoLeccion(bool aprob){
    Aprobado = aprob;
    MiLeccion = NULL;
    MisProgresos = set<Progreso*>();
}

InscriptoLeccion::~InscriptoLeccion(){
    set<Progreso*>::iterator itr = MisProgresos.begin();
    while(itr != MisProgresos.end()){
        Progreso* p = *itr;
        ++itr;
        MisProgresos.erase(p);
        delete p;
        
    }
}

// Getters
bool InscriptoLeccion::getAprobado(){
    return Aprobado;
}

Leccion* InscriptoLeccion::getMiLeccion(){
    return MiLeccion;
}

set<Progreso*> InscriptoLeccion::getMisProgresos(){
    return MisProgresos;
}

// Setters
void InscriptoLeccion::setAprobado(bool aprob){
    Aprobado = aprob;
}

void InscriptoLeccion::setMiLeccion(Leccion* l){
    MiLeccion = l;
}

// Para manejar MisProgresos
void InscriptoLeccion::addProgreso(Progreso* p){
    MisProgresos.insert(p);
}

void InscriptoLeccion::removeProgreso(Progreso* p){
    MisProgresos.erase(p);
}

//PARA CONSULTAR ESTADISTICAS

//esta devuelve la cantidad de progresos aprobados del InscriptoLeccion
int InscriptoLeccion::getEjerciciosAprobadosInscriptoLeccion(){
    int ejsAprobados=0;

    set<Progreso*>::iterator itr;
    for(itr = MisProgresos.begin(); itr != MisProgresos.end(); ++itr){
        Progreso* prog = *itr;
        if (prog->getAprobado()) {
            ejsAprobados++;
        }
    }

    return ejsAprobados;
}

//esta devuelve la cantidad de progresos (totales) del InscriptoLeccion
int InscriptoLeccion::getEjerciciosTotalesInscriptoLeccion(){
    return MisProgresos.size();
}



//realizar ejercicio
set<DataEjercicio> InscriptoLeccion::getEjsNoAprobUltLec(){
    set<DataEjercicio> res;
    set<Progreso*>::iterator it;
    for(it = MisProgresos.begin(); it != MisProgresos.end(); it++){
        Progreso* prog = *it;
        if(!prog->getAprobado()){
            Ejercicio* ej = prog->getMiEjercicio();
            DataEjercicio de(ej->getFrase(),ej->getDescripcion());
            res.insert(de);
        }
    }
    return res;
}

bool InscriptoLeccion::esLec(string lecTema){
    return MiLeccion->getTema() == lecTema;
}

bool InscriptoLeccion::revisarSiLecTerminada(string fraseEj){
    set<Progreso*>::iterator it;
    bool encontreP = false;
    Progreso* p;
    for (it = MisProgresos.begin();it != MisProgresos.end() && !encontreP;++it){
        p = *it;
        encontreP = p->esProgresoBuscado(fraseEj);
    }
    p->setAprobado(true);

    // recorro los progresos para ver si la lec fue terminada
    bool ejAprob = true;
    for (it = MisProgresos.begin();it != MisProgresos.end() && ejAprob;++it){
        p = *it;
        ejAprob = (*it)->getAprobado();
    }
    // si ejAprob -> todos los ejs estan aprobados
    // si !ejAprob -> se termina la iteracion porque dio false -> lec no terminada
    return ejAprob; 
}

//ELIMINAR CURSO
void InscriptoLeccion::destruirProgresos(){
    set<Progreso*>::iterator itP = MisProgresos.begin();
    while(itP != MisProgresos.end()){
        Progreso* p = *itP;
        ++itP;
        MisProgresos.erase(p);
        delete p;
    }
}