#ifndef CONTCURSO
#define CONTCURSO

#include "./ICurso.h"
#include "./Curso.h"
#include "./ContUsuario.h"
#include "./CompletarPalabra.h"
#include "./Traducir.h"

#include <list>

class ContCurso : public ICurso{
    private:
        static ContCurso* Instancia;
        ContCurso();
        ~ContCurso();
        
        string NombreCurso;
        string FraseE;
        string DescE;
        nivelDif DifC;
        string ProfC;
        string IdiomaC;
        string DescripcionC;
        set<string> PreviasC;
        int ultLec;
        map<int,DataLeccion> LeccionesC;
        map<int,list<DataEjercicioCompleto>> EjerciciosC;

        map<string,Curso*> ColecCursos;

    public:
        static ContCurso* getInstance();
        static void deleteInstance();

        string getNombreCurso();
        string getFraseE();
        string getDescE();
        nivelDif getDifC();
        string getProfC();
        string getIdiomaC();
        string getDescripcionC();
        set<string> getPreviasC();
        int getUltLec();
        map<int,DataLeccion> getLeccionesC();
        map<int,list<DataEjercicioCompleto>> getEjerciciosC();
        map<string,Curso*> getColecCursos();

        

        void addCurso(Curso*);
        void removeCurso(Curso*);

        void vaciarMemoriaControlador();

        set<string> listarNicknamesProfesores();
        void seleccionarProfesor(string);
        set<string> ingresarDatosCurso(string, string, nivelDif);
        void seleccionarIdiomaCurso(string);
        set<string> listarNombresCursosHabilitados();
        void seleccionarPrevias(set<string>);
        void ingresarDatosNuevaLeccion(string, string, string);
        void ingresarDatosEjercicio(bool,string,string,list<string>);
        void darAltaCurso();
        
        void eliminarCurso(string);

        set<string> listarNombresCursos(); 
        DataCursoConsulta mostrarInfoCompletaCurso(string);
        
        list<DataLeccionCompleta> obtenerLeccionesOrdenadasCompletas(string); 
        list<DataInscripcionConsulta> obtenerInscriptosDelCurso(string);



        set<string> obtenerCursosNoHabilitados();
        void darAltaLeccion();

        list<DataLeccion> obtenerLeccionesOrdenadas(string);
        void ingresarDatosEjercicioDeLeccion(DataLeccion,bool,string,string,list<string>);
        void darAltaEjercicio();

        set<string> getCursos();
        Ejercicio* conseguirEj(string,string);
        bool ejEsCompletar(string,string);
        int cantRespuestas(string,string,bool);

        void habilitarCurso(string);
        set<Curso*> obtenerCursosHabilitados();
        Curso* obtenerCurso(string);

        
};

#endif