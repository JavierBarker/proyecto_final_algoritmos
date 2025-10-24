INCLUIR "Utilidades.h"
INCLUIR LIBRERÍAS (iostream, string, conio.h, ctime)

FUNCION LOGICO Utilidades::autenticar(usuario POR REFERENCIA, contrasena POR REFERENCIA)
    CONST CADENA usuarioAdmin = "admin"
    CONST CADENA passAdmin = "admin"
    RETORNAR (usuario == passAdmin Y contrasena == passAdmin)
FIN FUNCION

PROCEDIMIENTO Utilidades::limpiarPantallaValidar()
    ESCRIBIR "Presione cualquier tecla para continuar..."
    ESPERAR TECLA (_getch())
    
    // Lógica condicional para limpiar la pantalla (Windows/Unix)
    SI DEFINIDO _WIN32 ENTONCES
        EJECUTAR COMANDO "cls"
    SINO
        EJECUTAR COMANDO "clear"
    FIN SI
FIN PROCEDIMIENTO

PROCEDIMIENTO Utilidades::limpiarPantalla()
    // Lógica condicional para limpiar la pantalla (Windows/Unix)
    SI DEFINIDO _WIN32 ENTONCES
        EJECUTAR COMANDO "cls"
    SINO
        EJECUTAR COMANDO "clear"
    FIN SI
FIN PROCEDIMIENTO

FUNCION CADENA Utilidades::obtenerFechaActual()
    OBTENER tiempo_t actual
    CONVERTIR a estructura tm local
    
    ENTERO dia = fechaLocal.tm_mday
    ENTERO mes = fechaLocal.tm_mon + 1
    ENTERO anio = fechaLocal.tm_year + 1900
    
    // Formato DD/MM/YYYY, añadiendo cero inicial si es necesario
    CADENA fechaFormateada = (SI dia < 10 ENTONCES "0" + dia SINO dia) + "/" +
                            (SI mes < 10 ENTONCES "0" + mes SINO mes) + "/" +
                            anio
                            
    RETORNAR fechaFormateada
FIN FUNCION
