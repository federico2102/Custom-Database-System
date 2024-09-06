//
// Created by Andres lasso on 28/8/17.
//

#ifndef BASEDATOS_H
#define BASEDATOS_H

#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include "Dato.h"
#include "Registro.h"
#include "Tabla.h"
#include "Restriccion.h"

using namespace std;

using Criterio = vector< Restriccion >;

class BaseDatos {

public:

    ~BaseDatos();

    // Generadores:
    BaseDatos();
    void AgTabla(string nombre, Tabla tabla);
    void AgRegistro(string tablaNombre, Registro registro);
    /** @corregir (ivan): Busqueda es un generador, ya que modifica el resultado del observador CriteriosUsados */ //OK
    Tabla Buscar(string tablaNombre, Criterio criterio);

    // Observadores:
    const vector<string> TablasDefinidas() const;
    const Tabla TablaPorNombre(string tablaNombre) const;
    const vector< tuple< Criterio, int> > CriteriosUsados() const;

    // Otras operaciones:
    bool ExisteTabla(string tablaNombre) const;
    bool PuedoAgRegistro(string tablaNombre, Registro registro) const;
    bool CriterioValido(string tablaNombre, Criterio criterio) const;

    const Criterio CriterioMasUsado() const;

    friend bool operator==(const BaseDatos&, const BaseDatos&);
    friend bool operator!=(const BaseDatos&, const BaseDatos&);

private:
    vector< tuple< string, Tabla*> > _tablas;
    vector< tuple< Criterio, int> > _criteriosUsados;

    // Auxiliares
    Tabla* dameTabla(string tablaNombre) const;
    vector<Dato> dameTipos(Tabla tabla) const;
    void sumarCriterio(Criterio criterio);
    bool mismasTablas(const BaseDatos &db1, const BaseDatos &db2)const;
    bool mismosCriteriosUsados(const BaseDatos &db1, const BaseDatos &db2)const;
    bool coincidenTiposCampos(const vector<string>& _camposTabla, const Tabla *_tabla, const Registro& registro, const vector<string>& _camposRegistro)const;
    bool repiteClave(const Tabla *_tabla, const Registro& registro, const vector<string>& _camposClave)const;
};


#endif //BASEDATOS_H
