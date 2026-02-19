# Mini-Javascript-Compiler-using-C-for-Linux

A lightweight Mini JavaScript Compiler built in C for Linux systems.  
This project implements a basic compilation pipeline including lexical analysis, parsing, and interpretation of simple JavaScript-like syntax.

## 🚀 Features

- Lexical Analysis (Tokenizer)
- Syntax Parsing
- Abstract Syntax Tree (AST) generation
- Basic Expression Evaluation
- Modular Compiler Architecture
- Structured Error Handling
- Linux-based execution

## 🛠 Tech Stack

- C Programming Language
- Linux (Ubuntu)
- GCC Compiler
- Modular Design (.c and .h files)

## 📂 Project Structure



.
├── main.c
├── lexer.c
├── lexer.h
├── parser.c
├── parser.h
├── interpreter.c
├── interpreter.h
└── README.md


## ⚙️ How It Works

1. Source code input is passed to the Lexer.
2. Lexer converts source code into tokens.
3. Parser builds syntax structures (AST).
4. Interpreter evaluates the parsed structure.
5. Output is displayed in the terminal.

## 🖥 How to Compile (Linux)

Make sure you are using Linux (Ubuntu recommended).

Open terminal inside project directory and run:

```bash
gcc main.c lexer.c parser.c interpreter.c -o compiler

▶ How to Run
./compiler


If your program accepts input file:

./compiler input.txt

📌 Example

Input:

let a = 5;
let b = 10;
a + b;


Output:

15

🎯 Learning Objectives

Understanding compiler design basics

Working with lexical analysis and parsing

Implementing AST structures

Memory management in C

Modular software design in Linux environment

👨‍💻 Author

Arnav Rana
Computer Science Undergraduate (2026)
