#include "reloj.h"

struct clk_s{
    uint8_t hora_actual[6];
    uint8_t tics;
    uint8_t tics_por_segundo;
    bool valida;
};

static struct clk_s instances;

clk_t ClkCreate(int tics_por_segundo){
    memset(&instances, 0, sizeof(instances));
    instances.tics_por_segundo=tics_por_segundo;
    return &instances;
}

bool ClkGetTime(clk_t reloj, uint8_t * hora, int size){
    memcpy(hora ,reloj->hora_actual, size);
    return reloj->valida;
}

bool ClkSetTime(clk_t reloj, const uint8_t * hora, int size){
    memcpy(reloj->hora_actual, hora, size);
    reloj->valida = true;
    return true;
}


/** @brief
 *
 *
*/
void ClkTick(clk_t reloj){
    reloj->tics++;
    if(reloj->tics==reloj->tics_por_segundo){
        reloj->hora_actual[5]++;
    }
    if(reloj->hora_actual[5]==10){
        reloj->hora_actual[5]=0;
        reloj->hora_actual[4]++;
    }
}
