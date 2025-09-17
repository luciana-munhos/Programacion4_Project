#include "../include/Profesor.h"
//Idiomas  validos con instancias ya creadas
Profesor::Profesor(string nick,string contra, string nom, string descripcion, string ins, set<Idioma*> idi){
    setNickname(nick);
    setContrasenia(contra);
    setNombre(nom);
    setDescripcion(descripcion);
    Instituto = ins;
    map<string,Idioma*> res;
    set<Idioma*>::iterator it;
    for(it = idi.begin();it != idi.end(); ++it){
        Idioma* idioma = *it;
        res[idioma->getNombre()] = idioma;
    }
    MisIdiomas = res;
}

Profesor::~Profesor(){
    map<string,Curso*>::iterator itr;
    for(itr = MisCursos.begin();itr != MisCursos.end(); ++itr){
        Curso* curso = itr->second;
        curso->setProfesor(NULL);
    }
}

string Profesor::getInstituto(){
    return Instituto;
}
void Profesor::setInstituto(string i){
    Instituto = i;
}
void Profesor::addIdioma(Idioma* i){
    MisIdiomas[i->getNombre()]=i;
}
void Profesor::addCurso(Curso* c){
    MisCursos[c->getNombre()] = c;
}

set<string> Profesor::getIdiomas(){
    set<string> res;
    map<string,Idioma*>::iterator it;
    for (it = MisIdiomas.begin();it != MisIdiomas.end();++it){
        res.insert(it->first);
    }
    return res;
}

set<string> Profesor::getCursosProf(){
    set<string> res;
    map<string, Curso*>::iterator itr;

    for (itr = MisCursos.begin();itr != MisCursos.end(); ++itr){
        Curso* ins = itr->second; 
        res.insert(ins->getNombre());
    }
    return res;
}

list<string> Profesor::listCursosProf(){
    list<string> res;
    map<string, Curso*>::iterator itr;

    for (itr = MisCursos.begin();itr != MisCursos.end(); ++itr){
        Curso* ins = itr->second; 
        res.push_back(ins->getNombre());
    }
    return res;
}

list<float> Profesor::getPorcentajeAvanceCurso(){ 
    list<float> res;
    map<string, Curso*>::iterator itr;
    for(itr = MisCursos.begin(); itr != MisCursos.end(); ++itr){
        Curso* curs = itr->second;
        float porcentajeCurso = curs->getPorcentajeAvanceDeEsteCurso();
        res.push_back(porcentajeCurso);
    }
    return res;
}


void Profesor::notificarUsuario(string nomI,string nomC){
    
    list<DataNotif> notif = getDataNotifCompleto();
    DataNotif nuevaNotif=DataNotif(nomI,nomC);
    notif.insert(notif.end(),nuevaNotif);
    list<DataNotif>::iterator itr;
                       
    setDataNotifCompleto(notif);
}



list<DataNotif> Profesor::listarNotificacionesRecibidasU(){
    list<DataNotif> res = getDataNotifCompleto();
    return res;

}

void Profesor::eliminarNotif(){
    list<DataNotif> eliminar = getDataNotifCompleto();
    eliminar.clear();
    setDataNotifCompleto(eliminar);
}

//ELIMINAR CURSO
void Profesor::removerCursoDeProf(string c){
    if(MisCursos.find(c) != MisCursos.end()){
        MisCursos.erase(c); //Si el curso pertenece a dicho prof, lo elimina
    }
}

void Profesor::eliminarNotifC(string nomC, string nomId){
    list<DataNotif>::iterator itr;
    list<DataNotif> dnc = getDataNotifCompleto();
    for (itr = dnc.begin(); itr != dnc.end(); ) {
        //me fijo que el nombre del curso y el idioma de la notificacion corresponda
        if (itr->getNombreCurso() == nomC && itr->getNombreIdioma() == nomId) {
            //y si es asi lo quito de la lista
            itr = dnc.erase(itr);
        } else { //si no lo encontre, lo sigo buscando
            ++itr;
        }
    }
    setDataNotifCompleto(dnc);
}