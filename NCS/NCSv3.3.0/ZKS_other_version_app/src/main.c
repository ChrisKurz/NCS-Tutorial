#include <zephyr/kernel.h>
#include "app_version.h"

int main(void)
{
     printk("Hello World!\n");

     printk("Application version (VERSION_MAJOR|VERSION_MINOR|PATCHLEVEL|VERSION_TWEAK): %d\n", APPVERSION);
     printk("Application version number (VERSION_MAJOR|VERSION_MINOR|PATCHLEVEL): %d\n", APP_VERSION_NUMBER);
     printk("Application version major (VERSION_MAJOR): %i\n", APP_VERSION_MAJOR);
     printk("Application version minor (VERSION_MINOR): %i\n", APP_VERSION_MINOR);
     printk("Application version Patchlevel (PATCHLEVEL): %i\n", APP_PATCHLEVEL);
     printk("Application version string (VERSION_MAJOR.VERSION_MINOR.PATCHLEVEL.EXTRAVERSION): %s\n", APP_VERSION_STRING);
     // APP_BUILD_VERSION is not used here. 

     return 0;
}
