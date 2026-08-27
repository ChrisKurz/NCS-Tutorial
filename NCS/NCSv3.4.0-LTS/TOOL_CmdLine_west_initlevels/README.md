# Command Line Tool: west - Initialization Levels of Threads

## Introduction

In Zephyr and _nRF Connect SDK_, initialization functions are assigned init levels such as:
- EARLY
- PRE_KERNEL_1
- PRE_KERNEL_2
- POST_KERNEL
- APPLICATION
- SMP

<code>west build -t initlevels</code> runs the build target that generates/displays information about the initialization levels and the functions assigned to them.

It's particularly useful when you're trying to understand Zephyr's boot sequence or debug why some initialization code runs before/after other code.

For example, if you have drivers or SYS_INIT() functions:

```c
static int my_init(void)
{
    /* initialization */
    return 0;
}
SYS_INIT(my_init, POST_KERNEL, 50);
```
the initlevels target can help you inspect where <code>my_init()</code> ends up in Zephyr's initialization sequence.


## Using <code>west build -t initlevels</code> together with SYSBUILD

Note that <code>west build -t initleves</code> can be called in the project folder of a non-sysbuild project. As soon as SYSBUILD is used for the project, the build path changes and the west command needs further information about the user project build folder. Here is an example for Zephyr's __hello world__ project:

```c
west build -d build/hello_word -t initlevels
```

The output in the terminal looks like this:

``` 
C:\Nordic\workspace\hello_world> west build -d build\hello_world -t initlevels
-- west build: running target initlevels
[0/1] C:\WINDOWS\system32\cmd.exe /C "cd /D C:\Nordic\workspace\hello_world\build\hello_worl...--elf-file=C:/Nordic/workspace/hello_world/build/hello_world/zephyr/zephyr.elf --initlevels"EARLY
  __init_nordicsemi_nrf54l_init: nordicsemi_nrf54l_init(NULL)
  __init_sys_clock_driver_init: sys_clock_driver_init(NULL)
PRE_KERNEL_1
  __init___device_dts_ord_64: clk_init(__device_dts_ord_64)
  __init___device_dts_ord_9: gpio_nrfx_init(__device_dts_ord_9)
  __init___device_dts_ord_14: gpio_nrfx_init(__device_dts_ord_14)
  __init___device_dts_ord_16: gpio_nrfx_init(__device_dts_ord_16)
  __init___device_dts_ord_109: uarte_20_init(__device_dts_ord_109)
  __init_uart_console_init: uart_console_init(NULL)
PRE_KERNEL_2
  __init_grtc_post_init: grtc_post_init(NULL)
POST_KERNEL
  __init_malloc_prepare: malloc_prepare(NULL)
  __init__psa_crypto_init: _psa_crypto_init(NULL)
APPLICATION
  __init_ncs_boot_banner: ncs_boot_banner(NULL)
SMP
```
