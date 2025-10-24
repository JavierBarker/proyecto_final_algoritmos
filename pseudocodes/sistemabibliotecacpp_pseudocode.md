INCLUIR "SistemaBiblioteca.h", "Utilidades.h", "Usuario.h", "Libro.h", "Prestamo.h"
// Declaración de Variables Globales (Instancias y Vectores)
// CONSTANTES para nombres de archivos (usuarios.txt, libros.txt, prestamos.txt)

// =======================================================
// MENÚ PRINCIPAL
// =======================================================
PROCEDIMIENTO SistemaBiblioteca::mostrarMenu()
    utilidades.limpiarPantalla()
    ENTERO opcion
    REPETIR
        MOSTRAR MENÚ PRINCIPAL (1. Libros, 2. Usuarios, 3. Préstamos, 4. Reportes, 5. Salir)
        PEDIR opcion

        SEGUN opcion
            CASO 1: mostrarMenuGestionLibro()
            CASO 2: mostrarMenuGestionUsuario()
            CASO 3: mostrarMenuGestionPrestamo()
            CASO 4: mostrarMenuGestionReportes()
            CASO 5: generarReporteGeneralTxt(); ESCRIBIR "Saliendo..."
            DEFECTO: ESCRIBIR "Opción inválida"
        FIN SEGÚN
    MIENTRAS opcion != 5
FIN PROCEDIMIENTO

// PROCEDIMIENTO mostrarMenuGestionUsuario()
// (Similar a mostrarMenu, llama a las funciones CRUD de Usuario)
// ...

// PROCEDIMIENTO mostrarMenuGestionLibro()
// (Similar a mostrarMenu, llama a las funciones CRUD de Libro)
// ...

// =======================================================
// CRUD USUARIOS (Ejemplo: Cargar, Agregar)
// =======================================================
PROCEDIMIENTO SistemaBiblioteca::cargarUsuarios()
    LEER archivo "usuarios.txt"
    MIENTRAS LEER líneaTexto CON DELIMITADOR ';'
        SI NO ES ENCABEZADO ("ID") ENTONCES
            SEPARAR líneaTexto EN campos (id, nombre, carrera, correo, telefono, librosPrestados)
            AGREGAR NUEVO Usuario(id, nombre, ..., ConvertirAEntero(librosPrestados)) AL vector 'usuarios'
        FIN SI
    FIN MIENTRAS
    CERRAR archivo
FIN PROCEDIMIENTO

FUNCION LOGICO SistemaBiblioteca::agregarUsuario()
    cargarUsuarios()
    CALCULAR nuevoId (último ID + 1)
    PEDIR nombre, carrera, correo, telefono
    AGREGAR nuevo Usuario AL vector 'usuarios'
    guardarUsuarios()
    LIMPIAR vector 'usuarios'
    RETORNAR VERDADERO
FIN FUNCION

// PROCEDIMIENTOS: guardarUsuarios, buscarUsuario, listarUsuarios, actualizarUsuario, eliminarUsuario
// (Siguen la lógica de cargar el vector, operar sobre él y guardarlo, usando get/setters)
// ...

// =======================================================
// CRUD LIBROS (Ejemplo: Cargar, Agregar)
// =======================================================
PROCEDIMIENTO SistemaBiblioteca::cargarLibros()
    LEER archivo "libros.txt"
    MIENTRAS LEER líneaTexto CON DELIMITADOR ';'
        SI NO ES ENCABEZADO ("ISBN") ENTONCES
            SEPARAR líneaTexto EN campos (isbn, titulo, autor, anio, categoria, cantidadDisponible)
            AGREGAR NUEVO Libro(isbn, titulo, ..., ConvertirAEntero(cantidadDisponible)) AL vector 'libros'
        FIN SI
    FIN MIENTRAS
    CERRAR archivo
FIN PROCEDIMIENTO

FUNCION LOGICO SistemaBiblioteca::agregarLibro()
    cargarLibros()
    PEDIR isbn, titulo, autor, anio, categoria, cantidadDisponible
    AGREGAR nuevo Libro AL vector 'libros'
    guardarLibros()
    LIMPIAR vector 'libros'
    RETORNAR VERDADERO
FIN FUNCION

// PROCEDIMIENTOS: guardarLibros, buscarLibro, listarLibros, actualizarLibro, eliminarLibro
// (Siguen la lógica de cargar el vector, operar sobre él y guardarlo, usando get/setters)
// ...

// =======================================================
// GESTIÓN DE PRÉSTAMOS
// =======================================================
FUNCION LOGICO SistemaBiblioteca::realizarPrestamo()
    cargarUsuarios(), cargarLibros(), cargarPrestamos()
    PEDIR idUsuario, isbn
    
    BUSCAR posUsuario (SI NO encontrado, ESCRIBIR "Usuario no encontrado" Y RETORNAR FALSO)
    SI NOT usuarios[posUsuario].puedePrestar() ENTONCES
        ESCRIBIR "Usuario excedió límite de préstamo" Y RETORNAR FALSO
    FIN SI
    
    BUSCAR posLibro (SI NO encontrado, ESCRIBIR "Libro no encontrado" Y RETORNAR FALSO)
    SI libros[posLibro].getCantidadDisponible() <= 0 ENTONCES
        ESCRIBIR "Libro no disponible" Y RETORNAR FALSO
    FIN SI

    // REGISTRAR PRÉSTAMO
    idPrestamo = tamaño de 'prestamos' + 1
    fechaHoy = utilidades.obtenerFechaActual()
    AGREGAR NUEVO Prestamo(idPrestamo, idUsuario, isbn, fechaHoy, "", ACTIVO=VERDADERO, multa=0.0) AL vector 'prestamos'
    
    // ACTUALIZAR ESTADOS
    libros[posLibro].setCantidadDisponible(cantidadDisponible - 1)
    usuarios[posUsuario].setLibrosPrestados(librosPrestados + 1)

    guardarPrestamos(), guardarLibros(), guardarUsuarios()
    ESCRIBIR "Préstamo realizado ✅"
    LIMPIAR vectores
    RETORNAR VERDADERO
FIN FUNCION

FUNCION LOGICO SistemaBiblioteca::registrarDevolucion()
    cargarUsuarios(), cargarLibros(), cargarPrestamos()
    PEDIR idPrestamo
    
    BUSCAR posPrestamo (debe estar ACTIVO)
    SI NO encontrado ENTONCES ESCRIBIR "Préstamo no encontrado o devuelto" Y RETORNAR FALSO

    // REGISTRAR DEVOLUCIÓN
    fechaHoy = utilidades.obtenerFechaActual()
    prestamos[posPrestamo].setFechaDevolucion(fechaHoy)
    
    // CALCULAR Y APLICAR MULTA
    prestamos[posPrestamo].calcularMulta(fechaPrestamo, fechaHoy) 
    
    // MARCAR COMO DEVUELTO
    prestamos[posPrestamo].setActivo(FALSO)

    // ACTUALIZAR ESTADOS
    BUSCAR usuario y RESTAR 1 a librosPrestados
    BUSCAR libro y SUMAR 1 a cantidadDisponible

    guardarPrestamos(), guardarLibros(), guardarUsuarios()
    ESCRIBIR "Devolución registrada. Multa: " + prestamos[posPrestamo].getMulta()
    // La función original estaba incompleta en el cuerpo de C++, se completó la lógica de guardado aquí.
    LIMPIAR vectores
    RETORNAR VERDADERO
FIN FUNCION
