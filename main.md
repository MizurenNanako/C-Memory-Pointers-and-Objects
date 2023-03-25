<style>.p{text-indent:2em;}@media print{.pagebreak{page-break-before:always;}}</style>

# C: Memory, Pointers, and Objects

<div style="display: flex; justify-content: flex-end;">
    <blockquote>
        <p>
            A brief introduction to
            C memory, pointer, and object-oriented programing
            <s>for Physics students</s>.
        </p>
    </blockquote>
</div>

This is an attempt to deliver a brief introduction of a few memory-related concepts for *C Language* beginners, with malformed grammar and ridiculous mistakes of spellings unavoidably included.

本文将尝试<s><small>简短地</small></s>介绍 *C语言* 中的几个内存相关概念。

> 关于「简短」：当我没说。

---

## Contents

- [C: Memory, Pointers, and Objects](#c-memory-pointers-and-objects)
  - [Contents](#contents)
  - [Prologue: Before the Introduction](#prologue-before-the-introduction)
    - [Preprocessing, Compile-time, Linking and Runtime](#preprocessing-compile-time-linking-and-runtime)
      - [Pre-processing:](#pre-processing)
        - [1. Missing include files:](#1-missing-include-files)
        - [2. Incorrect macro usage:](#2-incorrect-macro-usage)
        - [3. Conditional compilation errors:](#3-conditional-compilation-errors)
      - [Compile-time:](#compile-time)
        - [1. Syntax errors:](#1-syntax-errors)
        - [2. Type errors:](#2-type-errors)
        - [3. Undeclared variables:](#3-undeclared-variables)
        - [4. Incorrect function arguments:](#4-incorrect-function-arguments)
      - [Linking:](#linking)
        - [1. Undefined symbols:](#1-undefined-symbols)
        - [2. Multiple definitions:](#2-multiple-definitions)
      - [Runtime:](#runtime)
        - [1. Segmentation fault:](#1-segmentation-fault)
        - [2. Stack overflow:](#2-stack-overflow)
        - [3. Floating point exceptions:](#3-floating-point-exceptions)
  - [The Static Memory Model of C](#the-static-memory-model-of-c)
    - [Bytes and Static Memory Model](#bytes-and-static-memory-model)
    - [Memory Location](#memory-location)
      - [Memory Types](#memory-types)
      - [The Stack](#the-stack)
      - [The Heap](#the-heap)
    - [Memory Addresses](#memory-addresses)
      - [Address Types](#address-types)
    - [Memory Order](#smemory-orders)
  - [Pointers: Variables Supposed to Store Addresses](#pointers-variables-supposed-to-store-addresses)
    - [Addressing and Indirect Addressing](#addressing-and-indirect-addressing)
      - [Pointer as Function Parameters](#pointer-as-function-parameters)
    - [The True Mechanism behind scenes](#the-true-mechanism-behind-scenes)
    - [Array and Pointer Arithmetics](#array-and-pointer-arithmetics)
      - [Type Inconsistency](#type-inconsistency)
      - [World of Dangerous Freedom](#world-of-dangerous-freedom)
    - [C-String](#c-string)
    - [Dynamic Memory Allocation](#dynamic-memory-allocation)
      - [Allocation](#allocation)
      - [Memory Leak](#memory-leak)
  - [Data Structures (Embedded and Generalized)](#data-structures-embedded-and-generalized)
    - [Vector: Array with Dynamic Length](#vector-array-with-dynamic-length)
    - [Linking List](#linking-list)
      - [Forward List](#forward-list)
      - [Bidirectional List](#bidirectional-list)
      - [Cyclone List](#cyclone-list)
      - [Non-Embedded Implantation](#non-embedded-implantation)
      - [Linux List Implantation: The Wizard's Way](#linux-list-implantation-the-wizards-way)
    - [Tree](#tree)
      - [Segment Tree](#segment-tree)
      - [Trie Tree and KMP Algorithm](#trie-tree-and-kmp-algorithm)
    - [A glimpse into Graph](#a-glimpse-into-graph)
      - [Graph](#graph)
      - [Dijkstra Algorithm](#dijkstra-algorithm)
  - [Function Pointer and Higher-Order Function](#function-pointer-and-higher-order-function)
    - [Function Pointer](#function-pointer)
    - [Closure](#closure)
    - [Higher-Order Function](#higher-order-function)
  - [Object-Oriented Programing in C](#object-oriented-programing-in-c)
    - [Definition for an Object](#definition-for-an-object)
    - [A Simple Object Implantation in C](#a-simple-object-implantation-in-c)
      - [Attributes: Member Variables and Methods](#attributes-member-variables-and-methods)
      - [`this` Parameter, or You Can Name It `Self`](#this-parameter-or-you-can-name-it-self)
      - [Static or Dynamic? This is a Problem.](#static-or-dynamic-this-is-a-problem)
    - [Essence: Polymorphism](#essence-polymorphism)
      - [Examples of Static Polymorphism in `math.h`](#examples-of-static-polymorphism-in-mathh)
      - [The `_Generic` Macro](#the-generic-macro)
    - [Dynamic Polymorphism](#dynamic-polymorphism)
      - [Dynamic Polymorphism Implantation with Silly Type Checking](#dynamic-polymorphism-implantation-with-silly-type-checking)
      - [Implantation: The `Variant`](#implantation-the-variant)
      - [Composition: A Trick of Memory](#composition-a-trick-of-memory)
      - [Inheritance: The `vtable` and Method Overriding](#inheritance-the-vtable-and-method-overriding)
      - [Virtual Inheritance: `vtable` of Base Classes](#virtual-inheritance-vtable-of-base-classes)
  - [Epilogue: The Story of CFront](#epilogue-the-story-of-cfront)

---

## Prologue: Before the Introduction

### Preprocessing, Compile-time, Linking and Runtime

Obliviously, the translation progress consists a serial of different stages, each of which may generate error(s). Thus, a clarification of their functionality is acquired.

#### Pre-processing:

The pre-processing stage is the first phase of compilation in C programming. During this stage, a preprocessor reads the source code and processes it before actual compilation starts. The preprocessor performs various operations like macro substitution, file inclusion, and conditional compilation.

For example, if you use the `#define` directive to define a macro, the preprocessor replaces all occurrences of the macro with its corresponding value. The preprocessor also processes any `#include` statements in the code, which instructs the preprocessor to include the contents of another file in the current file.

There can be pre-processing errors that occur during the pre-processing stage of compiling a C program. These errors typically involve the use of preprocessor directives that are not properly formatted or do not have the intended effect. Here are some examples of pre-processing errors:

##### 1. Missing include files:

If a source file includes a header file that cannot be found, the preprocessor will produce an error. For example:

```c
#include <missing.h> 
// error: missing.h: No such file or directory

int main() {
   return 0;
}
```

##### 2. Incorrect macro usage:

If a macro is not defined correctly or is used incorrectly, the preprocessor will produce an error. For example:

```c
#include <stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))

int main() {
   printf("The max of two and three is %f\n", MAX(2,3,4)); 
   // error: macro "MAX" passed 3 arguments, but takes just 2
   return 0;
}
```

##### 3. Conditional compilation errors:

If a preprocessor conditional is not properly formed or is missing a required symbol definition, the preprocessor will produce an error. For example:

```c
#include <stdio.h>
#undef DEBUG
   printf("Debugging disabled\n"); 
#endif
// error: #endif without #if

int main() {
   return 0;
}
```

#### Compile-time:

The compilation stage takes place after the pre-processing stage. During this stage, the compiler reads the pre-processed source code and generates object code. The object code contains machine code that the CPU can understand. The compiler checks the syntax of the code and generates errors and warnings if it encounters any issues. The output of the compilation stage is an object file(`*.o`), which contains machine code but is not yet executable.

Examples of compile-time errors:

> In all of these cases, the errors occur during the compilation stage and prevent the program from being compiled into an object file.

##### 1. Syntax errors:

These occur when the code violates the syntax rules of the C language. For example, forgetting to close a parenthesis or a curly brace, or using an undeclared variable:

```c
int main() {
   printf("Hello World!");
   return 0;
// Error: Missing closing brace
```

##### 2. Type errors:

These occur when the type of a variable or expression is incompatible with the operation being performed on it. For example, trying to add an integer and a string:

```c
int main() {
   int a = 5;
   char b[] = "Hello";
   printf("%d%s", a+b);
   return 0;
}
// Error: Incompatible types in printf
```

##### 3. Undeclared variables:

These occur when a variable is used in the code without being declared first. For example:

```c
int main() {
   x = 5; // error: ‘x’ undeclared (first use in this function)
   return 0;
}
```

##### 4. Incorrect function arguments:

These occur when the number or type of arguments passed to a function does not match its definition. For example:

```c
#include <stdio.h>

void print_message(char* message) {
   printf("%s", message);
}

int main() {
   print_message(); 
   // error: too few arguments to function ‘print_message’
   return 0;
}
```

#### Linking:

The linker is a program that takes one or more object files and combines them into a single executable program or shared library. During Linking, the linker resolves external references and relocations, merges duplicate code and data sections and creates the final executable file. The output of this stage is an executable file that is ready to be run on the target platform.

Of cause, there are linking errors, the errors occur during the linking stage prevent the program from being linking and thus stop executable generating.

##### 1. Undefined symbols:

These occur when the linker cannot find the definition of a symbol (function or variable) that is referenced by the code. For example, forgetting to include the library that contains a function that is used in the code:

```c
#include <stdio.h>

int main() {
   printf("Hello World!");
   foo(); // undefined reference to `foo`
   return 0;
}
```

##### 2. Multiple definitions:

These occur when the linker finds multiple definitions of the same symbol in different object files. For example, defining a global variable in a header file that is included in multiple source files:

```c
// file.h
int x = 10;

// file1.c
#include "file.h"

// file2.c
#include "file.h"
int main() {
   return 0;
}
// Error: Multiple definition of `x`
```

#### Runtime:

The runtime stage is the stage at which the compiled program is executed. During this stage, the operating system loads the executable program into memory and starts executing it. The program's instructions are executed one by one, and any data used by the program is stored in memory. The runtime stage also involves interacting with input and output devices, such as keyboard and display, and performing any necessary operations on the data.

Though runtime errors won't be record in Windows, when a C program crashes due to a runtime error on Linux, it may produce a message like "Core dumped" or "Segmentation fault (core dumped)". This means that the program has attempted to access memory that it is not allowed to access, and the operating system has terminated the program and produced a core dump file, which can be analyzed to determine the cause of the error.

Here are some examples of runtime errors that can cause a core dump:

##### 1. Segmentation fault:

This occurs when a program tries to access a memory location that it is not allowed to access, usually because it is outside the program's memory space. This can happen when a program dereferences a null pointer, accesses an uninitialized pointer, or overflows a buffer. For example:

```c
int main() {
   int* ptr = NULL;
   *ptr = 5; // segmentation fault
   return 0;
}
```

##### 2. Stack overflow:

This occurs when a program uses more stack space than is available, usually because of a function call chain that is too deep or an excessively large array allocation on the stack. For example:

```c
void f() {
   int arr[1000000]; // allocate a large array on the stack
   f(); // call itself recursively
}

int main() {
   f(); // stack overflow
   return 0;
}
```

##### 3. Floating point exceptions:

This occurs when a program attempts to perform an illegal floating-point operation, such as dividing by zero, taking the square root of a negative number, or producing a result that is too large or too small to represent. For example:

```c
#include <math.h>

int main() {
   double x = -1.0;
   double y = sqrt(x); // domain error: square root of negative number
   return 0;
}
```

## The Static Memory Model of C

### Bytes and Static Memory Model

In C programming, memory refers to the space in the computer's memory system that is allocated for storing data during program execution. Memory is essential to store variables, data structures, and other program-related information.

Memory in C is organized into individual bytes, and each byte is assigned a unique memory address. These addresses can be used to access and manipulate data stored in memory.

> Beaware, a `byte` can be `9 bit` or `16 bit`. `1 byte == 8 bits` is not written in Standard.

### Memory Location

#### Memory Types

Memory in C is divided into two types: **stack memory** and **heap memory**. Stack memory is used for storing variables declared inside functions, while heap memory is used for dynamically allocated memory.

#### The Stack

Stack memory is allocated automatically by the program at compile time and is managed by the program's runtime environment. It is a limited resource and is typically much smaller than heap memory. Stack memory is used for storing variables that have a limited scope and lifetime, such as function arguments and local variables.

#### The Heap

Heap memory, on the other hand, is dynamically allocated during program execution using functions like malloc() and calloc(). Heap memory is not automatically managed by the program's runtime environment and must be explicitly allocated and released by the programmer. Heap memory is used for storing data structures and variables with a larger scope and lifetime, such as arrays and structures.

### Memory Addresses

#### Address Types

In computer systems, a memory address is a unique identifier that specifies the location of a specific byte in memory. Every byte of memory has its own unique address, and these addresses are used to access and manipulate data stored in memory.

While **physical addresses** represent the actual location of data in physical memory, **virtual addresses** are generated by the *operating system* and used by programs to access memory. The use of virtual memory provides several benefits, including memory protection, efficient memory usage, and the ability to run multiple programs simultaneously.

> The actual addresses we deal with in C are virtual addresses.

### <s>Memory Order</s>

Memory order in C refers to the order in which memory operations occur in parallel programming.

In parallel programming, multiple threads can access and modify the same memory location simultaneously, which can result in **data races** and other synchronization issues.

<blockquote><strong>Data races</strong> occur when threads access shared memory without proper synchronization. When multiple threads access and modify the same memory location without proper synchronization, the order in which these modifications occur is undefined. This can result in unpredictable behavior, such as incorrect results or program crashes.

For example, consider the following code fragment:

```c
#include <pthread.h>
int x = 0;

void* thread_func(void* arg) {
    x++;
    return NULL;
}

int main() {
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, thread_func, NULL);
    pthread_create(&tid[1], NULL, thread_func, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    printf("x = %d\n", x);
    return 0;
}
```

In this code, two threads are created, and each thread increments the value of the shared variable `x`. The result of the program depends on the order in which the threads execute their increments, and therefore, the result is unpredictable and varies from run to run.
</blockquote>

To avoid such issues, C provides a set of memory order primitives that can be used to ensure that memory operations are performed in a predictable and synchronized manner. These primitives include memory barriers and atomic operations.

Memory barriers are instructions that prevent reordering of memory operations by the compiler and the hardware. They ensure that memory operations are performed in the order specified by the program and prevent data races and other synchronization issues. In C, memory barriers can be specified using functions like `__sync_synchronize()` or `atomic_thread_fence()`.

Atomic operations, on the other hand, are operations that are guaranteed to be performed atomically, without interference from other threads. Atomic operations can be used to modify shared variables in a synchronized and predictable manner, without the need for locks or other synchronization mechanisms. In C, atomic operations can be specified using functions like `atomic_fetch_add()` or `atomic_fetch_sub()`.

Memory order is an important concept in parallel programming because it allows programs to safely and efficiently perform operations on shared memory. By ensuring that memory operations are performed in a synchronized and predictable manner, memory order primitives help to avoid data races and other synchronization issues, making it easier to write correct and efficient parallel programs.

## Pointers: Variables Supposed to Store Addresses

### Addressing and Indirect Addressing

#### Pointer as Function Parameters

### The True Mechanism behind scenes

### Array and Pointer Arithmetics

#### Type Inconsistency

#### World of Dangerous Freedom

### C-String

### Dynamic Memory Allocation

#### Allocation

#### Memory Leak

## Data Structures (Embedded and Generalized)

### Vector: Array with Dynamic Length

### Linking List

#### Forward List

#### Bidirectional List

#### Cyclone List

#### Non-Embedded Implantation

#### Linux List Implantation: The Wizard's Way

### Tree

#### Segment Tree

#### Trie Tree and KMP Algorithm

### A glimpse into Graph

#### Graph

#### Dijkstra Algorithm

## Function Pointer and Higher-Order Function

### Function Pointer

### Closure

### Higher-Order Function

## Object-Oriented Programing in C

### Definition for an Object

### A Simple Object Implantation in C

#### Attributes: Member Variables and Methods

#### `this` Parameter, or You Can Name It `Self`

#### Static or Dynamic? This is a Problem.

### Essence: Polymorphism

#### Examples of Static Polymorphism in `math.h`

#### The `_Generic` Macro

### Dynamic Polymorphism

#### Dynamic Polymorphism Implantation with Silly Type Checking

#### Implantation: The `Variant`

#### Composition: A Trick of Memory

#### Inheritance: The `vtable` and Method Overriding

#### Virtual Inheritance: `vtable` of Base Classes

## Epilogue: The Story of CFront
