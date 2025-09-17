#include "../include/Estudiante.h"

Estudiante::Estudiante(string nick,string contra, string nom, string descripcion, string pais, int dia, int mes, int anio){
    setNickname(nick);
    setContrasenia(contra);
    setNombre(nom);
    setDescripcion(descripcion);
    Pais = pais;
    Date d(dia,mes,anio);
    FechaNacimiento = d;
    Inscripciones = set<Inscripcion*>();
} 


Estudiante::~Estudiante(){
    set<Inscripcion*>::iterator it = Inscripciones.begin();
    while(it!=Inscripciones.end()){
        Inscripcion* ins = *it;
        Curso* c = ins->getMiCurso();
        ++it;
        c->removeInscripcion(ins);
        Inscripciones.erase(ins);
        delete ins;
    }    
}

string Estudiante::getPais(){
    return Pais;
}

Date Estudiante::getFechaNacimiento(){
    return FechaNacimiento;
}

void Estudiante::addInscripcion(Inscripcion* i){
    Inscripciones.insert(i);
}

void Estudiante::setPais(string p){
    Pais = p;
}

void Estudiante::setFechaNacimiento(Date d){
    FechaNacimiento = d;
}

list<DataCurso> Estudiante::getCursosNoAprobados(){
    list<DataCurso> res;
    set<Inscripcion*>::iterator it;
    for(it = Inscripciones.begin();it!=Inscripciones.end();++it){
        Inscripcion* ins = *it;
        if(!ins->getAprobado()){
            Curso* c = ins->getMiCurso();
            DataCurso dc(c->getNombre(),c->getDescripcion(),c->getDificultad());
            res.push_back(dc);
        }
    }
    return res;
}

set<DataEjercicio> Estudiante::getEjsNoAprobUltLec(string nombreCurso){
    set<DataEjercicio> res;
    set<Inscripcion*>::iterator it = Inscripciones.begin();
    Inscripcion* ins;
    bool encontre = false;
    while(!encontre && it != Inscripciones.end()){
        ins = *it;
        if(ins->getMiCurso()->getNombre() == nombreCurso)
            encontre = true;
        ++it;
    }
    if(encontre)
        res = ins->getEjsNoAprobUltLec();
    
    return res;
}


//CONSULTAR ESTADISTICAS
set<string> Estudiante::getCursosEst(){
    set<string> res;
    set<Inscripcion*>::iterator itr;

    for (itr = Inscripciones.begin();itr != Inscripciones.end(); ++itr){
        Inscripcion* ins = *itr; 
        res.insert(ins->getNombreCurso());
    }
    return res;
}

list<string> Estudiante::listCursosEst(){
    list<string> res;
    set<Inscripcion*>::iterator itr;

    for (itr = Inscripciones.begin();itr != Inscripciones.end(); ++itr){
        Inscripcion* ins = *itr;
        res.push_back(ins->getNombreCurso());
    }
    return res;
}

list<float> Estudiante::getPorcentajeAvanceInscripciones(){
    list<float> res;
    set<Inscripcion*>::iterator itr;
    for (itr = Inscripciones.begin();itr != Inscripciones.end(); ++itr){
        Inscripcion* ins = *itr;
        float porcentajeInsc = ins->getPorcentajeAvanceInscripcion();
        res.push_back(porcentajeInsc);
    }
    return res;
};


void Estudiante::notificarUsuario(string nomI,string nomC){
    list<DataNotif> notif = getDataNotifCompleto();
    DataNotif nuevaNotif = DataNotif(nomI,nomC);
    notif.insert(notif.end(),nuevaNotif);
    setDataNotifCompleto(notif);
    
    }

void Estudiante::realizarInscripcion(Curso* c){
    Inscripcion* insc = new Inscripcion(); // aprobado = false y fecha de hoy
    insc->setMiEstudiante(this);
    insc->setMiCurso(c);
    
    c->addInscripcion(insc); // uno al curso (que me dio ContCurso)
    Inscripciones.insert(insc); // uno al estudiante

    list<Leccion*> lecs = c->getMisLecciones();
    list<Leccion*>::iterator itL;
    Leccion* l;

    set<Ejercicio*> ejs;
    set<Ejercicio*>::iterator itE;
    Ejercicio* e;

    if (lecs.size() == 0){
        // Como no hay lecciones, el curso esta aprobado
        insc->setAprobado(true);
    }else{
        bool aprobado = true;
        for(itL = lecs.begin();itL!=lecs.end();++itL){
            // creo una Inscripcion por cada Leccion
            l = *itL; // L ES UN PUNTERO A LA LECCION 
            InscriptoLeccion* il = new InscriptoLeccion();
            il->setMiLeccion(l);
            insc->addInscriptoLeccion(il); // ir agregando las inscriptolecciones a la insc correspondiente

            ejs = l->getEjerciciosLeccion();
            if (ejs.size() == 0){
                // La leccion esta aprobada pues no hay ejercicios para resolver
                il->setAprobado(true);
            }else{
                for (itE = ejs.begin();itE!=ejs.end();++itE){
                    // creo un progreso para cada Ejercicio
                    aprobado = false;
                    e = *itE;
                    aprobado = false;
                    Progreso* p = new Progreso();
                    p->setMiEjercicio(e);
                    il->addProgreso(p); // ir agregando los progresos a la il correspondiente 
                }
            }
        }
        insc->setAprobado(aprobado);
    }
}

list<DataNotif> Estudiante::listarNotificacionesRecibidasU(){
    list<DataNotif> res = getDataNotifCompleto();
    return res;

}

void Estudiante::eliminarNotif(){
    list<DataNotif> eliminar =getDataNotifCompleto();
    eliminar.clear();
    setDataNotifCompleto(eliminar);
}

set<Inscripcion*> Estudiante::getInscripciones(){
    return Inscripciones;
}

//ELIMINAR CURSO
void Estudiante::removerInscripcion(Inscripcion* i){
    Inscripciones.erase(i);
}

void Estudiante::eliminarNotifC(string nomC, string nomId){
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

//REALIZAR EJERCICIO

void Estudiante::actualizarAprobados(string nC,string fraseEj,string lecTema){
        bool encontreI;
        bool actualizarAprobCurso;
        set<Inscripcion*>::iterator it;
        encontreI=false;
        Inscripcion* insc;
        for(it=Inscripciones.begin();it!=Inscripciones.end() && !encontreI;++it){
            insc = *it;
            encontreI = insc->esInsc(nC);
        }
        actualizarAprobCurso = insc->revisarSiCursoTerminado(fraseEj,lecTema);
        if(actualizarAprobCurso){
            insc->setAprobado(true);
        }
}
