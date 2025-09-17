#ifndef INSCRIPCION
#define INSCRIPCION

#include "./Curso.h" 
#include "./Estudiante.h"
#include "./InscriptoLeccion.h"

class Curso;
class Estudiante;
class InscriptoLeccion;

class Inscripcion{
    private:
        Date FechaInsc;
        bool Aprobado;

        Curso* MiCurso;
        Estudiante* MiEstudiante;
        set<InscriptoLeccion*> MisInscriptoLecciones; 

    public:
        Inscripcion();
        ~Inscripcion();

        Date getFechaInsc();
        bool getAprobado();
        Curso* getMiCurso();
        Estudiante* getMiEstudiante();
        set<InscriptoLeccion*> getMisInscriptoLecciones();

        set<DataEjercicio> getEjsNoAprobUltLec();
        
        string getNombreCurso();

        void setFechaInsc(Date);
        void setAprobado(bool);
        void setMiCurso(Curso*);
        void setMiEstudiante(Estudiante*);
        
        void removerInscripcionDeEst();
        void destruirInscriptoLeccionYProgresos();
        bool esInsc(string);
        bool revisarSiCursoTerminado(string,string);

        // Para manejar MisInscriptoLecciones
        void addInscriptoLeccion(InscriptoLeccion*);
        void removeInscriptoLeccion(InscriptoLeccion*);

        // Para consultar estadisticas
        float getPorcentajeAvanceInscripcion();
};

#endif