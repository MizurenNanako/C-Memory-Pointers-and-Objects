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
      - [Pointer Declaration](#pointer-declaration)
      - [Indirect Addressing](#indirect-addressing)
      - [Direct Addressing](#direct-addressing)
    - [Typing](#typing)
      - [Type of The Pointer And The Pointed-To](#type-of-the-pointer-and-the-pointed-to)
    - [Array and Pointer Arithmetics](#array-and-pointer-arithmetics)
      - [Array](#array)
      - [Pointer Arithmetics With Array Name](#pointer-arithmetics-with-array-name)
      - [Operator `[]`](#operator)
    - [Pointer as Function Parameters](#pointer-as-function-parameters)
    - [Dynamic Memory Allocation](#dynamic-memory-allocation)
      - [Allocation](#allocation)
      - [Memory Leak](#memory-leak)
    - [C-String](#c-string)
      - [C-Styled String](#c-styled-string)
    - [String Operation with Standard Library](#string-operation-with-standard-library)
      - [1. String length (`strlen()` and `strnlen()`)](#1-string-length-strlen-and-strnlen)
      - [2. String copy (`strcpy()` and `strncpy()`)](#2-string-copy-strcpy-and-strncpy)
      - [3. String concatenation (`strcat()` and `strncat()`)](#3-string-concatenation-strcat-and-strncat)
      - [4. String comparison (`strcmp()` and `strncmp()`)](#4-string-comparison-strcmp-and-strncmp)
      - [5. Substring search (`strstr()` and `strnstr()`)](#5-substring-search-strstr-and-strnstr)
      - [6. The Most Important: IO](#6-the-most-important-io)
        - [(1). Input using `scanf()`](#1-input-using-scanf)
        - [(2). Input using `scanf_s()`](#2-input-using-scanfs)
        - [(3). Output using `printf()`](#3-output-using-printf)
        - [(4). Output using `printf_s()`](#4-output-using-printfs)
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

> **Data races** occur when threads access shared memory without proper synchronization. When multiple threads access and modify the same memory location without proper synchronization, the order in which these modifications occur is undefined. This can result in unpredictable behavior, such as incorrect results or program crashes.
>
> For example, consider the following code fragment:
>
> ```c
> #include <pthread.h>
> int x = 0;
> 
> void* thread_func(void* arg) {
>     x++;
>     return NULL;
> }
> 
> int main() {
>     pthread_t tid[2];
>     pthread_create(&tid[0], NULL, thread_func, NULL);
>     pthread_create(&tid[1], NULL, thread_func, NULL);
>     pthread_join(tid[0], NULL);
>     pthread_join(tid[1], NULL);
>     printf("x = %d\n", x);
>     return 0;
> }
> ```
>
> In this code, two threads are created, and each thread increments the value of the shared variable `x`. The result of the program depends on the order in which the threads execute their increments, and therefore, the result is unpredictable and varies from run to run.

To avoid such issues, C provides a set of memory order primitives that can be used to ensure that memory operations are performed in a predictable and synchronized manner. These primitives include memory barriers and atomic operations.

Memory barriers are instructions that prevent reordering of memory operations by the compiler and the hardware. They ensure that memory operations are performed in the order specified by the program and prevent data races and other synchronization issues. In C, memory barriers can be specified using functions like `__sync_synchronize()` or `atomic_thread_fence()`.

Atomic operations, on the other hand, are operations that are guaranteed to be performed atomically, without interference from other threads. Atomic operations can be used to modify shared variables in a synchronized and predictable manner, without the need for locks or other synchronization mechanisms. In C, atomic operations can be specified using functions like `atomic_fetch_add()` or `atomic_fetch_sub()`.

Memory order is an important concept in parallel programming because it allows programs to safely and efficiently perform operations on shared memory. By ensuring that memory operations are performed in a synchronized and predictable manner, memory order primitives help to avoid data races and other synchronization issues, making it easier to write correct and efficient parallel programs.

## Pointers: Variables Supposed to Store Addresses

In C programming language, a pointer is a variable that stores the memory address of another variable. The pointer is used to access the value of the variable at the memory address it points to.

### Addressing and Indirect Addressing

#### Pointer Declaration

A pointer is declared by using the asterisk (*) symbol before the variable name. For example:

```c
int *ptr;
```

This declares a pointer named `ptr` that can store the memory address of an integer variable.

To assign a memory address to a pointer, we use the address-of operator (&) with the variable whose address we want to store. For example:

```c
int num = 10;
int *ptr = &num;
```

This assigns the memory address of the integer variable `num` to the pointer `ptr`.
To access the value of the variable at the memory address pointed to by the pointer, we use the **dereference operator (*)** with the pointer variable. For example:

```c
int num = 10;
int *ptr = &num;

printf("The value of num is %d\n", *ptr);
```

This prints the value of the integer variable `num`, which is 10.
Pointers are useful in C programming because they allow us to manipulate memory directly. We can use pointers to pass arguments to functions, to allocate memory dynamically, and to work with arrays and structures. However, pointers can also be a source of errors if not used carefully, such as when attempting to access memory that has not been properly allocated or has already been deallocated.

> The use of the `*` and `&` symbols for pointer operations in C can be traced back to the language's origins in the early 1970s.
>
> C was developed by Dennis Ritchie at Bell Labs as a language for systems programming. It was intended to be a simpler, more efficient alternative to the more complex languages of the time, such as Fortran and Algol. One of the key design principles of C was to provide direct access to the underlying hardware, including memory and other system resources.
>
> To achieve this goal, C included a powerful feature called pointers, which allowed programmers to manipulate memory addresses directly. To distinguish pointers from regular variables, Ritchie decided to use the `*` symbol to indicate that a variable was a pointer. This symbol was chosen because it was not used for any other purpose in C or in other languages at the time.
>
> The `&` symbol was chosen to represent the address-of operator, which is used to obtain the memory address of a variable. This symbol was also not used for any other purpose in C or in other languages at the time.
>
> Together, the `*` and `&` symbols form a simple, yet powerful syntax for working with pointers in C. Despite the fact that C has been around for over 50 years, this syntax has remained largely unchanged, and is still widely used today in many programming languages that have been influenced by C, including C++, Java, and Python.

#### Indirect Addressing

We just mentioned **Dereferencing** of a pointer. In C, if a pointer variable stores the memory address of another variable. The dereference operator (`*`) can be used to access the value stored at the memory address pointed to by the pointer variable. This is often referred to as "dereferencing" the pointer.

When we dereference a pointer, we are indirectly accessing the value stored at the memory location pointed to by the pointer. This is because we are **not accessing** the value directly through the pointer variable, but rather through the memory address it points to.

For example, consider the following code:

```c
int x = 10;
int *p = &x;

printf("Value of x: %d\n", x);
printf("Value of *p: %d\n", *p);
```

In this code, we declare an integer variable `x` and a pointer variable `p`. We use the address-of operator to assign the memory address of `x` to `p`. We then print out the values of `x` and `*p` using the `printf` function.
Note that `x` and `*p` both have the value of `10`. However, `x` is a regular variable, while `*p` is the value stored at the memory address pointed to by `p`. (Although in this case they are the same.) This demonstrates how the dereference operator is used to **indirectly** access the value stored in memory through a pointer variable.

#### Direct Addressing

In fact, when we use a regular variable in C, we are performing direct addressing.

In direct addressing, we are accessing the value stored in a memory location directly, without the use of an intermediate pointer variable, or an address. This is in contrast to indirect addressing, where we access the value stored at a memory location indirectly, through a pointer variable, in another words, a address.

### Typing

#### Type of The Pointer And The Pointed-To

**Pointers themselves do not store type information in C.** Instead, the type information of a pointer is used to derived the data type of the variable it points to.
When you declare a pointer variable in C, you specify the data type of the variable it points to. For example, the following declaration creates a pointer variable that points to an integer:

```c
int *ptr;
```

The data type of the pointer variable `ptr` is `int*`, which indicates that it **should be** pointed to, or **assumes** it will point to an integer variable. When you extract a memory address from a variable using the address-of operator (`&`), the data type of the variable **is actually lost**.
For example, consider the following code:

```c
float x = 3.14;
int *ptr = &x;
printf("The value %f reinterpreted as int is %d", x, *ptr);
// The value 3.140000 reinterpreted as int is 1078523331
// (On an x86_64 Linux with little endian CPU)
```

In this code, we declare a `float` variable `x`, and a pointer variable `ptr` of type `int *`. We then assign the memory address of `x` to `ptr`. Though **this code compiles without error**, it should not appear in most occasions. (It is a trick in some special scenes.) It will result in (platfrom based) undefined behavior, and **in 99.9% of time it may be a mistake**.

In fact, accessing the memory location pointed to by `ptr` with an `int` data type will interpret the bits in memory differently than if it were accessed with a `float` data type. This can result in unexpected behavior, such as the wrong value being read from memory, or even a crash.

### Array and Pointer Arithmetics

#### Array

In C programming language, an array is a collection of elements of the same data type, stored in contiguous memory locations. The elements in an array can be accessed using an index, which starts at 0 for the first element.

The simplest form of an array is a one-dimensional array, which is an array with a single row of elements. Here is an example:

```c
int arr[5] = {1, 2, 3, 4, 5};
```

This declares an integer array with 5 elements, and initializes it with the values 1, 2, 3, 4, and 5.

To access an element of an array, we use the square bracket notation along with the index of the element we want to access. For example:

```c
int num = arr[2];   
// Accesses the third element of the array (value 3)
```

In C, we can also create multi-dimensional arrays, which are arrays with multiple rows and columns. The most common form of a multi-dimensional array is a two-dimensional array, which can be thought of as a matrix.

Here is an example of a two-dimensional array:

```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```

This declares a 3x3 integer matrix, and initializes it with the values 1 through 9.

To access an element of a multi-dimensional array, we use the square bracket notation along with the row and column indices of the element we want to access. For example:

```c
int num = matrix[1][2];   
// Accesses the element in the 
//                    second row 
//                    and third column
// (value 6)
```

We can also create multi-dimensional arrays with more than two dimensions, such as a three-dimensional array, which can be thought of as a cube.

```c
int cube[2][3][4] = {
    {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
    {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
};
```

This declares a 2x3x4 integer cube, and initializes it with the values 1 through 24.

To access an element of a three-dimensional array, we use the square bracket notation along with the indices of the row, column, and depth of the element we want to access. For example:

```c
int num = cube[1][2][3];   
// Accesses the element in the 
//                        second row, 
//                        third column, 
//                        and fourth depth 
// (value 24)
```

And so on.

#### Pointer Arithmetics With Array Name

In C, an array name is a pointer to the first element of the array. We can use pointer arithmetics to access other elements of the array.

For example, consider the array declaration:

```c
int arr[5] = {1, 2, 3, 4, 5};
```

Here, `arr` is a pointer to the first element of the array, i.e., `arr[0]`. We can access other elements of the array using pointer arithmetics.

```c
printf("%d\n", *(arr+1));   // Output: 2, equivalent to arr[1]
printf("%d\n", *(arr+2));   // Output: 3, equivalent to arr[2]
printf("%d\n", *(arr+3));   // Output: 4, equivalent to arr[3]
```

For string is actually an array (this will be discussed later), pointer arithmetics can also be used to traverse a string:

```c
char str[] = "Hello, World!";
char *ptr = str;   // Assigns the address of the first character to ptr
while (*ptr != '\0') {
    printf("%c", *ptr);
    ptr++;
}
```

#### Operator `[]`

In C programming language, the `[]` operator is used to access elements of an array using an index, when we use the `[]` operator to access an element of an array, **it is equivalent to** dereferencing a pointer at a specific offset from the base address of the array. For example, consider the following array declaration:

```c
int arr[5] = {1, 2, 3, 4, 5};
```

To access the third element of the array, we can use the `[]` operator with an index of 2:

```c
int num = arr[2];   
// Accesses the third element of the array (value 3)
```

This is equivalent to dereferencing a pointer to the third element of the array:

```c
int num = *(arr+2);   
// Accesses the third element of the array (value 3)
```

Here, we are using pointer arithmetics to compute the memory address of the third element of the array, and then dereferencing it to obtain the value.

The equivalency also reveals that, the `[]` operator is commutative, which means the order of the operands does not matter, that `arr[1]` is equivalent to `1[arr]`.

To understand why this is the case, it's important to remember that the `[]` operator is implemented using pointer arithmetics. Specifically, `arr[1]` is equivalent to `*(arr + 1)`, which means "dereference the memory location that is one element after the address of the first element of the array". Similarly, `1[arr]` is equivalent to `*(1 + arr)`, which means "dereference the memory location that is one element after the address of the memory location pointed to by the variable `arr`".

Since addition is commutative, the expressions `arr + 1` and `1 + arr` are equivalent, and so `arr[1]` and `1[arr]` both refer to the same memory location and will yield the same result.

While using `1[arr]` is technically valid and will produce the same result as `arr[1]`, it is generally considered poor coding style and **should be avoided** in favor of the more common `arr[1]` notation.

### Pointer as Function Parameters

> Yet to be written.

### Dynamic Memory Allocation

> Yet to be written.

#### Allocation

> Yet to be written.

#### Memory Leak

> Yet to be written.

### C-String

#### C-Styled String

In C programming, **a C-styled string is a sequence of characters that is terminated by a null character ('\0')**. It is also known as a null-terminated string or a C string. C-styled strings are commonly used in C programming to represent text or character data, with implantation using character arrays, also known as char arrays.

**Thus, we can say that all C-styled strings are char arrays, but not every char array a C-styled string**, for C-styled strings are always terminated by a null character ('\0'). This null character is used to indicate the end of the string. Char arrays, on the other hand, do not have this null character by default. This means that char arrays can contain arbitrary data and may not represent a valid string.

In fact, when passing char array to functions, there should be another parameter which accepts the array's length. It is generally a good practice,since char arrays do not have a built-in way to determine their own length.

> Without passing the length of the array as a separate parameter, it can be difficult to correctly process the contents of the array. For example, if you are trying to copy the contents of one char array to another, and you do not know the length of the source array, you may end up copying too much data or not enough data.
>
> To avoid such issues, it is common to pass the length of the char array as a separate parameter when passing it to a function. For example, you might have a function like this:
>
> ```c
> void my_function(char my_array[], int length) {
>     // Do something with my_array and length
> }
> ```
>
> In this function, the `my_array` parameter is the char array being passed to the function, and the `length` parameter is the length of the array. By passing both of these parameters to the function, it is possible to correctly process the contents of the array without encountering any issues related to array length.

However, while C-Styled String has a null terminator, so their length can be acquired from themselves.

In fact, C-styled strings are often passed to functions as a pointer to the first character of the string, without the need to pass the length of the string as a separate parameter. This is because the null terminator at the end of the string serves as a sentinel value, indicating the end of the string.

> For example, the `strlen()` function in the standard C library is used to determine the length of a C-styled string. This function takes a C-styled string as its parameter and returns the length of the string, not including the null terminator. Here is an example of using `strlen()` to determine the length of a C-styled string:
>
> ```c
> char my_string[] = "Hello, world!";
> int length = strlen(my_string);
> ```
>
> In this example, the `my_string` array is a C-styled string, and the `strlen()` function is used to determine its length. The resulting value of `length` will be 13, which is the length of the string "Hello, world!".

### String Operation with Standard Library

Of course, there are both with-length and just-string versions of functions in standard library. So examples will be provided in both versions. By specifying the maximum length of the strings being manipulated, you can ensure that your code is safe from buffer overflows and other potential security vulnerabilities.

#### 1. String length (`strlen()` and `strnlen()`)

The `strlen()` function returns the length of a C-styled string, not including the terminating null character.

The `strnlen()` function does the same, but up to a maximum length specified by the caller.

```c
char str[] = "Hello, world!";
int len = strlen(str);  
// len = 13
int len = strnlen(str, sizeof(str));  
// len = 13
```

#### 2. String copy (`strcpy()` and `strncpy()`)

The `strcpy()` function copies a C-styled string from one location to another.

The `strncpy()` function does the same, but up to a maximum length specified by the caller.

Example:

```c
char src[] = "Hello, world!";
char dest[20];
strcpy(dest, src);  
// dest now contains "Hello, world!"
strncpy(dest, src, sizeof(dest));  
// dest now contains "Hello, world!"
```

#### 3. String concatenation (`strcat()` and `strncat()`)

The `strcat()` function appends one C-styled string to another.

The `strncat()` function does the same, but up to a maximum length specified by the caller.

Example:

```c
char str1[20] = "Hello, ";
char str2[] = "world!";
strcat(str1, str2);  
// str1 now contains "Hello, world!"
strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);  
// str1 now contains "Hello, world!"
```

Note that we subtract `strlen(str1) + 1` from the maximum length to ensure that the null terminator is always included.

#### 4. String comparison (`strcmp()` and `strncmp()`)

The `strcmp()` function compares two C-styled strings and returns an integer value that indicates their relative order.

The `strncmp()` function compares two C-styled strings up to a maximum length specified by the caller and returns an integer value that indicates their relative order.

Example:

```c
char str1[] = "Hello, world!";
char str2[] = "hello, world!";
int result = strcmp(str1, str2);  
// result = 1 (because 'H' comes after 'h' in the ASCII 
int result = strncmp(str1, str2, sizeof(str1));  
// result = 1 (because 'H' comes after 'h' in the ASCII table)table)
```

#### 5. Substring search (`strstr()` and `strnstr()`)

The `strstr()` function searches for a substring within a C-styled string and returns a pointer to the first occurrence of the substring.

The `strnstr()` function searches for a substring within a C-styled string up to a maximum length specified by the caller and returns a pointer to the first occurrence of the substring.

Example:

```c
char str[] = "The quick brown fox jumps over the lazy dog.";
char sub[] = "brown";
char* result = strstr(str, sub);  
// result points to the substring "brown"
char* result = strnstr(str, sub, sizeof(str));  
// result points to the substring "brown"
```

#### 6. The Most Important: IO

##### (1). Input using `scanf()`

The `scanf()` function can be used to read input from the user, including input that is stored in a C-styled string. You can specify a format string that describes the expected format of the input, and use the `%s` format specifier to read a string from the user.

Here is an example:

```c
char name[20];
printf("Enter your name: ");
scanf("%19s", name);  // read at most 19 characters into name
printf("Hello, %s!\n", name);
```

In this example, the `%19s` format specifier tells `scanf()` to read at most 19 characters into the `name` string, to avoid a buffer overflow.

##### (2). Input using `scanf_s()`

The `scanf_s()` function is a safer version of `scanf()` that includes additional checks to help prevent buffer overflows and other security issues. It takes the same arguments as `scanf()`, but also requires the length of the input buffer to be specified.

Here is an example:

```c
char name[20];
printf("Enter your name: ");
scanf_s("%19s", name, sizeof(name));  // read at most 19 characters into name
printf("Hello, %s!\n", name);
```

In this example, the `sizeof(name)` argument tells `scanf_s()` the length of the `name` buffer, so that it can ensure that no more than 19 characters are read into the buffer.

##### (3). Output using `printf()`

The `printf()` function can be used to output text to the console, including text that is stored in a C-styled string. You can use the `%s` format specifier to output a string to the console.

Here is an example:

```c
char message[] = "Hello, world!";
printf("%s\n", message);
```

In this example, the `%s` format specifier tells `printf()` to output the entire `message` string to the console.

##### (4). Output using `printf_s()`

The `printf_s()` function is a safer version of `printf()` that includes additional checks to help prevent buffer overflows and other security issues. It takes the same arguments as `printf()`, but also requires the length of the output buffer to be specified.

Here is an example:

```c
char message[] = "Hello, world!";
printf_s("%s\n", message);
```

In this example, the length of the output buffer is determined automatically based on the length of the `message` string.
These are just a few examples of the input and output functions that can be used with C-styled strings. By using the safer versions of these functions, you can help ensure that your code is free from potential security vulnerabilities.

## Data Structures (Embedded and Generalized)

### Vector: Array with Dynamic Length

> Yet to be written.

### Linking List

#### Forward List

> Yet to be written.

#### Bidirectional List

> Yet to be written.

#### Cyclone List

> Yet to be written.

#### Non-Embedded Implantation

> Yet to be written.

#### Linux List Implantation: The Wizard's Way

> Yet to be written.

### Tree

#### Segment Tree

> Yet to be written.

#### Trie Tree and KMP Algorithm

> Yet to be written.

### A glimpse into Graph

#### Graph

> Yet to be written.

#### Dijkstra Algorithm

> Yet to be written.

## Function Pointer and Higher-Order Function

### Function Pointer

> Yet to be written.

### Closure

> Yet to be written.

### Higher-Order Function

> Yet to be written.

## Object-Oriented Programing in C

### Definition for an Object

> Yet to be written.

### A Simple Object Implantation in C

#### Attributes: Member Variables and Methods

> Yet to be written.

#### `this` Parameter, or You Can Name It `Self`

> Yet to be written.

#### Static or Dynamic? This is a Problem.

> Yet to be written.

### Essence: Polymorphism

#### Examples of Static Polymorphism in `math.h`

> Yet to be written.

#### The `_Generic` Macro

> Yet to be written.

### Dynamic Polymorphism

#### Dynamic Polymorphism Implantation with Silly Type Checking

> Yet to be written.

#### Implantation: The `Variant`

> Yet to be written.

#### Composition: A Trick of Memory

> Yet to be written.

#### Inheritance: The `vtable` and Method Overriding

> Yet to be written.

#### Virtual Inheritance: `vtable` of Base Classes

> Yet to be written.

## Epilogue: The Story of CFront

> Yet to be written.
