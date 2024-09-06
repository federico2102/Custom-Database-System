#include "gtest/gtest.h"
#include "../src/Tabla.h"
#include "../src/utils.h"

using namespace std;

class TablaTests : public ::testing::Test {

protected:
    TablaTests() : t({"LU", "Año", "Nombre", "Carrera"},
                     { "LU", "Año" },
                     { datoNat(0), datoNat(0), datoStr(""), datoStr("")}),
                   t2({"Cod", "Carrera"},
                      {"Cod"},
                      {datoNat(0), datoStr("")}) {};

    Tabla t;
    Tabla t2;

};

TEST(tabla_test, crear) {
    Tabla t({ "LU", "Año", "Nombre", "Carrera" },
            {"LU", "Año"},
            {datoNat(0), datoNat(0), datoStr(""), datoStr("")});
    Tabla t2({ "Cod", "Carrera" },
             {"Cod"},
             {datoNat(0), datoStr("")});
};

TEST_F(TablaTests, campos) {
    EXPECT_EQ(t.campos(), vector<string>({"LU", "Año", "Nombre", "Carrera"}));
    EXPECT_EQ(t2.campos(), vector<string>({"Cod", "Carrera"}));
};

TEST_F(TablaTests, claves) {
    EXPECT_EQ(t.claves(), vector<string>({"LU", "Año"}));
    EXPECT_EQ(t2.claves(), vector<string>({"Cod"}));
}

TEST_F(TablaTests, tipoCampo) {
    EXPECT_EQ(t.tipoCampo("LU").esNat(), true);
    EXPECT_EQ(t.tipoCampo("LU").esString(), false);
    EXPECT_EQ(t.tipoCampo("Nombre").esNat(), false);
    EXPECT_EQ(t.tipoCampo("Nombre").esString(), true);
}

TEST_F(TablaTests, registros) {
    Tabla t3({}, {}, {});
    EXPECT_EQ(t3.registros().size(), 0);

    vector<string> campos = {"LU", "Año", "Nombre", "Carrera"};
    Registro r1(campos, {datoNat(181), datoNat(2017), datoStr("March"), datoStr("Comp")});
    Registro r2(campos, {datoNat(182), datoNat(2015), datoStr("Ariana"), datoStr("Mate")});
    Registro r3(campos, {datoNat(12), datoNat(2005), datoStr("Juan"), datoStr("Biol")});

    EXPECT_EQ(t.registros().size(), 0);
    t.agregarRegistro(r1);
    EXPECT_EQ(t.registros().size(), 1);
    EXPECT_EQ(t.registros().front(), r1);
    t.agregarRegistro(r2);
    EXPECT_EQ(t.registros().size(), 2);
    EXPECT_TRUE(pertenece(r1, t.registros()));
    EXPECT_TRUE(pertenece(r2, t.registros()));
    EXPECT_FALSE(pertenece(r3, t.registros()));
    t.agregarRegistro(r3);
    EXPECT_EQ(t.registros().size(), 3);
    EXPECT_TRUE(pertenece(r1, t.registros()));
    EXPECT_TRUE(pertenece(r2, t.registros()));
    EXPECT_TRUE(pertenece(r3, t.registros()));
}

TEST_F(TablaTests, igobs) {
    Tabla t1({"LU"}, {"LU"}, {datoStr("")});
    Tabla t2({"LU"}, {"LU"}, {datoStr("")});
    EXPECT_EQ(t1, t2); // Claves == campos

    t1 = Tabla({"LU", "Nombre"}, {"LU"}, {datoStr(""), datoStr("")});
    t2 = Tabla({"LU", "Nombre"}, {"LU"}, {datoStr(""), datoStr("")});
    EXPECT_EQ(t1, t2); // Claves != campos

    t2 = Tabla({"LU", "Nombre"}, {"Nombre"}, {datoStr(""), datoStr("")});
    EXPECT_NE(t1, t2); // Cambio clave

    t1 = Tabla({"Nombre", "LU"}, {"LU"}, {datoStr(""), datoStr("")});
    t2 = Tabla({"LU", "Nombre"}, {"LU"}, {datoStr(""), datoStr("")});
    EXPECT_EQ(t1, t2); //  Campos distinto roden

    t1 = Tabla({"Nombre", "LU"}, {"Nombre"}, {datoStr(""), datoStr("")});
    t2 = Tabla({"LU", "Nombre"}, {"Nombre"}, {datoStr(""), datoStr("")});
    EXPECT_EQ(t1, t2); //  Campos distinto orden + otra clave

    t1 = Tabla({"Nombre", "LU"}, {"Nombre"}, {datoStr(""), datoNat(0)});
    t2 = Tabla({"LU", "Nombre"}, {"Nombre"}, {datoStr(""), datoStr("")});
    EXPECT_NE(t1, t2); //  Campos distinto orden + distinto tipo no clave

    t1 = Tabla({"Nombre", "LU"}, {"LU"}, {datoStr(""), datoNat(0)});
    t2 = Tabla({"LU", "Nombre"}, {"LU"}, {datoStr(""), datoStr("")});
    EXPECT_NE(t1, t2); //  Campos distinto orden + distinto tipo clave

    t1 = Tabla({"Nombre", "LU"}, {"Nombre"}, {datoStr(""), datoStr("")});
    t2 = Tabla({"LU", "Nombre"}, {"Nombre"}, {datoStr(""), datoStr("")});
    t1.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("March"), datoStr("64/9")}));
    EXPECT_NE(t1, t2); // Distintos registros

    t2.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("March"), datoStr("64/9")}));
    EXPECT_EQ(t1, t2); // Igualo registros

    t1.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("Gerva"), datoStr("65/9")}));
    EXPECT_NE(t1, t2); // Distintos registros

    t2.agregarRegistro(Registro({"LU", "Nombre"}, {datoStr("65/9"), datoStr("Gerva")}));
    EXPECT_EQ(t1, t2); // Igualo registros pero con campos al reves

    t1.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("Ana"), datoStr("100/10")}));
    t1.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("Luis"), datoStr("101/10")}));
    t2.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("Luis"), datoStr("101/10")}));
    t2.agregarRegistro(Registro({"Nombre", "LU"}, {datoStr("Ana"), datoStr("100/10")}));
    EXPECT_EQ(t1, t2); // Agrego registros en otro orden
}
