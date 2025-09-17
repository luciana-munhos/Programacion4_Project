#include "../include/Inscripcion.h"
#include <ctime>

Inscripcion::Inscripcion(){
    Aprobado = false;
    // FECHA DE HOY
    time_t tiempoActual = std::time(nullptr);
    tm* fechaHora = std::localtime(&tiempoActual);
    int a = fechaHora->tm_year + 1900; // El anio se cuenta desde 1900
    int m = fechaHora->tm_mon + 1;     // Los meses se cuentan desde 0
    int d = fechaHora->tm_mday;        // Dia del mes
    Date f(d,m,a);
    FechaInsc = f;
    MiCurso = NULL;
    MiEstudiante = NULL;
}

Inscripcion::~Inscripcion(){
    Curso* c = getMiCurso();
    if(c != NULL)
        c->removeInscripcion(this);
    set<InscriptoLeccion*>::iterator it = MisInscriptoLecciones.begin();
    while(it!=MisInscriptoLecciones.end()){
        InscriptoLeccion* insLecc = *it;
        ++it;
        MisInscriptoLecciones.erase(insLecc);
        delete insLecc;
    }
}

// Getters
Date Inscripcion::getFechaInsc(){
    return FechaInsc;
}

bool Inscripcion::getAprobado(){
    return Aprobado;
}

Curso* Inscripcion::getMiCurso(){
    return MiCurso;
}

Estudiante* Inscripcion::getMiEstudiante(){
    return MiEstudiante;
}

set<InscriptoLeccion*> Inscripcion::getMisInscriptoLecciones(){
    return MisInscriptoLecciones;
}

string Inscripcion::getNombreCurso(){
    return MiCurso->getNombre();
}

// Setters
void Inscripcion::setFechaInsc(Date d){ // no deberia existir
    FechaInsc = d;
}

void Inscripcion::setAprobado(bool aprob){
    Aprobado = aprob;
}

void Inscripcion::setMiCurso(Curso* c){
    MiCurso = c;
}

void Inscripcion::setMiEstudiante(Estudiante* e){
    MiEstudiante = e;
}

// Para manejar misInscriptoLecciones
void Inscripcion::addInscriptoLeccion(InscriptoLeccion* il){
    MisInscriptoLecciones.insert(il);
}

void Inscripcion::removeInscriptoLeccion(InscriptoLeccion* il){
    MisInscriptoLecciones.erase(il);
}

float Inscripcion::getPorcentajeAvanceInscripcion(){
    float res;
    set<InscriptoLeccion*>::iterator itr;
    int ejsAprobadosDeMisLecciones = 0;
    int ejsTotalesDeMisLecciones = 0;


    for(itr = MisInscriptoLecciones.begin(); itr != MisInscriptoLecciones.end(); itr++){
        InscriptoLeccion* insLecc = *itr;

        ejsAprobadosDeMisLecciones += insLecc->getEjerciciosAprobadosInscriptoLeccion();
        ejsTotalesDeMisLecciones += insLecc->getEjerciciosTotalesInscriptoLeccion();

    }
    res = (ejsAprobadosDeMisLecciones*100)/ejsTotalesDeMisLecciones;
    return res;
}

//Realizarej
set<DataEjercicio> Inscripcion::getEjsNoAprobUltLec(){
    set<DataEjercicio> res;
    set<InscriptoLeccion*>::iterator itr = MisInscriptoLecciones.begin();
    InscriptoLeccion* insLecc = *itr;

    while(insLecc->getAprobado() && itr != MisInscriptoLecciones.end() ){
        ++itr;
        insLecc = *itr;
    }
    res = insLecc->getEjsNoAprobUltLec();
    return res;
}

//ELIMINAR CURSO
void Inscripcion::removerInscripcionDeEst(){
    if(getMiEstudiante() != NULL){
        getMiEstudiante()->removerInscripcion(this);
    }
}

void Inscripcion::destruirInscriptoLeccionYProgresos(){
    set<InscriptoLeccion*>::iterator itIL = MisInscriptoLecciones.begin();
    InscriptoLeccion * inscriptoLeccion;
    while(itIL != MisInscriptoLecciones.end()){
        inscriptoLeccion = *itIL;
        ++itIL;
        inscriptoLeccion->destruirProgresos();
        MisInscriptoLecciones.erase(inscriptoLeccion);
        delete inscriptoLeccion;
    }
}

bool Inscripcion::esInsc(string nC){
    return nC==getNombreCurso();
}

bool Inscripcion::revisarSiCursoTerminado(string fraseEj,string lecTema){
        set<InscriptoLeccion*>::iterator it;
        bool actualizarAprobLec;
        bool lecAprob;
        bool encontreL = false;
        InscriptoLeccion* il;
        for(it = MisInscriptoLecciones.begin();it != MisInscriptoLecciones.end() && !encontreL;++it){
            il = *it;
            encontreL = il->esLec(lecTema);  
        }
        actualizarAprobLec = il->revisarSiLecTerminada(fraseEj);
        if(actualizarAprobLec){
            il->setAprobado(true);
            lecAprob = true; // iterar mientras sea true
            for(it = MisInscriptoLecciones.begin();it != MisInscriptoLecciones.end() && lecAprob;++it){
                il = *it;
                lecAprob = il->getAprobado();
            }
            if(lecAprob){ // pues todas las lecciones estan aprobadas
                return true;
            }
        }
        return false;   
}