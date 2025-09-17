#include "../include/Menu.h"
#include <vector>
using namespace std;

Menu::Menu(){
    cargueDatos = false;
    opcionActual = 1;
}

Menu::~Menu(){}

map<int,string> conseguirOpciones(set<string> l){
    map<int,string> res;
    int i = 1;
    for(set<string>::iterator it = l.begin(); it != l.end(); ++it){
        res[i] = *it;
        i++;
    }
    return res;
}

void Menu::setOpcionActual(int oa){
    opcionActual = oa;
}
int Menu::getOpcionActual(){
    return opcionActual;
}

void Menu::mostrarMenuInicial(){
    map<int,string> ini;

    ini[ALTA_USUARIO] = "Alta de Usuario";
    ini[CONSULTA_USUARIO] = "Consulta de Usuario";
    ini[ALTA_IDIOMA] = "Alta de Idioma";
    ini[CONSULTA_IDIOMA] = "Consulta de Idioma";
    ini[ALTA_CURSO] = "Alta de Curso";
    ini[AGREGAR_LECCION] = "Agregar Leccion";
    ini[AGREGAR_EJERCICIO] = "Agregar Ejercicio";
    ini[HABILITAR_CURSO] = "Habilitar Curso";
    ini[ELIMINAR_CURSO] = "Eliminar Curso";
    ini[CONSULTAR_CURSO] = "Consultar Curso"; 
    ini[INSCRIBIRSE_CURSO] = "Inscribirse a un Curso"; 
    ini[REALIZAR_EJERCICIO] = "Realizar Ejercicio";
    ini[CONSULTAR_ESTADISTICAS] = "Consultar Estadisticas"; 
    ini[SUSCRIBIRSE_NOTIF] = "Suscribirse a Notificaciones";
    ini[CONSULTA_NOTIF] = "Consultar Notificaciones";
    ini[ELIMINAR_SUSC] = "Eliminar Suscripcion";
    ini[SALIR] = "Salir";

    ini[0] = "Agregar datos precargados en el sistema";
    elegirOpcion("Menu Principal",ini);
    procesarOpcion();

}

void Menu::elegirOpcion(string titulo,map<int,string> s) {
    setOpcionActual(1);
    int opcion = 1;
    char tecla = 'a';
    int cantOpciones = s.size();
    int min = 1;
    if(s.find(0) != s.end()){
         min = 0;
         cantOpciones--;
    }
       

    while (tecla != 10) { // 10 es el código ASCII para la tecla Enter
        system("clear"); // Limpia la pantalla en Linux

        mostrarOpciones(titulo,s);

        tecla = getch(); // Obtiene la tecla presionada

        switch (tecla) {
            case 65: // Código ASCII para la flecha arriba
                opcion--;
                if (opcion < min) opcion = cantOpciones; // Si está en la primera opción, vuelve a la última
                break;
            case 66: // Código ASCII para la flecha abajo
                opcion++;
                if (opcion > cantOpciones) opcion = min; // Si está en la última opción, vuelve a la primera
                break;
            default:
                break;
        }

        setOpcionActual(opcion); // Actualiza la opción actual
    }
    
}

void Menu::mostrarOpciones(string titulo,map<int,string> opciones) {
    int i = 1;
    cout<<"----"<<titulo<< "----" <<endl;
    while(opciones.find(i) != opciones.end()){
        cout << (opcionSeleccionada(i) ? "> " : "  ") << i << ". "<< opciones[i] << endl;
        i++;
    }
    if(opciones.find(0)!=opciones.end())
        cout << (opcionSeleccionada(0) ? "> " : "  ") << "0. "<< opciones[0] << endl;
    
    cout<<"-----------------------" <<endl;
}

bool Menu::opcionSeleccionada(int opcion) {
    return opcionActual == opcion;
}

char Menu::getch() {
    struct termios oldTermios, newTermios;
    int ch;

    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

    return ch;
}

void Menu::procesarOpcion() {       
    
    try{
        switch (opcionActual) {
            case 0:
                cargarDatos();
                break;

            case ALTA_USUARIO:
                CU_altaUsuario();
                break;

            case CONSULTA_USUARIO:
                CU_consultaUsuario();
                break;

            case ALTA_IDIOMA:
                CU_altaIdioma();
                break;

            case CONSULTA_IDIOMA:
                CU_consultaIdioma();
                break;

            case ALTA_CURSO:
                CU_altaCurso();
                break;

            case AGREGAR_EJERCICIO:
                CU_agregarEjercicio();
                break;  
            case AGREGAR_LECCION:
                CU_agregarLeccion();
                break;
            case CONSULTAR_ESTADISTICAS:
                CU_consultarEstadisticas();
                break;
            
            case CONSULTAR_CURSO:
                CU_consultarCurso();
                break;

            case HABILITAR_CURSO: 
                CU_habilitarCurso();
                break;
            
            case INSCRIBIRSE_CURSO:          
                CU_inscribirseCurso();
                break;

            case REALIZAR_EJERCICIO:
                CU_realizarEjercicio();
                break;

            case SUSCRIBIRSE_NOTIF:
                CU_suscribirseNotif();
                break;  
        
            case CONSULTA_NOTIF:
                CU_consultarNotif();
                break;
            
            case ELIMINAR_SUSC:
                CU_eliminarSuscripcion();
                break;

            case ELIMINAR_CURSO:
                CU_eliminarCurso();
                break;

            case SALIR:
                cout << "Hasta luego!" << endl;
                break;  
                
            default:
                break;
        }
    }
    catch(exception &e){
            cout << "(!) "<<e.what() << endl;
    }

    if(opcionActual != SALIR){
        cout << "Presione enter para volver.";
        string enter;
        getline(cin,enter);
    }
    else{
        this_thread::sleep_for(chrono::seconds(2));
        system("clear");
        Fabrica::deleteIUsuario();
        Fabrica::deleteICurso();
    }
} 

bool Menu::getCargueDatos(){
    return cargueDatos;
}

void Menu::setCargueDatos(bool b){
    cargueDatos = b;
}

void Menu::cargarDatos(){
    if(!getCargueDatos()){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    ICurso* interfazCurso = Fabrica::getICurso();

    char delimitador = ';';
    string linea = "",tipoU = "",ref = "";
    
    int dia=0,mes=0,anio=0;
    string op="",nomC="",profC="",descC="",previa="",temaL="",objL="",descE="",sol="",fraseE="",idiomaA="", nomEst="", nomProf="";
    string p="",n="",contra="",nom="",desc="",resp="";

    bool aux=false, esCompletar=false;

    nivelDif difC=Principiante;

    map<string,ifstream> archivos;
    
    
    map<string,vector<string>> datos;
    set<string> previas,ingreso;
    list<string> solE;
    
        
    archivos["idiomas"] = ifstream("./data/Idiomas.csv");
    archivos["usuarios"] = ifstream("./data/Usuarios.csv");
    archivos["usuarios_est"] = ifstream("./data/Usuarios-Estudiantes.csv");
    archivos["usuarios_prof"] = ifstream("./data/Usuarios-Profesores.csv");
    archivos["cursos"] = ifstream("./data/Cursos.csv");
    archivos["cursos_previos"] = ifstream("./data/Cursos-Previos.csv");
    archivos["cursos_lecciones"] = ifstream("./data/Cursos-Lecciones.csv");
    archivos["cursos_lec_ej"] = ifstream("./data/Cursos-Lecciones-Ejercicios.csv");
    archivos["inscripciones"] = ifstream("./data/Inscripciones.csv");
    archivos["inscripciones_ej_aprob"] = ifstream("./data/Inscripciones-EjerciciosAprobados.csv");

    for(map<string,ifstream>::iterator it=archivos.begin();it!= archivos.end();++it)
        getline(it->second,linea);  //quito el titulo
    
    while(getline(archivos["idiomas"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);    //le saco el ref
        getline(fila,linea,delimitador);
        datos[ref].push_back(linea);
        interfazUsuario->altaIdioma(linea);
    }

    while(getline(archivos["usuarios"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);    //le saco el ref

        getline(fila,tipoU,delimitador);
        getline(fila,n,delimitador);

        datos[ref].push_back(n);

        getline(fila,contra,delimitador);
        datos[ref].push_back(contra);
        getline(fila,nom,delimitador);
        datos[ref].push_back(nom);
        getline(fila,desc,delimitador);
        datos[ref].push_back(desc);
        
        interfazUsuario->ingresoDatosComunes(n,contra,nom,desc);
        if(tipoU == "E"){
            getline(archivos["usuarios_est"],linea);
            stringstream fila(linea);
            getline(fila,linea,delimitador);    //le saco el ref
            getline(fila,linea,delimitador);
            datos[ref].push_back(linea);
            stringstream fecha(linea);
            
            getline(fecha,linea,'/');
            dia = stoi(linea);
            getline(fecha,linea,'/');
            mes = stoi(linea);
            getline(fecha,linea,'/');
            anio = stoi(linea);

            getline(fila,p,delimitador);
            datos[ref].push_back(p);

            interfazUsuario->altaEstudiante(p,dia,mes,anio);
        }else{
            ingreso.clear();
            getline(archivos["usuarios_prof"],linea);
            stringstream fila(linea);
            getline(fila,linea,delimitador); //le saco el ref
            getline(fila,n,delimitador); //En n tengo el instituto
            datos[ref].push_back(n);
            //Obtener idiomas
            for(int i = 1; i <= 3; i++){
                getline(fila,linea,delimitador);
                if(linea != string("")){
                    ingreso.insert(datos["I" + to_string(i)][0]);
                    datos[ref].push_back("I" + to_string(i));
                }
            }
            interfazUsuario->altaProfesor(n,ingreso);
        }
    }
    
    while(getline(archivos["cursos_lecciones"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,linea,delimitador);
        datos[ref].push_back(linea);
        
        getline(fila,temaL,delimitador);
        datos[ref].push_back(temaL);

        getline(fila,objL,delimitador);
        datos[ref].push_back(objL);
    }
    
    while(getline(archivos["cursos_lec_ej"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,linea,delimitador);
        datos[ref].push_back(linea);	
        
        getline(fila,linea,delimitador);
        datos[ref].push_back(linea);
        
        getline(fila,descE,delimitador);
        datos[ref].push_back(descE);
        
        getline(fila,fraseE,delimitador);
        datos[ref].push_back(fraseE);
        
        getline(fila,linea,delimitador); 
        stringstream solu(linea);
        while(getline(solu,linea,',')){
                datos[ref].push_back(linea);
                
        }
    }
    
    while(getline(archivos["cursos_previos"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,linea,delimitador);
        datos["P"+ref].push_back(linea);
    }
    
    while(getline(archivos["cursos"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,nomC,delimitador);
        datos[ref].push_back(nomC);
        getline(fila,descC,delimitador);
        datos[ref].push_back(descC);
        getline(fila,linea,delimitador);

        datos[ref].push_back(linea);
        if(linea == "Medio")
            difC = Intermedio;
        else if(linea == "Avanzado")
            difC = Avanzado;
        else
            difC = Principiante;

        getline(fila,linea,delimitador);
        profC = datos[linea][0];
        datos[ref].push_back(linea);
        getline(fila,linea,delimitador);
        datos[ref].push_back(linea);
        idiomaA = datos[linea][0];
        
        getline(fila,linea,delimitador);
        aux = linea == "Si"; //aux es true sii debo habilitar curso
        
        interfazCurso->seleccionarProfesor(profC);
        interfazCurso->ingresarDatosCurso(nomC, descC,difC);
        interfazCurso->seleccionarIdiomaCurso(idiomaA);
    
        int i = 1;
        while(datos.find("L"+to_string(i)) != datos.end() && datos["L"+to_string(i)][0] != ref)
            i++;
        
        while(datos.find("L"+to_string(i)) != datos.end() && datos["L"+to_string(i)][0] == ref){
            temaL = datos["L"+to_string(i)][1];
            objL = datos["L"+to_string(i)][2];
            interfazCurso->ingresarDatosNuevaLeccion(nomC,temaL,objL);
            int j=1;

            while(datos.find("E"+to_string(j)) != datos.end() && datos["E"+to_string(j)][0]!="L"+ to_string(i))
                j++;

            while(datos.find("E"+to_string(j)) != datos.end() && datos["E"+to_string(j)][0]=="L"+ to_string(i)){
                esCompletar = datos["E"+to_string(j)][1] == "R";
                descE = datos["E"+to_string(j)][2];
                fraseE = datos["E"+to_string(j)][3];
                solE.clear();
                long unsigned int x = 4;
                while(x < datos["E"+to_string(j)].size()){
                    solE.push_back(datos["E"+to_string(j)][x]);
                    x++;
                }
                interfazCurso->ingresarDatosEjercicio(esCompletar,descE,fraseE,solE);
                j++;
            }
            i++;
        }
        
        previas.clear();
        for(long unsigned int i = 0;i<datos["P"+ref].size();i++)
            previas.insert(datos[datos["P"+ref][i]][0]);
        
        interfazCurso->seleccionarPrevias(previas);
        
        interfazCurso->darAltaCurso();
        if(aux){
            interfazCurso->habilitarCurso(nomC);
        }
    }

    while(getline(archivos["inscripciones"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,nom,delimitador); //estudiante
        interfazUsuario->mostrarCursosHabilitadosAInscribirse(datos[nom][0]);
        datos[ref].push_back(nom);
        getline(fila,nomC,delimitador); //curso
        datos[ref].push_back(nomC);
        interfazUsuario->realizarInscripcion(datos[nomC][0]);
    }

    while(getline(archivos["inscripciones_ej_aprob"],linea)){
        stringstream fila(linea);
        getline(fila,ref,delimitador);
        getline(fila,linea,delimitador); //ejercicio
        solE.clear();
        nom = datos[datos[ref][0]][0];
        nomC = datos[datos[ref][1]][0];
        fraseE = datos[linea][3];
        interfazUsuario->mostrarCursosNoAprobados(nom);
        interfazUsuario->mostrarEjsNoAprobadosUltLec(nomC);
        DataEjercicio dataej(fraseE,datos[linea][2]);
        interfazUsuario->presentarProblema(dataej);
        for(long unsigned int i = 4; i < datos[linea].size();i++)
            solE.push_back(datos[linea][i]);
        interfazUsuario->resolveryCorregir(solE);
    }
    solE.clear();


    cout << "Se agregaron datos" <<endl;
    setCargueDatos(true);
    }
    else{
        cout << "Los datos ya fueron ingresados \n";
    }
}

void Menu::CU_altaUsuario(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    string n="",contra="",nom="",desc="",p="";
    int dia=0,mes=0,anio=0;
    cout << "Ingrese nickname del nuevo usuario: \n";
    getline(cin,n);
    cout << "Ingrese contraseña del nuevo usuario: \n";
    getline(cin,contra);
    while(contra.length() < 6){
        cout << "La contraseña debe tener al menos 6 caracteres, ingrese una nueva: \n";
        getline(cin,contra);
    }
    cout << "Ingrese nombre del nuevo usuario: \n";
    getline(cin,nom);
    cout << "Ingrese descripción del nuevo usuario: \n";
    getline(cin,desc);
    interfazUsuario->ingresoDatosComunes(n,contra,nom,desc); 
    
    map<int,string> opciones;
    opciones[1] = "Estudiante";
    opciones[2] = "Profesor";
    elegirOpcion("Que tipo de usuario desea agregar? ",opciones);
    if(opcionActual == 1){ //Creo estudiante
        cout << "Ingrese pais de residencia del estudiante:"<<endl;
        getline(cin,p);
        bool aux = true;
        while(aux){
            cout << "Ingrese dia de nacimiento: \n";
            cin >> dia;
            try {
                if(cin.fail()) {
                    throw runtime_error("Se debe ingresar un numero entero.");
                }else if (dia < 1 || dia > 31){
                    throw out_of_range("El día debe ser mayor a 0 y menor a 32.");
                }else {
                    aux = false;
                }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        aux = true;
        while(aux){
            cout << "Ingrese mes de nacimiento: \n";
            cin >> mes;
            try {
                if(cin.fail()) {
                    throw runtime_error("Se debe ingresar un numero entero.");
                }else if (mes < 1 || mes > 12){
                    throw out_of_range("El mes debe ser mayor a 0 y menor a 13.");
                }else {
                    aux = false;
                }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        aux = true;
        while(aux){
            cout << "Ingrese año de nacimiento: \n";
            cin >> anio;
            try {
                if(cin.fail()) {
                    throw runtime_error("Se debe ingresar un numero entero.");
                }else if (anio < 1900 || anio > 2022){
                    throw out_of_range("El año debe ser mayor a 1900 y menor a 2023.");
                }else {
                    aux = false;
                }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (!interfazUsuario->altaEstudiante(p,dia,mes,anio))
            throw runtime_error("No se pudo dar de alta el usuario, ya existe otro usuario con el mismo nickname");
        
        cout<<"Estudiante creado con exito"<<endl;
        
    }else{ //Creo profesor
        cout << "Ingrese instituto donde trabaja el profesor: \n";
        getline(cin,p);
        set<string> lista = interfazUsuario->listarIdiomas();
        int tam = lista.size();
        set<string> ingreso;

        if(tam == 0)
            throw runtime_error("No se puede agregar idiomas al profesor, pues no existen idiomas disponibles");
        
        cout << "Seleccione los idiomas en los que se especializa el profesor\n";
        setOpcionActual(1);
        bool primero = true;
        while (lista.size() > 0 && (opcionActual != 0)){                  
            opciones = conseguirOpciones(lista);
            if(!primero)
                opciones[0] = "No deseo agregar";
            elegirOpcion("Idiomas disponibles",opciones);  
            if(opcionActual != 0){ //Agrego a ingreso el idioma y lo elimino de la lista
                ingreso.insert(opciones[opcionActual]);
                lista.erase(opciones[opcionActual]);
            }  
            primero = false;      
        }
        
        if (!interfazUsuario->altaProfesor(p,ingreso))
            throw runtime_error("No se pudo dar de alta el usuario, ya existe otro usuario con el nickname "+n);
        
        cout<<"Profesor creado con exito"<<endl;    
    }
}

void Menu::CU_consultaUsuario(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();

    set<string> lista = interfazUsuario->listarNicknamesUsuario();
    map<int,string> opciones = conseguirOpciones(lista);
    DataUsuario* dataU;

    if(lista.size()==0)
        throw runtime_error("No existen usuarios en el sistema");
    
    elegirOpcion("Elija a un usuario",opciones);
    dataU = interfazUsuario->obtenerDataUsuario(opciones[opcionActual]);                 
    cout << dataU << endl;
    
    interfazUsuario->destruirDataUsuario(dataU);
}

void Menu::CU_altaIdioma(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    string idiomaA = "";

    cout << "Ingrese el nombre del nuevo idioma a crear:"<< endl;
    getline(cin,idiomaA);

    if(!interfazUsuario->altaIdioma(idiomaA))
        throw runtime_error("No se pudo dar de alta el idioma '"+idiomaA+"', ya existe otro idioma con el mismo nombre");

    cout<<"Idioma creado con exito"<<endl;
    
}

void Menu::CU_consultaIdioma(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarIdiomas();

    if(lista.size()==0)
        throw runtime_error("No existen idiomas en el sistema");
    
    cout << "Los idiomas existentes en el sistema son: \n";
    cout << lista;
    
}

void Menu::CU_altaCurso(){
    ICurso* interfazCurso = Fabrica::getICurso();
    map<int,string> opciones = conseguirOpciones(interfazCurso->listarNicknamesProfesores());
    if(opciones.size()==0)
        throw runtime_error("No existen profesores en el sistema");
    
    elegirOpcion("Profesores disponibles",opciones);

    string profC = opciones[opcionActual];
    opciones.clear();
    interfazCurso->seleccionarProfesor(profC);
    cout << "Has seleccionado al profesor "<< profC << endl;

    cout << "Ingrese los datos del nuevo curso a crear."<<endl;

    string nomC = "";
    string descC = "";
    while (nomC == ""){
        cout << "Nombre: ";
        getline(cin,nomC);
    }
    while(descC == ""){
        cout << "Descripcion: ";
        getline(cin,descC);
    }

    opciones[1] = "Principiante";
    opciones[2] = "Intermedio";
    opciones[3] = "Avanzado";
    elegirOpcion("Dificultad del curso: " + nomC,opciones);
    nivelDif difC = opciones[opcionActual] == "Principiante" ? Principiante : opciones[opcionActual] == "Intermedio" ? Intermedio : Avanzado;

    set<string> lista;
    while(lista.size()==0){
        try{
            lista = interfazCurso->ingresarDatosCurso(nomC,descC,difC);
        }catch(const invalid_argument& e){
            cout << "Error: " << e.what() << endl;
            nomC = "";
            cout << "Ingrese otro nombre para el curso: ";
            getline(cin,nomC);
            
        }   
    }
    opciones = conseguirOpciones(lista);
    elegirOpcion("Idiomas disponibles de "+profC,opciones);
    string idiomaA = opciones[opcionActual];
    interfazCurso->seleccionarIdiomaCurso(idiomaA);

    opciones.clear();
    opciones[1] = "Si";
    opciones[2] = "No";

    elegirOpcion("Desea agregar cursos previos? ",opciones);
    
    if(opciones[opcionActual] == "Si"){
        set<string> previas;
        lista = interfazCurso->listarNombresCursosHabilitados();
        if(!lista.size())
            cout << "Oopsie. No hay ningun curso habilitado!"<<endl;
        else    
            while(opcionActual != 0 && lista.size() > 0){
                opciones = conseguirOpciones(lista);
                opciones[0] = "No agregar mas";
                elegirOpcion("Cursos disponibles",opciones);
                if(opcionActual != 0){
                    previas.insert(opciones[opcionActual]);
                    lista.erase(opciones[opcionActual]);
                }
                opciones.clear();
            }
            
        interfazCurso->seleccionarPrevias(previas);
        cout << "Presione enter para volver.";
        string previa = "";
        getline(cin,previa);
    }

    opciones.clear();
    opciones[1] = "Si";
    opciones[2] = "No";
    elegirOpcion("Desea agregar lecciones? ",opciones);
    int i = 1;
    while(opciones[opcionActual] == "Si"){ //MAS LECCIONES
        
        cout<<"Ingrese el tema de la leccion "<< i <<": ";
        string temaL="",objL="";
        getline(cin,temaL);
        cout<<"Ingrese el objetivo de la leccion "<< i <<": ";
        getline(cin,objL);
        interfazCurso->ingresarDatosNuevaLeccion(nomC,temaL,objL);

        opciones.clear();
        opciones[1] = "Si";
        opciones[2] = "No";

        elegirOpcion("Desea agregar ejercicios a la leccion "+to_string(i)+"?",opciones);
        int j=1;
        while(opciones[opcionActual] == "Si"){ //MAS EJERCICIOS
            cout<< "Ingrese la descripcion del ejercicio "<<j<< " de la leccion "<<i<<": ";
            string descE="",fraseE="";

            getline(cin,descE);
            cout << "Ingrese la frase del ejercicio " << j << " de la leccion "<< i <<": ";                                      
            getline(cin,fraseE);

            opciones.clear();
            opciones[1] = "Completar Palabra";
            opciones[2] = "Traducir";
            elegirOpcion("Tipo de ejercicio",opciones);
            string op = opciones[opcionActual] == "Completar Palabra" ? "C" : "T";

            if(op == "C")
                cout << "Ingrese las palabras de la solucion separadas por comas Y SIN ESPACIOS: "<<endl;
            else
                cout << "Ingrese la solucion: "<<endl;
            
            list<string> solE;
            string sol = "";
            string sol_ingresadas = "";

            getline(cin,sol_ingresadas);
            stringstream ss(sol_ingresadas);
            while(getline(ss,sol,','))
                solE.push_back(sol);

            interfazCurso->ingresarDatosEjercicio(op == "C",descE,fraseE,solE);
            opciones.clear();
            opciones[1] = "Si";
            opciones[2] = "No";
            elegirOpcion("Desea agregar mas ejercicios a la leccion "+to_string(i)+"?",opciones);
            j++;
        }
        opciones.clear();
        opciones[1] = "Si";
        opciones[2] = "No";
        elegirOpcion("Desea agregar mas lecciones? ",opciones);
        i++;
    }
    interfazCurso->darAltaCurso();

    cout << "Se creo el curso '"+nomC+"' correctamente"<<endl;
}

void Menu::CU_agregarEjercicio(){
    ICurso* interfazCurso = Fabrica::getICurso();
    set<string> lista = interfazCurso->obtenerCursosNoHabilitados();
    
    if(lista.size() == 0)
        throw runtime_error("No hay cursos sin habilitar");
    
    map<int, string> opciones = conseguirOpciones(lista);
    elegirOpcion("Cursos no habilitados disponibles:",opciones);

    string nomC = opciones[opcionActual];
    opciones.clear();
    cout << "Has seleccionado el curso "<< nomC << endl;

    list<DataLeccion> leccionesDeCurso = interfazCurso->obtenerLeccionesOrdenadas(nomC);
    // mostrar datalecciones
    if (leccionesDeCurso.size() == 0)
        throw runtime_error("Uy! No hay lecciones en el curso seleccionado donde agregar ejercicios");
        
    cout << "LECCIONES DEL CURSO SELECCIONADO:" << endl;
    cout << leccionesDeCurso;

    int x = 1;
    int num_max = leccionesDeCurso.size();
    bool aux = true;
    
    while(aux){
        cout << "Ingrese el numero de leccion elegida: ";
        
        cin >> x; // x = lecElegida

        try {
            if(cin.fail()) {
                throw runtime_error("Se debe ingresar un numero entero.");
            }else if (x < 1 || x > num_max){
                throw out_of_range("El numero ingresado no corresponde a ninguna leccion.");
            }else {
                aux = false;
            }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    opciones[1] = "Traducir";
    opciones[2] = "Completar Palabra";
    elegirOpcion("Tipo de ejercicio que desea agregar",opciones);
    bool esCompletar = opcionActual == 2; // 1 -> Traducir
    
    opciones.clear();

    string descE="",fraseE="",sol="";
    list<string> solE;

    cout << "Ingrese su descripcion: ";
    getline(cin,descE);
    cout << "Ingrese su frase: ";
    getline(cin,fraseE);

    if(esCompletar)
        cout << "Ingrese las palabras de la solucion separadas por comas Y SIN ESPACIOS: "<<endl;
    else
        cout << "Ingrese la solucion: "<<endl;

    string sol_ingresadas;
    getline(cin,sol_ingresadas);
    stringstream ss(sol_ingresadas);
    while(getline(ss,sol,','))
        solE.push_back(sol);

    opciones.clear();

    list<DataLeccion>::iterator itDL = leccionesDeCurso.begin();
    int i = 1;
    while (i != x){
        itDL = ++itDL;
        i++;
    } // itDL apunta a la datalec elegida 
    DataLeccion lec = *itDL;
    aux = true;            
    while(aux){
        try{
            interfazCurso->ingresarDatosEjercicioDeLeccion(lec,esCompletar,descE,fraseE,solE);
            aux = false;                            
        }catch(const invalid_argument& e){
            cout << "Error: " << e.what() << endl;
            fraseE = "";
            cout << "Ingrese otra frase para el ejercicio: ";
            getline(cin,fraseE);
        }   
    }

    cout << "Datos del ejercicio ingresados correctamente" << endl;
    
    interfazCurso->darAltaEjercicio();
    cout << "EJERCICIO CREADO CORRECTAMENTE" << endl;
    
}

void Menu::CU_agregarLeccion(){
    ICurso* interfazCurso = Fabrica::getICurso();
    set<string> lista = interfazCurso->obtenerCursosNoHabilitados();
    if(lista.size() == 0)
        throw runtime_error("No hay cursos sin habilitar");
    

    map<int,string> opciones = conseguirOpciones(lista);

    elegirOpcion("Seleccione uno de los cursos no habilitados:",opciones);
    string nomC = opciones[opcionActual];
    cout << "Ingrese el tema de la Leccion a agregar: ";
    string temaL="",descE="",fraseE="";
    getline(cin,temaL);
    cout << "Ingrese la descripcion de la Leccion a agregar: ";
    getline(cin,descE);

    interfazCurso->ingresarDatosNuevaLeccion(nomC,temaL,descE);

    opciones.clear();
    opciones[1] = "Si";
    opciones[2] = "No";
    elegirOpcion("Desea agregar ejercicios a la leccion?",opciones);
    int j = 1;
    while(opciones[opcionActual] == "Si"){ //MAS EJERCICIOS
        cout<< "Ingrese la descripcion del ejercicio "<<j<< " de la leccion: ";
        getline(cin,descE);
        cout << "Ingrese la frase del ejercicio " << j << " de la leccion: ";                                      
        getline(cin,fraseE);

        opciones.clear();
        opciones[1] = "Completar Palabra";
        opciones[2] = "Traducir";
        elegirOpcion("Tipo de ejercicio",opciones);
        string op = opciones[opcionActual] == "Completar Palabra" ? "C" : "T";

        list<string> solE;
        string sol="";
        string sol_ingresadas = "";

        if(op == "C")
            cout << "Ingrese las palabras de la solucion separadas por comas Y SIN ESPACIOS: "<<endl;
        else
            cout << "Ingrese la solucion: "<<endl;

        getline(cin,sol_ingresadas);
        stringstream ss(sol_ingresadas);
        while(getline(ss,sol,','))
            solE.push_back(sol);
        
        interfazCurso->ingresarDatosEjercicio(op == "C",descE,fraseE,solE);
        opciones.clear();
        opciones[1] = "Si";
        opciones[2] = "No";
        elegirOpcion("Desea agregar mas ejercicios a la leccion?",opciones);
        j++;
    }
    interfazCurso->darAltaLeccion();
    cout << "Leccion creada correctamente"<<endl;
}

void Menu::CU_consultarEstadisticas(){
    map<int,string> opciones;
    opciones[1] = "Estudiante";
    opciones[2] = "Profesor";
    opciones[3] = "Curso";
    elegirOpcion("De que desea consultar estadisticas? ",opciones);

    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista;

    if(opciones[opcionActual] == "Estudiante"){
        opciones.clear();
        lista = interfazUsuario->listarNombresEstudiantes();
        if (lista.size() == 0) 
            throw runtime_error("No hay estudiantes en el sistema");
        

        cout << "Estudiante que quiere consultar:" << endl;
        opciones = conseguirOpciones(lista);
        elegirOpcion("Estudiantes en el sistema:",opciones);
        string nomEst = opciones[opcionActual]; 
        opciones.clear(); 
        list<string> cursosEst = interfazUsuario->listarCursosEst(nomEst);
        list<float> listFloat = interfazUsuario->porcentajeAvanceCursosEst(nomEst); 
        if (cursosEst.size() == 0){
            throw runtime_error("Hasta ahora, el estudiante '"+nomEst+"' no se ha anotado a ningun curso.");
        } else {
            cout << "- Los cursos del estudiante '"<<nomEst<<"' son: " << endl;
            cout << cursosEst << endl;
            cout << "- Y sus respectivos porcentajes de avance: " << endl;
            cout << listFloat << endl;
        }    
                            
    } else if (opciones[opcionActual] == "Profesor"){
        opciones.clear();
        lista = interfazUsuario->listarNombresProfesores();
        if (lista.size() == 0) 
            throw runtime_error("No hay profesores en el sistema");
        
        cout << "Profesor que quiere consultar:" << endl;
        opciones = conseguirOpciones(lista);
        elegirOpcion("Profesores en el sistema:",opciones);
        string nomProf = opciones[opcionActual]; 
        opciones.clear(); 
        list<string> cursosProf = interfazUsuario->listarCursosProf(nomProf);
        list<float> listFloat = interfazUsuario->porcentajeAvanceCursosProf(nomProf);
        if (cursosProf.size() == 0){
            throw runtime_error("Hasta ahora, el profe '"+ nomProf + "' no tiene cursos.");
        } else {
            cout<< "- Los cursos del profesor '"<<nomProf<<"' son: " << endl;
            cout << cursosProf << endl;
            cout << "- Y sus respectivos porcentaje de avance: " << endl;
            cout << listFloat << endl;
        }

    } else { //curso
        opciones.clear();
        lista = interfazUsuario->listarNombresCursos();
        
        if (lista.size() == 0)
            throw runtime_error("No existen cursos en el sistema.");
        
        cout << "Curso que quiere consultar:" << endl;
        opciones = conseguirOpciones(lista);
        elegirOpcion("Cursos en el sistema:",opciones);
        string nomC = opciones[opcionActual];
        DataCursoConsulta dataConsulta = interfazUsuario->mostrarInfoCompletaCurso(nomC);
        float porcentAvanceCurso = interfazUsuario->porcentajeAvanceCurso(nomC);
        cout << "- La info del curso es: " << endl; 
        cout << dataConsulta << endl;
        cout << "- Y el porcentaje de avance del curso es: " << porcentAvanceCurso << "%" << endl;
        cout << endl;
        
    }
}

void Menu::CU_consultarCurso(){
    ICurso* interfazCurso = Fabrica::getICurso();
    set<string> lista = interfazCurso->listarNombresCursos();
    if (lista.size() == 0) 
        throw runtime_error("No existen cursos en el sistema");
    
    cout << "Curso que quiere consultar:" << endl;
    map<int,string> opciones = conseguirOpciones(lista);
    elegirOpcion("Cursos en el sistema:",opciones);
    string nomC = opciones[opcionActual];
    opciones.clear();

    DataCursoConsulta dataConsulta = interfazCurso->mostrarInfoCompletaCurso(nomC);
    list<DataLeccionCompleta> leccionesDeCursoCompleta = interfazCurso->obtenerLeccionesOrdenadasCompletas(nomC); 
    list<DataInscripcionConsulta> inscriptosCurso = interfazCurso->obtenerInscriptosDelCurso(nomC); 
    cout<< "* Info general del curso: " << endl;
    cout << endl;
    cout << dataConsulta << endl;

    cout << "* Lecciones del curso: " << endl;
    cout << endl;
    if (leccionesDeCursoCompleta.size() == 0)
        cout << "Por el momento, el curso '" + nomC + "' no cuenta con ninguna leccion" << endl;
    
    cout << leccionesDeCursoCompleta << endl;


    cout <<"* Inscriptos al curso: " << endl;
    cout << endl;
    if (inscriptosCurso.size() == 0)
        cout << "Por el momento, nadie se ha inscripto al curso :(" << endl;
    
    cout << inscriptosCurso << endl; 
}

void Menu::CU_habilitarCurso(){
    ICurso* interfazCurso = Fabrica::getICurso();
    set<string> lista = interfazCurso->obtenerCursosNoHabilitados();            
    map<int,string> opciones = conseguirOpciones(lista);
    if(lista.size()==0)
        throw runtime_error("No existen cursos no habilitados en el sistema");

      
    elegirOpcion("Elija un curso",opciones);
    map<int,string>::iterator it=opciones.find(opcionActual);
    string n=it->second;
    interfazCurso->habilitarCurso(it->second);
    cout << "El curso fue habilitado con éxito"<<endl;
}

void Menu::CU_inscribirseCurso(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarNicknamesEstudiantes();
    if(lista.size() == 0)
        throw runtime_error("No hay ningun estudiante en el sistema");
        
    
    map<int,string> opciones = conseguirOpciones(lista);
    elegirOpcion("Seleccione un estudiante:",opciones);
    string nom = opciones[opcionActual];
    
    set<DataCursoyCants> cursosYCants = interfazUsuario->mostrarCursosHabilitadosAInscribirse(nom);
    
    if(cursosYCants.size() == 0)
        throw runtime_error("No hay ningun curso al que '" + nom + "' pueda inscribirse");

    cout<< "Cursos disponibles a los que "<< nom << " puede inscribirse:" <<endl;
    
    cout << cursosYCants << endl;
    bool aux = true;
    unsigned long int l = 1;
    while(aux){
        cout << "Ingrese el numero del curso al que desea inscribirse: ";
        cin >> l;

        try {
            if(cin.fail()) {
                throw runtime_error("Se debe ingresar un numero entero.");
            }else if (l < 1 || l > cursosYCants.size()){
                throw out_of_range("El numero ingresado no corresponde a ningun curso.");
            }else {
                aux = false;
            }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    set<DataCursoyCants>::iterator it = cursosYCants.begin();
    int x = 1;
    int i = l;
    while(x != i){
        ++it;
        x++;
    }
    DataCursoyCants cursoYCant = *it;

    interfazUsuario->realizarInscripcion(cursoYCant.getNombre());
    system("clear");
    cout<<nom<<" se ha inscripto correctamente al curso "<<cursoYCant.getNombre()<<endl;
    
}

void Menu::CU_realizarEjercicio(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarNicknamesEstudiantes();
    if(lista.size() == 0)
        throw runtime_error("No hay ningun estudiante en el sistema");
    
    map<int,string> opciones = conseguirOpciones(lista);
    elegirOpcion("Seleccione su nickname:",opciones);
    string n = opciones[opcionActual]; // nickname de estudiante
    opciones.clear();

    list<DataCurso> dataCursos = interfazUsuario->mostrarCursosNoAprobados(n);

    if (dataCursos.size() == 0)
        throw runtime_error(n + " no tiene cursos sin aprobar");
    
    cout<< "Cursos no aprobados en los que se puede resolver ejercicios:" <<endl;

    cout << dataCursos;
    bool aux = true;
    long unsigned int l = 1;
    while(aux){
        cout << "Ingrese el numero del curso elegido: ";
        cin >> l;

        try {
            if(cin.fail()) {
                throw runtime_error("Se debe ingresar un numero entero.");
            }else if (l < 1 || l > dataCursos.size()){
                throw out_of_range("El numero ingresado no corresponde a ningun curso.");
            }else {
                aux = false;
            }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    system("clear"); // limpia pantalla
    list<DataCurso>::iterator it = dataCursos.begin();
    int x = 1;
    int i = l;
    while(x != i){
        ++it;
        x++;
    }
    // *it apunta al dataCursoElegido por el estudiante
    string nomC = (*it).getNombre();
    set<DataEjercicio> ejs = interfazUsuario->mostrarEjsNoAprobadosUltLec(nomC);
    
    if (ejs.size() == 0)
        throw runtime_error("No hay ejercicios sin aprobar");
    
    cout<< "Ejercicios no aprobados de la ultima leccion del curso " << nomC << ": " << endl;

    cout << ejs;
    aux = true;
    while(aux){
        cout << "Ingrese el numero del ejercicio a realizar: ";
        cin >> l;

        try {
            if(cin.fail()) {
                throw runtime_error("Se debe ingresar un numero entero.");
            }else if (l < 1 || l > ejs.size()){
                throw out_of_range("El numero ingresado no corresponde a ningun curso.");
            }else {
                aux = false;
            }
            }catch(const out_of_range& e) {
                cout << e.what() << endl;
            }catch(const exception& e){
                cout << "Error: " << e.what() << endl;
                cin.clear();
            }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    system("clear"); // limpia pantalla
    set<DataEjercicio>::iterator itE = ejs.begin();
    x = 1;
    i = l;
    while(x != i){
        ++itE;
        x++;
    }
    // al salir estoy apuntando al ejercicio que se quiere resolver con *it
    DataEjercicio ej("","");
    ej = *itE;
    string fraseE = interfazUsuario->presentarProblema(ej); 
    string descE = ej.getDescripcion();
    for (int i = 0; i < 40; i++)
        cout << "-";
    cout << endl;
    cout << "Hola " << n << ", exitos con tu ejercicio!" << endl;
    cout << endl;
    cout << "Descripcion: " << descE << endl;
    cout << "Frase: " << fraseE << endl;
    for (int i = 0; i < 40; i++)
        cout << "-";
    cout << endl;

    ICurso* interfazCurso = Fabrica::getICurso();
    bool esCompletar = interfazCurso->ejEsCompletar(nomC,fraseE); 
    int cantR = interfazCurso->cantRespuestas(nomC,fraseE,esCompletar);
    
    list<string> respE;
    string resp;
    if (!esCompletar){
        cout << "Ingrese su respuesta:" << endl;
        getline(cin,resp);
        respE.push_back(resp);
    }else{ // esCompletar
        cout<< "Ingreso del conjunto de respuestas ordenadas de izquierda a derecha" << endl;
        for(int k = 1;k<=cantR;k++){
            cout<<"Ingrese la respuesta para el espacio "<<k<<": ";
            getline(cin,resp);
            respE.push_back(resp);
        }
    }

    bool respBien = interfazUsuario->resolveryCorregir(respE);
    if (respBien){
        cout << "Muy bien! Has respondido correctamente" <<endl;
    }else{
        cout << "Respuesta incorrecta. Intentelo luego nuevamente!" << endl;
    }    
}

void Menu::CU_suscribirseNotif(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarNicknamesUsuario();            
    map<int,string> opciones = conseguirOpciones(lista);

    if(lista.size()==0)
        throw runtime_error("No existen usuarios en el sistema");
        
    elegirOpcion("Elija un usuario",opciones);
    interfazUsuario->cargarNicknames(opciones[opcionActual]);
    lista.clear();
    opciones.clear();
    lista = interfazUsuario->listarIdiomasNoSuscrito();                
    opciones = conseguirOpciones(lista);

    if(lista.size()==0)
        throw runtime_error("No existen idiomas en el sistema");
                  
    int cantE=1;
    opcionActual=0;
    set<string> ingreso;
    while(opcionActual!=cantE+1){
            cantE=lista.size();
        opciones[cantE+1]="Salir";
        elegirOpcion("Elegir idiomas a suscribirse",opciones);
        if(cantE==0){    
            opcionActual=1;
        }
        if(opciones[opcionActual]!="Salir"){
            ingreso.insert(opciones[opcionActual]);   
            lista.erase(opciones[opcionActual]);    
            opciones = conseguirOpciones(lista);   
        }                     
    }
    interfazUsuario->cargarIdiomasSuscripcion(ingreso);
    
    
}

void Menu::CU_consultarNotif(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarNicknamesUsuario();            
    map<int,string> opciones = conseguirOpciones(lista);

    if(lista.size()==0)
        throw runtime_error("No existen usuarios en el sistema");
    
    elegirOpcion("Elija un usuario",opciones);
    interfazUsuario->cargarNicknames(opciones[opcionActual]);
    lista.clear();
    opciones.clear();
    list<DataNotif> notif = interfazUsuario->listarNotificacionesRecibidas();
    cout << notif << endl;
    interfazUsuario->eliminarNotificaciones();      

}

void Menu::CU_eliminarSuscripcion(){
    IUsuario* interfazUsuario = Fabrica::getIUsuario();
    set<string> lista = interfazUsuario->listarNicknamesUsuario();            
    map<int,string> opciones = conseguirOpciones(lista);

    if(lista.size()==0)
        throw runtime_error("No existen usuarios en el sistema");
    
    elegirOpcion("Elija un usuario",opciones);
    interfazUsuario->cargarNicknames(opciones[opcionActual]);
    lista.clear();
    opciones.clear();
    lista = interfazUsuario->listarIdiomasSuscritos();
    opciones = conseguirOpciones(lista);

    if(lista.size()==0)
        throw runtime_error("No esta suscrito a ningun idioma");
                        
    int cantE=1;
    opcionActual=0;
    while(opcionActual!=cantE+1){
            cantE=lista.size();
        opciones[cantE+1]="Salir";
        elegirOpcion("Elegir idiomas a desuscribirse",opciones);
        if(cantE==0){    
            opcionActual=1;
        }
        if(opciones[opcionActual]!="Salir"){  
            interfazUsuario->eliminarSuscripcionIdioma(opciones[opcionActual]);
            lista.erase(opciones[opcionActual]);
            opciones = conseguirOpciones(lista);
        }
        
    }                
    

}

void Menu::CU_eliminarCurso(){
    ICurso* interfazCurso = Fabrica::getICurso();
    set<string>lista = interfazCurso->listarNombresCursos();
    map<int,string> opciones = conseguirOpciones(lista);
    if(lista.size()==0)
        throw runtime_error("No existen cursos en el sistema");

    elegirOpcion("Elija el curso a eliminar",opciones);
    string nomC = opciones[opcionActual];
    interfazCurso->eliminarCurso(nomC);
    cout << "Se ha eliminado el curso "<<nomC<<"."<<endl;
    
}

ostream& operator<<(ostream& os, const set<string>& obj){
    set<string>::iterator it;
    int i = 1;
    for(it = obj.begin();it!=obj.end();++it){
        cout << i << ". " << *it << endl;
        i++;
    }
        
    return os;
}


ostream& operator<<(ostream& os, DataUsuario*& d){
    
    if(dynamic_cast<DataEstudiante*>(d)){
        DataEstudiante* e = dynamic_cast<DataEstudiante*>(d); 
        cout << " - Nombre: " << e->getNombre() << "\n";
        cout << " - Descripcion:  " << e->getDescripcion() << "\n";
        cout << " - Pais: " << e->getPais() << "\n";
        Date fn = e->getFechaNac();
        cout << " - Fecha de nacimiento: " << fn.getDia() << "/" << fn.getMes() << "/" << fn.getAnio() << "\n";

    }else if(dynamic_cast<DataProfesor*>(d)){
        DataProfesor* p = dynamic_cast<DataProfesor*>(d);
        cout << " - Nombre: " << p->getNombre() << "\n";
        cout << " - Descripcion: " << p->getDescripcion() << "\n";
        cout << " - Instituto: " << p->getInstituto() << "\n";
        cout << "Idiomas: \n";
        set<string>::iterator it;
        set<string> s = p->getMisIdiomas();
        for(it = s.begin(); it != s.end(); ++it){
            cout << " * " << *it << "\n";
        }
                              
    } 

    return os;
}

ostream& operator<<(ostream& os,set<DataLeccion>& d){
    set<DataLeccion>::iterator it;
    int i = 1;
    for(it = d.begin();it!=d.end();++it){
        DataLeccion l = *it;
        cout << i << ". " << l.getTema() << endl;
        cout << "   " << l.getObjetivo() << endl;
        i++;
    }
        
    return os;
}

ostream& operator<<(ostream& os,list<DataLeccion>& d){
    list<DataLeccion>::iterator it;
    int i = 1;
    for(it = d.begin();it!=d.end();++it){
        DataLeccion l = *it;
        cout << i << ". " << l.getTema() << endl;
        cout << "   " << l.getObjetivo() << endl;
        i++;
    }
        
    return os;
}

ostream& operator<<(ostream& os, DataCursoyCants & dc){
    cout << "\tNombre: " << dc.getNombre() << endl;
    cout << "\tDescripción: " << dc.getDescripcion() << endl;
    cout << "\tDificultad: ";
    switch (dc.getDificultad()) {
        case Principiante:
            os << "Principiante";
            break;
        case Intermedio:
            os << "Intermedio";
            break;
        case Avanzado:
            os << "Avanzado";
            break;
    }
    cout << endl;
    cout << "\tCantidad de Lecciones: " << dc.getCantLecciones() << endl;
    cout << "\tCantidad de Ejercicios: " << dc.getCantEjercicios();

    return os;
}

ostream& operator<<(ostream& os, set<DataCursoyCants> & dc){
    set<DataCursoyCants>::iterator it;
    int i = 0;
    for(it = dc.begin(); it!=dc.end();++it){
        i++;
        cout << "---->CURSO "<< i << "<----" << endl;
        DataCursoyCants d = *it;
        cout << d << endl;
        cout << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, DataCursoConsulta& dcc) {
    cout << "Nombre: " << dcc.getNomC() << endl;
    cout << "Descripción: " << dcc.getDescC() << endl;
    cout << "Dificultad: ";
    switch (dcc.getDifC()) {
        case Principiante:
            os << "Principiante";
            break;
        case Intermedio:
            os << "Intermedio";
            break;
        case Avanzado:
            os << "Avanzado";
            break;
    }
    cout << endl;
    cout << "Idioma: " << dcc.getIdiomaC() << endl;
    cout << "Profesor: " << dcc.getProfC() << endl;
    cout << "Habilitado: " << (dcc.getEstaHabilitado() ? "Sí" : "No") << endl;

    return os;
}

ostream& operator<<(ostream& os,list<DataNotif>& dn){
    list<DataNotif>::iterator itr;
    if(dn.empty()){
        cout << "No hay notificaciones" << endl;
    }                          
    for(itr = dn.begin(); itr!=dn.end(); ++itr){
        DataNotif n = *itr;
        cout << "Idioma:  " << n.getNombreIdioma() << endl;
        cout << "Curso: " << n.getNombreCurso() << "\n";
        cout << " " <<endl;
    } 
    return os;  
}

ostream& operator<<(ostream& os, DataCurso & dc){
    cout << "\tNombre: " << dc.getNombre() << endl;
    cout << "\tDescripción: " << dc.getDescripcion() << endl;
    cout << "\tDificultad: ";
    switch (dc.getNivelDif()) {
        case Principiante:
            os << "Principiante";
            break;
        case Intermedio:
            os << "Intermedio";
            break;
        case Avanzado:
            os << "Avanzado";
            break;
    }
    return os;
}

ostream& operator<<(ostream& os, list<DataCurso> & dc){
    list<DataCurso>::iterator it;
    int i = 0;
    for(it = dc.begin(); it!=dc.end();++it){
        i++;
        cout << "---->CURSO "<< i << "<----" << endl;
        DataCurso d = *it;
        cout << d << endl;
        cout << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, DataEjercicio & ej){
    cout << "\tFrase: " << ej.getFrase() << endl;
    cout << "\tDescripción: " << ej.getDescripcion() << endl;
    return os;
}

ostream& operator<<(ostream& os, set<DataEjercicio> & ej){
    set<DataEjercicio>::iterator it;
    int i = 0;
    for(it = ej.begin(); it!=ej.end();++it){
        i++;
        cout << "---->EJERCICIO "<< i << "<----" << endl;
        DataEjercicio ej = *it;
        cout << ej << endl;
        cout << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, list<string>& ls) {
    list<string>::iterator itr;
    int i = 1;
    for (itr = ls.begin(); itr != ls.end(); ++itr) {
        os << i << ". " << *itr << endl;
        i++;
    }
    return os;
}

ostream& operator<<(ostream& os, list<DataLeccionCompleta>& dlc){
    list<DataLeccionCompleta>::iterator itr;                       
    int i = 1;                                                         
    for(itr = dlc.begin(); itr!=dlc.end(); ++itr){
        DataLeccionCompleta l = *itr;
        cout << "Leccion " << i << ": " << l.getTema() << endl;
        cout << "Objetivo de la leccion: " << l.getObjetivo() << endl;

        set<DataEjercicioCompleto>::iterator itrej; 
        set<DataEjercicioCompleto> ejs = l.getEjercicios();
        int j = 1;
        if (ejs.size() == 0){
            cout << "La leccion no tiene ejercicios." << endl;
        } else {
            for(itrej = ejs.begin(); itrej != ejs.end(); ++itrej){
                DataEjercicioCompleto ej = *itrej;
                cout << "Ejercicio " << j << endl;
                cout << " -> Descripcion:  " << ej.getDescripcion() << endl;
                cout << " -> Frase:  " << ej.getFrase() << endl;
                cout << " -> Solucion/es: " << endl; 
                list<string>::iterator it;
                list<string> sols = ej.getSolucion();
                for (it = sols.begin(); it != sols.end(); ++it) {
                    cout << "     " << *it << endl;
                }
                j++;
                cout << endl;
            }
        }
        cout<<endl;
        i++;
    } 
    return os;
}

ostream& operator<<(ostream& os, list<DataInscripcionConsulta>& dic) {
    list<DataInscripcionConsulta>::iterator itr;
    int i = 1;
    for(itr = dic.begin(); itr != dic.end(); ++itr){
        DataInscripcionConsulta ins = *itr;
        cout << "Inscripto " << i << endl;
        cout << " - Nombre de inscripto: " << ins.getNombreEst() << endl;
        cout << " - Fecha de inscripcion: " << ins.getFechaInsc().getDia() << "/" << ins.getFechaInsc().getMes() << "/" << ins.getFechaInsc().getAnio() << "\n";
        i++;
    }
    
    return os;
}

ostream& operator<<(ostream& os, list<float>& floatSet) {
    list<float>::iterator itr;
    int i = 1;
    for (itr = floatSet.begin(); itr != floatSet.end(); ++itr) {
        cout << "Porcentaje de avance del curso " << i << " es: " << *itr << "%" << endl;
        i++;
    }
    return os;
}