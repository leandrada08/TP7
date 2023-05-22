#include "unity.h"
#include "reloj.h"

// Hacer test para ver si devuelve falso set

/*void test_inicializacion(void){
    TEST_FAIL_MESSAGE("FUNCIONA!!!");
}*/

#define TICS_POR_SEGUNDO 5

#define SimulateSecond(VALUE,funcion2)\
    for(int count = 0; count<VALUE;count ++){\
        for(int index=0;index<TICS_POR_SEGUNDO;index++){\
            funcion2;\
        }\
    }


static clk_t reloj;
static uint8_t hora[6];


void setUp(void){
    static const uint8_t INICIAL[]={1, 2, 3, 4};
    reloj = ClkCreate(TICS_POR_SEGUNDO);
    TEST_ASSERT_TRUE(ClkSetTime(reloj, INICIAL, sizeof(INICIAL)));
}


//Prueba para que cuando inicie el reloj este en 00:00 y con hora invalida

void test_reloj_arranca_con_hora_invalida(void){
    static const uint8_t ESPERADO[]={0, 0, 0, 0, 0, 0}; //Definimos la hora que esperamos
    uint8_t hora[6] = {0xFF};
    reloj = ClkCreate(TICS_POR_SEGUNDO);
    TEST_ASSERT_FALSE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); //Comparamos nuestra hora con esperado, el 6 es la cantidad de componentes que compararemos
}


//Al ajustar la hora el reloj queda en hora y es valida

void test_ajustar_hora(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 0, 0}; //Definimos la hora que esperamos
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}


void test_incrementar_second_unidad(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 0, 1}; //Definimos la hora que esperamos
    SimulateSecond(1, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora))); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}


void test_incrementar_second_decenas(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 1, 0}; //Definimos la hora que esperamos
    SimulateSecond(10, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora))); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}


