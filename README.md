# Strassen Matrix Multiplication Implementations

This repository contains two implementations of matrix multiplication algorithms in C++, demonstrating different approaches to the problem.

## Code Overview

### `strassen`

The `strassen` code implements the Strassen algorithm for matrix multiplication. This is a fleshed out version of the my initial implementation of the Strassen algorithm, developed during a class session. 
Here's a brief overview of the components:

- **`Matrix` struct**: Defines a matrix structure with a size and data stored in a vector of vectors.
- **`addMatrices` function**: Adds two matrices element-wise.
- **`subtractMatrices` function**: Subtracts one matrix from another element-wise.
- **`naiveMultiplyMatrices` function**: Naively multiplies two matrices using three nested loops.
- **`multiplyMatrices` function**: Implements the Strassen algorithm for matrix multiplication using recursion and divide-and-conquer strategy.
- **`printMatrix` function**: Prints the elements of a matrix.
- **`main` function**: Prompts the user to enter the size of matrices and their elements, multiplies them using the `multiplyMatrices` function, and prints the result.

### `revisedStrassen`

The `revisedStrassen` code provides a different implementation of matrix multiplication, utilizing a one-dimensional array to represent matrices. Here's a summary of its components:

- **`Matrix` struct**: Defines a matrix structure with a size and data stored in a one-dimensional vector, simulating a two-dimensional array.
- **`addMatrices` function**: Adds two matrices element-wise.
- **`subtractMatrices` function**: Subtracts one matrix from another element-wise.
- **`multiplyMatrices` function**: Implements the Strassen algorithm for matrix multiplication using recursion and divide-and-conquer strategy, with optimized memory access.
- **`printMatrix` function**: Prints the elements of a matrix.
- **`validateSize` function**: Validates whether the input size is a power of 2 and greater than 0.
- **`populateMatrix` function**: Populates a matrix with values entered by the user.
- **`main` function**: Prompts the user to enter the size of square matrices, validates the size, populates two matrices with user-input values, multiplies them using the `multiplyMatrices` function, and prints the result.

## Usage

To use these implementations:

1. Clone the repository.
2. Compile the desired code (e.g., `g++ strassen.cpp -o strassen`).
3. Run the executable and follow the prompts to input matrix sizes and elements.
4. View the resulting product matrix.

## Planned Changes

- Both implementations are subject to future modifications to enhance performance, readability, or functionality.

## Notes

- The `strassen` implementation uses a traditional vector of vectors to represent matrices.
- The `revisedStrassen` implementation optimizes memory access by using a one-dimensional vector to represent matrices.
- Both implementations achieve the same goal of multiplying matrices, but they differ in their internal representation of matrices and how they handle operations on them.
