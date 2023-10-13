```markdown
# C/C++ Compiler Cheatsheet

A no-frills guide to the C/C++ compiler toolchain.

## Overview

There are four distinct steps involved in transforming a C or C++ source file into an executable binary: preprocessing, compiling, assembling, and linking. In theory, each step is the responsibility of a dedicated tool: the preprocessor `cpp`, the compiler `cc`, the assembler `as`, and the linker `ld`. In practice, the compiler can orchestrate all four steps for us using a single command:

```shell
$ cc source.c
```

By default, the resulting executable will be named `a.out`, but you can specify a custom output name like this:

```shell
$ cc -o name source.c
```

## Preprocessing

The C preprocessor `cpp` is responsible for executing `#` directives and expanding macros. It takes a `.c` source file as input and outputs an expanded source file, typically with a `.i` extension. You can view the preprocessed source using the `-E` flag:

```shell
$ cc -E source.c
```

Various preprocessor options are available, including `-C` to retain source comments, `-D <name>=<value>` to define symbols, `-I <directory>` to specify include file search paths, `-P` to omit debugging information, and `-U <name>` to undefine symbols.

## Compiling

The compiler `cc` translates a C source file into assembly language, represented as `.s` files. You can generate assembly files using the `-S` flag:

```shell
$ cc -S source.c
```

## Assembling

The assembler `as` translates assembly language files into executable binary code, producing `.o` object files for each input file. Use the `-c` flag to retain these object files:

```shell
$ cc -c source.c
```

## Linking

Linking is the final stage of the compilation process, performed by the linker `ld`. It combines multiple object files into a single executable file, linking in code from the standard library and any external libraries referenced by the files. To link in a static library, use the `-l` flag:

```shell
$ cc source.c -lfoo
```

To link to a library that isn't on the default search path, you can specify the library's full filepath or add the containing directory to the search path using the `-L` flag.

## Multiple Files

The compiler can accept multiple input files at different compilation stages, as demonstrated:

```shell
$ cc src.c asm.s obj.o
```

In this example, `src.c` will be compiled and assembled, `asm.s` will be assembled, and the resulting object files will be linked into an executable.

## Warnings & Standards

To enable compiler warnings and specify C standards, use the following flags:

```shell
$ cc -Wall -Wextra --std=c99 --pedantic
```

You can turn off individual warnings using flags like `-Wno-unused-parameter`.

## Compiling Static Libraries

Static libraries, created with the `ar` tool, are collections of object files with a `lib` prefix and `.a` extension. Example:

```shell
$ ar -rv libfoo.a one.o two.o three.o
```

Static libraries are linked into the executable at compile time and don't need to be present during runtime.

## Compiling Dynamic Libraries

Dynamic or shared object libraries, denoted by a `lib` prefix and `.so` extension, can be loaded by a program at runtime using the `--shared` flag:

```shell
$ cc --shared -o libfoo.so one.o two.o three.o
```

Dynamic libraries can be linked at compile time or loaded and unloaded at runtime, forming the basis of a plugin system for an application.

## Compiling using the math.h lib

When your program is using the `math.h` library, don't forget to use the `-lm`arg while compiling in order to tell the compiler to link the lib into the final executable file.

```shell
$ cc volume_cylindre -lm
```

Dynamic libraries can be linked at compile time or loaded and unloaded at runtime, forming the basis of a plugin system for an application.