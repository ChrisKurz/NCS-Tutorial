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
> Examle:
> <code>add_library(mylib STATIC)</code>
> <code>target_sources(mylib PRIVATE a.c)</code>


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
