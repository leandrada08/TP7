#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct clk_s * clk_t;

clk_t ClkCreate(int tics_por_segundo);

bool ClkGetTime(clk_t reloj, uint8_t * hora, int size);

bool ClkSetTime(clk_t reloj, const uint8_t * hora, int size);
