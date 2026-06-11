#include <iostream>
#include <string.h>
#include <fstream>

//Integrantes del equipo: David Amayo//
using namespace std;

struct Sproducto{
    int codigo;
    string nombre;
    string marca;
    string descripcion;
    Sproducto *psig;
};

struct Sasociado{
    int codigo;
    string nombre;
    string direccion;
    string telefono;
    Sasociado *pnext, *pventas;
};

struct Sventa{
    int num_operacion;
    string producto;
    string cantidad;
    string precio_unitario;
    string fecha;
    Sventa *prventas;
};

void Agregar_Productos(Sproducto **productos, int x) {
    auto Validar = []() -> int {
        int codigo;
        while (true) {
            cout << "Inserte Codigo: ";
            if (cin >> codigo) {
                cin.ignore();
                return codigo;
            }
            else {
                cout << "Entrada inválida. Por favor, inserte un numero entero.\n";
                cin.clear();
                cin.ignore(); 
            }
        }
    };
    if (*productos == NULL) {
        cout << "No hay datos en la tienda\n";
        x=Validar();

        Sproducto *ax = new Sproducto;
        ax->codigo = x;
        ax->psig = NULL;

        string nombre, marca, descripcion;
        cout << "Inserte Nombre: "; getline(cin, nombre);
        cout << "Inserte Marca: "; getline(cin, marca);
        cout << "Inserte Descripcion: "; getline(cin, descripcion);
        cout << "Desea almacenar estos datos" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        int n;
        cin >> n;
        cin.ignore();
        if (n == 1) {
            *productos = ax;
            ofstream archivo("ListaDatosSproductos.txt", ios::app);
            if (!archivo) {
                cerr << "No se pudo abrir el archivo\n";
                exit(1);
            }
            archivo << x << "         " << nombre << "           " << marca << "           " << descripcion << endl;
            archivo.close();
        }
        else {
            delete ax;
            cout << "Datos descartados" << endl;
        }
        return;
    }

    Sproducto *act = *productos;
    while (act != NULL) {
        if (act->codigo == x) {
            cout << "No se puede insertar claves repetidas\n";
            return;
        }
        if (act->psig == NULL)
            break; 
        act = act->psig;
    }
    x=Validar();
    string nombre, marca, descripcion;
    cout << "Inserte Nombre: "; getline(cin, nombre);
    cout << "Inserte Marca: "; getline(cin, marca);
    cout << "Inserte Descripcion: "; getline(cin, descripcion);
    cout << "Desea almacenar estos datos" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    int n;
    cin >> n;
    cin.ignore();
    if (n == 1) {
        Sproducto *ax = new Sproducto;
        ax->codigo = x;
        ax->psig = NULL;

        act->psig = ax;
        ofstream archivo("ListaDatosSproductos.txt", ios::app);
        if (!archivo) {
            cerr << "No se pudo abrir el archivo\n";
            exit(1);
        }
        archivo << x << "         " << nombre << "           " << marca << "           " << descripcion << endl;
        archivo.close();
    }
    else {
        cout << "Datos descartados" << endl;
    }
}

void Consultar_codigo_producto(Sproducto *producto, int x){
    Sproducto *ax=producto;
    while(ax!=NULL){    
        if(ax->codigo==x){
        cout<<"Codigo encontrado\n";
        cout<<""<< ax->codigo<<""<<endl;
        return;
        }
        else
        ax=ax->psig;
    };
    cout<<"El codigo no existe"<<endl;

}

void consultar_producto_pornombre(const string &ListaDatosSproductos, const string &palabra) {
    FILE *archivo = fopen("ListaDatosSproductos.txt", "r");
    if (!archivo) {
        cout << "No se pudo abrir el archivo: "<< '\n';
        return;
    }
    
    char linea[500];
    int num_linea = 0;
    int total_apariciones = 0;
    bool encontrado = false;
    
    while (fscanf(archivo, " %[^\n]", linea) == 1) {
        num_linea++;
        size_t pos = 0;
        int apariciones_linea = 0;
        string linea_str(linea); 
        while ((pos = linea_str.find(palabra, pos)) != string::npos) {
            apariciones_linea++;
            pos += palabra.size();
        }
        
        if (apariciones_linea > 0) {
            encontrado = true;
            total_apariciones += apariciones_linea;
            cout << "Linea " << num_linea << ": " << linea << '\n';
        }
    }
    
    if (!encontrado) {
        cout << "No se encontró \"" << palabra << "\" en " << ListaDatosSproductos << '\n';
    }
    
    fclose(archivo);
}

void ModificarProducto(Sproducto *producto, int x) {
    Sproducto *ax = producto;
    while (ax != NULL) {
        if (ax->codigo == x) {
            cout << "Codigo encontrado\n";

            int op;
            string texto;
            do {
                cout << "Seleccione la opcion que desea modificar:\n";
                cout << "1. Nombre\n";
                cout << "2. Marca\n";
                cout << "3. Descripcion\n";
                cout << "4. Salir\n";
                cout << "Opción: ";
                cin >> op;
                cin.ignore(); 

                switch (op) {
                    case 1:
                        cout << "Ingrese nuevo nombre: ";
                        getline(cin, texto);
                        ax->nombre = texto;
                        cout << "Nombre modificado correctamente.\n";
                        break;
                    case 2:
                        cout << "Ingrese nueva marca: ";
                        getline(cin, texto);
                        ax->marca = texto;
                        cout << "Marca modificada correctamente.\n";
                        break;
                    case 3:
                        cout << "Ingrese nueva descripcion: ";
                        getline(cin, texto);
                        ax->descripcion = texto;
                        cout << "Descripcion modificada correctamente.\n";
                        break;
                    case 4:
                        cout << "Saliendo de modificaciones...\n";
                        break;
                    default:
                        cout << "Opcion invalida. Intente de nuevo.\n";
                }
            } while (op != 4);

            return;
        }
        ax = ax->psig;
    }
    cout << "Codigo no encontrado\n";
}


void EliminarCodigoProducto(Sproducto **producto, int x){
    Sproducto *ax=*producto, *t=NULL;
    if(ax!=NULL){
        if(ax->codigo==x){
            *producto=(*producto)->psig;
            delete ax;
        }
        else{
            while((ax->psig!=NULL)&&(ax->psig->codigo!=x)){
                ax=ax->psig;
            }
            if(ax->psig!=NULL){
                t=ax->psig;
                ax->psig=t->psig;
                delete t;
            }
        }
    }
}

void MostrarProducto(){
    ifstream archivo;
    string texto;
    archivo.open("ListaDatosSproductos.txt", ios::in);
    if (archivo.fail()){
        cout<< "No se pudo abrir el archivo";
        return
        ;}
        cout<<"Codigo       Nombre                  Marca               Descripcion"<<endl;
    while(!archivo.eof()){
        getline(archivo,texto);
        cout<<texto<<endl;
    }
    archivo.close();
    
}
void AgregarAsociado(Sasociado **asociado, int x) {
    auto Validar = []() -> int {
        int codigo;
        while (true) {
            cout << "Inserte Codigo: ";
            if (cin >> codigo) {
                cin.ignore();
                return codigo;
            }
            else {
                cout << "Entrada inválida. Por favor, inserte un numero entero.\n";
                cin.clear();
                cin.ignore(); 
            }
        }
    };

    if (*asociado == NULL) {
        cout << "No hay datos en la tienda\n";
        x=Validar();

        Sasociado *ax = new Sasociado;
        ax->codigo = x;
        ax->pnext = NULL;

        string nombre, direccion, telefono;
        cout << "Inserte Nombre: "; getline(cin, nombre);
        cout << "Inserte Direccion: "; getline(cin, direccion);
        cout << "Inserte Telefono: "; getline(cin, telefono);
        cout << "Desea almacenar estos datos" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        int n;
        cin >> n;
        cin.ignore();
        if (n == 1) {
            *asociado = ax;
            ofstream archivo("ListaDatosSasociados.txt", ios::app);
            if (!archivo) {
                cerr << "No se pudo abrir el archivo\n";
                exit(1);
            }
            archivo << x << "         " << nombre << "           " << direccion << "           " << telefono << endl;
            archivo.close();
        }
        else {
            delete ax;
            cout << "Datos descartados" << endl;
        }
        return;
    }

    Sasociado *act = *asociado;
    while (act != NULL) {
        if (act->codigo == x) {
            cout << "No se puede insertar claves repetidas\n";
            return;
        }
        if (act->pnext == NULL)
            break; 
        act = act->pnext;
    }
    x=Validar();

    string nombre, direccion, telefono;
    cout << "Inserte Nombre: "; getline(cin, nombre);
    cout << "Inserte Direccion: "; getline(cin, direccion);
    cout << "Inserte Telefono: "; getline(cin, telefono);
    cout << "Desea almacenar estos datos" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    int n;
    cin >> n;
    cin.ignore();
    if (n == 1) {
        Sasociado *ax = new Sasociado;
        ax->codigo = x;
        ax->pnext = NULL;

        act->pnext = ax;
        ofstream archivo("ListaDatosSasociados.txt", ios::app);
        if (!archivo) {
            cerr << "No se pudo abrir el archivo\n";
            exit(1);
        }
        archivo << x << "         " << nombre << "           " << direccion << "           " << telefono << endl;
        archivo.close();
    }
    else {
        cout << "Datos descartados" << endl;
    }
}

void Consultar_codigo_Asociado(Sasociado *asociado, int x){
    Sasociado *ax=asociado;
    while(ax!=NULL){    
        if(ax->codigo==x){
        cout<<"Codigo encontrado\n";
        cout<<""<< ax->codigo<<""<<endl;
        return;
        }
        else
        ax=ax->pnext;
    };
    cout<<"El codigo no existe"<<endl;

}

void consultar_asociado_pornombre(const string &ListaDatosSasociados, const string &palabra) {
    FILE *archivo = fopen("ListaDatosSasociados.txt", "r");
    if (!archivo) {
        cout << "No se pudo abrir el archivo: " << '\n';
        return;
    }
    
    char linea[500];
    int num_linea = 0;
    int total_apariciones = 0;
    bool encontrado = false;
    
    while (fscanf(archivo, " %[^\n]", linea) == 1) {
        num_linea++;
        size_t pos = 0;
        int apariciones_linea = 0;
        string linea_str(linea); 
        while ((pos = linea_str.find(palabra, pos)) != string::npos) {
            apariciones_linea++;
            pos += palabra.size();
        }
        
        if (apariciones_linea > 0) {
            encontrado = true;
            total_apariciones += apariciones_linea;
            cout << "Linea " << num_linea << ": " << linea << '\n';
        }
    }
    
    if (!encontrado) {
        cout << "No se encontró \"" << palabra << "\" en " << ListaDatosSasociados << '\n';
    } 

    
    fclose(archivo);
}

void ModificarAsociado(Sasociado *asociado, int x) {
    Sasociado *ax=asociado;
    while(ax!=NULL){
        if(ax->codigo==x){
            cout<<"Codigo encontrado"<<endl;
            return;
        }
        ax=ax->pnext;
    };
    cout<<"Codigo no encontrado"<<endl;
    return;
}
void EliminarCodigoAsociado(Sasociado **asociado, int x){
    Sasociado *ax=*asociado, *t=NULL;
    if(ax!=NULL){
        if(ax->codigo==x){
            *asociado=(*asociado)->pnext;
            delete ax;
        }
        else{
            while((ax->pnext!=NULL)&&(ax->pnext->codigo!=x)){
                ax=ax->pnext;
            }
            if(ax->pnext!=NULL){
                t=ax->pnext;
                ax->pnext=t->pnext;
                delete t;
            }
        }
    }
}

void MostrarAsociado(){
    ifstream archivo;
    string texto;
    archivo.open("ListaDatosSasociados.txt", ios::in);
    if (archivo.fail()){
        cout<< "No se pudo abrir el archivo"; 
        return;
    }
        cout<<"Codigo       Nombre              Direccion           Telefono"<<endl;
    while(!archivo.eof()){
        getline(archivo,texto);
        cout<<texto<<endl;
    }
    archivo.close();
    
}


void MenuAsociados(){
    system("cls");
    int op=-1, n=0;
    Sasociado *asociado=NULL;
    while(op!=0){
        cout << "1) Agregar\n2) Consultar por codigo\n3) Consultar por nombre\n4) Modificar por codigo\n5) Eliminar por codigo\n6) Mostrar todas los asociados\n\n0) Salir\n\n";
        cout << "Opcion:\n ";
        cin>>op;
        switch(op){
            case 1:cout<<"Inserte el codigo a validar"<<endl;
            cin>>n;
            AgregarAsociado(&asociado, n);
            break;
            case 2:
            cout<<"Inserte el codigo a consultar"<<endl;cin>>n;
            Consultar_codigo_Asociado(asociado, n);
            break;
            case 3: {
            cout<<"Inserte el nombre a consultar"<<endl;
            cin.ignore();
            string nombre;
            getline(cin, nombre);
            consultar_asociado_pornombre("ListaDatosSasociados.txt", nombre);
            break;
            }
            case 4:
            cout<<"Inserte el codigo"<<endl;cin>>n;
            ModificarAsociado(asociado, n);
            break;
            case 5:
            cout<<"Inserte el codigo a eliminar"<<endl;cin>>n;
            EliminarCodigoAsociado(&asociado, n);
            break;
            case 6:
            MostrarAsociado();
            break;
            case 0:
            break;
            default:cout << "Opcion invalida.\n"; break;
            }
            system("pause");
            system("cls");
        }
    
}

void MenuProductos(){
    system("cls");
    int op=-1, n=0;
    Sproducto *producto=NULL;
    while(op!=0){
        cout << "1) Agregar\n2) Consultar por codigo\n3) Consultar por nombre\n4) Modificar por codigo\n5) Eliminar por codigo\n6) Mostrar todas los productos\n\n0) Salir\n\n";
        cout << "Opcion:\n ";
        cin>>op;
        switch(op){
            case 1:cout<<"Inserte el codigo"<<endl;
            cin>>n;
            Agregar_Productos(&producto, n);
            break;
            case 2:
            cout<<"Inserte el codigo a consultar"<<endl;cin>>n;
            Consultar_codigo_producto(producto, n);
            break;
            case 3: {
            cout<<"Inserte el nombre a consultar"<<endl;
            cin.ignore();
            string nombre;
            getline(cin, nombre);
            consultar_producto_pornombre("ListaDatosSproductos.txt", nombre);
            break;
            }
            case 4:
            cout<<"Inserte el codigo"<<endl;cin>>n;
            ModificarProducto(producto, n);
            break;
            case 5:
            cout<<"Inserte el codigo a eliminar"<<endl;cin>>n;
            EliminarCodigoProducto(&producto, n);
            break;
            case 6:
            MostrarProducto();
            break;
            case 0:
            break;
            default:cout << "Opcion invalida.\n"; break;
            }
            system("pause");
            system("cls");
        }
    
}

int main(){
    int op=-1;
    while (op!=0){
        cout << "\n                              === SISTEMA INVENTARIO ===            \n";
        cout << "\nRealizado por\nDavid Amayo C.I: 31.784.426\n";
        cout << "\n                              ===   MENU PRINCIPAL   ===            \n";
        cout << "1) Asociados\n2) Productos\n3) Ventas\n\n0) Salir\n\n";
        cout << "Opcion:\n ";
        cin>>op;
        switch (op){
        case 1:
            MenuAsociados();
        break;
        case 2:
            MenuProductos();
        break;  
        case 3:
        break;
        default: cout << "Opcion invalida.\n"; break;
        }
        system("cls");
    }
}

