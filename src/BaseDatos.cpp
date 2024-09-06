//
// Created by Andres lasso on 28/8/17.
//

#include "BaseDatos.h"

using namespace std;

BaseDatos::~BaseDatos() {
    for(int i=0; i<_tablas.size(); i++){
        Tabla* _tabla = get<1>(_tablas[i]);
        delete _tabla;
    }
}

/*************************************************************************
 *  GENERADORES
 *************************************************************************/

BaseDatos::BaseDatos() {

}

void BaseDatos::AgTabla(string nombre, Tabla tabla) {
    if(!ExisteTabla(nombre)) {

        vector<string> campos(tabla.campos());
        vector<string> claves(tabla.claves());
        /** @comentario (ivan): podrían hacer una función que les de los tipos de la tabla
         * Actualización: CORREGIDO*/
        vector<Dato> tipos = dameTipos(tabla);

        Tabla *tablaPtr = new Tabla(campos, claves, tipos);
        tuple<string, Tabla*> tupla = make_pair(nombre,tablaPtr);
        _tablas.push_back(tupla);
    }

}

/**
 * Pre: ExisteTabla(tablaNombre) && PuedoAgRegistro(tablaNombre, registro)
 *
 * @param tabla
 * @param registro
 */
void BaseDatos::AgRegistro(string tablaNombre, const Registro registro) {
    Tabla* _tabla = dameTabla(tablaNombre);
    _tabla->agregarRegistro(registro);
}


/**
 * pre: ExisteTabla(tablaNombre) && CriterioValido(tablaNombre, criterio)
 *
 * @param tablaNombre
 * @param criterio
 * @return
 */
Tabla BaseDatos::Buscar(string tablaNombre, Criterio criterio ) {
    sumarCriterio(criterio);                    //Agrego el nuevo criterio a la lista de criterios usados
    Tabla *tablaBase = dameTabla(tablaNombre);

    /** Copio Tabla **/
    vector<string> campos(tablaBase->campos());
    vector<string> claves(tablaBase->claves());

    vector<Dato> tipos = dameTipos(*tablaBase);

    Tabla tablaResultante(campos,claves,tipos);
    /** END Copio Tabla **/

    /** Copio Registros **/
    vector<Registro> _registros(tablaBase->registros());
    /** END Copio Registros **/

    /** Busco **/
    for (int l=0; l<criterio.size(); ++l){
        Restriccion restriccion = criterio[l];

        vector<Registro>::iterator itReg = _registros.begin();
        while (itReg != _registros.end()){
            bool aplicaRestriccion = false;

            vector<string>::iterator itCampo = find(itReg->campos().begin(), itReg->campos().end(), restriccion.Campo());

            //if( itCampo != itReg->campos().end() ){
            //El campo esta en el registro, me fijo si aplica la restriccion
            /** @corregir (ivan): El campo no puede no estar en el registro.. Sino no se podría haber insertado en la tabla.
             * Actualización: CORREGIDO */
            if(restriccion.getOpcionBusqueda() == Restriccion::OpcionBusqueda::Igual){
                if(itReg->dato(*itCampo) == restriccion.Valor() )
                    aplicaRestriccion = true;
            }else{
                if(itReg->dato(*itCampo) != restriccion.Valor() )
                    aplicaRestriccion = true;
            }
            //}

            if(aplicaRestriccion)
                itReg++;
            else
                itReg = _registros.erase(itReg);
        }
    }

    /** END Buscar **/

    //Copio los registro a la tabla resultante..
    for(int i=0; i<_registros.size(); i++){
        tablaResultante.agregarRegistro(_registros[i]);
    }

    return tablaResultante;
}


/*************************************************************************
 *  OBSERVADORES
 *************************************************************************/

const vector<string> BaseDatos::TablasDefinidas() const {
    vector<string> ret;
    auto it = _tablas.begin(); //vector< tuple< string, Tabla*> >::const_iterator
    while(it != _tablas.end()){
        ret.push_back( get<0>(*it) );
        it++;
    }
    return ret;
}

const Tabla BaseDatos::TablaPorNombre(string tablaNombre) const {
    return *dameTabla(tablaNombre);
}

const vector< tuple< Criterio, int> > BaseDatos::CriteriosUsados() const {
    return _criteriosUsados;
}


/*************************************************************************
 *  OTRAS OPERACIONES
 *************************************************************************/

bool BaseDatos::ExisteTabla(string tablaNombre) const {
    bool ret = false;

    auto it = _tablas.begin(); //vector< tuple< string, Tabla*> >::const_iterator
    while(it != _tablas.end() && !ret){
        if(tablaNombre == get<0>(*it))
            ret = true;
        it++;
    }

    return ret;
}

/**
 * pre: ExisteTabla(tablaNombre)
 *
 * @param tablaNombre
 * @param registro
 * @return
 *
 */
bool BaseDatos::PuedoAgRegistro(string tablaNombre, Registro registro) const {
    bool _ret = true;
    Tabla *_tabla = dameTabla(tablaNombre); //Busco la tabla

    vector<string> _camposTabla = _tabla->campos();
    vector<string> _camposClave = _tabla->claves();
    vector<string> _camposRegistro = registro.campos();

    /** @corregir (ivan): no están teniendo en cuenta que podrían ser los mismos campos pero en otro orden
     * Actualización: CORREGIDO */
    if(not igualdadConjuntos(_camposTabla, registro.campos())) //OK
        _ret = false;

    if(not coincidenTiposCampos(_camposTabla, _tabla, registro, _camposRegistro)) _ret = false;

    if(not repiteClave(_tabla, registro, _camposClave)) _ret = false;

    return _ret;
}

/**
 * pre: ExisteTabla(tablaNombre)
 *
 * @param tablaNombre
 * @param criterio
 * @return
 */
bool BaseDatos::CriterioValido(string tablaNombre, Criterio criterio) const {
    int i = 0;
    int j;

    //Busco tabla asociada al nombre dado
    Tabla *tabla = dameTabla(tablaNombre);

    while(i < criterio.size()){
        j = 0;
        while(j < tabla->campos().size()) {
            if(criterio[i].Campo() == tabla->campos()[j]) {
                if(tabla->tipoCampo(tabla->campos()[j]).esNat() == criterio[i].Valor().esNat()) {
                   break;
                }else{
                    return false;
                }
            }                                          /*Si encuentro un campo de la tabla que coincida con
                                                    el campo del criterio actual, paso al siguiente criterio*/
            if(j == tabla->campos().size() - 1)
                return false;                       //Sino, el campo no se encuentra en la tabla
            j++;
        }
        i++;
    }
    return i == criterio.size();
}

/**
 * Pre: CriteriosUsados().size() > 0
 *
 * @return
 */
const Criterio BaseDatos::CriterioMasUsado() const{
    tuple<Criterio, int> masUsado = _criteriosUsados[0];

    for(int i=1; i<_criteriosUsados.size(); i++){
        if(get<1>(_criteriosUsados[i]) > get<1>(masUsado))
            masUsado = _criteriosUsados[i];
    }

    return get<0>(masUsado);
}


bool operator==(const BaseDatos& db1, const BaseDatos& db2) {
    return db1.mismasTablas(db1, db2) && db1.mismosCriteriosUsados(db1, db2);
}

bool operator!=(const BaseDatos& db1, const BaseDatos& db2) {
    return !(db1==db2);
}


/*************************************************************************
 *  OTRAS OPERACIONES (privadas)
 *************************************************************************/



/**
 * Pre: ExisteTabla(tablaNombre)
 *
 * @param tablaNombre
 * @return
 */
Tabla* BaseDatos::dameTabla(string tablaNombre) const {

    for(int i=0; i<_tablas.size(); i++){
        if(tablaNombre == get<0>(_tablas[i])){
            return get<1>(_tablas[i]);
        }
    }
}

vector<Dato> BaseDatos::dameTipos(Tabla tabla) const {
    vector<string> campos = tabla.campos();
    vector<Dato> ret;

    for(int i=0; i<campos.size(); i++){
        Dato d = tabla.tipoCampo(campos[i]);
        Dato dato(d.valorNat(),d.valorStr(),d.esNat());
        ret.push_back(dato);
    }

    return ret;
}

void BaseDatos::sumarCriterio(Criterio criterio) {
    int i;

    for(i=0; i<_criteriosUsados.size(); i++){
        /*Los criterios son conjuntos de restricciones, entonces veo que los conjuntos sean iguales*/
        if(igualdadConjuntos(get<0>(_criteriosUsados[i]), criterio)) {
            get<1>(_criteriosUsados[i])++;
            break;
        }
    }

    if(i == _criteriosUsados.size()) {
        _criteriosUsados.push_back(make_tuple(criterio, 0));
    }

}

bool BaseDatos::mismasTablas(const BaseDatos &db1, const BaseDatos &db2)const {
    if(igualdadConjuntos(db1.TablasDefinidas(), db2.TablasDefinidas())) {

        for (int k = 0; k < db1.TablasDefinidas().size(); k++)
            if (db1.TablaPorNombre(db1.TablasDefinidas()[k]) !=
                db2.TablaPorNombre(db1.TablasDefinidas()[k])) //Tablas con mismos nombres son iguales
                return false;

        return true;
    }else{
        return false;
    }
}

bool BaseDatos::mismosCriteriosUsados(const BaseDatos &db1, const BaseDatos &db2)const {
    if(db1.CriteriosUsados().size() != db2.CriteriosUsados().size()) //Tienen la misma cantidad de elementos?
        return false;

    int j = 0;
    int i = 0;
    while(i<db1.CriteriosUsados().size() && j<db2.CriteriosUsados().size()){
        int a = get<1>(db1.CriteriosUsados()[i]); //Cantidad de veces que se uso el criterio en db1
        int b = get<1>(db2.CriteriosUsados()[j]); // Cantidad de veces que se uso el criterio en db2
        if(igualdadConjuntos(get<0>(db1.CriteriosUsados()[i]), get<0>(db2.CriteriosUsados()[j])) && a == b){
            j++;
            i=0;
        }else {
            i++;
        }
    }

    return j == db2.CriteriosUsados().size(); // Para todos los elementos en v2, existe uno en v1
}

bool BaseDatos::coincidenTiposCampos(const vector<string>& _camposTabla, const Tabla* _tabla,
                                     const Registro& registro, const vector<string>& _camposRegistro)const {
    bool _ret = true;
    int i=0;
    /** @comentario (ivan): podrían hacer una función que diga si coinciden los tipos de los campos */ //OK
    while(i < _camposTabla.size() && _ret) {
        if(_tabla->tipoCampo(_camposTabla[i]).esNat() != registro.dato(_camposRegistro[i]).esNat())
            _ret = false;
        i++;
    }

    return _ret;
}

bool BaseDatos::repiteClave(const Tabla* _tabla, const Registro& registro, const vector<string>& _camposClave)const {
    bool _ret = true;
    int i=0;
    /** @comentario (ivan): podrían hacer una función que diga si el registro nuevo repite clave
     * Actualización: CORREGIDO */
    while (i < _tabla->registros().size() && _ret) {
        Registro _tablaRegistro = _tabla->registros()[i];
        if (_tablaRegistro == registro)
            _ret = false;
        else{
            int j = 0;
            for(int l=0; l<_camposClave.size() && _ret; l++){
                string _clave = _camposClave[l];
                /** @corregir (ivan): en realidad, hay que chequear que los dos registros no coincidan en TODAS las claves.
                 * Con que haya al menos una clave distinta en los dos, alcanza para poder agregarlo.
                 * Actualización: CORREGIDO */
                if(_tablaRegistro.dato(_clave) == registro.dato(_clave))
                    j++;
            }
            if(j == _camposClave.size()) _ret = false;
        }
        i++;
    }

    return _ret;
}

