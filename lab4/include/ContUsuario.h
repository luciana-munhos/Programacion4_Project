#ifndef CONTUSUARIO
#define CONTUSUARIO

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>

#include "./ContCurso.h" 
#include "./IUsuario.h"
#include "./Usuario.h"
#include "./Idioma.h"

using namespace std;

class ContUsuario : public IUsuario{
    private:
        static ContUsuario* Instancia;
        ContUsuario();
        ~ContUsuario();
        string Nickname;
        string NombreCurso;
        string Frase;
        string NombreUsuario;
        string Contrasenia;
        string Descripcion;
        map<string,IObserver*> ColecUsuarios;
        map<string,Idioma*> ColecIdiomas;

    public:
        static ContUsuario * getInstance();
        static void deleteInstance();
        

        string getNickname();
        string getNombreCurso();
        string getFrase();
        string getNombreUsuario();
        string getContrasenia();
        string getDescripcion();
        map<string,IObserver*> getColecUsuarios();

        void setNickname(string);
        void setNombreCurso(string);
        void setFrase(string);
        void setNombreUsuario(string);
        void SetContrasenia(string);
        void setDescripcion(string);

        bool altaIdioma(string);
        list<DataCurso> mostrarCursosNoAprobados(string);
        set<DataEjercicio> mostrarEjsNoAprobadosUltLec(string);
        string presentarProblema(DataEjercicio);
        bool resolveryCorregir(list<string>);
        void ingresoDatosComunes(string,string,string,string);
        bool altaEstudiante(string,int, int ,int);
        set<string> listarIdiomas();
        bool altaProfesor(string,set<string>);
        set<string> listarNicknamesUsuario();
        set<string> listarNicknamesEstudiantes();
        DataUsuario* obtenerDataUsuario(string);
        void destruirDataUsuario(DataUsuario*);
        set<string> listarNombresEstudiantes();
        list<string> listarCursosEst(string); 
        list<float> porcentajeAvanceCursosEst(string); 
        set<string> listarNombresProfesores();
        list<string> listarCursosProf(string); 
        list<float> porcentajeAvanceCursosProf(string); 
        set<string> listarNombresCursos();
        DataCursoConsulta mostrarInfoCompletaCurso(string);
        float porcentajeAvanceCurso(string); 
        void cargarNicknames(string);
        set<string> listarIdiomasNoSuscrito();
        void cargarIdiomasSuscripcion(set<string>);

        list<DataNotif> listarNotificacionesRecibidas();
        void eliminarNotificaciones();
        set<string> listarIdiomasSuscritos();                                                     
        void eliminarSuscripcionIdioma(string);         
        set<string> getNicknamesProfesores();
        set<string> getIdiomasProfC(string);
        Profesor* asignarCursoAProf(Curso*,string);
        Idioma* getIdioma(string);
        IObserver* getUsuario(string);
        void realizarInscripcion(string);

        set<DataCursoyCants> mostrarCursosHabilitadosAInscribirse(string nick);

        void vaciarMemoriaControlador();

        string getNickFromNameEstudiante(string);
        string getNickFromNameProfesor(string);
};



#endif