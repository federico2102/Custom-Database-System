#include "Dato.h"
#include <iostream>

using namespace std;

Dato::Dato(int valorNat, string valorStr, bool esNat) :
        _valorNat(valorNat), _valorStr(valorStr), _esNat(esNat) { };

bool Dato::esNat() const {
    return _esNat;
};

bool Dato::esString() const {
    return not esNat();
}

string Dato::valorStr() const {
    return _valorStr;
};

int Dato::valorNat() const {
    return _valorNat;
};


Dato datoNat(int valorNat) {
    return Dato(valorNat, "", true);
}

Dato datoStr(string valorStr) {
    return Dato(0, valorStr, false);
}

bool operator==(const Dato& d1, const Dato& d2) {
    if (d1.esNat() == d2.esNat()) {
        if (d1.esNat()) {
            return d1.valorNat() == d2.valorNat();
        } else {
            return d1.valorStr() == d2.valorStr();
        }
    }
    return false;
}

bool operator!=(const Dato& d1, const Dato& d2) {
    return !(d1 == d2);
}
