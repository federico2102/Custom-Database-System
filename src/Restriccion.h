//
// Created by Andres lasso on 28/8/17.
//

#ifndef RESTRICCION_H
#define RESTRICCION_H

#include<vector>
#include<iostream>
#include "Dato.h"
#include "utils.h"

using namespace std;

class Restriccion {

public:

    enum class OpcionBusqueda { Igual, Distinto };

    // Generador
    Restriccion(string campo, Dato valor, Restriccion::OpcionBusqueda opcion) ;

    // Observadores
    string Campo() const;
    Dato Valor() const;
    OpcionBusqueda getOpcionBusqueda() const;

    // OtrasOperaciones
    friend bool operator==(const Restriccion&, const Restriccion&);
    friend bool operator!=(const Restriccion&, const Restriccion&);

private:
    string _campo;
    Dato _valor;
    OpcionBusqueda _opcionBusqueda;

};


#endif //RESTRICCION_H
