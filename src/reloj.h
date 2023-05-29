#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct clk_s * clk_t;



/** @brief Funcion para crear un reloj
 * @param tics_por_segundo: Cuantos tics del micro seran un segundo en nuestro reloj
 * @return Nos devuelve un puntero al reloj creado
 * Esta funcion nos inicia un espacio del tamanio clk_s con 0
*/
clk_t ClkCreate(int tics_por_segundo);


/** @brief Funcion para ver la hora de un reloj
 * @param clk_t reloj: Puntero al reloj que necesitamos ver la hora
 * @param uint8_t hora: Vector donde la funcion nos devolvera la hora
 * @param int size: Tamanio de la hora que queremos ver
 * @return Nos devuelve 1 si la hora es valida o 0 si es invalida
 *
*/
bool ClkGetTime(clk_t reloj, uint8_t * hora, int size);


/** @brief Funcion para modificar la hora del reloj
 * Esta funcion nos devuelve 1 o 0 si el reloj es invalido o valido
 * @param clk_t reloj
 * @param uint8_t hora
 * @param int size
 * @return bool 
 *
*/
bool ClkSetTime(clk_t reloj, const uint8_t * hora, int size);



/** @brief Funcion para contar segundos,
 * Le mandamos el reloj y nos cuenta 1 segundo en el reloj dado
 * @param: clk_t reloj
 *
*/
void ClkTick(clk_t reloj);

/**
 * @brief Funcion para ver la hora de la alarma
 * 
 * @param reloj 
 * @param hora 
 * @param sizeof 
 * @return true Si la alarma esta activada(si ya fue configurada)
 * @return false Si la alarma esta desactiva(si no fue configurada)
 */
bool ClkGetAlarma(clk_t reloj,uint8_t * hora, int size);

/**
 * @brief 
 * 
 * @param reloj 
 * @param hora 
 * @param size 
 */
void ClkSetAlarma(clk_t reloj,const uint8_t * hora, int size);