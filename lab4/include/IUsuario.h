#ifndef IUSUARIO
#define IUSUARIO

#include <stdio.h>
#include <iostream>
#include <set>

#include "./Datatypes.h"


using namespace std;

class IUsuario{
    public:
        virtual ~IUsuario() = 0;
        
        
        virtual bool altaIdioma(string)=0;
        virtual list<DataCurso> mostrarCursosNoAprobados(string)=0;
        virtual set<DataEjercicio> mostrarEjsNoAprobadosUltLec(string)=0;
        virtual string presentarProblema(DataEjercicio)=0;
        virtual bool resolveryCorregir(list<string>)=0;
        virtual void ingresoDatosComunes(string,string,string,string)=0;
        virtual bool altaEstudiante(string,int,int,int)=0;
        virtual set<string> listarIdiomas()=0;
        virtual bool altaProfesor(string,set<string>)=0;
        virtual set<string> listarNicknamesUsuario()=0;
        virtual set<string> listarNicknamesEstudiantes()=0;
        virtual DataUsuario* obtenerDataUsuario(string)=0;
        virtual void destruirDataUsuario(DataUsuario*)=0;
        virtual set<string> listarNombresEstudiantes()=0;
        virtual list<string> listarCursosEst(string)=0; 
        virtual list<float> porcentajeAvanceCursosEst(string)=0; 
        virtual set<string> listarNombresProfesores()=0;
        virtual list<string> listarCursosProf(string)=0; 
        virtual list<float> porcentajeAvanceCursosProf(string)=0;
        virtual set<string> listarNombresCursos()=0;
        virtual DataCursoConsulta mostrarInfoCompletaCurso(string)=0; 
        virtual float porcentajeAvanceCurso(string)=0; 
        virtual void cargarNicknames(string)=0;
        virtual set<string> listarIdiomasNoSuscrito()=0;
        virtual void cargarIdiomasSuscripcion(set<string>)=0;
        virtual list<DataNotif> listarNotificacionesRecibidas()=0;
        virtual void eliminarNotificaciones()=0;
        virtual set<string> listarIdiomasSuscritos()=0;                                                     
        virtual void eliminarSuscripcionIdioma(string)=0;       //24 operacion y 1 destructor
        virtual void realizarInscripcion(string)=0;

        virtual set<DataCursoyCants> mostrarCursosHabilitadosAInscribirse(string nick) = 0; 

        

};


#endif