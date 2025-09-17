#ifndef FABRICA
#define FABRICA

#include "./IUsuario.h"
#include "./ICurso.h"
#include "./ContUsuario.h"
#include "./ContCurso.h"

class Fabrica{
    private:
        static IUsuario* intUsuario;
        static ICurso* intCurso;
    public:
        static IUsuario* getIUsuario();
        static ICurso* getICurso();

        static void deleteIUsuario();   
        static void deleteICurso();
};


#endif