# Assembler in C++

This project implements a MIPS assembler in C++ that converts MIPS assembly code into corresponding machine code. The assembler follows a two-pass approach:

1. **First Pass**: It generates a symbol table by identifying labels and their addresses.
2. **Second Pass**: It generates the machine code for each instruction.

## Key Features

- **File Parsing**: The assembler reads an assembly file and splits it into data and text segments.
- **Instruction Support**: It supports a wide range of MIPS instructions, including:
  - Arithmetic operations (e.g., add, sub)
  - Logical operations (e.g., and, or, nor)
  - Memory access instructions (e.g., lw, sw)
  - Branch and jump instructions (e.g., beq, bne, j, jal)
  - Shift operations (e.g., sll, srl)

## How to Use

1. Compile the C++ source code.
2. Provide a MIPS assembly file as input.
3. The assembler will output the corresponding machine code in hexadecimal format to `objectfile.txt`.
