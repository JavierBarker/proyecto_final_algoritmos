#include "SistemaBiblioteca.h"
#include "Utilidades.h"
#include <iostream>


using namespace std;

void SistemaBiblioteca::mostrarMenu() {
    Utilidades utilidades;

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
        do{
        int opcion2;
            cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
            cout << "║ 1. Mostrar usuarios en sistema                               ║" << endl;
            cout << "║ 2. Ingresar nuevo usuario                                    ║" << endl;
            cout << "║ 3. Consultar prestamos de usuario:                           ║" << endl;
            cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
 
           switch (opcion2) {
           case 1:
            mostrarInformacion() const;
            cout << endl;
            break;

            case 2:
            guardarEnArchivo();
            cout << endl;
            cout << " usuario registrado correctamente :) " << endl;
            cout << endl;
            break;

            case 3:
            if (puedePrestar() < 4) {
            cout << "Usuario puede prestar libro tiene: " << puedePrestar() << " prestamos" << endl;         
            } else {
            cout << "Usuario no tiene permitido mas prestamos " << endl;
            cout << "presenta " << puedePrestar() << " libros prestados " << endl;
            }
            cout << endl;
            break;

           default: 
           cout << "Opcion ingresada invalida" << endl;
            break;
           }
           } while (opcion2 != 3);
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