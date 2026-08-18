# Zephyr's C Libraries:  Newlib

## Introduction

The ‘Newlib’ and ‘Newlib-nano’ C libraries have been removed from the latest Zephyr SDK, as ‘Picolibc’ is now the default C library. ‘Picolibc’ offers a complete, resource-efficient C library solution specifically tailored to embedded systems, thereby rendering the more resource-intensive ‘Newlib’ and ‘Newlib-nano’ libraries redundant. 

Although the KCONFIG symbol <code>CONFIG_NEWLIB_LIBC</code> is still available in Zephyr, it has a direct dependency that looks for the symbol <code>CONFIG_NEWLIB_LIBC_SUPPORTED</code> – an invisible KCONIFG symbol that is only enabled when Newlib is available. 
