#include "reloj.h"

struct clk_s{
    uint8_t hora_actual[6];
    uint8_t tics;
    uint8_t tics_por_segundo;
    bool hora_valida;

    uint8_t alarma[6];
    bool alarma_valida;
};

static struct clk_s instances;

clk_t ClkCreate(int tics_por_segundo){
    memset(&instances, 0, sizeof(instances));
    instances.tics_por_segundo=tics_por_segundo;
    return &instances;
}

bool ClkGetTime(clk_t reloj, uint8_t * hora, int size){
    memcpy(hora ,reloj->hora_actual, size);
    return reloj->hora_valida;
}


bool ClkSetTime(clk_t reloj, const uint8_t * hora, int size){
    bool mal=0;
    if(hora[5]>9 || hora[4]>5){//<! Verifico que la hora no sea una hora invalida
        mal=1;
    }
    if(hora[3]>9 || hora[2]>5){
        mal=1;
    }
    if(hora[1]>9 || hora[0]>2){
        mal=1;
    }
    if(hora[0]==2 && hora[1]>3){
        mal=1;
    }
    if(mal==0){
        memcpy(reloj->hora_actual, hora, size);
        reloj->hora_valida = true;
        return true;
    }else{
        return false;
    }
}


/** @brief
 *
 *
*/
void ClkTick(clk_t reloj){
    reloj->tics++;
    if(reloj->tics==reloj->tics_por_segundo){
        reloj->hora_actual[5]++;
        reloj->tics=0;
    }
    if(reloj->hora_actual[5]==10){
        reloj->hora_actual[5]=0;
        reloj->hora_actual[4]++;
    }
    if(reloj->hora_actual[4]==6){
        reloj->hora_actual[4]=0;
        reloj->hora_actual[3]++;
    }
    if(reloj->hora_actual[3]==10){
        reloj->hora_actual[3]=0;
        reloj->hora_actual[2]++;
    }
    if(reloj->hora_actual[2]==6){
        reloj->hora_actual[2]=0;
        reloj->hora_actual[1]++;
    }
    if(reloj->hora_actual[1]==10){
        reloj->hora_actual[1]=0;
        reloj->hora_actual[0]++;
    }
    if(reloj->hora_actual[0]==2 && reloj->hora_actual[1]==4){
        reloj->hora_actual[0]=0;
        reloj->hora_actual[1]=0;
    }


}


bool ClkGetAlarma(clk_t reloj,uint8_t * hora, int size){
    memcpy(hora ,reloj->alarma, size);
    return reloj->alarma_valida;
}


void ClkSetAlarma(clk_t reloj,const uint8_t * hora, int size){
    memcpy(reloj->alarma, hora, size);
    reloj->alarma_valida = true;
}