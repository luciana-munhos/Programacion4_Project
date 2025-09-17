#include "../include/Datatypes.h"

// Date 
Date::Date(){
    Dia = 0;
    Mes = 0;
    Anio = 0;
}

Date::Date(int dia, int mes,int anio){
    Dia = dia;
    Mes = mes;
    Anio = anio;
}

int Date::getDia(){
    return Dia;
}

int Date::getMes(){
    return Mes;
}

int Date::getAnio(){
    return Anio;
}

//DataNotif
DataNotif::DataNotif(string i,string c){
    NombreIdioma = i;
    NombreCurso = c;
}

string DataNotif::getNombreIdioma(){
    return NombreIdioma;
}

string DataNotif::getNombreCurso(){
    return NombreCurso;
}


// DataEjercicio
DataEjercicio::DataEjercicio(string f,string d){
    Frase = f;
    Descripcion = d;
}

string DataEjercicio::getFrase(){
    return Frase;
}

string DataEjercicio::getDescripcion(){
    return Descripcion;
}

//DataLeccion
DataLeccion::DataLeccion(){
    Tema = "";
    Objetivo = "";
}

DataLeccion::DataLeccion(string t, string o){
    Tema = t;
    Objetivo = o;
}


string DataLeccion::getTema(){
    return Tema;
}

string DataLeccion::getObjetivo(){
    return Objetivo;
}

//DataCurso
DataCurso::DataCurso(string n,string desc,nivelDif nd){
    Nombre = n;
    Descripcion = desc;
    Dificultad = nd;
}

string DataCurso::getNombre(){
    return Nombre;
}
string DataCurso::getDescripcion(){
    return Descripcion;
}
nivelDif DataCurso::getNivelDif(){
    return Dificultad;
}

// DataEjercicioCompleto
DataEjercicioCompleto::DataEjercicioCompleto(string frase, string desc, list<string> sol, bool esC){
    Frase = frase;
    Descripcion = desc;
    Solucion = sol;
    EsCompletar = esC;
}

string DataEjercicioCompleto::getFrase(){
    return Frase;
}

string DataEjercicioCompleto::getDescripcion(){
    return Descripcion;
}

list<string> DataEjercicioCompleto::getSolucion(){
    return Solucion;
}
bool DataEjercicioCompleto::getEsCompletar(){
    return EsCompletar;
}
// DataLeccionCompleta
DataLeccionCompleta::DataLeccionCompleta(string t,string obj,set<DataEjercicioCompleto> ejs){
    Tema = t;
    Objetivo = obj;
    Ejercicios = ejs;
}
DataLeccionCompleta::DataLeccionCompleta(string t,string obj){
    Tema = t;
    Objetivo = obj;
}
string DataLeccionCompleta::getTema(){
    return Tema;
}

string DataLeccionCompleta::getObjetivo(){
    return Objetivo;
}

set<DataEjercicioCompleto> DataLeccionCompleta::getEjercicios(){
    return Ejercicios;
}

void DataLeccionCompleta::addEjercicio(DataEjercicioCompleto& DataEjC){
    Ejercicios.insert(DataEjC);
}

DataCursoyCants::DataCursoyCants(){
    Nombre = "";
    Descripcion = "";
    Dificultad = Principiante;
    cantLecciones = 0;
    cantEjercicios = 0;
}


// DataCursoCompleto

string DataCursoCompleto::getNomC(){
    return NomC;
}

string DataCursoCompleto::getDescC(){
    return DescC;
}

nivelDif DataCursoCompleto::getDifC(){
    return DifC;
}

string DataCursoCompleto::getIdiomaC(){
    return IdiomaC;
}

string DataCursoCompleto::getProfC(){
    return ProfC;
}

bool DataCursoCompleto::getEstaHabilitado(){
    return estaHabilitado;
}

set<string> DataCursoCompleto::getPreviasC(){
    return PreviasC;
}

map<int,DataLeccion> DataCursoCompleto::getLecciones(){
    return Lecciones;
}

list<DataEjercicioCompleto> DataCursoCompleto::getEjercicios(int i){
    return Ejercicios[i];
}

DataCursoCompleto::DataCursoCompleto(string nom,string desc,nivelDif dif,string idi,string prof,bool hab,set<string> previas,map<int,DataLeccion> lecciones,map<int,list<DataEjercicioCompleto>> ejercicios){
    NomC = nom;
    DescC = desc;
    DifC = dif;
    IdiomaC = idi;
    ProfC = prof;
    estaHabilitado = hab;
    if(previas.size() > 0)
        PreviasC = previas;
    if(lecciones.size() > 0)
        Lecciones = lecciones;
    if(ejercicios.size() > 0)
        Ejercicios = ejercicios;
}

void DataCursoCompleto::setNomC(string& n){
    NomC = n;
}

void DataCursoCompleto::setDescC(string& d){
    DescC = d;
}

void DataCursoCompleto::setDifC(nivelDif& nD){
    DifC = nD;
}

void DataCursoCompleto::setIdiomaC(string& id){
    IdiomaC = id;
}

void DataCursoCompleto::setProfC(string& p){
    ProfC = p;
}

void DataCursoCompleto::setEstaHabilitado(bool& h){
    estaHabilitado = h;
}

void DataCursoCompleto::setPreviasC(set<string>& p){
    PreviasC = p;
}

void DataCursoCompleto::addPreviaC(string& p){
    PreviasC.insert(p);
}

void DataCursoCompleto::removePreviaC(string& p){
    PreviasC.erase(p);
}


bool operator<(DataLeccion lhs, DataLeccion rhs) {
    if (lhs.getTema() != rhs.getTema()) {
        return lhs.getTema() < rhs.getTema();
    } else {
        return lhs.getObjetivo() < rhs.getObjetivo();
    }
}

bool operator==(DataLeccion lhs, DataLeccion rhs) {
    return (lhs.getTema() == rhs.getTema()) && (lhs.getObjetivo() == rhs.getObjetivo());
}

bool operator<(DataNotif lhs, DataNotif rhs){
    return lhs.getNombreCurso() < rhs.getNombreCurso();
}

//DataCursoConsulta
string DataCursoConsulta::getNomC(){
    return NomC;
}

string DataCursoConsulta::getDescC(){
    return DescC;
}

nivelDif DataCursoConsulta::getDifC(){
    return DifC;
}

string DataCursoConsulta::getIdiomaC(){
    return IdiomaC;
}

string DataCursoConsulta::getProfC(){
    return ProfC;
}

bool DataCursoConsulta::getEstaHabilitado(){
    return estaHabilitado;
}

DataCursoConsulta::DataCursoConsulta(){
}

DataCursoConsulta::DataCursoConsulta(string nom,string desc,nivelDif dif,string idi,string prof,bool hab){
    NomC = nom;
    DescC = desc;
    DifC = dif;
    IdiomaC = idi;
    ProfC = prof;
    estaHabilitado = hab;
}

//DataInscripcionConsulta
DataInscripcionConsulta::DataInscripcionConsulta(string e, Date fecha){
    nombreEst = e;
    fechaInsc = fecha;
}

DataInscripcionConsulta::DataInscripcionConsulta(){
}

string DataInscripcionConsulta::getNombreEst(){
    return nombreEst;
}

Date DataInscripcionConsulta::getFechaInsc(){
    return fechaInsc;
}



//constructor of datacursoycants
DataCursoyCants::DataCursoyCants(string nom,string desc,nivelDif dif,int cantL,int cantE){
    Nombre = nom;
    Descripcion = desc;
    Dificultad = dif;
    cantLecciones = cantL;
    cantEjercicios = cantE;
}

string DataCursoyCants::getNombre(){
    return Nombre;
}

string DataCursoyCants::getDescripcion(){
    return Descripcion;
}

nivelDif DataCursoyCants::getDificultad(){
    return Dificultad;
}

int DataCursoyCants::getCantLecciones(){
    return cantLecciones;
}

int DataCursoyCants::getCantEjercicios(){
    return cantEjercicios;
}

//DATAUSUARIO
DataUsuario::~DataUsuario(){};

DataEstudiante::DataEstudiante(string n,string d,string p,Date fn){
            setNombre(n);
            setDescripcion(d);
            pais = p;
            fechaNac = fn;
            }

DataProfesor::DataProfesor(string n,string d,string i,set<string> idi){
            setNombre(n);
            setDescripcion(d);            
            Instituto = i;
            MisIdiomas = idi;
            }

bool operator<(DataEjercicio ej1, DataEjercicio ej2) {
    if (ej1.getDescripcion() != ej2.getDescripcion()) {
        return ej1.getDescripcion() < ej2.getDescripcion();
    } else {
        return ej1.getFrase() < ej2.getFrase();
    }
}

bool operator==(DataEjercicio ej1, DataEjercicio ej2) {
    return (ej1.getDescripcion() == ej2.getDescripcion()) && (ej1.getFrase() == ej2.getFrase());
}


bool operator<(DataCursoyCants c1, DataCursoyCants c2) {
    return c1.getNombre() < c2.getNombre();
}

bool operator<(DataInscripcionConsulta dic1, DataInscripcionConsulta dic2) {
    if (dic1.getFechaInsc().getAnio() < dic2.getFechaInsc().getAnio()){
        return true;
    } else if (dic1.getFechaInsc().getAnio() > dic2.getFechaInsc().getAnio()){
        return false;
    } else if (dic1.getFechaInsc().getMes() < dic2.getFechaInsc().getMes()){
        return true;
    } else if (dic1.getFechaInsc().getMes() > dic2.getFechaInsc().getMes()) {
        return false;
    } else {
        return (dic1.getFechaInsc().getDia() < dic2.getFechaInsc().getDia());
    }    
}

bool operator==(DataInscripcionConsulta dic1, DataInscripcionConsulta dic2) {
    return (dic1.getFechaInsc().getDia() == dic2.getFechaInsc().getDia()) && (dic1.getFechaInsc().getMes() == dic2.getFechaInsc().getMes()) && (dic1.getFechaInsc().getAnio() == dic2.getFechaInsc().getAnio());
}


bool operator<(DataEjercicioCompleto ej1, DataEjercicioCompleto ej2) {
    if (ej1.getDescripcion() != ej2.getDescripcion()) {
        return ej1.getDescripcion() < ej2.getDescripcion();
    } else {
        return ej1.getFrase() < ej2.getFrase();
    }
}

bool operator==(DataEjercicioCompleto ej1, DataEjercicioCompleto ej2) {
    return (ej1.getDescripcion() == ej2.getDescripcion()) && (ej1.getFrase() == ej2.getFrase());
}


bool operator<(DataLeccionCompleta lecc1, DataLeccionCompleta lecc2) {
    if (lecc1.getTema() != lecc2.getTema()) {
        return lecc1.getTema() < lecc2.getTema();
    } else {
        return lecc1.getObjetivo() < lecc2.getObjetivo();
    }
}

bool operator==(DataLeccionCompleta lecc1, DataLeccionCompleta lecc2) {
    return (lecc1.getTema() == lecc2.getTema()) && (lecc1.getObjetivo() == lecc2.getObjetivo());
}
