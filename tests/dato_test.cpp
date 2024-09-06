#include "gtest/gtest.h"

#include "../src/Dato.h"

TEST(dato_test, generadores) {
    Dato(5, "", true);
    Dato(0, "hola", false);
}

TEST(dato_test, esNat) {
    EXPECT_EQ(Dato(5, "hola", true).esNat(), true);
    EXPECT_EQ(Dato(100, "chau", true).esNat(), true);
    EXPECT_EQ(Dato(10, "", false).esNat(), false);
    EXPECT_EQ(Dato(5, "hola", false).esNat(), false);
}

TEST(dato_test, esString) {
    EXPECT_NE(Dato(5, "hola", true).esString(), true);
    EXPECT_NE(Dato(100, "chau", true).esString(), true);
    EXPECT_NE(Dato(10, "", false).esString(), false);
    EXPECT_NE(Dato(5, "hola", false).esString(), false);
}

TEST(dato_test, valores) {
    EXPECT_EQ(Dato(10, "", true).valorNat(), 10);
    EXPECT_EQ(Dato(5, "hola", true).valorNat(), 5);
    EXPECT_EQ(Dato(100, "chau", true).valorNat(), 100);
    EXPECT_EQ(Dato(10, "", false).valorStr(), "");
    EXPECT_EQ(Dato(5, "hola", false).valorStr(), "hola");
    EXPECT_EQ(Dato(100, "chau", false).valorStr(), "chau");
}

TEST(dato_test, igobs) {
    EXPECT_EQ(Dato(5, "", true), Dato(5, "", true));
    EXPECT_EQ(Dato(5, "hola", true), Dato(5, "chau", true));
    EXPECT_NE(Dato(10, "hola", true), Dato(5, "hola", true));
    EXPECT_NE(Dato(5, "", false), Dato(5, "", true));

    EXPECT_EQ(Dato(5, "hola", false), Dato(5, "hola", false));
    EXPECT_EQ(Dato(1, "hola", false), Dato(5, "hola", false));
    EXPECT_NE(Dato(5, "holas", false), Dato(5, "hola", false));
    EXPECT_NE(Dato(5, "hola", true), Dato(5, "hola", false));
}

TEST(dato_test, shortcuts) {
    EXPECT_EQ(datoNat(5), Dato(5, "", true));
    EXPECT_EQ(datoNat(5), Dato(5, "hola", true));
    EXPECT_NE(datoNat(10), Dato(5, "hola", true));
    EXPECT_NE(datoNat(5), Dato(5, "hola", false));

    EXPECT_EQ(datoStr("hola"), Dato(5, "hola", false));
    EXPECT_EQ(datoStr("hola"), Dato(10, "hola", false));
    EXPECT_NE(datoStr(""), Dato(5, "hola", false));
    EXPECT_NE(datoStr("hola"), Dato(5, "hola", true));
}
