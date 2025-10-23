#include "Libro.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Libro::estaDisponible() const {
    return cantidadDisponible > 0;
}



