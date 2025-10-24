INICIO FUNCIÓN PRINCIPAL main()

    // Configuración inicial
    CONFIGURAR CONSOLA PARA SOPORTE UTF-8 (SetConsoleOutputCP)

    // Declaración de variables
    INSTANCIA sistema DE SistemaBiblioteca
    INSTANCIA utilidades DE Utilidades
    CADENA usuario, contrasena

    REPETIR
        // Mostrar cabecera de autenticación
        MOSTRAR "╔════════... SISTEMA DE GESTIÓN DE BIBLIOTECA ...════════╗"
        
        // Pedir credenciales
        ESCRIBIR "║ Ingrese el Usuario: "
        LEER LINEA usuario
        ESCRIBIR "║ Ingrese su contraseña: "
        LEER LINEA contrasena
        MOSTRAR "╚══════════════════════════════════════════════════════════════╝"

        SI utilidades.autenticar(usuario, contrasena) ES VERDADERO ENTONCES
            sistema.mostrarMenu() // Acceso concedido, iniciar menú
        SINO
            ESCRIBIR "\nUsuario o contraseña incorrectos. 🚨"
            utilidades.limpiarPantallaValidar() // Limpiar y esperar tecla
        FIN SI
        
    MIENTRAS utilidades.autenticar(usuario, contrasena) NO ES VERDADERO 
    // Nota: El bucle se repite hasta que la autenticación sea exitosa.

    RETORNAR 0
FIN FUNCIÓN
