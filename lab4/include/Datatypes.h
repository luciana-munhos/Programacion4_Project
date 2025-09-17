#ifndef DATATYPE
#define DATATYPE

#include <iostream>
#include <set>
#include <map>
#include <list>
using namespace std;

enum nivelDif{
    Principiante, Intermedio, Avanzado
};

class Date{
    private:
        int Dia;
        int Mes;
        int Anio;
    public:
        Date();
        Date(int,int,int);
        int getDia();
        int getMes();
        int getAnio();
};

class DataEjercicio{
    private: 
        string Frase;
        string Descripcion;
    public:
        DataEjercicio(string,string);
        string getFrase();
        string getDescripcion();
};

class DataLeccion{
    private:
        string Tema;
        string Objetivo;
    public:
        DataLeccion();
        DataLeccion(string t,string o);
        
        string getTema();
        string getObjetivo();
};

class DataNotif{
    private:
        string NombreIdioma;
        string NombreCurso;
    public:
        DataNotif(string, string);
        string getNombreIdioma();
        string getNombreCurso();
};

class DataCurso{
    private:
        string Nombre;
        string Descripcion;
        nivelDif Dificultad;
    public:
        DataCurso(string,string,nivelDif);
        string getNombre();
        string getDescripcion();
        nivelDif getNivelDif();
};

class DataEjercicioCompleto{
    private:
        string Frase;
        string Descripcion;
        list<string> Solucion;
        bool EsCompletar;
    public:
        DataEjercicioCompleto(string,string,list<string>,bool);
        string getFrase();
        string getDescripcion();
        list<string> getSolucion();
        bool getEsCompletar();
};

class DataLeccionCompleta{
    private:
        string Tema;
        string Objetivo;
        set<DataEjercicioCompleto> Ejercicios;
    
    public:
        DataLeccionCompleta(){};
        DataLeccionCompleta(string t,string ob);
        DataLeccionCompleta(string t,string ob,set<DataEjercicioCompleto>);
        string getTema();
        string getObjetivo();
        set<DataEjercicioCompleto> getEjercicios();

        void addEjercicio(DataEjercicioCompleto&);
};


class DataInscripcionConsulta{
    private:
        string nombreEst; //nombre del estudiante de la inscripcion
        Date fechaInsc;//y su fecha de insc

    public:
        DataInscripcionConsulta();
        DataInscripcionConsulta(string nomE, Date fecha);
        string getNombreEst();
        Date getFechaInsc();

};

class DataCursoConsulta{ 
    private:
        string NomC;
        string DescC;
        nivelDif DifC;
        string IdiomaC;
        string ProfC;
        bool estaHabilitado;
        set<DataLeccion> leccionesCurso;
    public:
        DataCursoConsulta();
        DataCursoConsulta(string, string, nivelDif, string, string, bool);

        string getNomC();
        string getDescC();
        nivelDif getDifC();
        string getIdiomaC();
        string getProfC();
        bool getEstaHabilitado();
        set<DataLeccionCompleta> getLecciones(); //devuelve las lecciones con sus ejs

};


class DataCursoCompleto{
    private:
        string NomC;
        string DescC;
        nivelDif DifC;
        string IdiomaC;
        string ProfC;
        bool estaHabilitado;
        set<string> PreviasC;
        map<int,DataLeccion> Lecciones; 
        map<int,list<DataEjercicioCompleto>> Ejercicios;
    public:
        DataCursoCompleto(string,string,nivelDif,string,string,bool,set<string>,map<int,DataLeccion>,map<int,list<DataEjercicioCompleto>>);
        string getNomC();
        string getDescC();
        nivelDif getDifC();
        string getIdiomaC();
        string getProfC();
        bool getEstaHabilitado();
        set<string> getPreviasC();
        map<int,DataLeccion> getLecciones();
        list<DataEjercicioCompleto> getEjercicios(int);

        void setNomC(string&);
        void setDescC(string&);
        void setDifC(nivelDif&);
        void setIdiomaC(string&);
        void setProfC(string&);
        void setEstaHabilitado(bool&);
        void setPreviasC(set<string>&);
        void addPreviaC(string&);
        void removePreviaC(string&);

};

class DataUsuario{
    private:
        string nombre;
        string descripcion;
    public:
        virtual ~DataUsuario()=0;
        string getNombre(){
            return nombre;
        }
        string getDescripcion(){
            return descripcion;
        }
        void setNombre(string n){
            nombre = n;
        }
        void setDescripcion(string d){
            descripcion = d;
        }
};


class DataEstudiante:public DataUsuario{
    private:
        string pais;
        Date fechaNac;
    public:
        ~DataEstudiante(){};
        DataEstudiante(string n,string d,string p,Date fn);
        string getPais(){
            return pais;
        }
        Date getFechaNac(){
            return fechaNac;
        }
};
class DataProfesor:public DataUsuario{
    private:
        string Instituto;
        set<string> MisIdiomas;
    public:
        ~DataProfesor(){};
        DataProfesor(string n,string d,string i,set<string> idi);
        string getInstituto(){
            return Instituto;
        }
        set<string> getMisIdiomas(){
            return MisIdiomas;
        }
        
};

class DataCursoyCants{
    private:
        string Nombre;
        string Descripcion;
        nivelDif Dificultad;
        int cantLecciones;
        int cantEjercicios;
    public:
        DataCursoyCants();
        DataCursoyCants(string nom,string desc,nivelDif dif, int cantL, int cantE);

        string getNombre();
        string getDescripcion();
        nivelDif getDificultad();
        int getCantLecciones();
        int getCantEjercicios();
};


bool operator<(DataLeccion lhs, DataLeccion rhs);
bool operator==(DataLeccion lhs, DataLeccion rhs);

bool operator<(DataEjercicio ej1, DataEjercicio ej2);
bool operator==(DataEjercicio ej1, DataEjercicio ej2);

bool operator<(DataCursoyCants c1, DataCursoyCants c2);

bool operator<(DataInscripcionConsulta dic1, DataInscripcionConsulta dic2);
bool operator==(DataInscripcionConsulta dic1, DataInscripcionConsulta dic2); 

bool operator<(DataEjercicioCompleto ej1, DataEjercicioCompleto ej2);
bool operator==(DataEjercicioCompleto ej1, DataEjercicioCompleto ej2);


bool operator<(DataLeccionCompleta lecc1, DataLeccionCompleta lecc2);
bool operator==(DataLeccionCompleta lecc1, DataLeccionCompleta lecc2);

#endif 
