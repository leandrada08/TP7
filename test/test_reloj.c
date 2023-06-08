#include "unity.h"
#include "reloj.h"
#include "main.c"


/*
Requerimientos:
• La librería deberá proporcionar una función para posponer la alarma una cantidad arbitraria
de minutos.
• La librería deberá manejar todas las horas como un arreglo de bytes en formato BCD sin
compactar, con la decena de horas en la primera posición y la unidad de los segundos en la
última posición del vector.
Pruebas:
- La funcion para posponer la alarmr, genera mueve la hora de la alarma una cantidad arbitraria de minutos
- La funcion para posponer alarma, no modifica la hora original de la alarma
- La funcion para porponer alarma, frena el buzzer
- La funcion posponer alarma solo se activa cuando esta sonando la alarma

*/


#define TICS_POR_SEGUNDO 5

#define SimulateSecond(VALUE,funcion2)\
    for(int count = 0; count<VALUE;count ++){\
        for(int index=0;index<TICS_POR_SEGUNDO;index++){\
            funcion2;\
        }\
    }

static bool ocurrio_evento_suena;

void RegistraEventoAlarma(clk_t reloj){
        ocurrio_evento_suena=true;
}

static clk_t reloj;
static uint8_t hora[6];


void setUp(void){
    static const uint8_t INICIAL[]={1, 2, 3, 4, 0, 0};
    ocurrio_evento_suena=false;
    reloj = ClkCreate(TICS_POR_SEGUNDO,RegistraEventoAlarma);
    TEST_ASSERT_TRUE(ClkSetTime(reloj, INICIAL, sizeof(INICIAL)));
}


//Prueba para que cuando inicie el reloj este en 00:00 y con hora invalida
void test_reloj_arranca_con_hora_invalida(void){
    static const uint8_t ESPERADO[]={0, 0, 0, 0, 0, 0}; //Definimos la hora que esperamos
    uint8_t hora[6] = {0xFF};
    reloj = ClkCreate(TICS_POR_SEGUNDO,RegistraEventoAlarma);
    TEST_ASSERT_FALSE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6); //Comparamos nuestra hora con esperado, el 6 es la cantidad de componentes que compararemos
}


//Al ajustar la hora el reloj queda en hora y es valida
void test_ajustar_hora(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 0, 0}; //Definimos la hora que esperamos
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, 6)); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

//Test para verificar si set nos vuelve 0 cuando la hora es invalida
void test_hora_invalida(void){
    static const uint8_t HORAMALA[]={3, 4, 7, 10, 6, 10};
    TEST_ASSERT_FALSE(ClkSetTime(reloj, HORAMALA, sizeof(HORAMALA)));
}

//Incrementa unidades de segundo?
void test_incrementar_second_unidad(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 0, 1}; //Definimos la hora que esperamos
    SimulateSecond(1, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora))); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

// Incrementa decenas de segundo?
void test_incrementar_second_decenas(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 4, 1, 0}; //Definimos la hora que esperamos
    SimulateSecond(10, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora))); //Usamos la funcion ClkGetTime que le tenemos que enviar el reloj que usaremos, el vector donde nos colcoara la hora y cuantas componentes tiene este
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}


// Incrementa unidades de minutos?
void test_incrementar_minutos_unidad(void){
    static const uint8_t ESPERADO[]={1, 2, 3, 5, 0, 0}; 
    SimulateSecond(60, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

// Incrementa decenas de minutos?
void test_incrementar_minutos_decenas(void){
    static const uint8_t ESPERADO[]={1, 2, 4, 4, 0, 0}; 
    SimulateSecond(60*10, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

// Incrementa unidades de hora?
void test_incrementar_hora_unidad(void){
    static const uint8_t ESPERADO[]={1, 3, 3, 4, 0, 0}; 
    SimulateSecond(60*10*6, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}


// Incrementa decenas de horas?
void test_incrementar_hora_decenas(void){
    static const uint8_t ESPERADO[]={2, 2, 3, 4, 0, 0}; 
    SimulateSecond(60*10*6*10, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}



// Pasa bien de 23:59 a 00:00?
void test_incrementar_dia(void){
    static const uint8_t ESPERADO[]={0, 0, 0, 0, 0, 0}; 
    static const uint8_t INICIAL[]={2, 3, 5, 9, 5, 9};
    TEST_ASSERT_TRUE(ClkSetTime(reloj, INICIAL, sizeof(INICIAL)));
    SimulateSecond(1, ClkTick(reloj));
    TEST_ASSERT_TRUE(ClkGetTime(reloj, hora, sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, sizeof(ESPERADO));
}

// Ajustar alarma
void test_ajustar_alarma(void){
    static const uint8_t ESPERADO[]={2, 3, 4, 5, 0, 1}; 
    uint8_t hora[6] = {0xFF};
    ClkSetAlarma(reloj, ESPERADO, sizeof(ESPERADO));
    ClkGetAlarma(reloj, hora, 6); 
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Al configurar la alarma, comienza activa?
void test_alarma_activa(void){
    static const uint8_t ESPERADO[]={2, 3, 4, 5, 0, 1}; 
    uint8_t hora[6] = {0xFF};
    ClkSetAlarma(reloj, ESPERADO, sizeof(ESPERADO));
    TEST_ASSERT_TRUE(ClkGetAlarma(reloj, hora, 6));
}

// Desactivar alarma
void test_alarma_desactivar(void){
    static const uint8_t ESPERADO[]={2, 3, 4, 5, 0, 1}; 
    uint8_t hora[6] = {0xFF};
    ClkSetAlarma(reloj, ESPERADO, sizeof(ESPERADO));
    ClkActivateAlarma(reloj,0);
    TEST_ASSERT_FALSE(ClkGetAlarma(reloj, hora, 6));
}

// Activar alarma
void test_alarma_activar(void){
    static const uint8_t ESPERADO[]={2, 3, 4, 5, 0, 1}; 
    uint8_t hora[6] = {0xFF};
    ClkSetAlarma(reloj, ESPERADO, sizeof(ESPERADO));
    ClkActivateAlarma(reloj,0);
    TEST_ASSERT_FALSE(ClkGetAlarma(reloj, hora, 6));
    ClkActivateAlarma(reloj,1);
    TEST_ASSERT_TRUE(ClkGetAlarma(reloj, hora, 6)); 
}



// Suena la alarma si son iguales
void test_alarma_suena(void){
    static const uint8_t Alarma[]={1,2,3,5,0,0};
    ocurrio_evento_suena=false;
    ClkSetAlarma(reloj,Alarma,sizeof(Alarma));
    SimulateSecond(60, ClkTick(reloj));
    TEST_ASSERT_TRUE(ocurrio_evento_suena);
}

// No suena alarma si son distintos
void test_alarma_no_suena(void){
    static const uint8_t Alarma[]={1,2,3,4,0,3};
    ocurrio_evento_suena=false;
    ClkSetAlarma(reloj,Alarma,sizeof(Alarma));
    SimulateSecond(1, ClkTick(reloj));
    TEST_ASSERT_FALSE(ocurrio_evento_suena);
}


// Alarma no suena si esta desactivada
void test_alarma_no_suena_desactivada(void){
    static const uint8_t Alarma[]={1,2,3,5,0,0};
    ocurrio_evento_suena=false;
    ClkSetAlarma(reloj,Alarma,sizeof(Alarma));
    ClkActivateAlarma(reloj,0);
    SimulateSecond(60, ClkTick(reloj));
    TEST_ASSERT_FALSE(ocurrio_evento_suena);
}


// Se pospone una cantidad arbitraria de minutos
void test_alarma_pospone_n_minutos(void){
    static const uint8_t Alarma[]={1,2,3,5,0,0};
    uint8_t hora[6] = {0xFF};
    static const uint8_t Alarma_pospuesta[]={1,2,4,5,0,0};
    uint8_t posponer = 10;
    ocurrio_evento_suena=false;
    ClkSetAlarma(reloj,Alarma,sizeof(Alarma));
    SimulateSecond(60, ClkTick(reloj));
    PosponerAlarma(reloj,posponer);
    ClkGetAlarma(reloj,hora, 6); 
    TEST_ASSERT_EQUAL_UINT8_ARRAY(hora, Alarma_pospuesta, sizeof(Alarma));
}