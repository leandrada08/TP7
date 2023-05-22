#include "unity.h"
#include "reloj.h"

/*void test_inicializacion(void){
    TEST_FAIL_MESSAGE("FUNCIONA!!!");
}*/

//Prueba para que cuando inicie el reloj este en 00:00 y con hora invalida

void test_reloj_arranca_con_hora_invalida(void){
    static const uint8_t ESPERADO[]={0, 0, 0, 0, 0, 0}; //Definimos la hora que esperamos
    uint8_t hora[6] = {0xFF};
    clk_t reloj = ClkCreate(5); //Creamos un reloj, esperando que este se inicialice en 0 y que cambie el segundo luego de 5 T del micro
    TEST_ASSERT_FALSE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); //Comparamos nuestra hora con esperado, el 6 es la cantidad de componentes que compararemos
}


//Al ajustar la hora el reloj queda en hora y es valida

void test_ajustar_hora(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 0, 0}; //Definimos la hora que esperamos
    uint8_t hora[6];
    clk_t reloj = ClkCreate(5); //Creamos un reloj, esperando que este se inicialice en 0 y que cambie el segundo luego de 5 T del micro
    TEST_ASSERT_TRUE(ClkSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

