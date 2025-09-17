#include "./include/Menu.h"

int main(){
    Menu menu;
    while(menu.getOpcionActual()!= SALIR){
        menu.mostrarMenuInicial();
    }
        
    return 0;
}

