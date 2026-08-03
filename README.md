# Two-Pass Assembler in C

A two-pass assembler implemented in C as part of the Programming Laboratory course in the B.Sc. Computer Science program at the Open University of Israel.

The assembler expands macros, builds a symbol table, performs first and second passes, and generates encoded output files in a custom base-32 format.

## Features

- Macro expansion
- Symbol table management
- Two-pass assembly process
- Support for labels, entry and external symbols
- Multiple addressing modes
- Binary encoding
- Custom base-32 output
- Error handling

## Build

```bash
make
```

## Run

```bash
./myrun program
```

The input file should be named: `program.as`
