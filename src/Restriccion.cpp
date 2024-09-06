//
// Created by Andres lasso on 28/8/17.
//

#include "Restriccion.h"

Restriccion::Restriccion(string campo, Dato valor, OpcionBusqueda opcion)
        : _campo(campo) ,_valor(valor), _opcionBusqueda(opcion){}


string Restriccion::Campo() const {
    return _campo;
}

Dato Restriccion::Valor() const {
    return _valor;
}

Restriccion::OpcionBusqueda Restriccion::getOpcionBusqueda() const {
    return _opcionBusqueda;
}

bool operator==(const Restriccion& reg1, const Restriccion& reg2) {
    return (reg1._campo==reg2._campo) && (reg1._valor==reg2._valor) && (reg1._opcionBusqueda==reg2._opcionBusqueda);
}

bool operator!=(const Restriccion& reg1, const Restriccion& reg2) {
    return !(reg1==reg2);
}