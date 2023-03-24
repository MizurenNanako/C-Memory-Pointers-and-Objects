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

本文将尝试简短地介绍 *C语言* 中的几个内存相关概念。

---

## Contents

- [C: Memory, Pointers, and Objects](#c-memory-pointers-and-objects)
  - [Contents](#contents)
  - [Prologue: Before the Introduction](#prologue-before-the-introduction)
    - [Compiling and Linking](#compiling-and-linking)
    - [Preprocessing, Compile-time and Runtime](#preprocessing-compile-time-and-runtime)
      - [The Preprocessing Stage](#the-preprocessing-stage)
      - [The Compilation](#the-compilation)
      - [Runtime Error Like Segment Fault](#runtime-error-like-segment-fault)
  - [The Static Memory Model of C](#the-static-memory-model-of-c)
    - [Bytes and Static Memory Model](#bytes-and-static-memory-model)
    - [Memory Location](#memory-location)
      - [The Stack](#the-stack)
      - [The Heap](#the-heap)
      - [Virtual Addresses](#virtual-addresses)
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
    - [A glimpse on Graph](#a-glimpse-on-graph)
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

### Compiling and Linking

> The translation from human readable sources to executable machine code.

从人类可读的 *Source Code* 到可执行的 *Machine Code*，一个 `C` 程序需要经过 *Compiling* and *Linking*。前者包括 *Pre-Compilation Process* 和 *Binary Object File Generation*，后者主要是 *Symbol(External Links) Resolution* 与 *Executable Generation*。

如果细究这部分内容，请出门左转 *Compiler Principles*；本文无意于详述，Just mention to clarify that *Compiling* and *Linking* are two different processes.

### Preprocessing, Compile-time and Runtime

Obliviously, the translation progress consists a serial of different stages, each of which may generate error(s). Thus, a clarification of their functionality is acquired.

#### The Preprocessing Stage

#### The Compilation

#### Runtime Error Like Segment Fault

## The Static Memory Model of C

### Bytes and Static Memory Model

### Memory Location

#### The Stack

#### The Heap

#### Virtual Addresses

### <s>Memory Order</s>

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

### A glimpse on Graph

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
