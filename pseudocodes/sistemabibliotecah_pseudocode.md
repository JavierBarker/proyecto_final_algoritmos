CLASE SistemaBiblioteca
    // Atributos Privados (Vectores para persistencia en memoria)
    PRIVADO
        VECTOR<Libro> libros
        VECTOR<Usuario> usuarios
        VECTOR<Prestamo> prestamos
        
    // Métodos Públicos (Menús, CRUD, Préstamos, Reportes)
    PUBLICO
        // MENÚS
        PROCEDIMIENTO mostrarMenu()
        PROCEDIMIENTO mostrarMenuGestionUsuario()
        PROCEDIMIENTO mostrarMenuGestionLibro()
        PROCEDIMIENTO mostrarMenuGestionPrestamo()
        PROCEDIMIENTO mostrarMenuGestionReportes()

        // CRUD USUARIOS (Cargar, Guardar, Agregar, Buscar, Listar, Actualizar, Eliminar)
        // ... 
        
        // CRUD LIBROS (Cargar, Guardar, Agregar, Buscar, Listar, Actualizar, Eliminar)
        // ...

        // PRESTAMOS
        PROCEDIMIENTO cargarPrestamos()
        PROCEDIMIENTO guardarPrestamos()
        FUNCION LOGICO realizarPrestamo()
        FUNCION LOGICO registrarDevolucion()
        PROCEDIMIENTO consultarHistorialPorUsuario()
        PROCEDIMIENTO listarPrestamosActivos()
        PROCEDIMIENTO calcularMultasRetraso()

        // REPORTES
        PROCEDIMIENTO reporteLibrosMasPrestados()
        PROCEDIMIENTO reporteUsuariosConMasPrestamos()
        PROCEDIMIENTO reporteLibrosBajaDisponibilidad()
        PROCEDIMIENTO reporteMultasPendientes()
        PROCEDIMIENTO generarReporteGeneralTxt()
FIN CLASE
