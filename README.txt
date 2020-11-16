Tanner Williams, Mason Hamilton, Brent Lund
CST 405
Project 2: Semantic Analyzer

Project Purpose: In this project we are looking to identify and display semantic errors that are found in the gcupl input file. 
We are given seventeen rules that we are tasked with implementing into our parser. Violating one of these rules will result in an error 
which will be identified by our program. These could include language errors, type errors, multiple declarations of a variable or a variable 
being outside the scope of the code trying to utilize and modify it. The two major components of this project are the symbol table, 
which tallies all ID in the program analyzes their context in terms of scope, whether there are multiple declarations of one variable
that would cause issues and lastly it will allow us to check the type of said ID. The AST or IR is what holds the semantic rules. 
This is incorporated into the parse tree to identify whether the code is syntactically correct. 

Necessary to run:

 - Flex and Bison on Ubuntu
 - All associated files

Resources:
Symbol Table Help:
https://www.tutorialspoint.com/compiler_design/compiler_design_symbol_table.htm


Code Help:
https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-passing-information-from-lexer-to-parser

Mudaware M., Compiler Design, Symbol Tables, Hashing, and Hash Tables, http://www.cse.aucegypt.edu/~rafea/csce447/slides/table.pdf, retrieved 11.15.2020