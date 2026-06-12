#include <iostream>
#include <string.h>
#include <fstream>
#include <limits>

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

void Agregar_Productos(Sproducto **productos) { 
    
    auto Validar = []() -> int {
        int codigo;
        while (true) {
            cout << "Inserte Codigo: ";
            if (cin >> codigo) {
                cin.ignore();
                return codigo;
            }
            else {
                cout << "ERROR: Debe ingresar un numero\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    };
    

    int x = Validar();
    
    Sproducto *act = *productos;
    while (act != NULL) {
        if (act->codigo == x) {
            cout << "ERROR: No se puede insertar codigo repetido\n";
            return;
        }
        act = act->psig;
    }
    
    Sproducto *ax = new Sproducto;
    ax->codigo = x;
    ax->psig = NULL;
    
    string nombre, marca, descripcion;
    ax->nombre = nombre;
    ax->marca = marca;
    ax->descripcion = descripcion;
    cout << "Inserte Nombre: "; 
    getline(cin, nombre);
    cout << "Inserte Marca: "; 
    getline(cin, marca);
    cout << "Inserte Descripcion: "; 
    getline(cin, descripcion);
    
    cout << "Desea almacenar estos datos" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    int n;
    cin >> n;
    cin.ignore();
    
    if (n == 1) {

        if (*productos == NULL) {
            *productos = ax; 
        } else {
            act = *productos;
            while (act->psig != NULL) {
                act = act->psig;
            }
            act->psig = ax;
        }
        
        ofstream archivo("ListaDatosSproductos.txt", ios::app);
        if (!archivo) {
            cerr << "ERROR: No se pudo abrir el archivo\n";
            return;
        }
        archivo << x << "        " << nombre << "             " << marca << "             " << descripcion << endl;
        archivo.close();
        
        cout << "Producto guardado correctamente\n";
    }
    else {
        delete ax;
        cout << "Datos descartados.\n";
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
                cout << "\nSeleccione la opcion que desea modificar:\n";
                cout << "1. Nombre\n";
                cout << "2. Marca\n";
                cout << "3. Descripcion\n";
                cout << "0. Salir y guardar\n";
                cout << "Opcion: ";
                cin >> op;
                cin.ignore();
                
                switch (op) {
                    case 1:
                        cout << "Ingrese nuevo nombre: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->nombre = texto;
                            cout << "Nombre modificado correctamente.\n";
                        }
                        break;
                    case 2:
                        cout << "Ingrese nueva marca: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->marca = texto;
                            cout << "Marca modificada correctamente.\n";
                        }
                        break;
                    case 3:
                        cout << "Ingrese nueva descripcion: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->descripcion = texto;
                            cout << "Descripcion modificada correctamente.\n";
                        }
                        break;
                    case 0:
                        cout << "Se guardo los cambios\n";
                        break;
                    default:
                        cout << "Opcion invalida\n";
                }
            } while (op != 0);
            
            ofstream archivo("ListaDatosSproductos.txt");
            if (archivo) {
                Sproducto *temp = producto;
                while (temp != NULL) {
                    archivo << temp->codigo << "        " 
                            << temp->nombre << "             " 
                            << temp->marca << "             " 
                            << temp->descripcion << endl;
                    temp = temp->psig;
                }
                archivo.close();
                cout << "Cambios guardados correctamente.\n";
            } else {
                cerr << "ERROR: No se pudo guardar los cambios\n";
            }
            
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
void AgregarAsociado(Sasociado **asociado) { 
    
    auto Validar = []() -> int {
        int codigo;
        while (true) {
            cout << "Inserte Codigo: ";
            if (cin >> codigo) {
                cin.ignore();
                return codigo;
            }
            else {
                cout << "ERROR: Debe ingresar un numero\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    };
    

    int x = Validar();
    
    Sasociado *act = *asociado;
    while (act != NULL) {
        if (act->codigo == x) {
            cout << "ERROR: No se puede insertar codigo repetido\n";
            return;
        }
        act = act->pnext;
    }
    
    Sasociado *ax = new Sasociado;
    ax->codigo = x;
    ax->pnext = NULL;
    
    string nombre, direccion, telefono;
    cout << "Inserte Nombre: "; 
    getline(cin, nombre);
    cout << "Inserte Direccion: "; 
    getline(cin, direccion);
    cout << "Inserte Telefono: "; 
    getline(cin, telefono);
    
    cout << "Desea almacenar estos datos" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    int n;
    cin >> n;
    cin.ignore();
    
    if (n == 1) {

        if (*asociado == NULL) {
            *asociado = ax; 
        } else {
            act = *asociado;
            while (act->pnext != NULL) {
                act = act->pnext;
            }
            act->pnext = ax;
        }
        
        ofstream archivo("ListaDatosSasociados.txt", ios::app);
        if (!archivo) {
            cerr << "ERROR: No se pudo abrir el archivo\n";
            return;
        }
        archivo << x << "        " << nombre << "             " << direccion << "             " << telefono << endl;
        archivo.close();
        
        cout << "Producto guardado correctamente\n";
    }
    else {
        delete ax;
        cout << "Datos descartados\n";
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
    Sasociado *ax = asociado;
    
    while (ax != NULL) {
        if (ax->codigo == x) {
            cout << "Codigo encontrado\n";
            
            int op;
            string texto;
            
            do {
                cout << "\nSeleccione la opcion que desea modificar:\n";
                cout << "1. Nombre\n";
                cout << "2. Direccion\n";
                cout << "3. Telefono\n";
                cout << "0. Salir y guardar\n";
                cout << "Opcion: ";
                cin >> op;
                cin.ignore();
                
                switch (op) {
                    case 1:
                        cout << "Ingrese nuevo nombre: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->nombre = texto;
                            cout << "Nombre modificado correctamente.\n";
                        }
                        break;
                    case 2:
                        cout << "Ingrese nueva direccion: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->direccion = texto;
                            cout << "Marca modificada correctamente.\n";
                        }
                        break;
                    case 3:
                        cout << "Ingrese nuevo telefono: ";
                        getline(cin, texto);
                        if (!texto.empty()) {
                            ax->telefono = texto;
                            cout << "Descripcion modificada correctamente.\n";
                        }
                        break;
                    case 0:
                        cout << "Se guardo los cambios\n";
                        break;
                    default:
                        cout << "Opcion invalida\n";
                }
            } while (op != 0);
            
            ofstream archivo("ListaDatosSasociados.txt");
            if (archivo) {
                Sasociado *temp = asociado;
                while (temp != NULL) {
                    archivo << temp->codigo << "        " 
                            << temp->nombre << "             " 
                            << temp->direccion << "             " 
                            << temp->telefono << endl;
                    temp = temp->pnext;
                }
                archivo.close();
                cout << "Cambios guardados correctamente.\n";
            } else {
                cerr << "ERROR: No se pudo guardar los cambios\n";
            }
            
            return;
        }
        ax = ax->pnext;
    }
    
    cout << "Codigo no encontrado\n";
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
            case 1:
            AgregarAsociado(&asociado);
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
            case 1:
            Agregar_Productos(&producto);
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
