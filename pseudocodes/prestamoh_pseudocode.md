CLASE Prestamo
    // Atributos Privados
    PRIVADO
        CADENA idPrestamo
        CADENA idUsuario
        CADENA isbn
        CADENA fechaPrestamo
        CADENA fechaDevolucion
        LOGICO activo
        REAL multa

    // Métodos Públicos
    PUBLICO
        // Constructor con valores por defecto
        CONSTRUCTOR Prestamo(...)

        // Getters y Setters
        // ...

        // Métodos funcionales (Implementados en prestamo.cpp)
        FUNCION ESTRUCTURA tm stringAFecha(fechaStr POR REFERENCIA)
        FUNCION ENTERO calcularDiasRetraso(fecha1 POR REFERENCIA, fecha2 POR REFERENCIA)
        PROCEDIMIENTO calcularMulta(fechaPrestamo, fechaHoy) // $5 por día después de 7 días
FIN CLASE
