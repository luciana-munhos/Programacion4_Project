#include "../include/Leccion.h"
#include "../include/CompletarPalabra.h"
#include "../include/Traducir.h"

Leccion::Leccion(){
    Tema = "";
    Objetivo = "";

    MiCurso = NULL;
}

Leccion::Leccion(string t,string o){
    Tema = t;
    Objetivo = o;

    MiCurso = NULL;
}

Leccion::Leccion(Curso* c,DataLeccion lec,list<DataEjercicioCompleto> ejs){
    Tema = lec.getTema();
    Objetivo = lec.getObjetivo();
    
    MiCurso = c;

    list<DataEjercicioCompleto>::iterator ejIt;
    
    for(ejIt = ejs.begin();ejIt != ejs.end();++ejIt){
        DataEjercicioCompleto ej = *ejIt;
        Ejercicio* e;

        string desc = ej.getDescripcion();
        string frase = ej.getFrase();
        list<string> sol = ej.getSolucion();

        if(ej.getEsCompletar())
            e = new CompletarPalabra(desc,frase,sol);
        
        else
            e = new Traducir(desc,frase,sol);

        MisEjercicios[frase] = e;
        e->setLeccion(this);
    }
}

Leccion::~Leccion(){
    map<string,Ejercicio*>::iterator it = MisEjercicios.begin();
    while(it != MisEjercicios.end()){
        Ejercicio* e = it->second;
        ++it;
        MisEjercicios.erase(e->getFrase());
        delete e;
    }
}

string Leccion::getObjetivo(){
    return Objetivo;
}

string Leccion::getTema(){
    return Tema;
}

Curso* Leccion::getCurso(){
    return MiCurso;
}

Ejercicio* Leccion::getEj(string ej){
    return MisEjercicios[ej];
}

int Leccion::getCantEjercicios(){
    return MisEjercicios.size();
}

void Leccion::setObjetivo(string o){
    Objetivo = o;
}

void Leccion::setTema(string t){
    Tema = t;
}

void Leccion::setCurso(Curso* c){
    MiCurso = c;
}

void Leccion::addEjercicio(Ejercicio* e){
    MisEjercicios[e->getFrase()] = e;
}

void Leccion::removeEjercicio(Ejercicio *e){
    MisEjercicios.erase(e->getFrase());
    delete e; 
}

//devuelve el set de ejercicios correspondientes a la leccion
set<Ejercicio*> Leccion::getEjerciciosLeccion(){
    set<Ejercicio*> res;
    map<string,Ejercicio*>::iterator itr;

    for(itr = MisEjercicios.begin(); itr != MisEjercicios.end(); ++itr){
        Ejercicio* e = itr->second;
        res.insert(e);
    }

    return res;
}

//ELIMINAR CURSO
void Leccion::destruirEjerciciosLeccion(){
    set<Ejercicio*>::iterator itE;
    set<Ejercicio*> ejerciciosLeccion = getEjerciciosLeccion();
    for(itE = ejerciciosLeccion.begin(); itE != ejerciciosLeccion.end(); ++itE){
        delete (*itE);
    }
}


//Realizar ejercicio
map<string,Ejercicio*> Leccion::getMisEjercicios(){
    return MisEjercicios;
}
bool Leccion::esEjercicio(string fraseEj){
    return MisEjercicios.find(fraseEj) != MisEjercicios.end();
}
