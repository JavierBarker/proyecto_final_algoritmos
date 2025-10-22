#include "Usuario.h"
#include <iostream>
#include <fstream>

using namespace std;

bool Usuario::puedePrestar() const
{
    return librosPrestados < 4;
}



