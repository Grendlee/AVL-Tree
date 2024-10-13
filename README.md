# AVL-Tree (C++)

This project consists of a basic arithmetic operations calculator to demonstrate low-level arithmetic implemenations using registers.

The supported operations include:

1. Less than (x < y)
2. Addition (x + y)
3. Subtraction (x - y)
4. Multiplication (x * y)

# Components

1. main.c: The driver that provides a command-line interface.

2. calculator.s: The assembly code that implements the arithmetic operations.

# Assemble
```as -o calculator.o calculator.s```

# Compile

```gcc -o main main.c calculator.o```

# Run

```./main <int x> <int y>```
