#include <string>

using namespace std;

class Prestamo
{
private:
    string idPrestamo;
    string idUsuario;
    string isbn;
    string fechaPrestamo;
    string fechaDevolucion;
    bool activo;
    double multa;

public:
    // Métodos para calcular días de retraso y multas
    int calcularDiasRetraso() const;
    double calcularMulta() const; // $5 por día
};