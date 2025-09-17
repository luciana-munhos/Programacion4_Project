#include "../include/Curso.h"
#include "../include/Traducir.h"
#include "../include/CompletarPalabra.h"

Curso::Curso(){
    Nombre = "";
    Descripcion = "";
    Dificultad = Principiante;
    Habilitado = false;

    MiProfesor = NULL;
    MiIdioma = NULL;
}

Curso::~Curso(){
    if(MiProfesor != NULL)
        MiProfesor->removerCursoDeProf(Nombre);

    set<Inscripcion*>::iterator itIns = MisInscripciones.begin();
    while(itIns != MisInscripciones.end()){
        Inscripcion* i = *itIns;
        ++itIns;
        MisInscripciones.erase(i);
        delete i;
    }

    for(map<string,Curso*>::iterator it = MisPrevias.begin();it != MisPrevias.end();++it){
        Curso* c = it->second;
        c->removePosterior(this);
    }

    for(map<string,Curso*>::iterator it = CursosPosteriores.begin();it != CursosPosteriores.end();++it){
        Curso* c = it->second;
        c->removePrevia(this);
    }

    list<Leccion*>::iterator it = MisLecciones.begin();
    while(it != MisLecciones.end()){
        Leccion* l = *it;
        ++it;
        MisLecciones.remove(l);
        delete l;
    }
}

Curso::Curso(string& nomC,string& descC,nivelDif difC,bool habC){
    Nombre = nomC;
    Descripcion = descC;
    Dificultad = difC;
    Habilitado = habC;

    MiProfesor = NULL;
    MiIdioma = NULL;
}

Curso::Curso(DataCursoCompleto dataC){
    Nombre = dataC.getNomC();
    Descripcion = dataC.getDescC();
    Dificultad = dataC.getDifC();
    

    Habilitado = false;

    map<int,DataLeccion> Lecciones = dataC.getLecciones();
    set<DataLeccion>::iterator lecIt;
    DataLeccion lec;
    

    for(unsigned int i = 1; i<=Lecciones.size(); i++){
        list<DataEjercicioCompleto> ejs = dataC.getEjercicios(i);
        lec = Lecciones[i];
        Leccion* l = new Leccion(this,lec,ejs);
        MisLecciones.push_back(l);
    }
}


string Curso::getNombre(){
    return Nombre;
}

string Curso::getDescripcion(){
    return Descripcion;
}
nivelDif Curso::getDificultad(){
    return Dificultad;
}

bool Curso::getHabilitado(){
    return Habilitado;
}

Profesor* Curso::getProfesor(){
    return MiProfesor;
}

Idioma* Curso::getIdioma(){
    return MiIdioma;
}

set<Inscripcion*> Curso::getMisIncripciones(){
    return MisInscripciones;
}

Leccion* Curso::getLeccion(string temaLec){
    list<Leccion*>::iterator it;
    Leccion* l;
    for(it = MisLecciones.begin();it!=MisLecciones.end();++it){
        l = *it;
        if(l->getTema() == temaLec){
            return l;
        }
    }
    return NULL;
}

int Curso::getCantLecciones(){
    return MisLecciones.size();
}

int Curso::getCantEjercicios(){
    int res = 0;
    list<Leccion*>::iterator it;

    for(it = MisLecciones.begin();it!=MisLecciones.end();++it){
        Leccion* l = *it;
        res += l->getCantEjercicios();
    }
    return res;
}

map<string,Curso*> Curso::getPrevias(){
    return MisPrevias;
}

map<string,Curso*> Curso::getCursosPosteriores(){
    return CursosPosteriores;
}

list<Leccion*> Curso::getMisLecciones(){
    return MisLecciones;
}

Ejercicio* Curso::getEj(string fraseEj){
    list<Leccion*>::iterator itL;
    bool encontreE = false;
    Leccion* l;
    for(itL = MisLecciones.begin(); itL != MisLecciones.end() && !encontreE; ++itL){
        l = *itL;
        encontreE = l->esEjercicio(fraseEj);
    }
    if(encontreE){
        return l->getEj(fraseEj);
    }
    return NULL;
}

void Curso::setNombre(string n){
    Nombre = n;
}
void Curso::setDescripcion(string desc){
    Descripcion = desc;
}

void Curso::setDificultad(nivelDif dif){
    Dificultad = dif;
}

void Curso::setHabilitado(bool hab){
    Habilitado = hab;
}

void Curso::setProfesor(Profesor* p){
    MiProfesor = p;
}

void Curso::setIdioma(Idioma* i){
    MiIdioma = i;
}

void Curso::addLeccion(Leccion* l){
    MisLecciones.push_back(l);
}

void Curso::addPrevia(Curso* c){
    MisPrevias[c->getNombre()] = c;
}

void Curso::addCursoPosterior(Curso* c){
    CursosPosteriores[c->getNombre()] = c;
}

void Curso::addInscripcion(Inscripcion* insc){
    MisInscripciones.insert(insc);
}

void Curso::removePrevia(Curso* c){
    MisPrevias.erase(c->getNombre());
}
void Curso::removePosterior(Curso* c){
    CursosPosteriores.erase(c->getNombre());
}

list<DataLeccion> Curso::obtenerLeccionesOrdenadas(){
    list<DataLeccion> res;
    list<Leccion*>::iterator it;
    for(it = MisLecciones.begin();it!=MisLecciones.end();++it){
        // creo el DataLeccion que la representa y lo inserto en res
        Leccion* l = *it;
        string obj = l->getObjetivo();
        string tema = l->getTema();
        DataLeccion dataLec(tema,obj);
        res.push_back(dataLec);
    }
    return res;
}


void Curso::habilitarC(string nomC){
    Idioma* idioma = getIdioma();
    idioma->notificar(nomC);
}

//CONSULTAR ESTADISTICAS
float Curso::getPorcentajeAvanceDeEsteCurso(){
    float res;
    set<Inscripcion*>::iterator itr;
    int totalInsc = MisInscripciones.size();
    if (totalInsc == 0) {
        return 0;
    }
    float sumaPromedios = 0;
    float porcentajeInsc = 0;

    for (itr = MisInscripciones.begin(); itr != MisInscripciones.end(); ++itr){
        Inscripcion* ins = *itr;
        porcentajeInsc = ins->getPorcentajeAvanceInscripcion();
        sumaPromedios += porcentajeInsc;
    }
    res = sumaPromedios/totalInsc; 
    return res;
}

list<DataLeccionCompleta> Curso::obtenerLeccionesCompletasOrdenadasDelCurso(){ 
    list<DataLeccionCompleta> res; 
    list<Leccion*>::iterator it; 
    for(it = MisLecciones.begin();it!=MisLecciones.end();++it){
        Leccion* l = *it;
        string obj = l->getObjetivo();
        string tema = l->getTema();
        set<Ejercicio*> ejs = l->getEjerciciosLeccion();
        set<Ejercicio*>::iterator itr;

        set<DataEjercicioCompleto> ejercicios; 

        for(itr = ejs.begin(); itr != ejs.end(); ++itr){
            Ejercicio* ej = *itr;
            string frase = ej->getFrase();
            string desc = ej->getDescripcion();
    
            list<string> sol;
            bool tipoEjercicio;
            
            Traducir* tr = dynamic_cast<Traducir*>(ej);
            if (tr) {
                string solucion = tr->getSolucion();
                sol.push_back(solucion);
                tipoEjercicio = false;
            } else {
                CompletarPalabra* com = dynamic_cast<CompletarPalabra*>(ej);
                sol = com->getSolucion();
                tipoEjercicio = true;
            }

            DataEjercicioCompleto ejer(frase,desc, sol,tipoEjercicio);
            ejercicios.insert(ejer); 
    
        }
        DataLeccionCompleta dataLec(tema, obj, ejercicios);
        res.push_back(dataLec); 
    } 
    return res;
}

list<DataInscripcionConsulta> Curso::obtenerInscriptosCurso(){ 
    list<DataInscripcionConsulta> res;

    set<Inscripcion*>::iterator itr;
    for(itr = MisInscripciones.begin(); itr != MisInscripciones.end(); ++itr){
        Inscripcion* insc = *itr;
        string nom = insc->getMiEstudiante()->getNombre();
        Date dt = insc->getFechaInsc();

        DataInscripcionConsulta dic(nom, dt);
        res.push_back(dic);
    }
    return res;
}

void Curso::removeInscripcion(Inscripcion* ins){
    MisInscripciones.erase(ins);
}

//ELIMINAR CURSO
void Curso::desvincularProfDeCurso(){
    if(MiProfesor!=NULL)
        MiProfesor->removerCursoDeProf(Nombre);
}

void Curso::eliminarLeccionesYEjercicios(){
    list<Leccion*>::iterator itL = MisLecciones.begin();
    list<Leccion*>::iterator borrar;
    while(itL != MisLecciones.end()){
        Leccion* lec = *itL;
        borrar = itL;
        ++itL;
        MisLecciones.erase(borrar);
        delete lec;
    }
}
void Curso::desvincularInscripcionesYEliminar(){
    set<Inscripcion*>::iterator itI = MisInscripciones.begin();
    while(itI != MisInscripciones.end()){
        Inscripcion* ins = *itI;
        ++itI;
        ins->removerInscripcionDeEst();
        ins->destruirInscriptoLeccionYProgresos();
        MisInscripciones.erase(ins);
        delete ins;
    }
}

void Curso::sacarDePrevias(){
    map<string,Curso*>::iterator itr = CursosPosteriores.begin(); 
    while(itr != CursosPosteriores.end()){
        Curso* c = itr->second;
        ++itr;
        c->removePrevia(this);
    }
    itr = MisPrevias.begin(); 
    while(itr != MisPrevias.end()){
        Curso* c = itr->second;
        ++itr;
        c->removePosterior(this);
    }
}

void Curso::eliminarNotificaciones(){
    Idioma* id = getIdioma();
    if(id!=NULL)
        id->eliminarNotifC(this->getNombre());
}
