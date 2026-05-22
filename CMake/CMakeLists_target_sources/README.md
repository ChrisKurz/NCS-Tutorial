# _CMakeLists.txt_ File: <code>target_sources()</code>

<code>target_sources()</code> is a CMake command used to assign additional source files to an existing target.

Syntax:

    target_sources( <target>
    
                    <PRIVATE|PUBLIC|INTERFACE>
                    
                    <sources...>
                    
    )

Example: <code> target_sources(app PRIVATE src/main.c) </code>


## target

CMake manages targets as objects with properties.

A target can be:
- Executable
- Library
- Interface library
- Zephyr <code>app</code>

target_sources() expands the property "SOURCES" of the target.

In principle, this is similar to:

myapp.SOURCES += utils.c

> Important: <code>target_sources()</code> does not create a new target. The target must already exist.
> 
> Example:
> 
> <code>add_library(mylib STATIC)</code>
>
> <code>target_sources(mylib PRIVATE a.c)</code>

### Deep-Dive: Where is the <code>app</code> target defined in Zephyr 

The <code>app</code> target in Zephyr is created by the Zephyr CMake infrastructure, not in your application. It is defined when you call <code>find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})</code> in your application's CMakeLists.txt. The definition is done in the file _<ZEPHYR_BASE>/cmake/modules/kernel.cmake_ by using [following macro call](https://github.com/nrfconnect/sdk-zephyr/blob/544950b66a38cde53c651a4259a76d392d390006/cmake/modules/kernel.cmake#L225): 

<code>zephyr_library_named(app)</code>

So, the kernel.cmake is the one that actually defines the target <code>app</code>.

The macro [<code>zpephyr_library_named()</code>](https://github.com/nrfconnect/sdk-zephyr/blob/544950b66a38cde53c651a4259a76d392d390006/cmake/modules/extensions.cmake#L460) is defined in the file _<ZEPHYR_BASE>/cmake/modules/extensions.cmake_. Here you will find the macro definition <code>macro(zephyr_library_named name)</code>. There, the target creation is done with the instruction <code>add_library(${name} STATIC "")</code>. 

This is the canonical definition of the app library target used by <code>target_sources(app PRIVATE src/main.c)</code>.

The target gets created during <code>find_package(Zephyr)</code> from your application CMakeLists.txt. Typical call chain is roughly:

> find_package(Zephyr)
> 
>    -> zephyr-config.cmake
> 
>    -> boilerplate.cmake / kernel.cmake
> 
>    -> add_library(app STATIC)


## PRIVATE/PUBLIC/INTERFACE

These keywords determine visibility.

### PRIVATE

Files apply only to this target.

<code>target_sources(app PRIVATE main.c)</code>

→ Only app uses this file.

This is the standard case for .c files.

### PUBLIC

The sources are part of the target and are also passed on to dependent targets.

This is rarely used for .c files, but more commonly for header files or file sets.

### INTERFACE

Visible only to dependent targets, not to the target itself.

This is particularly useful for header-only libraries.
