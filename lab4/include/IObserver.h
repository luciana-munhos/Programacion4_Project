#ifndef IOBSERVER
#define IOBSERVER

#include <stdio.h>
#include <iostream>
#include <set>

#include "./Datatypes.h"

using namespace std;


class IObserver{    
   public:                    
        virtual void eliminarNotifC(string, string)=0 ; 
        virtual void notificarUsuario(string,string)=0;
        virtual ~IObserver() = 0;
};




#endif