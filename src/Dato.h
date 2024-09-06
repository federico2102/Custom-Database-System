#ifndef DATO_H
#define DATO_H

#include <string>

using namespace std;

class Dato {

public:

    /**
     * @brief Constructor de dato
     *
     * @generador
     *
     * Esta no es la forma más elegante de implementar el TAD dato como un
     * módulo. Para hacerlo de forma prolija es necesario utilizar
     * contenidos por fuera de la materia como herencia o polimorfismo.
     */
    Dato(int valorNat, string valorStr, bool esNat);

    // @observador
    bool esNat() const;

    // @observador
    bool esString() const;

    // @observador
    string valorStr() const;

    // @observador
    int valorNat() const;

private:

    int _valorNat;
    string _valorStr;
    bool _esNat;

};

Dato datoNat(int valorNat);

Dato datoStr(string valorStr);

bool operator==(const Dato&, const Dato&);

bool operator!=(const Dato&, const Dato&);

#endif // DATO_H
