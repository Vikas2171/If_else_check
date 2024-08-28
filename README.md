# If_else_parser

## Introduction
**If_else_check** is a C++ project designed to validate whether an input string conforms to the syntax of an `if-else` conditional statement in C++. This tool is useful for programmers, students, and educators who want to ensure the correctness of `if-else` constructs in their code.

The project performs the following tasks:

1. __Syntax Validation:__ It takes an input string and checks if it is a valid syntax for an `if-else` conditional statement in C++.
2. __Parse Tree Generation:__ If the syntax is valid, the tool generates and prints all levels of the parse tree, with each level displayed on a separate line.
3. __Grammar Rules:__ It prints the context-free grammar rules used in the validation process, presented as an adjacency list.
## Team Members
This project is a collaborative effort by the following team members:

* Sohit Dhawan  [[Linkdin](https://www.linkedin.com/in/sohit-dhawan-78676a255/)]
* Shubham Gupta  [[Linkdin](https://www.linkedin.com/in/shubham-gupta-79876a255/)]
* Vikas Prajapati [[Linkdin](https://www.linkedin.com/in/vikas-prajapati-577bab252/)]

## Features
* __Validation of if-else Syntax:__ The tool strictly adheres to the C++ syntax rules for `if-else` statements.
* __Parse Tree Visualization:__ It displays all the levels of the parse tree, making it easier to understand how the input is parsed.
* __Grammar Rule Display:__ Lists all the context-free grammar rules applied during parsing, represented as an adjacency list for better comprehension.
* __Support for Nested if-else Conditions:__ The tool also supports the validation of nested if-else conditions.

## Assumptions

In developing this project, we have made the following assumptions:

* Only a single relational expression should be given as the condition of the if block.
```cpp
(a >= b) 
```
* The if and else blocks should be empty ({}).
```cpp
if(condition){}else{}
```
* Variable names should be a single character only.
```cp
a, b, c,....
```
* The syntax is considered correct only if there is a corresponding else block for every if block.
```cp
"if(condition){}"
- This is considered as invalid syntax by our parser.
"if(condition){}else{}"
- This is valid.
```
## Getting Started

### Prerequisites
To run this project, you need:

* A C++ compiler (e.g., GCC, Clang)
* Basic knowledge of C++ and context-free grammars

### Installation
1. Clone the repository:
```cpp
git clone https://github.com/Vikas2171/If_else_parser.git
```
2. Navigate to the Project Directory:
```cpp
cd If_else_parser
```
3. Compile the Program:
```cpp
g++ -o if_else_parser if_else_parser.cpp
```
4. Run the Program:
```cpp
./if_else_parser
```

## Usage
1. Input:

    The program prompts you to enter a string representing an `if-else` conditional statement in C++.

2. Output:

    If the input is valid, the program will:
    * Print "The given input is valid"
    * Display the parse tree with each level on a separate line.
    * List all the context-free grammar rules used, displayed as an adjacency list.
    * If the input is invalid, it will print "The given input has Invalid Syntax".

## Example Run
* INPUT
```cp
if(condition){}else{}
```
* OUTPUT

![output](https://github.com/Vikas2171/If_else_parser/blob/main/image.png)

## Acknowledgements
We would like to express our sincere gratitude to Senior Professor Subhasis Bhattacharjee of IIT Jammu for his guidance and support throughout this course project. His expertise and insights have been invaluable in the development of this parser.