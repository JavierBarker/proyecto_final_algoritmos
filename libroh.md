CLASE Libro
    // Atributos Privados
    PRIVADO
        CADENA isbn
        CADENA titulo
        CADENA autor
        ENTERO anio
        CADENA categoria
        ENTERO cantidadDisponible

    // Métodos Públicos
    PUBLICO
        // Constructores
        CONSTRUCTOR Libro()
        CONSTRUCTOR Libro(isbn, titulo, autor, anio, categoria, cantidad)

        // Getters
        FUNCION CADENA obtenerISBN()
        FUNCION CADENA obtenerTitulo()
        FUNCION CADENA obtenerAutor()
        FUNCION ENTERO obtenerAnio()
        FUNCION CADENA obtenerCategoria()
        FUNCION ENTERO obtenerCantidadDisponible()

        // Setters
        PROCEDIMIENTO establecerISBN(isbn)
        PROCEDIMIENTO establecerTitulo(titulo)
        PROCEDIMIENTO establecerAutor(autor)
        PROCEDIMIENTO establecerAnio(anio)
        PROCEDIMIENTO establecerCategoria(categoria)
        PROCEDIMIENTO establecerCantidadDisponible(cantidad)

        // Métodos Funcionales
        FUNCION LOGICO estaDisponible()
        PROCEDIMIENTO mostrarInformacion()

        // Métodos de Archivo (Estáticos)
        PROCEDIMIENTO ESTATICO registrarLibro()
        PROCEDIMIENTO ESTATICO listarLibros()
        PROCEDIMIENTO ESTATICO buscarLibro()
        PROCEDIMIENTO ESTATICO eliminarLibro()
FIN CLASE
