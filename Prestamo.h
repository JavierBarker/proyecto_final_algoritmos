#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <ctime>

using namespace std;

class Prestamo {
private:
    string idPrestamo;
    string idUsuario;
    string isbn;
    string fechaPrestamo;
    string fechaDevolucion;
    bool   activo;
    double multa;

public:

    Prestamo(string idPrestamo = "", string idUsuario = "", string isbn = "", string fechaPrestamo = "", string fechaDevolucion = "", bool activo = true, double multa = 0.0)
        : idPrestamo(idPrestamo), idUsuario(idUsuario), isbn(isbn), fechaPrestamo(fechaPrestamo), fechaDevolucion(fechaDevolucion),activo(activo), multa(multa) {}

    // Getters
    string getIdPrestamo() { return idPrestamo; }
    string getIdUsuario() { return idUsuario; }
    string getISBN() { return isbn; }
    string getFechaPrestamo() { return fechaPrestamo; }
    string getFechaDevolucion() { return fechaDevolucion; }
    bool   getActivo() { return activo; }
    double getMulta() { return multa; }

    // Setters
    void setIdPrestamo(string& id) { idPrestamo = id; }
    void setIdUsuario(string& usuario) { idUsuario = usuario; }
    void setISBN(string& bookIsbn) { isbn = bookIsbn; }
    void setFechaPrestamo(string& fechaP) { fechaPrestamo = fechaP; }
    void setFechaDevolucion(string& fechaD) { fechaDevolucion = fechaD; }
    void setActivo(bool estado) { activo = estado; }
    void setMulta(double m) { multa = m; }


    // Métodos para calcular días de retraso y multas
    tm stringAFecha( string& fechaStr);
    int calcularDiasRetraso( string& fecha1, string& fecha2);
    void calcularMulta(string fechaPrestamo, string fechaHoy); // $5 por día
};

#endif