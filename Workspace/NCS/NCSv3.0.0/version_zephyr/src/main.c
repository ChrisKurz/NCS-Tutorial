#include <zephyr/kernel.h>

#include <version.h>

int main(void)
{
     uint32_t kernel_version;
     uint8_t  Version_Major;
     uint8_t  Version_Minor;
     uint8_t  Version_Patch;

     printk("Hello World!\n");

     printk("USING ZEPHYR'S SYSTEM FUNCTIONS:\n");
     kernel_version=sys_kernel_version_get();
     Version_Major=SYS_KERNEL_VER_MAJOR(kernel_version);
     Version_Minor=SYS_KERNEL_VER_MINOR(kernel_version);
     Version_Patch=SYS_KERNEL_VER_PATCHLEVEL(kernel_version);
     printk("Zephyr Version: %d\n",kernel_version);
     printk("Zephyr Version - Major: %i\n",Version_Major);
     printk("Zephyr Version - Minor: %i\n",Version_Minor);
     printk("Zephyr Version - Patchlevel: %i\n",Version_Patch);
     printk("\n");

     printk("----------------------------------------------------------\n");
     printk("USING VERSION.H HEADER FILE:\n");
     printk("Zephyr Version Code: %d\n", ZEPHYR_VERSION_CODE);
     printk("Zephyr Kernel Version Major: %i\n", KERNEL_VERSION_MAJOR);
     printk("Zephyr Kernel Version Minor: %i\n", KERNEL_VERSION_MINOR);
     printk("Zephyr Kernel Version Patch-Level: %i\n", KERNEL_PATCHLEVEL);
     printk("Zephyr Kernel Version Sting: %s\n",KERNEL_VERSION_STRING);
     printk("Nordic Semiconductor's Zephyr build version: %s\n", STRINGIFY(BUILD_VERSION));

     return 0;
}
