INCLUIR "Prestamo.h"
INCLUIR LIBRERÍAS (iostream, ctime, sstream)

FUNCION ESTRUCTURA tm Prestamo::stringAFecha(fechaStr POR REFERENCIA)
    // Convierte una cadena "DD/MM/AAAA" a la estructura tm
    tm fecha
    EXTRAER dia, mes, anio DE fechaStr USANDO stringstream Y DELIMITADOR '/'
    ASIGNAR dia A fecha.tm_mday
    ASIGNAR mes - 1 A fecha.tm_mon
    ASIGNAR anio - 1900 A fecha.tm_year
    RETORNAR fecha
FIN FUNCION

FUNCION ENTERO Prestamo::calcularDiasRetraso(fecha1 POR REFERENCIA, fecha2 POR REFERENCIA)
    f1 = stringAFecha(fecha1)
    f2 = stringAFecha(fecha2)

    CONVERTIR f1 Y f2 A time_t (t1, t2)
    CALCULAR diferenciaEnSegundos = difftime(t2, t1)
    CALCULAR diferenciaEnDias = diferenciaEnSegundos / (60 * 60 * 24)
    
    RETORNAR diferenciaEnDias
FIN FUNCION

PROCEDIMIENTO Prestamo::calcularMulta(fechaPrestamo, fechaHoy)
    diasRetraso = calcularDiasRetraso(fechaPrestamo, fechaHoy)
    
    SI diasRetraso > 7 ENTONCES
        diasA_Multar = diasRetraso - 7
        multaCalculada = diasA_Multar * 5.0
        ESTE.setMulta(multaCalculada)
    SINO
        ESTE.setMulta(0.0)
    FIN SI
FIN PROCEDIMIENTO
