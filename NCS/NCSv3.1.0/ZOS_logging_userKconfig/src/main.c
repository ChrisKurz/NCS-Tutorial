#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/*
 * The following CONFIGs from prj.conf control the log messages:
 * - CONFIG_MYAPP_LOG_ENABLED 
 *          0: logging messages are disabled. Use Log_Level None
 *          1: logging messages are enabled
 * - CONFIG_MYAPP_LOG_LEVEL 
 *          severity level of the logging messages that are to be output
 */
#if IS_ENABLED(CONFIG_MYAPP_LOG_ENABLED) 
    #define LOG_LEVEL CONFIG_MYAPP_LOG_LEVEL
#else
    #define LOG_LEVEL 0
#endif
LOG_MODULE_REGISTER(MyApp, LOG_LEVEL);

int main(void)
{
     printk("Hello World!\n");

     LOG_INF("1-This is a test");
     LOG_ERR("1-ERROR: test");
     LOG_WRN("1-WARNING: test");
     LOG_DBG("1-DEBUG: test");

     return 0;
}