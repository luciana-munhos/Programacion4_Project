#include <string>
#include <iostream>


#include "../include/ContUsuario.h"

ContUsuario* ContUsuario::Instancia=NULL;

ContUsuario::ContUsuario(){
         Nickname="";
         NombreCurso="";
         Frase="";
         NombreUsuario="";
         Contrasenia="";
         Descripcion="";
}

ContUsuario::~ContUsuario(){
    map<string,IObserver*>::iterator itUsuarios = ColecUsuarios.begin();
    map<string,Idioma*>::iterator itIdiomas = ColecIdiomas.begin();
    string clave;
    while (itUsuarios!=ColecUsuarios.end()){
        clave = itUsuarios->first;
        IObserver* obs = itUsuarios->second;
        ++itUsuarios;
        ColecUsuarios.erase(clave);
        delete obs;
    }
    while (itIdiomas!=ColecIdiomas.end()){
        clave = itIdiomas->first;
        Idioma* id = itIdiomas->second;
        ++itIdiomas;
        ColecIdiomas.erase(clave);
        delete id;
    }
}

IUsuario::~IUsuario(){}

ContUsuario* ContUsuario::getInstance(){
    if (Instancia == NULL)
        Instancia = new ContUsuario();
    return Instancia;
}

void ContUsuario::deleteInstance(){
    if (Instancia != NULL){
        delete Instancia;
        Instancia = NULL;
    }
}

//GETTERS

string ContUsuario::getNickname(){
    return Nickname;
}

string ContUsuario::getNombreCurso(){
    return NombreCurso;
}

string ContUsuario::getFrase(){
    return Frase;
}

string ContUsuario::getNombreUsuario(){
    return NombreUsuario;
}

string ContUsuario::getContrasenia(){
    return Contrasenia;
}

string ContUsuario::getDescripcion(){
    return Descripcion;
}


//SETTERS

void ContUsuario:: setNickname(string nick){
    Nickname=nick;
}

void ContUsuario:: setNombreCurso(string nomC){
    NombreCurso=nomC;
}

void ContUsuario:: setFrase(string f){
    Frase=f;
}

void ContUsuario:: setNombreUsuario(string nomU){
    NombreUsuario=nomU;
}

void ContUsuario:: SetContrasenia(string c){
    Contrasenia=c;
}

void ContUsuario:: setDescripcion(string d){
    Descripcion=d;
}


set<string> ContUsuario::getNicknamesProfesores(){
    set<string> res;
    map<string,IObserver*>::iterator it;

    for(it = ColecUsuarios.begin();it != ColecUsuarios.end();++it){
        if(dynamic_cast<Profesor*>(it->second)){
            Profesor* pr = dynamic_cast<Profesor*>(it->second);
            res.insert(pr->getNickname());
        }
    }
    return res;
}

set<string> ContUsuario::getIdiomasProfC(string profC){
    set<string> res;
    IObserver* p = ColecUsuarios[profC];

    Profesor* pr = dynamic_cast<Profesor*>(p);
    if (pr)
        res = pr->getIdiomas();
    
    return res;
}

Profesor* ContUsuario::asignarCursoAProf(Curso* c, string profC){
    IObserver* p = ColecUsuarios[profC];
    Profesor* prof = dynamic_cast<Profesor*>(p);
    if(prof)
        prof->addCurso(c);
    return prof;
}

Idioma* ContUsuario::getIdioma(string id){
    return ColecIdiomas[id];
}

//Precondicion:El parametro contra debe tener al menos 6 caracteres
void ContUsuario::ingresoDatosComunes(string nick,string contra,string nom,string desc){
    setNickname(nick);
    SetContrasenia(contra);
    setDescripcion(desc);
    setNombreUsuario(nom);
}

bool ContUsuario::altaEstudiante(string pais,int dia, int mes, int anio){
    string nick = getNickname();
    if(ColecUsuarios.find(nick) == ColecUsuarios.end()){ 
        string nom = getNombreUsuario();
        string des = getDescripcion();
        string contra = getContrasenia();
        IObserver* e = new Estudiante(nick,contra,nom,des,pais,dia,mes,anio);
        ColecUsuarios[nick] = e;
        vaciarMemoriaControlador();
        return true;
    }
    vaciarMemoriaControlador();
    return false;
}

set<string> ContUsuario::listarNicknamesUsuario(){
    set<string> res;
    map<string,IObserver*>::iterator it;
    for(it = ColecUsuarios.begin();it != ColecUsuarios.end(); ++it){
        res.insert(it->first);
    }
    return res;
}
DataUsuario* ContUsuario::obtenerDataUsuario(string n){
    IObserver* u = ColecUsuarios[n];
    DataUsuario* res;
    if(dynamic_cast<Estudiante*>(u)){
        Estudiante* es = dynamic_cast<Estudiante*>(u);
        res = new DataEstudiante(es->getNombre(),es->getDescripcion(),es->getPais(),es->getFechaNacimiento());
    }else if(dynamic_cast<Profesor*>(u)){
        Profesor* prof = dynamic_cast<Profesor*>(u);
        res = new DataProfesor(prof->getNombre(),prof->getDescripcion(),prof->getInstituto(),prof->getIdiomas());
    }
    return res;     
}

void ContUsuario::destruirDataUsuario(DataUsuario* d){
    delete d;
}

set<string> ContUsuario::listarIdiomas(){
    set<string> res;
    map<string,Idioma*>::iterator it;
    for(it = ColecIdiomas.begin(); it != ColecIdiomas.end(); ++it){
        res.insert(it->first); //Agrego la clave con it first
    }
    return res;
}
//Precondicion, el set de string tienen q ser idiomas validos
bool ContUsuario::altaProfesor(string institutoP,set<string> nombreI){
    string nick = getNickname();
    if(ColecUsuarios.find(nick) == ColecUsuarios.end()){
        string contra = getContrasenia();
        string des = getDescripcion();
        string nom = getNombreUsuario();
        //Pasar set de string a set de Idioma*, chequeando sean validos, precond del constructor
        set<Idioma*> idiomasA;

        set<string>::iterator it;
        for(it = nombreI.begin();it != nombreI.end();++it){
            map<string,Idioma*>::iterator itI = ColecIdiomas.find(*it);
            if(itI != ColecIdiomas.end()){
                //existe el idioma debemos agregarlo
                idiomasA.insert(itI->second);
            }else{
                //reportar Error
                return false;
            }
        }
        IObserver* p = new Profesor(nick,contra,nom,des,institutoP,idiomasA);
        ColecUsuarios[nick] = p;
        vaciarMemoriaControlador();
        return true;
    }
    vaciarMemoriaControlador();
    return false;
}

bool ContUsuario::altaIdioma(string i){
    if(ColecIdiomas.find(i) == ColecIdiomas.end()){
        //Agregar idioma
        Idioma* idi = new Idioma(i);
        ColecIdiomas[i] = idi;
        vaciarMemoriaControlador();
        return true;
    }
    vaciarMemoriaControlador();
    return false;
}

//OPERACIONES DE CONSULTAR ESTADISTICAS 

//pre: existe el estudiante con este nombre
string ContUsuario::getNickFromNameEstudiante(string nombre){
    map<string, IObserver*>::iterator itr;
    for (itr = ColecUsuarios.begin(); itr != ColecUsuarios.end(); ++itr) {
        IObserver* observer = itr->second;
        Estudiante* estudiante = dynamic_cast<Estudiante*>(observer);
        if (estudiante && estudiante->getNombre() == nombre) {
            return itr->first;
        }
    }
    return "";  
}

//pre: existe el profesor con este nombre
string ContUsuario::getNickFromNameProfesor(string nombre){
    map<string, IObserver*>::iterator itr;
    for (itr = ColecUsuarios.begin(); itr != ColecUsuarios.end(); ++itr) {
        IObserver* observer = itr->second;
        Profesor* profesor = dynamic_cast<Profesor*>(observer);
        if (profesor && profesor->getNombre() == nombre) {
            return itr->first; 
        }
    }
    return "";  
}

set <string> ContUsuario::listarNombresEstudiantes(){
    set<string> res;
    map<string, IObserver*>::iterator itr;

    for(itr = ColecUsuarios.begin(); itr != ColecUsuarios.end(); ++itr){
        if(dynamic_cast<Estudiante*>(itr->second)){
            Estudiante* es = dynamic_cast<Estudiante*>(itr->second);
            res.insert(es->getNombre());
        }
    }
    return res;
}


list<string> ContUsuario::listarCursosEst(string nomEst){
    list<string> res;
    ContUsuario* contUsuario = ContUsuario::getInstance();
    string nick = contUsuario->getNickFromNameEstudiante(nomEst);
    IObserver* e = ColecUsuarios[nick];
    Estudiante* est = dynamic_cast<Estudiante*>(e);
    res = est->listCursosEst();
    

    return res;
}

list<float> ContUsuario::porcentajeAvanceCursosEst(string nomEst){ 
    list<float> res;
    ContUsuario* contUsuario = ContUsuario::getInstance();
    string nick = contUsuario->getNickFromNameEstudiante(nomEst);
    IObserver* e = ColecUsuarios[nick]; 
    
    Estudiante* est = dynamic_cast<Estudiante*>(e);
    res = est->getPorcentajeAvanceInscripciones(); 
    
    return res;
}

set<string> ContUsuario::listarNombresProfesores(){
    set<string> res;
    map<string, IObserver*>::iterator itr;

    for(itr = ColecUsuarios.begin(); itr != ColecUsuarios.end(); ++itr){
        if(dynamic_cast<Profesor*>(itr->second)){
            Profesor* pr = dynamic_cast<Profesor*>(itr->second);
            res.insert(pr->getNombre());
        }
    }
    return res;
}

list<string> ContUsuario::listarCursosProf(string nomProf){
    list<string> res;
    ContUsuario* contUsuario = ContUsuario::getInstance();
    string nick = contUsuario->getNickFromNameProfesor(nomProf);
    IObserver* p = ColecUsuarios[nick];
    Profesor* prof = dynamic_cast<Profesor*>(p);
    res = prof->listCursosProf();
    

    return res;
}

set<string> ContUsuario::listarNicknamesEstudiantes(){
    map<string,IObserver*>::iterator it;
    set<string> res;
    for(it = ColecUsuarios.begin();it != ColecUsuarios.end(); ++it){
        if(dynamic_cast<Estudiante*>(it->second)){
            res.insert(it->first);
        }
    }
    return res;
}

list<float> ContUsuario::porcentajeAvanceCursosProf(string nomProf){ 
    list<float> res;
    ContUsuario* contUsuario = ContUsuario::getInstance();
    string nick = contUsuario->getNickFromNameProfesor(nomProf);
    IObserver* p = ColecUsuarios[nick]; 
    Profesor* prof = dynamic_cast<Profesor*>(p);

    res = prof->getPorcentajeAvanceCurso(); 
    return res; 
}

map<string,IObserver*> ContUsuario::getColecUsuarios(){
    return ColecUsuarios;
}

set<string> ContUsuario::listarNombresCursos(){
    ContCurso* CC = ContCurso::getInstance();
    return CC->listarNombresCursos();
}

DataCursoConsulta ContUsuario::mostrarInfoCompletaCurso(string nomC){
    ContCurso* CC = ContCurso::getInstance();

    map<string,Curso*> cursos = CC->getColecCursos();
    map<string, Curso*>::iterator itr = cursos.find(nomC);
    Curso* curso = itr->second;
    
    //DataCursoConsulta que debo devolver
    string NomC = nomC;
    string DescC = curso->getDescripcion();
    nivelDif DifC = curso->getDificultad();
    string IdiomaC = curso->getIdioma()->getNombre(); 
    string ProfC = curso->getProfesor()->getNombre();
    bool estaHabilitado = curso->getHabilitado();

    DataCursoConsulta res = DataCursoConsulta(NomC, DescC, DifC, IdiomaC, ProfC, estaHabilitado);

    return res;
}


float ContUsuario::porcentajeAvanceCurso(string nomC){
    float res;
    ContCurso* CC = ContCurso::getInstance();
    map<string,Curso*> cursos = CC->getColecCursos();
    map<string, Curso*>::iterator itr = cursos.find(nomC);
    Curso* curso = itr->second;
    res = curso->getPorcentajeAvanceDeEsteCurso();
    return res;
}

// PRE: el Nickname del estudiante DEBE estar en memoria
void ContUsuario::realizarInscripcion(string nombreCursoElegido){
    
    string nick = getNickname();
    IObserver* e = ColecUsuarios[nick];
    Estudiante* estu = dynamic_cast<Estudiante*>(e);

    ContCurso* CC = ContCurso::getInstance();
    Curso* c = CC->obtenerCurso(nombreCursoElegido);

    estu->realizarInscripcion(c);
    vaciarMemoriaControlador();
}

void ContUsuario::vaciarMemoriaControlador(){
    Nickname = "";
    NombreCurso = "";
    NombreUsuario = "";
    Frase = "";
    Contrasenia = "";
    Descripcion = "";
}

set<DataCursoyCants> ContUsuario::mostrarCursosHabilitadosAInscribirse(string nick){
    Nickname = nick;
    set<DataCursoyCants> res;
    
    ContCurso* contCurso = ContCurso::getInstance();

    IObserver* obs = getUsuario(nick);
    Usuario* u = dynamic_cast<Usuario*>(obs);

    set<Curso*> cursosHab = contCurso->obtenerCursosHabilitados();

    Estudiante* e = dynamic_cast<Estudiante*>(u);
    set<Inscripcion*> inscripciones = e->getInscripciones();

    if(e){
        for(set<Curso*>::iterator it = cursosHab.begin(); it != cursosHab.end(); ++it){
            Curso* c = *it;

            set<Inscripcion*>::iterator itIns = inscripciones.begin();
            while(itIns != inscripciones.end()){ //recorro las inscripciones del estudiante
                Inscripcion* i = *itIns;       
                if(i->getMiCurso() == c)      //si el curso de la inscripcion es el mismo que el curso que estoy recorriendo
                    break;                     
                
                ++itIns; //si no es el mismo curso, avanzo al siguiente
            }
            if(itIns == inscripciones.end()){ //no encontre el curso entre las inscripciones
                
                bool previasAprobadas = true;
                map<string,Curso*> previas = c->getPrevias();
                map<string,Curso*>::iterator itPrev = previas.begin();
    
                while(previasAprobadas && itPrev != previas.end()){
                    previasAprobadas = false;
                    Curso* previa = itPrev->second; 
                    set<Inscripcion*>::iterator itInsPrev = inscripciones.begin(); //iterador de las inscripciones del estudiante
                    
                    while(itInsPrev != inscripciones.end()){ //recorro las inscripciones del estudiante
                        Inscripcion* i = *itInsPrev;        //la inscripcion
                        if(i->getMiCurso() == previa){      //si el curso de la inscripcion es el previo
                            if(i->getAprobado()){          //si esta aprobado
                                previasAprobadas = true;   //puedo inscribirme
                            }
                            break;
                        }
                        ++itInsPrev; //paso a la siguiente inscripcion
                    }
                     
                    if(!previasAprobadas) //si no estan aprobadas las previas, no puedo inscribirme
                        break;
                    ++itPrev; //paso a la siguiente previa
                }
                if(previasAprobadas){ //si estan aprobadas las previas, puedo inscribirme
                    DataCursoyCants d = DataCursoyCants(c->getNombre(), c->getDescripcion(),c->getDificultad(), c->getCantLecciones(),c->getCantEjercicios());
                    res.insert(d);
                }
            }
        }
    }
    return res;
}

IObserver* ContUsuario::getUsuario(string nick){
    return ColecUsuarios[nick];
}

//OPERACIONES DE SUSCRIBIRSE

void ContUsuario::cargarNicknames(string Nickname){
    setNickname(Nickname);
}

set<string> ContUsuario::listarIdiomasNoSuscrito(){
    string Nickname=getNickname();
    set<string> nomId;
    map<string,Idioma*>::iterator it;
    bool noEsta;
    for(it=ColecIdiomas.begin();it!=ColecIdiomas.end();it++){
        noEsta = it->second->noEstaSuscrito(Nickname);
        if (noEsta){
            nomId.insert(it->second->getNombre());
        }
    }
    return nomId;
}

void ContUsuario::cargarIdiomasSuscripcion(set<string> idiomas){
    map<string,IObserver*>::iterator it;
    it=ColecUsuarios.find(Nickname);
    set<string>::iterator iter;
    map<string,Idioma*>::iterator iterar;

    for(iter=idiomas.begin();iter!=idiomas.end();iter++){
        iterar=ColecIdiomas.find((*iter));
        iterar->second->agregarSuscriptor(it->first,it->second);
        }

}


//CONSULTAR NOTIFICACIONES

list<DataNotif> ContUsuario::listarNotificacionesRecibidas(){
    map<string,IObserver*>::iterator it;
    it=ColecUsuarios.find(Nickname);
    Usuario* usuario = dynamic_cast<Usuario*>(it->second);
    list<DataNotif> res = usuario->listarNotificacionesRecibidasU();

    return res;
}

void ContUsuario::eliminarNotificaciones(){
    map<string,IObserver*>::iterator it;
    it=ColecUsuarios.find(Nickname);
    Usuario* usuario = dynamic_cast<Usuario*>(it->second);
    usuario->eliminarNotif();
}


//ELIMINAR SUSCRIPCION

set<string> ContUsuario::listarIdiomasSuscritos(){
    string Nickname=getNickname();
    set<string> nomId;
    map<string,Idioma*>::iterator it;
    bool noEsta;
    for(it=ColecIdiomas.begin();it!=ColecIdiomas.end();it++){
        noEsta = it->second->noEstaSuscrito(Nickname);
        if (noEsta==false){
            nomId.insert(it->second->getNombre());
        }
    }
    return nomId;
}


void ContUsuario:: eliminarSuscripcionIdioma(string nomI){
        map<string,Idioma*>::iterator it;
        it=ColecIdiomas.find(nomI);
        it->second->eliminarSuscriptor(Nickname);    
}

//REALIZAR EJERCICIO
list<DataCurso> ContUsuario::mostrarCursosNoAprobados(string nicknameE){
    list<DataCurso> res;
    Nickname = nicknameE;
    IObserver* obs = ColecUsuarios[nicknameE];

    Estudiante* e = dynamic_cast<Estudiante*>(obs);

    try{
        res = e->getCursosNoAprobados();
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    return res;
}

set<DataEjercicio> ContUsuario::mostrarEjsNoAprobadosUltLec(string nombreCurso){
    NombreCurso = nombreCurso;
    set<DataEjercicio> res;
    IObserver* obs = ColecUsuarios[Nickname];

    Estudiante* e = dynamic_cast<Estudiante*>(obs);

    try{
        res = e->getEjsNoAprobUltLec(nombreCurso);
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }
    return res;
}

string ContUsuario::presentarProblema(DataEjercicio dataEj){
    Frase = dataEj.getFrase();
    return Frase;
}

bool ContUsuario::resolveryCorregir(list<string> resp){
    bool respBien = false;
    string lecTema;
    ContCurso* contC = ContCurso::getInstance();
    string f = getFrase();
    string nC = getNombreCurso();
    Ejercicio* ej = contC->conseguirEj(f,nC);
    if(ej != NULL){
        respBien = ej->corregirResp(resp);
        if(respBien){
            lecTema = ej->getTemaLeccion();
            IObserver* e = getColecUsuarios()[getNickname()];
            Estudiante* estu = dynamic_cast<Estudiante*>(e);
            string noC = getNombreCurso();
            string fr = getFrase();
            try{
                estu->actualizarAprobados(noC,fr,lecTema);
            }
            catch(const exception& e){
                cerr << e.what() << '\n';
            } 
        }
    }
    vaciarMemoriaControlador();
    return respBien;
}