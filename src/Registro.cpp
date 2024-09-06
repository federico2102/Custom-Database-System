#include <iostream>
#include "Registro.h"
#include "utils.h"

using namespace std;

Registro::Registro(vector<string> campos, vector<Dato> datos)
        : _campos(campos), _datos(datos) {};


Dato Registro::dato(string campo) const {
    for (uint i = 0; i < _campos.size(); ++i) {
        if (_campos[i] == campo) {
            return _datos[i];
        }
    }
}

vector<string> Registro::campos() const {
    return _campos;
}

bool operator==(const Registro& r1, const Registro& r2) {
    vector<string> c1 = r1.campos();
    vector<string> c2 = r2.campos();
    if (not seteq(c1, c2)) {
        return false;
    }
    vector<string> campos = r1.campos();
    for (uint i = 0; i < campos.size(); ++i) {
        if (r1.dato(campos[i]) != r2.dato(campos[i])) {
            return false;
        }
    }
    return true;
}
