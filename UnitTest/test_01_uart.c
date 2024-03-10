/**
 * @file test_01_uart.c
 * @author cy023
 * @date 2022.09.17
 * @brief 
 * 
 */

#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

int main()
{
    system_init();
    printf("System Boot.\n");
    printf("[test01]: sysnow ...\n");

    uint32_t sec = 0;
    while (1) {
        printf("Time: %ld sec\n", sec++);
        system_delay_ms(1000);
    }
    return 0;
}
