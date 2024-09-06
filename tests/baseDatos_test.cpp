//
// Created by Andres lasso on 29/8/17.
//
#include "gtest/gtest.h"
#include "../src/BaseDatos.h"
#include "../src/utils.h"

using namespace std;

class BaseDatosTest : public ::testing::Test {

protected:
    BaseDatosTest() : db(), db1(),  db2(){

        Tabla t1({ "LU", "Año", "Nombre", "Carrera" },  {"LU", "Año"},  {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
        Tabla t2({ "Cod", "Carrera" },  {"Cod"},  {datoNat(0), datoStr("")});

        db1.AgTabla("Alumnos", t1);
        db1.AgTabla("Carreras", t2);

        db2.AgTabla("Alumnos", t1);

    };

    BaseDatos db;
    BaseDatos db1;
    BaseDatos db2;
};

TEST_F(BaseDatosTest, crear_y_agTabla) {
    BaseDatos _db = BaseDatos();

    Tabla t({ "LU", "Año", "Nombre", "Carrera" },  {"LU", "Año"},  {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    Tabla t2({ "Cod", "Carrera" },  {"Cod"},  {datoNat(0), datoStr("")});

    _db.AgTabla("Alumnos", t);
    _db.AgTabla("Carreras", t2);
}

TEST_F(BaseDatosTest, existeTabla){
    EXPECT_FALSE(db.ExisteTabla("Alumnos"));
    EXPECT_TRUE(db1.ExisteTabla("Alumnos"));
    EXPECT_TRUE(db1.ExisteTabla("Carreras"));

    EXPECT_TRUE(db2.ExisteTabla("Alumnos"));
    EXPECT_FALSE(db2.ExisteTabla("Carreras"));
}

TEST_F(BaseDatosTest, tablas){
    vector<string> tablas;
    vector<string> tablas1;
    vector<string> tablas2;

    tablas1.push_back("Alumnos");
    tablas1.push_back("Carreras");
    tablas2.push_back("Alumnos");

    EXPECT_EQ(db.TablasDefinidas(), tablas);
    EXPECT_EQ(db1.TablasDefinidas(), tablas1);
    EXPECT_EQ(db2.TablasDefinidas(), tablas2);
}

TEST_F(BaseDatosTest, puedoAgRegistro) {
    vector<string> campos1 = {"LU", "Año", "Nombre", "Carrera"};
    vector<string> campos2 = {"LU", "Carrera"};
    vector<string> campos3 = { "Cod", "Carrera" };


    Registro r1(campos1, {datoNat(181), datoNat(2017), datoStr("March"), datoStr("Computacion")});
    Registro r2(campos1, {datoNat(182), datoNat(2015), datoStr("Ariana"), datoStr("Matematicas")});
    Registro r3(campos2, {datoNat(12), datoStr("Biologia")});
    Registro r4(campos3, {datoNat(11122), datoStr("AED2")});

    EXPECT_TRUE(db1.PuedoAgRegistro("Alumnos",r1));
    EXPECT_TRUE(db1.PuedoAgRegistro("Alumnos",r2));
    EXPECT_FALSE(db1.PuedoAgRegistro("Alumnos", r3));
    EXPECT_TRUE(db1.PuedoAgRegistro("Carreras", r4));

    db1.AgRegistro("Alumnos", r1);
    EXPECT_FALSE(db1.PuedoAgRegistro("Alumnos",r1));
    EXPECT_TRUE(db1.PuedoAgRegistro("Alumnos",r2));

    db1.AgRegistro("Alumnos", r2);
    EXPECT_FALSE(db1.PuedoAgRegistro("Alumnos",r2));

    //Probando Claves
    Registro r5(campos1, {datoNat(181), datoNat(2016), datoStr("March"), datoStr("Fisica")}); //LU Clave
    Registro r6(campos1, {datoNat(183), datoNat(2017), datoStr("Andres"), datoStr("Biologia")}); //Año Clave
    Registro r7(campos3, {datoNat(12), datoStr("Quimica")}); //Cod Clave
    Registro r8(campos2, {datoNat(12), datoStr("Quimica")});

    EXPECT_TRUE(db1.PuedoAgRegistro("Alumnos",r5));
    EXPECT_TRUE(db1.PuedoAgRegistro("Alumnos",r6));
    EXPECT_TRUE(db1.PuedoAgRegistro("Carreras",r7));
    EXPECT_FALSE(db1.PuedoAgRegistro("Carreras",r8));
}

TEST_F(BaseDatosTest, CriterioValido){
    //Tabla t({ "LU", "Año", "Nombre", "Carrera" },  {"LU", "Año"},  {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    //Tabla t2({ "Cod", "Carrera" },  {"Cod"},  {datoNat(0), datoStr("")});

    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random1("Departamento", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random2("Carrera", datoNat(0), Restriccion::OpcionBusqueda::Distinto);

    Criterio criterio1;
    Criterio criterio2;

    criterio1.push_back(rest_lu);
    criterio2.push_back(rest_lu);
    EXPECT_TRUE(db1.CriterioValido("Alumnos",criterio1));

    criterio1.push_back(rest_anio);
    criterio2.push_back(rest_anio);
    EXPECT_TRUE(db1.CriterioValido("Alumnos",criterio1));

    criterio1.push_back(rest_random1);
    EXPECT_FALSE(db1.CriterioValido("Alumnos",criterio1));

    criterio2.push_back(rest_random2);
    EXPECT_FALSE(db1.CriterioValido("Alumnos",criterio2));

}

TEST_F(BaseDatosTest, agRegistro) {
    vector<string> campos1 = {"LU", "Año", "Nombre", "Carrera"};
    vector<string> campos3 = { "Cod", "Carrera"};


    Registro r1(campos1, {datoNat(181), datoNat(2017), datoStr("March"), datoStr("Computacion")});
    Registro r2(campos1, {datoNat(182), datoNat(2015), datoStr("Ariana"), datoStr("Matematicas")});
    Registro r4(campos3, {datoNat(11122), datoStr("AED2")});

    db1.AgRegistro("Alumnos", r1);
    db1.AgRegistro("Carreras", r4);

    //Utilizo buscar pero sin Criterios y restricciones!
    Criterio sincriterios;

    Tabla tabla1 = db1.Buscar("Alumnos", sincriterios);
    Tabla tabla2 = db1.Buscar("Carreras", sincriterios);

    vector<Registro> registros1 = tabla1.registros();
    vector<Registro> registros2 = tabla2.registros();

    EXPECT_TRUE(pertenece(r1, registros1));
    EXPECT_FALSE(pertenece(r2, registros1));

    EXPECT_TRUE(pertenece(r4, registros2));

    db1.AgRegistro("Alumnos", r2);
    tabla1 = db1.Buscar("Alumnos", sincriterios);
    registros1 = tabla1.registros();

    EXPECT_TRUE(pertenece(r1, registros1));
    EXPECT_TRUE(pertenece(r2, registros1));
}

TEST_F(BaseDatosTest, igualdadBasesDatos) {

    BaseDatos db4 = BaseDatos();
    BaseDatos db5 = BaseDatos();

    Tabla t({ "LU", "Año", "Nombre", "Carrera" },  {"LU", "Año"},  {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    Tabla t1({ "Cod", "Carrera" },  {"Cod"},  {datoNat(0), datoStr("")});
    Tabla t2({ "NoSeQuePoner", "Fruta" },  {"NoSeQuePoner"},  {datoNat(7), datoStr("sarasa")});

    vector<string> campos1 = {"LU", "Año", "Nombre", "Carrera"};
    vector<string> campos3 = { "Cod", "Carrera"};


    Registro r1(campos1, {datoNat(181), datoNat(2017), datoStr("March"), datoStr("Computacion")});
    Registro r2(campos1, {datoNat(182), datoNat(2015), datoStr("Ariana"), datoStr("Matematicas")});
    Registro r4(campos3, {datoNat(11122), datoStr("AED2")});

    db4.AgTabla("Alumnos", t);
    db4.AgTabla("Carreras", t1);
    db5.AgTabla("Carreras", t1);

    db4.AgRegistro("Alumnos", r1);
    db4.AgRegistro("Carreras", r4);
    db5.AgRegistro("Carreras", r4);

    EXPECT_FALSE(db4 == db5); //db5 no tiene la tabla alumnos

    db5.AgTabla("Alumnos", t);
    db5.AgRegistro("Alumnos", r1);

    EXPECT_TRUE(db4 == db5); //Mismas tablas pero en distintos indices de sus respectivos vectores de tablas

    db5.AgRegistro("Alumnos", r2);

    EXPECT_FALSE(db4 == db5); //A db4 le falta el registro r2

    db4.AgRegistro("Alumnos", r2);
    db5.AgTabla("Fruta", t2);

    EXPECT_FALSE(db4 == db5);

    db4.AgTabla("Fruta", t2);

    EXPECT_TRUE(db4 == db5);

    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random1("Departamento", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random2("Carrera", datoNat(0), Restriccion::OpcionBusqueda::Distinto);

    Criterio criterio1;
    Criterio criterio2;
    Criterio criterio3;
    Criterio criterio4;

    criterio1.push_back(rest_lu);
    criterio2.push_back(rest_nombre);
    criterio3.push_back(rest_lu);
    criterio3.push_back(rest_nombre);

    //EXPECT_TRUE(db4.CriterioValido("Alumnos", criterio2));

    db4.Buscar("Alumnos", criterio1);
    db4.Buscar("Alumnos", criterio2);

    EXPECT_FALSE(db4 == db5);

    db5.Buscar("Alumnos", criterio3);

    EXPECT_FALSE(db4 == db5);

    db4.Buscar("Alumnos", criterio3);
    db5.Buscar("Alumnos", criterio2);
    db5.Buscar("Alumnos", criterio1);

    EXPECT_TRUE(db4 == db5);

    criterio2.push_back(rest_lu);
    criterio4.push_back(rest_lu);
    criterio4.push_back(rest_nombre);

    db4.Buscar("Alumnos", criterio2);
    db5.Buscar("Alumnos", criterio4);

    EXPECT_TRUE(db4 == db5); //Mismos criterios, distinto orden de las restricciones

    db5.Buscar("Carreras", criterio4);

    EXPECT_FALSE(db4 == db5);

    EXPECT_TRUE(db5.CriterioMasUsado() == criterio4);

}

TEST_F(BaseDatosTest, CriterioMasUsadoTest){

    Restriccion rest_lu("LU", datoNat(182), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_anio("Año", datoNat(18), Restriccion::OpcionBusqueda::Igual);
    Restriccion rest_nombre("Nombre", datoStr("March"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_carrera("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random1("Departamento", datoStr("Computacion"), Restriccion::OpcionBusqueda::Distinto);
    Restriccion rest_random2("Carrera", datoNat(0), Restriccion::OpcionBusqueda::Distinto);

    Criterio criterio1;
    Criterio criterio2;
    Criterio criterio3;
    Criterio criterio4;

    criterio1.push_back(rest_lu);
    criterio2.push_back(rest_nombre);
    criterio2.push_back(rest_lu);
    criterio3.push_back(rest_anio);
    criterio3.push_back(rest_nombre);
    criterio4.push_back(rest_lu);
    criterio4.push_back(rest_nombre);
//Criterios 2 y 4 son el mismo pero con restricciones en distinto orden

    db1.Buscar("Alumnos", criterio1);
    db1.Buscar("Alumnos", criterio1);
    db1.Buscar("Alumnos", criterio2);
    db1.Buscar("Alumnos", criterio2);
    db1.Buscar("Alumnos", criterio1);

    EXPECT_TRUE(igualdadConjuntos(db1.CriterioMasUsado(), criterio1));

    db1.Buscar("Alumnos", criterio2);
    db1.Buscar("Carreras", criterio2);

    EXPECT_TRUE(igualdadConjuntos(db1.CriterioMasUsado(), criterio2));
    EXPECT_TRUE(igualdadConjuntos(db1.CriterioMasUsado(), criterio4));
    EXPECT_FALSE(igualdadConjuntos(db1.CriterioMasUsado(), criterio3));

    db1.Buscar("Carreras", criterio3);
    db1.Buscar("Carreras", criterio3);
    db1.Buscar("Carreras", criterio3);
    db1.Buscar("Carreras", criterio3);
    db1.Buscar("Carreras", criterio3);

    EXPECT_TRUE(igualdadConjuntos(db1.CriterioMasUsado(), criterio3));
    EXPECT_FALSE(igualdadConjuntos(db1.CriterioMasUsado(),criterio2));

    db1.Buscar("Alumnos", criterio4);
    db1.Buscar("Carreras", criterio4);

    EXPECT_TRUE(igualdadConjuntos(db1.CriterioMasUsado(), criterio2));
    EXPECT_FALSE(igualdadConjuntos(db1.CriterioMasUsado(), criterio1));
}


TEST_F(BaseDatosTest, Buscar){
    /**
     * OBSERVACION:
     * Para este Test no voy a usar puedoAgRegistro y voy a omitir que no se pueden agregar registros con claves
     * iguales, dado que solo quiero testear bien Buscar. En Test anteriores se probó la correcta funcionalidad
     * de puedoAgRegistro.
     */

    vector<string> campos1 = {"LU", "Año", "Nombre", "Carrera"};
    vector<string> campos2 = { "Cod", "Carrera"};
    vector<string> claves1 = {"LU", "Año"};
    vector<string> claves2 = {"Cod"};
    vector<Dato> tipos1 = {datoNat(0), datoNat(0), datoStr(""), datoStr("")};
    vector<Dato> tipos2 = {datoNat(0), datoStr("")};

    Tabla t1(campos1,  claves1,  tipos1);
    Tabla t2(campos2,  claves2,  tipos2);

    //             Campos:      LU              Año             Nombre                  Carrera
    Registro t1_r1(campos1, {datoNat(123), datoNat(2017), datoStr("Andres"),    datoStr("Computacion")});
    Registro t1_r2(campos1, {datoNat(123), datoNat(2017), datoStr("Jorge"),     datoStr("Matematicas")});
    Registro t1_r3(campos1, {datoNat(714), datoNat(2017), datoStr("Pedro"),     datoStr("Biologia")});
    Registro t1_r4(campos1, {datoNat(714), datoNat(2015), datoStr("Andres"),    datoStr("Biologia")});
    Registro t1_r5(campos1, {datoNat(182), datoNat(2015), datoStr("Facundo"),   datoStr("Computacion")});
    Registro t1_r6(campos1, {datoNat(182), datoNat(2015), datoStr("Federico"),  datoStr("Ingenieria")});
    Registro t1_r7(campos1, {datoNat(929), datoNat(2010), datoStr("Federico"),  datoStr("Fisica")});
    Registro t1_r8(campos1, {datoNat(283), datoNat(2011), datoStr("Juan"),      datoStr("Quimica")});
    Registro t1_r9(campos1, {datoNat(328), datoNat(2012), datoStr("Eduardo"),   datoStr("Agronomia")});

    //              Campos:       Cod              Carrera
    Registro t2_r1(campos2, {datoNat(01101), datoStr("Computacion")});
    Registro t2_r2(campos2, {datoNat(12345), datoStr("Matematicas")});
    Registro t2_r3(campos2, {datoNat(23248), datoStr("Biologia")});
    Registro t2_r4(campos2, {datoNat(123),   datoStr("Ingenieria")});
    Registro t2_r5(campos2, {datoNat(1435),  datoStr("Fisica")});
    Registro t2_r6(campos2, {datoNat(1530),  datoStr("Quimica")});
    Registro t2_r7(campos2, {datoNat(1530),  datoStr("Agronomia")});
    Registro t2_r8(campos2, {datoNat(23248), datoStr("Abogacia")});
    Registro t2_r9(campos2, {datoNat(9284),  datoStr("Medicina")});


    /*** **** ****  Sin Criterios **** **** **** ***/
    Criterio sincriterios;

    Tabla tabla1 = db1.Buscar("Alumnos", sincriterios);
    Tabla tabla2 = db1.Buscar("Carreras", sincriterios);

    vector<Registro> registros1 = tabla1.registros();
    vector<Registro> registros2 = tabla2.registros();

    EXPECT_EQ(registros1.size(), 0);
    EXPECT_EQ(registros2.size(), 0);

    EXPECT_EQ(t1, tabla1);
    EXPECT_EQ(t2, tabla2);

    /*** **** ****  Lleno la Base de datos **** **** **** ***/

    db1.AgRegistro("Alumnos",t1_r1);
    db1.AgRegistro("Alumnos",t1_r2);
    db1.AgRegistro("Alumnos",t1_r3);
    db1.AgRegistro("Alumnos",t1_r4);
    db1.AgRegistro("Alumnos",t1_r5);
    db1.AgRegistro("Alumnos",t1_r6);
    db1.AgRegistro("Alumnos",t1_r7);
    db1.AgRegistro("Alumnos",t1_r8);
    db1.AgRegistro("Alumnos",t1_r9);

    db1.AgRegistro("Carreras",t2_r1);
    db1.AgRegistro("Carreras",t2_r2);
    db1.AgRegistro("Carreras",t2_r3);
    db1.AgRegistro("Carreras",t2_r4);
    db1.AgRegistro("Carreras",t2_r5);
    db1.AgRegistro("Carreras",t2_r6);
    db1.AgRegistro("Carreras",t2_r7);
    db1.AgRegistro("Carreras",t2_r8);
    db1.AgRegistro("Carreras",t2_r9);


    /*** **** ****  Sin Criterios **** **** **** ***/

    tabla1 = db1.Buscar("Alumnos", sincriterios);
    tabla2 = db1.Buscar("Carreras", sincriterios);

    registros1 = tabla1.registros();
    registros2 = tabla2.registros();

    vector<Registro> test_registro1 = {t1_r1,t1_r2,t1_r3,t1_r4,t1_r5,t1_r6,t1_r7,t1_r8,t1_r9};
    vector<Registro> test_registro2 = {t2_r1,t2_r2,t2_r3,t2_r4,t2_r5,t2_r6,t2_r7,t2_r8,t2_r9};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));
    EXPECT_TRUE(igualdadConjuntos(registros2,test_registro2));

    Tabla tabla1_test1(campos1,  claves1,  tipos1);
    Tabla tabla2_test1(campos2,  claves2,  tipos2);
    tabla1_test1.agregarRegistro(t1_r1);
    tabla1_test1.agregarRegistro(t1_r2);
    tabla1_test1.agregarRegistro(t1_r3);
    tabla1_test1.agregarRegistro(t1_r4);
    tabla1_test1.agregarRegistro(t1_r5);
    tabla1_test1.agregarRegistro(t1_r6);
    tabla1_test1.agregarRegistro(t1_r7);
    tabla1_test1.agregarRegistro(t1_r8);
    tabla1_test1.agregarRegistro(t1_r9);

    tabla2_test1.agregarRegistro(t2_r1);
    tabla2_test1.agregarRegistro(t2_r2);
    tabla2_test1.agregarRegistro(t2_r3);
    tabla2_test1.agregarRegistro(t2_r4);
    tabla2_test1.agregarRegistro(t2_r5);
    tabla2_test1.agregarRegistro(t2_r6);
    tabla2_test1.agregarRegistro(t2_r7);
    tabla2_test1.agregarRegistro(t2_r8);
    tabla2_test1.agregarRegistro(t2_r9);

    EXPECT_EQ(tabla1, tabla1_test1);
    EXPECT_EQ(tabla2, tabla2_test1);


    /*** **** **** Criterios 1 **** **** **** ***/

    Restriccion criterio1_rest1("LU", datoNat(123), Restriccion::OpcionBusqueda::Igual);
    Restriccion criterio1_rest2("Cod", datoNat(23248), Restriccion::OpcionBusqueda::Igual);

    Criterio criterio1 = {criterio1_rest1};
    Criterio criterio2 = {criterio1_rest2};

    tabla1 = db1.Buscar("Alumnos", criterio1);
    tabla2 = db1.Buscar("Carreras", criterio2);

    registros1 = tabla1.registros();
    registros2 = tabla2.registros();

    test_registro1 = {t1_r1,t1_r2};
    test_registro2 = {t2_r3,t2_r8};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));
    EXPECT_TRUE(igualdadConjuntos(registros2,test_registro2));

    Tabla tabla1_test2(campos1,  claves1,  tipos1);
    Tabla tabla2_test2(campos2,  claves2,  tipos2);
    tabla1_test2.agregarRegistro(t1_r1);
    tabla1_test2.agregarRegistro(t1_r2);

    tabla2_test2.agregarRegistro(t2_r3);
    tabla2_test2.agregarRegistro(t2_r8);

    EXPECT_EQ(tabla1, tabla1_test2);
    EXPECT_EQ(tabla2, tabla2_test2);


    /*** **** **** Criterios 2 **** **** **** ***/

    Restriccion criterio2_rest1("Nombre", datoStr("Andres"), Restriccion::OpcionBusqueda::Igual);
    Restriccion criterio2_rest2("Carrera", datoStr("Computacion"), Restriccion::OpcionBusqueda::Igual);

    criterio1 = {criterio2_rest1};
    criterio2 = {criterio2_rest2};

    tabla1 = db1.Buscar("Alumnos", criterio1);
    tabla2 = db1.Buscar("Carreras", criterio2);

    registros1 = tabla1.registros();
    registros2 = tabla2.registros();

    test_registro1 = {t1_r1,t1_r4};
    test_registro2 = {t2_r1};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));
    EXPECT_TRUE(igualdadConjuntos(registros2,test_registro2));

    Tabla tabla1_test3(campos1,  claves1,  tipos1);
    Tabla tabla2_test3(campos2,  claves2,  tipos2);
    tabla1_test3.agregarRegistro(t1_r1);
    tabla1_test3.agregarRegistro(t1_r4);
    tabla2_test3.agregarRegistro(t2_r1);

    EXPECT_EQ(tabla1, tabla1_test3);
    EXPECT_EQ(tabla2, tabla2_test3);


    /*** **** **** Criterios 3 **** **** **** ***/

    Restriccion criterio3_rest1("Año", datoNat(2017), Restriccion::OpcionBusqueda::Igual);
    Restriccion criterio3_rest2("Nombre", datoStr("Jorge"), Restriccion::OpcionBusqueda::Igual);

    criterio1 = {criterio3_rest1};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {t1_r1,t1_r2,t1_r3};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test4(campos1,  claves1,  tipos1);
    tabla1_test4.agregarRegistro(t1_r1);
    tabla1_test4.agregarRegistro(t1_r2);
    tabla1_test4.agregarRegistro(t1_r3);

    EXPECT_EQ(tabla1, tabla1_test4);

    //otro criterio..
    criterio1 = {criterio3_rest1, criterio3_rest2};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {t1_r2};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test5(campos1,  claves1,  tipos1);
    tabla1_test5.agregarRegistro(t1_r2);

    EXPECT_EQ(tabla1, tabla1_test5);



    /*** **** **** Criterios 4 **** **** **** ***/

    Restriccion criterio4_rest1("Año", datoNat(2017), Restriccion::OpcionBusqueda::Distinto);
    Restriccion criterio4_rest2("Nombre", datoStr("Federico"), Restriccion::OpcionBusqueda::Igual);
    Restriccion criterio4_rest3("LU", datoNat(929), Restriccion::OpcionBusqueda::Distinto);
    Restriccion criterio4_rest4("Carrera", datoStr("Fisica"), Restriccion::OpcionBusqueda::Igual);

    criterio1 = {criterio4_rest1};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {t1_r4,t1_r5,t1_r6,t1_r7,t1_r8,t1_r9};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test6(campos1,  claves1,  tipos1);
    tabla1_test6.agregarRegistro(t1_r4);
    tabla1_test6.agregarRegistro(t1_r5);
    tabla1_test6.agregarRegistro(t1_r6);
    tabla1_test6.agregarRegistro(t1_r7);
    tabla1_test6.agregarRegistro(t1_r8);
    tabla1_test6.agregarRegistro(t1_r9);

    EXPECT_EQ(tabla1, tabla1_test6);

    //otro criterio..
    criterio1 = {criterio4_rest1, criterio4_rest2};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {t1_r6,t1_r7};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test7(campos1,  claves1,  tipos1);
    tabla1_test7.agregarRegistro(t1_r6);
    tabla1_test7.agregarRegistro(t1_r7);

    EXPECT_EQ(tabla1, tabla1_test7);


    //otro criterio..
    criterio1 = {criterio4_rest1, criterio4_rest2, criterio4_rest3};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {t1_r6};

    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test8(campos1,  claves1,  tipos1);
    tabla1_test8.agregarRegistro(t1_r6);

    EXPECT_EQ(tabla1, tabla1_test8);

    //otro criterio..
    criterio1 = {criterio4_rest1, criterio4_rest2, criterio4_rest3, criterio4_rest4};
    tabla1 = db1.Buscar("Alumnos", criterio1);
    registros1 = tabla1.registros();

    test_registro1 = {};
    EXPECT_TRUE(igualdadConjuntos(registros1,test_registro1));

    Tabla tabla1_test9(campos1,  claves1,  tipos1);
    EXPECT_EQ(tabla1, tabla1_test9);


    /*** **** **** Fin Buscar **** **** **** ***/
}