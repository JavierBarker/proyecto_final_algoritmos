INCLUIR "Libro.h"
INCLUIR LIBRERÍAS DE ENTRADA/SALIDA/FICHEROS/VECTOR/MANIPULACIÓN

// CONSTRUCTORES
PROCEDIMIENTO Libro::Libro()
    // Constructor por defecto (No hace nada)
FIN PROCEDIMIENTO

PROCEDIMIENTO Libro::Libro(isbn, titulo, autor, anio, categoria, cantidad)
    ESTE.isbn = isbn
    ESTE.titulo = titulo
    ESTE.autor = autor
    ESTE.anio = anio
    ESTE.categoria = categoria
    ESTE.cantidadDisponible = cantidad
FIN PROCEDIMIENTO

// GETTERS (Devuelven el valor del atributo)
// [Se omiten por ser triviales: obtenerISBN() retorna isbn, etc.]

// SETTERS (Asignan el valor al atributo)
// [Se omiten por ser triviales: establecerISBN(isbn) asigna isbn al atributo this.isbn, etc.]

// MÉTODOS FUNCIONALES
FUNCION LOGICO Libro::estaDisponible()
    RETORNAR cantidadDisponible > 0
FIN FUNCION

PROCEDIMIENTO Libro::mostrarInformacion()
    ESCRIBIR "\nISBN: " + isbn
    ESCRIBIR "\nTítulo: " + titulo
    ESCRIBIR "\nAutor: " + autor
    ESCRIBIR "\nAño: " + anio
    ESCRIBIR "\nCategoría: " + categoria
    ESCRIBIR "\nCantidad disponible: " + cantidadDisponible
FIN PROCEDIMIENTO

// MÉTODOS ESTÁTICOS DE GESTIÓN DE FICHEROS
FUNCION ESTATICA VECTOR<Libro> cargarLibros()
    VECTOR<Libro> libros
    ABRIR ARCHIVO "libros.txt" EN MODO LECTURA
    SI NO ARCHIVO ESTÁ ABIERTO ENTONCES
        RETORNAR libros // Vector vacío
    FIN SI

    MIENTRAS LEER DE ARCHIVO: isbn, titulo, autor, anio, categoria, cantidad (separados por '|')
        AGREGAR NUEVO Libro(isbn, titulo, autor, anio, categoria, cantidad) A libros
    FIN MIENTRAS

    CERRAR ARCHIVO
    RETORNAR libros
FIN FUNCION

PROCEDIMIENTO ESTATICO guardarLibros(libros)
    ABRIR ARCHIVO "libros.txt" EN MODO ESCRITURA (SOBREESCRIBIR)
    PARA CADA libro EN libros HACER
        ESCRIBIR EN ARCHIVO: libro.getISBN() + "|" + libro.getTitulo() + "|" + ... + "\n"
    FIN PARA
    CERRAR ARCHIVO
FIN PROCEDIMIENTO

// MÉTODOS CRUD
PROCEDIMIENTO Libro::registrarLibro()
    PEDIR isbn, titulo, autor, anio, categoria, cantidad
    ABRIR ARCHIVO "libros.txt" EN MODO AÑADIR
    ESCRIBIR EN ARCHIVO: isbn + "|" + titulo + "|" + ... + "\n"
    CERRAR ARCHIVO
    ESCRIBIR "Libro registrado exitosamente."
FIN PROCEDIMIENTO

PROCEDIMIENTO Libro::listarLibros()
    libros = cargarLibros()
    SI libros ESTÁ VACÍO ENTONCES
        ESCRIBIR "No hay libros registrados."
        RETORNAR
    FIN SI

    ESCRIBIR "=== Lista de Libros ==="
    PARA CADA libro EN libros HACER
        libro.mostrarInformacion()
    FIN PARA
FIN PROCEDIMIENTO

PROCEDIMIENTO Libro::buscarLibro()
    libros = cargarLibros()
    SI libros ESTÁ VACÍO ENTONCES
        ESCRIBIR "No hay libros registrados."
        RETORNAR
    FIN SI

    PEDIR busqueda (título, autor o ISBN)
    LOGICO encontrado = FALSO

    PARA CADA libro EN libros HACER
        SI libro.getISBN() == busqueda O libro.getTitulo() == busqueda O libro.getAutor() == busqueda ENTONCES
            libro.mostrarInformacion()
            encontrado = VERDADERO
        FIN SI
    FIN PARA

    SI NO encontrado ENTONCES
        ESCRIBIR "No se encontró ningún libro con ese dato."
    FIN SI
FIN PROCEDIMIENTO

PROCEDIMIENTO Libro::eliminarLibro()
    libros = cargarLibros()
    SI libros ESTÁ VACÍO ENTONCES
        ESCRIBIR "No hay libros registrados."
        RETORNAR
    FIN SI

    PEDIR isbnEliminar
    LOGICO eliminado = FALSO
    VECTOR<Libro> nuevos

    PARA CADA libro EN libros HACER
        SI libro.getISBN() NO ES IGUAL A isbnEliminar ENTONCES
            AGREGAR libro A nuevos
        SINO
            eliminado = VERDADERO
        FIN SI
    FIN PARA

    SI eliminado ENTONCES
        guardarLibros(nuevos)
        ESCRIBIR "Libro eliminado correctamente."
    SINO
        ESCRIBIR "No se encontró un libro con ese ISBN."
    FIN SI
FIN PROCEDIMIENTO
