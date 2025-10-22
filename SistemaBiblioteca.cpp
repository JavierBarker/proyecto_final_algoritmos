#include "SistemaBiblioteca.h"
#include "Utilidades.h"
#include "Usuario.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

//Variables Globales
Utilidades utilidades;
Usuario usuario;

//vectores
vector<Usuario> usuarios;


string usuariosTxt = "usuarios.txt";
string librosTxt = "/output/libros.txt";
string prestamosTxt = "/output/prestamos.txt";

void SistemaBiblioteca::mostrarMenu() {
    utilidades.limpiarPantalla();
    int opcion;

    do
    {
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === SISTEMA DE BIBLIOTECA ===                   ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Gestión de Libros                                         ║" << endl;
        cout << "║ 2. Gestión de Usuarios                                       ║" << endl;
        cout << "║ 3. Gestión de Prestamos                                      ║" << endl;
        cout << "║ 4. Reportes y Estadísticas                                   ║" << endl;
        cout << "║ 5. Guardar y Salir                                           ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl; 

        switch (opcion)
        {
        case 1:
            
            /* code */
            break;
        case 2:
            utilidades.limpiarPantalla();
            mostrarMenuGestionUsuario();
           break;
           
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        
        case 5:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Saliendo del programa... 🫡" << endl;
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion != 5);
}


//CRUD USUARIOS
void SistemaBiblioteca::cargarUsuarios(){
    ifstream archivo(usuariosTxt);
    string lineaTexto;

    while (getline(archivo, lineaTexto)){

        stringstream infoLineaTexto(lineaTexto);
        string id, nombre, carrera, correo, telefono, librosPrestados;

        getline(infoLineaTexto, id, ';');
        getline(infoLineaTexto, nombre, ';');
        getline(infoLineaTexto, carrera, ';');
        getline(infoLineaTexto, correo, ';');
        getline(infoLineaTexto, telefono, ';');
        getline(infoLineaTexto, librosPrestados, ';');

        if (id == "ID") continue;
        usuarios.push_back(Usuario(id, nombre, carrera, correo, telefono, stoi(librosPrestados)));
    }

    archivo.close();
}

void SistemaBiblioteca::guardarUsuarios(){
    ofstream archivo(usuariosTxt, ios::trunc);

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo Usuario.txt" << endl;
    }else{
        archivo << "ID;Nombre;Carrera;Correo;Telefono;LibrosPrestados" << endl;
        for (size_t i = 0; i < usuarios.size(); i++)
        {
            archivo 
                << usuarios[i].getId() << ";"
                << usuarios[i].getNombre() << ";"
                << usuarios[i].getCarrera() << ";"
                << usuarios[i].getCorreo() << ";"
                << usuarios[i].getTelefono() << ";"
                << usuarios[i].getLibrosPrestados() << endl;
        }

        archivo.close();
    }
}

bool SistemaBiblioteca::agregarUsuario(){
    cargarUsuarios();

    string nombre, carrera, correo, telefono;
    int idUsuario = stoi(usuarios[usuarios.size() - 1].getId()) + 1;
    
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              === Registrar Usuario No. " << idUsuario << " ===                 ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
    cout << "║ Nombre: "; getline(cin, nombre);
    cout << "║ Carrera: "; getline(cin, carrera); 
    cout << "║ Correo: "; getline(cin, correo);
    cout << "║ Telefono: "; getline(cin, telefono);
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;


    cout << endl;
    cout << " Usuario registrado correctamente ✅ " << endl;

    usuarios.push_back(Usuario(to_string(idUsuario), nombre, carrera, correo, telefono, 0));
    guardarUsuarios();
    
    usuarios.clear();
    return true;
}

void SistemaBiblioteca::buscarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Buscar Usuario por ID o Nombre ===                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
        } 
    }

    if (encontrado != 1) cout << "Usuario no Encontrado. 🚨" << endl;
    usuarios.clear();
}

void SistemaBiblioteca::listarUsuarios(){
    cargarUsuarios();

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Lista de Usuarios ===                                    ║" << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "  Usuario No. " << usuarios[i].getId() << endl;
        cout << "  Nombre: " << usuarios[i].getNombre() << endl;
        cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
        cout << "  Correo: " << usuarios[i].getCorreo() << endl;
        cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
        cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
    }
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    usuarios.clear();
}

void SistemaBiblioteca::actualizarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Actualizar Usuario ===                                   ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    if (encontrado == 1){
        //actualizar usuario
        string nombre, carrera, correo, telefono, librosPrestados;
        
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║  === Ingrese los Nuevos Valores ===                          ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ Usuario No. " << usuarios[posicion].getId() << endl;
        cout << "║ Nombre: "; getline(cin, nombre);
        cout << "║ Carrera: "; getline(cin, carrera); 
        cout << "║ Correo: "; getline(cin, correo);
        cout << "║ Telefono: "; getline(cin, telefono);
        cout << "║ Libros Prestados: "; getline(cin, librosPrestados);
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        //actualizamos los datos
        usuarios[posicion].setNombre(nombre);
        usuarios[posicion].setCarrera(carrera);
        usuarios[posicion].setCorreo(correo);
        usuarios[posicion].setTelefono(telefono);
        usuarios[posicion].setLibrosPrestados(stoi(librosPrestados));
        guardarUsuarios();

        cout << "Usuario Actualizado. ✅" << endl;
    }else{
        cout << "Usuario no Encontrado. 🚨" << endl;
    }

    usuarios.clear();
}

void SistemaBiblioteca::eliminarUsuario(){
    cargarUsuarios();
    string buscar;
    int encontrado, posicion;

    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║ === Eliminar Usuario ===                                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << "   Ingrese el Id o Nombre: ";
    getline(cin, buscar);
    cout << endl;

    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i].getId() == buscar || usuarios[i].getNombre() == buscar)
        {
            cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
            cout << "  Usuario No. " << usuarios[i].getId() << endl;
            cout << "  Nombre: " << usuarios[i].getNombre() << endl;
            cout << "  Carrera: " << usuarios[i].getCarrera() << endl;
            cout << "  Correo: " << usuarios[i].getCorreo() << endl;
            cout << "  Telefono: " << usuarios[i].getTelefono() << endl;
            cout << "  Libros Prestados: " << usuarios[i].getLibrosPrestados() << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
            cout << endl;
            cout << "Usuario Encontrado. ✅" << endl;
            encontrado = 1;
            posicion = i;
        } 
    }

    string respuesta;
    if (encontrado == 1){
        cout << "Desea Eliminar el Usuario? 🚧 (S/N): ";
        getline(cin, respuesta);

        if (respuesta == "S" || respuesta == "s")
        {
            usuarios.erase(usuarios.begin() + posicion);
        }
        guardarUsuarios();
        cout << "Usuario Eliminado. ✅" << endl;
    }else{
        cout << "Usuario no Encontrado. 🚨" << endl;
    }

    usuarios.clear();
}

void SistemaBiblioteca::mostrarMenuGestionUsuario()
{
    int opcion2;
    do
    {
        cout << endl;
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              === GESTIÓN DE USUARIOS ===                     ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << "║ 1. Registrar Usuario                                         ║" << endl;
        cout << "║ 2. Buscar Usuario                                            ║" << endl;
        cout << "║ 3. Listar Usuarios                                           ║" << endl;
        cout << "║ 4. Actualizar Usuario                                        ║" << endl;
        cout << "║ 5. Eliminar Usuario                                          ║" << endl;
        cout << "║ 6. Regresar                                                  ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;

        cout << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion2;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << endl;

        switch (opcion2)
        {
        case 1:
        {
            agregarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
        }
        break;

        case 2:
            buscarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 3:
            listarUsuarios();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 4:
            actualizarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 5:
            eliminarUsuario();
            utilidades.limpiarPantallaValidar();
            cout << endl;
            break;

        case 6:
            utilidades.limpiarPantalla();
            cout << endl;
            break;
        default:
            utilidades.limpiarPantalla();
            cout << endl;
            cout << "Opción inválida. Por favor, intente de nuevo. 🚨" << endl;
            cout << endl;
            break;
        }
    } while (opcion2 != 6);
}

