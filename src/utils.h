#ifndef UTILS_H
#define UTILS_H

template<class T>
bool pertenece(T x, vector<T> v) {
    for (int i = 0; i < v.size(); ++i) {
        if (x == v[i]) {
            return true;
        }
    }
    return false;
}

template<class T>
bool subset(vector<T> v1, vector<T> v2) {
    for (int i = 0; i < v1.size(); ++i) {
        if (not pertenece(v1[i], v2)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool seteq(vector<T> v1, vector<T> v2) {
    return subset(v1, v2) and subset(v2, v1);
}

template <typename T>
bool igualdadConjuntos(const vector<T> v1, const vector <T> v2) {
    if(v1.size() != v2.size()) //Tienen la misma cantidad de elementos?
        return false;

    int j = 0;
    int i = 0;
    while(i<v1.size() && j < v2.size()){

        if(v1[i] == v2[j]){
            j++;
            i=0;
        }else {
            i++;
        }
    }

    return j == v2.size(); // Para todos los elementos en v2, existe uno en v1
}

#endif //UTILS_H
