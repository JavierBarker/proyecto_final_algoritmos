#include "Prestamo.h"
#include <iostream>
#include <ctime>
#include <sstream>


using namespace std;


tm Prestamo::stringAFecha(string& fechaStr){
    tm fecha = {};
    int dia, mes, anio;
    char sep; // para los '/'
    stringstream ss(fechaStr);
    ss >> dia >> sep >> mes >> sep >> anio;

    fecha.tm_mday = dia;
    fecha.tm_mon = mes - 1; // meses de 0 a 11
    fecha.tm_year = anio - 1900; // años desde 1900
    fecha.tm_hour = 0;
    fecha.tm_min = 0;
    fecha.tm_sec = 0;

    return fecha;
}

int Prestamo::calcularDiasRetraso(string& fecha1, string& fecha2) {
    tm f1 = stringAFecha(fecha1);
    tm f2 = stringAFecha(fecha2);

    time_t t1 = mktime(&f1);
    time_t t2 = mktime(&f2);

    double diffSegundos = difftime(t2, t1);
    int diffDias = static_cast<int>(diffSegundos / (60 * 60 * 24));

    return diffDias;
}

void Prestamo::calcularMulta(string fechaPrestamo, string fechaHoy) {
    int diasRetraso = calcularDiasRetraso(fechaPrestamo, fechaHoy);
    double calcularMulta = static_cast<double>((diasRetraso - 7) * 5);
    this->setMulta(calcularMulta);
}