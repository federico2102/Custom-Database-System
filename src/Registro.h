#ifndef _REGISTRO_H
#define _REGISTRO_H

#include<vector>
#include<iostream>
#include "Dato.h"

using namespace std;

class Registro {

public:

    // @generador
    Registro(vector<string> campos, vector<Dato> datos);

    // @observador
    Dato dato(string campo) const;

    // @observador
    vector<string> campos() const;

private:

    vector<string> _campos;
    vector<Dato> _datos;

    friend bool operator==(const Registro&, const Registro&);
};


#endif //_REGISTRO_H
