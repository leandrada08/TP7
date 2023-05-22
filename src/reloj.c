#include "reloj.h"

struct clk_s{
    uint8_t hora_actual[6];
    bool valida;
};

clk_t ClkCreate(int tics_por_segundo){
    static struct clk_s self[1];
    memset(self, 0, sizeof(self));
    return self;
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
