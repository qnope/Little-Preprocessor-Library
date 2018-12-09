# Little Preprocessor Library

## Introduction
Little preprocessor Library is a simple preprocessor library. All _macros_ begin by `LPL_`. There is some macro to perform conditions, kind of loops, _computation_, and simplify some use of **variadic macros**.

## Stringification and concatenation

There is 2 macros to perform such a task. `LPL_CAT(x, y)` for concatenation and `LPL_STRINGIFY(x)` for _stringification_.

### Concatenation

```cpp
#define SOME_MACRO() 0
#define SOME_MACRO_0() This one is called
#define SOME_COMPUTATION LPL_CAT(SOME_MACRO_, SOME_MACRO())()
```

`SOME_COMPUTATION` will be expanded to `This one is called`

You have to understand that both `x` and `y` will be **expanded** before evaluation. It allows to perform a **macro concatenation** between a *result* of a macro and a text. 

### Stringification

As for concatenation, `x` will be expanded before evaluation. So, if you write

```cpp
LPL_STRINGIFY(SOME_COMPUTATION)
```

the output will be `This one is called` and not `SOME_COMPUTATION`.

## Variadic Macro Helpers
There is 3 helpers for variadic macros.

* `LPL_HEAD` that gets the first argument.
* `LPL_SECOND` that gets the second argument.
* `LPL_TAIL` that gets all the arguments but the first

## Evaluation helper
### Expansion and Annulation
To force evaluation of a macro, there is the `LPL_EXPAND` macro.

To avoid evaluation of a macro, there is the `LPL_EAT` macro.

### Defering evaluation
To defer at the next expansion the expansion of a macro, there is the macro `LPL_DEFER` or `LPL_DEFER_TWICE`. The last one defer not for the next expansion but for the next next one :).

```cpp
#define A() 5
A() // expand to 5
LPL_EXPAND(A()) // expand to 5
LPL_DEFER(A)() // expand to A()
LPL_EXPAND(LPL_DEFER(A)()) // expand to 5
LPL_EXPAND(LPL_DEFER_TWICE(A)()) // expand to A()
```

### Recursion and force multiple evaluation of a macro

To perform a recursion, you have to use a tips. Let's say you want to write the same text recursively.

```cpp
#define WRITE(x) x WRITE(x)
```
here `WRITE` is _painted-blue_ so, if you write `WRITE(blah)`it will be expanded as `blah WRITE(blah)`

The tips is to defer the evaluation of an indirection of `WRITE`.

```cpp
#define WRITE(x) x LPL_DEFER(WRITE_I)()(x)
#define WRITE_I() WRITE

WRITE(blah) // Expand to blah WRITE_I()(blah)
LPL_EXPAND(WRITE(blah)) // Expand to blah blah WRITE_I()(blah)
```

To perform multiple evaluation, there is the `LPL_EVAL` macro.

```c++
LPL_EVAL(WRITE(blah)) // blah blah blah blah .... blah WRITE_I()(blah)
```

### Map / for_each

Let's say you have a macro `F` and you want to call `F` multiple times with different arguments:

```c++
#define F(x) x,
LPL_MAP(F, 0, 1, 2, 3, 4, 5)  => F(0) F(1) F(2) F(3) F(4) F(5) => 0, 1, 2, 3, 4, 5, 
```

## Conditions
### End for variadic macro
Inside **Little Preprocessor Library**, the end marker for variadic macro is `()`

### If condition

The `if` statement is defined as : 
```c++
LPL_IF(condition)(statement-for-true, statement-for-false) 
```

There is also a `when`statement :
```c++
LPL_WHEN(condition)(statement-for-true)
```

### while statement
There is a `while` statement if you need a `while` for the preprocessor. However it is defined a bit weird way.

```c++
#define LPL_WHILE(x, predicat, macroToApplyToX, motif)
```

## Example
For example you may check the `main.cpp`


## Compatibility
It works with at least `MSVC` with `/experimental:preprocessor` option, `Clang` and `GCC`.
