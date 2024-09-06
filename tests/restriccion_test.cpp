//
// Created by Andres lasso on 29/8/17.
//

#include "gtest/gtest.h"
#include "../src/Dato.h"
#include "../src/Registro.h"
#include "../src/Restriccion.h"
#include <vector>

using namespace std;

TEST(restriccion_test, generadores) {
    Restriccion("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
}

TEST(restriccion_test, campos) {
    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);

    EXPECT_EQ(rest_lu.Campo(), "LU");
    EXPECT_EQ(rest_anio.Campo(), "Año");
    EXPECT_EQ(rest_nombre.Campo(), "Nombre");
    EXPECT_EQ(rest_carrera.Campo(), "Carrera");
}

TEST(restriccion_test, valores){
    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);

    EXPECT_EQ(rest_lu.Valor(), datoNat(182));
    EXPECT_EQ(rest_anio.Valor(), datoNat(18));
    EXPECT_EQ(rest_nombre.Valor(), datoStr("March"));
    EXPECT_EQ(rest_carrera.Valor(), datoStr("Computacion"));
}


TEST(restriccion_test, opcionBusqueda){
    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);

    EXPECT_EQ(rest_lu.getOpcionBusqueda(), Restriccion::OpcionBusqueda::Igual);
    EXPECT_EQ(rest_anio.getOpcionBusqueda(), Restriccion::OpcionBusqueda::Igual);
    EXPECT_EQ(rest_nombre.getOpcionBusqueda(), Restriccion::OpcionBusqueda::Distinto);
    EXPECT_EQ(rest_carrera.getOpcionBusqueda(), Restriccion::OpcionBusqueda::Distinto);
}

TEST(restriccion_test, ig_obs){
    Restriccion rest1("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest2("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);

    // Iguales
    EXPECT_TRUE(rest1 == rest2);

    // Distintos
    EXPECT_FALSE(rest1 != rest2);

    // Distinto OpBusqueda
    Restriccion rest3("LU", datoNat(182), Restriccion::OpcionBusqueda::Distinto);
    EXPECT_FALSE(rest1 == rest3);

    // Distinto tipo
    Restriccion rest4("LU", datoNat(112), Restriccion::OpcionBusqueda::Igual);
    EXPECT_FALSE(rest1 == rest4);
    Restriccion rest5("LU", datoStr("182"), Restriccion::OpcionBusqueda::Igual);
    EXPECT_FALSE(rest1 == rest5);

    // Distinto campo
    Restriccion rest6("DNI", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    EXPECT_FALSE(rest1 == rest6);

    // Distinto todo
    Restriccion rest7("Nombre", datoStr("Carlos"), Restriccion::OpcionBusqueda::Distinto);
    EXPECT_FALSE(rest1 == rest7);
    EXPECT_TRUE(rest1 != rest7);

}