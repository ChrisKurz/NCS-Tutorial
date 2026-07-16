#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(MyApp, LOG_LEVEL_DBG);

void function(void) {
   printk("function is called!\n");   

    LOG_INF("2-This is a test");
    LOG_ERR("2-ERROR: test");
    LOG_WRN("2-WARNING: test");
    LOG_DBG("2-DEBUG: test");
}