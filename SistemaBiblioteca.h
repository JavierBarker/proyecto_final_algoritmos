#include <string>
#include <vector>
#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"

using namespace std;

class SistemaBiblioteca
{
private:
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
public:
    // Muestra el menú principal del sistema
    void mostrarMenu();
    void mostrarMenuGestionUsuario();
    void mostrarMenuGestionLibro();
    void mostrarMenuGestionPrestamo();
    void mostrarMenuGestionReportes();

    // CRUD USUARIOS
    void cargarUsuarios();
    void guardarUsuarios();
    bool agregarUsuario();
    void buscarUsuario();
    void listarUsuarios();
    void actualizarUsuario();
    void eliminarUsuario();

    // CRUD LIBROS
    void cargarLibros();
    void guardarLibros();
    bool agregarLibro();
    void buscarLibro();
    void listarLibros();
    void actualizarLibro();
    void eliminarLibro();

    // PRESTAMOS
    void cargarPrestamos();
    void guardarPrestamos();
    bool realizarPrestamo();
    bool registrarDevolucion();
    void consultarHistorialPorUsuario();
    void listarPrestamosActivos();
    void calcularMultasRetraso();

    // REPORTES Y ESTADÍSTICAS
    void reporteLibrosMasPrestados();
    void reporteUsuariosConMasPrestamos();
    void reporteLibrosBajaDisponibilidad();
    void mostrarMenuReportes();
    void reporteMultasPendientes();


    // REPORTE GENERAL
    void generarReporteGeneralTxt();
};