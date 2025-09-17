#ifndef MENU
#define MENU

#define ALTA_USUARIO 1
#define CONSULTA_USUARIO 2
#define ALTA_IDIOMA 3
#define CONSULTA_IDIOMA 4
#define ALTA_CURSO 5
#define AGREGAR_LECCION 6
#define AGREGAR_EJERCICIO 7
#define HABILITAR_CURSO 8
#define ELIMINAR_CURSO 9
#define CONSULTAR_CURSO 10
#define INSCRIBIRSE_CURSO 11
#define REALIZAR_EJERCICIO 12
#define CONSULTAR_ESTADISTICAS 13 
#define SUSCRIBIRSE_NOTIF 14
#define CONSULTA_NOTIF 15
#define ELIMINAR_SUSC 16
#define SALIR 17

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <map>

#include <chrono>
#include <thread>
#include <limits> //Para descartar saltos de linea
#include <fstream>
#include <sstream>
#include "./Fabrica.h"

using namespace std;

class Menu {
    private:
        bool cargueDatos;
        int opcionActual;  //Para saber por cual voy recorriendo
        void mostrarOpciones(string,map<int,string>);
        bool opcionSeleccionada(int);
        char getch();
        void procesarOpcion();

        void cargarDatos();
        void CU_altaUsuario();
        void CU_consultaUsuario();
        void CU_altaIdioma();
        void CU_consultaIdioma();
        void CU_altaCurso();
        void CU_agregarLeccion();
        void CU_agregarEjercicio();
        void CU_habilitarCurso();
        void CU_eliminarCurso();
        void CU_consultarCurso();
        void CU_inscribirseCurso();
        void CU_realizarEjercicio();
        void CU_consultarEstadisticas();
        void CU_suscribirseNotif();
        void CU_consultarNotif();
        void CU_eliminarSuscripcion();
    public:
        Menu();
        ~Menu();
        bool getCargueDatos();

        void setCargueDatos(bool);

        void elegirOpcion(string,map<int,string>);
        void mostrarMenuInicial();
        void setOpcionActual(int);
        int getOpcionActual();
};

ostream& operator<<(ostream&, const set<string>& );
ostream& operator<<(ostream&,DataUsuario*&);
ostream& operator<<(ostream&, set<DataLeccion>&);
ostream& operator<<(ostream& os,list<DataLeccion>& d);
ostream& operator<<(ostream& , DataCursoConsulta&);

ostream& operator<<(ostream& os, DataCursoyCants & dc);
ostream& operator<<(ostream& os, set<DataCursoyCants> & dc);
ostream& operator<<(ostream& os, list<DataNotif> & dc);
ostream& operator<<(ostream& os, DataCurso & dc);
ostream& operator<<(ostream& os, list<DataCurso> & dc);
ostream& operator<<(ostream& os, DataEjercicio & ej);
ostream& operator<<(ostream& os, set<DataEjercicio> & ej);

ostream& operator<<(ostream& os, list<string>& ls);

ostream& operator<<(ostream& os, list<DataLeccionCompleta>& dlc); 
ostream& operator<<(ostream& os, list<DataInscripcionConsulta>& dic); 
ostream& operator<<(ostream& os, list<float>& listF);


#endif













 









































































































