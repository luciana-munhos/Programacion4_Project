#include "../include/ContCurso.h"


ContCurso* ContCurso::Instancia=NULL;

ContCurso::ContCurso(){
    NombreCurso = "";
    FraseE = "";
    DescE = "";
    ultLec = 0;
}

ContCurso::~ContCurso(){
    map<string,Curso*>::iterator it = ColecCursos.begin();
    string clave;
    while (it != ColecCursos.end()){
        clave = it->first;
        Curso* c = it->second;
        ++it;
        clave = c->getNombre();
        ColecCursos.erase(clave);
        delete c;
    }
}

ICurso::~ICurso(){}

ContCurso* ContCurso::getInstance(){
    if (Instancia == NULL)
        Instancia = new ContCurso();
    
    return Instancia;
}

void ContCurso::deleteInstance(){
    if(Instancia != NULL){
        delete Instancia;
        Instancia = NULL;
    }
}

set<string> ContCurso::listarNicknamesProfesores(){
    ContUsuario* CU = ContUsuario::getInstance();
    return CU->getNicknamesProfesores();
}

void ContCurso::seleccionarProfesor(string profC){
    ProfC = profC;
}

//PRE: ContCurso tiene profesor en memoria
set<string> ContCurso::ingresarDatosCurso(string nomC, string descC, nivelDif difC){
    if(ColecCursos.find(nomC) != ColecCursos.end())
        throw invalid_argument("Ya existe un curso con ese nombre");
    ContUsuario* CU = ContUsuario::getInstance();
    NombreCurso = nomC;
    DescripcionC = descC;
    DifC = difC;

    return CU->getIdiomasProfC(ProfC);
}

void ContCurso::seleccionarIdiomaCurso(string idiomaC){
    IdiomaC = idiomaC;
}

set<string> ContCurso::listarNombresCursosHabilitados(){
    set<string> res;
    map<string,Curso*>::iterator it;
    for(it = ColecCursos.begin();it!=ColecCursos.end();++it){
        Curso* c = it->second;
        if(c->getHabilitado()){
            res.insert(c->getNombre());
        }
    }
    return res;
}

void ContCurso::vaciarMemoriaControlador(){
    NombreCurso = "";
    FraseE = "";
    DescE = "";
    DifC = Principiante;
    ProfC = "";
    IdiomaC = "";
    DescripcionC = "";
    PreviasC.clear();
    ultLec = 0;
    LeccionesC.clear();
    EjerciciosC.clear();
}

void ContCurso::seleccionarPrevias(set<string> previasC){
    PreviasC = previasC;
}

void ContCurso::ingresarDatosNuevaLeccion(string nomC, string temaL, string objL){
    NombreCurso = nomC;
    DataLeccion lec(temaL,objL);
    ultLec++;
    LeccionesC[ultLec] = lec;
}

void ContCurso::ingresarDatosEjercicio(bool esCompletar,string descE,string fraseE,list<string> sol){
    DataEjercicioCompleto ej(fraseE,descE,sol,esCompletar);
    EjerciciosC[ultLec].push_back(ej);
}



void ContCurso::darAltaCurso(){
    DataCursoCompleto DataC(NombreCurso,DescripcionC,DifC,IdiomaC,ProfC,false,PreviasC,LeccionesC,EjerciciosC);
    Curso* c = new Curso(DataC);
    
    ContUsuario* CU = ContUsuario::getInstance();

    Usuario* p = CU->asignarCursoAProf(c,ProfC);
    Profesor* prof = dynamic_cast<Profesor*>(p);
    if(prof)
        c->setProfesor(prof);
    
    c->setIdioma(CU->getIdioma(IdiomaC));
    
    set<string>::iterator it;

    for(it = PreviasC.begin();it!=PreviasC.end();++it){
        string nombrePrevia = *it;
        Curso* cp = ColecCursos[nombrePrevia];
        if(cp){
            c->addPrevia(cp);
            cp->addCursoPosterior(c);
        }
    }
    ColecCursos[NombreCurso] = c;
    
    vaciarMemoriaControlador();
}

set<string> ContCurso::obtenerCursosNoHabilitados(){
    set<string> res;
    map<string,Curso*>::iterator it;
    for(it = ColecCursos.begin();it!=ColecCursos.end();++it){
        if (!it->second->getHabilitado())
            res.insert(it->first);
    }
    return res;
}

void ContCurso::darAltaLeccion(){
    Curso* c = ColecCursos[NombreCurso];
    Leccion* l = new Leccion(c, LeccionesC[ultLec],EjerciciosC[ultLec]); //hay una única leccion en este CU
    c->addLeccion(l);
    
    vaciarMemoriaControlador();
}

list<DataLeccion> ContCurso::obtenerLeccionesOrdenadas(string nomC){
    NombreCurso = nomC;
    Curso* c = ColecCursos[nomC];
    list<DataLeccion> res;
    res = c->obtenerLeccionesOrdenadas();
    return res;
}

void ContCurso::ingresarDatosEjercicioDeLeccion(DataLeccion nomL, bool esCompletar, string descE, string fraseE, list<string> solE){
    string nC = getNombreCurso();
    Curso* c = ColecCursos[nC];
    list<Leccion*> lecs = c->getMisLecciones(); 
    list<Leccion*>::iterator it; // busco a la leccion y luego dentro busco si existe ejercicio con esa frase
    bool encontreL = false;
    Leccion * l;
    map<string,Ejercicio*> ejs;
    for (it = lecs.begin(); it != lecs.end() && !encontreL; ++it){
        l = *it;
        encontreL = l->getTema() == nomL.getTema();
    }
    if (encontreL){
        ejs = l->getMisEjercicios();
        if (ejs.find(fraseE) != ejs.end())
            throw invalid_argument("Ya existe un ejercicio con esa frase");
    }
    DataLeccion lec(nomL.getTema(),nomL.getObjetivo());
    ultLec++;
    LeccionesC[ultLec] = lec;
    ingresarDatosEjercicio(esCompletar,descE,fraseE,solE);
}

void ContCurso::darAltaEjercicio(){
    Curso* c = ColecCursos[NombreCurso];
    DataLeccion DataLec = LeccionesC[ultLec]; // unica leccion guardada
    
    Leccion* l = c->getLeccion(DataLec.getTema()); 
    DataEjercicioCompleto DataEj = *EjerciciosC[ultLec].begin(); // unico ejercicio guardado
    Ejercicio* e;
    list<string> sol = DataEj.getSolucion();
    string desc = DataEj.getDescripcion();
    string frase = DataEj.getFrase();
    
    if(DataEj.getEsCompletar()){
        e = new CompletarPalabra(desc,frase,sol);
    }
    else{
        e = new Traducir(desc,frase,sol);
    }
    e->setLeccion(l);
    l->addEjercicio(e);

    vaciarMemoriaControlador();
}

string ContCurso::getNombreCurso(){
    return NombreCurso;
}

string ContCurso::getFraseE(){
    return FraseE;
}


string ContCurso::getDescE(){
    return DescE;
}

nivelDif ContCurso::getDifC(){
    return DifC;
}

string ContCurso::getProfC(){
    return ProfC;
}

string ContCurso::getIdiomaC(){
    return IdiomaC;
}

string ContCurso::getDescripcionC(){
    return DescripcionC;
}

set<string> ContCurso::getPreviasC(){
    return PreviasC;
}

map<int,DataLeccion> ContCurso::getLeccionesC(){
    return LeccionesC;
}

map<int,list<DataEjercicioCompleto> > ContCurso::getEjerciciosC(){
    return EjerciciosC;
}

map<string,Curso*> ContCurso::getColecCursos(){
    return ColecCursos;
}

void ContCurso::removeCurso(Curso* c){
    ColecCursos.erase(c->getNombre());
}

void ContCurso::addCurso(Curso* c){
    ColecCursos[c->getNombre()] = c;
}



//OPERACIONES DE CONSULTAR ESTADISTICAS
set<string> ContCurso::getCursos(){
    set<string> res;
    map<string, Curso*>::iterator itr;

    for(itr = ColecCursos.begin(); itr != ColecCursos.end(); ++itr){
            res.insert(itr->second->getNombre());
    }
    return res;
}

//OPERACIONES DE CONSULTAR CURSO (y listarNombresCursos tambien de eliminar curso)
set<string> ContCurso::listarNombresCursos(){
    return getCursos();
}

DataCursoConsulta ContCurso::mostrarInfoCompletaCurso(string nomC){
    Curso* c = ColecCursos[nomC];

    string NomC = nomC;
    string DescC = c->getDescripcion();
    nivelDif DifC = c->getDificultad();
    string IdiomaC = c->getIdioma()->getNombre(); 
    string ProfC = c->getProfesor()->getNombre();
    bool estaHabilitado = c->getHabilitado();

    DataCursoConsulta res(NomC, DescC, DifC, IdiomaC, ProfC, estaHabilitado);

    return res;
}

//OPERACIONES DE CONSULTAR CURSO

list<DataLeccionCompleta> ContCurso::obtenerLeccionesOrdenadasCompletas(string nomC){ 
    NombreCurso = nomC;
    Curso* c = ColecCursos[nomC];
    list<DataLeccionCompleta> res; 
    res = c->obtenerLeccionesCompletasOrdenadasDelCurso();
    return res;
}

list<DataInscripcionConsulta> ContCurso::obtenerInscriptosDelCurso(string nomC){
    NombreCurso = nomC;
    Curso* c = ColecCursos[nomC];
    list<DataInscripcionConsulta> res;
    res = c->obtenerInscriptosCurso();
    return res;
}   

//OPERACION DE HABILITAR CURSO

void ContCurso::habilitarCurso(string nomC){
    map<string,Curso*>::iterator it=ColecCursos.find(nomC);
    list<Leccion*> lecciones = it->second->getMisLecciones();
    bool habilitar = true;
    if (lecciones.empty())
        throw invalid_argument("No se puede habilitar el curso porque no tiene lecciones");

    for(list<Leccion*>::iterator it = lecciones.begin(); habilitar && it != lecciones.end(); ++it)
        habilitar = (*it)->getCantEjercicios() > 0;
    

    if(!habilitar)
        throw invalid_argument("No se puede habilitar el curso porque tiene lecciones sin ejercicios");

    it->second->setHabilitado(true);
    it->second->habilitarC(nomC);
}

set<Curso*> ContCurso::obtenerCursosHabilitados(){
    set<Curso*> res;
    map<string,Curso*>::iterator it;
    for(it = ColecCursos.begin();it!=ColecCursos.end();++it){
        if (it->second->getHabilitado())
            res.insert(it->second);
    }
    return res;
}
 

Curso* ContCurso::obtenerCurso(string nomC){
    return ColecCursos[nomC];
}

//ELIMINAR CURSO
void ContCurso::eliminarCurso(string nombreC){
    Curso* c = ColecCursos[nombreC];
    //cout << "** Obtuve curso" << endl;
    c->desvincularProfDeCurso();
    //cout << "**Desvincule prof de curso" << endl;
    c->eliminarLeccionesYEjercicios();
    //cout << "**Elimino lecc y ejercicios" << endl;
    c->desvincularInscripcionesYEliminar();
    //cout << "**Desvinculo inscripciones de curso y las elimino" << endl;
    c->sacarDePrevias();
    //cout << "**Lo saco de previas" << endl;
    c->eliminarNotificaciones();
    //cout << "**Lo elimino de notificaciones" << endl;

    ColecCursos.erase(nombreC);
    //cout << "**Lo quito de ColecCursos en ContCurso" << endl;

    delete c;
    //cout << "**Y por ultimo lo borro a el" << endl;
}


//REALIZAR EJERCICIO
Ejercicio* ContCurso::conseguirEj(string fraseEj,string nC){
    Curso* c = getColecCursos()[nC]; 
    if(c != NULL){  //Me aseguro el curso exista
        Ejercicio* ej = c->getEj(fraseEj);
            if(ej != NULL){ //Me aseguro el ejercicio exista
                return ej;
            }
    }
    return NULL;
}

bool ContCurso::ejEsCompletar(string nC, string f){
    Curso* c = getColecCursos()[nC]; 
    bool esCompletar = false;
    if(c != NULL){  //Me aseguro el curso exista
        Ejercicio* ej = c->getEj(f);
        CompletarPalabra* cp;
        if(ej != NULL){ //Me aseguro que el ejercicio exista
            cp = dynamic_cast<CompletarPalabra*>(ej); // retorna null si no es completar palabra
            esCompletar = cp != NULL; // cp = NULL -> es traducir
        }
    }
    return esCompletar;
}

int ContCurso::cantRespuestas(string nC,string f,bool esCompletar){
    Curso* c = getColecCursos()[nC]; 
    int cant = 1; // traducir
    if(c != NULL && esCompletar){  //Me aseguro el curso exista
        Ejercicio* ej = c->getEj(f);
        CompletarPalabra* cp;
        if(ej != NULL){ //Me aseguro que el ejercicio exista
            cp = dynamic_cast<CompletarPalabra*>(ej);
            if (cp != NULL){ // Me aseguro que exista
                cant = cp->getSolucion().size();
            }
        }
    }
    return cant;
}