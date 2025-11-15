#include <zephyr/kernel.h>
#include "mcumgr_smp_bluetooth.h"

int main(void)
{
    printk("Hello World!\n");
    printf("Image: original SMP BLE image \n");

    start_mcumgr_smp_bluetooth();   

    return 0;     
}
