# Noam - Simple c++ parsers

Noam is a library that allows you to parse strings according to a [context-free grammar](https://en.wikipedia.org/wiki/Context-free_grammar) defined in the code, and receive a generated [abstract syntax tree (AST)](https://en.wikipedia.org/wiki/Abstract_syntax_tree). Next, it allows you to easily run your own logic against the AST using a [visitor design pattern](https://en.wikipedia.org/wiki/Visitor_pattern) by providing a custom visitor class.

Library was designed with a simplicity and ease of use in mind. In order to effectively create your own parsers you only need to be familiar with the basics of [context-free grammars](https://en.wikipedia.org/wiki/Context-free_grammar). It's default parsing algorithm is [LALR(1)](https://en.wikipedia.org/wiki/LALR_parser) but it provides also an [LL(1)](https://en.wikipedia.org/wiki/LL_parser) implementation. Noam is meant to be used in simple scenarios like evaluating expressions or interpreting simple scripts. All the stages of parsing like constructing a grammar or generating parsing tables for a language are done in run-time. It is not a full-featured compiler-compiler.

## Features

* Facilities to define [context-free grammars](https://en.wikipedia.org/wiki/Context-free_grammar) in code using syntax similar to BNF notation
* Lexer
* Two parsing algorithms: [LALR(1)](https://en.wikipedia.org/wiki/LALR_parser), [LL(1)](https://en.wikipedia.org/wiki/LL_parser)
* Generating [Abstract Syntax Trees](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
* Punctuation - symbols that are excluded by default from AST.
* Infrastructure for running logic against AST using [visitor design pattern](https://en.wikipedia.org/wiki/Visitor_pattern).

## Status

| Branch | g++8 |
| --- | --- |
| `develop` | [![Build Status](https://travis-ci.org/ditrytus/noam.svg?branch=develop)](https://travis-ci.org/ditrytus/noam) |

## Simple example

The following example shows a grammar that defines a text that can be optionally enclosed in a brackets. Brackets can be nested.

Few examples of strings in that language:

``No brackets``

``(Some brackets)``

``((()()))``

``Lorem (ipsum (dolor) sit) amet (dolor)``

**STEP 1**: Define a grammar:

```c++
auto CONTENT = "C"_N;
auto BRACKETS = "B"_N;

auto text = R"([^\(\)]+)"_Tx;

Grammar grammar = {
    R(CONTENT >> text | BRACKETS | CONTENT + CONTENT),
    R(BRACKETS >> "("_P + CONTENT + ")"_P)
};
```

**STEP 2**: Obtain a parsing function:

```c++
auto parse = createDefaultParseFunc(grammar);
```

**STEP 3**: Generate AST from input:

```c++
auto ast = parse("Lorem (ipsum (dolor)) sit (amet)");
```

**STEP 4**: Print the AST:

```c++
cout << toString(ast) << endl;
```

Last step will print the entire AST in an ASCII art manner:

```
<CONTENT> ::= <CONTENT><CONTENT>
|  
|- <CONTENT> ::= [^\(\)]+
|  |  
|  +- [^\(\)]+ ~ "Lorem"
|  
+- <CONTENT> ::= <CONTENT><CONTENT>
   |  
   |- <CONTENT> ::= <BRACKETS>
   |  |  
   |  +- <BRACKETS> ::= (<CONTENT>)
   |     |  
   |     +- <CONTENT> ::= <CONTENT><CONTENT>
   |        |  
   |        |- <CONTENT> ::= [^\(\)]+
   |        |  |  
   |        |  +- [^\(\)]+ ~ "ipsum"
   |        |  
   |        +- <CONTENT> ::= <BRACKETS>
   |           |  
   |           +- <BRACKETS> ::= (<CONTENT>)
   |              |  
   |              +- <CONTENT> ::= [^\(\)]+
   |                 |  
   |                 +- [^\(\)]+ ~ "dolor"
   |  
   +- <CONTENT> ::= <CONTENT><CONTENT>
      |  
      |- <CONTENT> ::= [^\(\)]+
      |  |  
      |  +- [^\(\)]+ ~ "sit"
      |  
      +- <CONTENT> ::= <BRACKETS>
         |  
         +- <BRACKETS> ::= (<CONTENT>)
            |  
            +- <CONTENT> ::= [^\(\)]+
               |  
               +- [^\(\)]+ ~ "amet"
```

Full source code [here](https://github.com/ditrytus/noam/blob/develop/examples/text-brackets/text_brackets.cpp).

## Documentation

Docs are maintained in this repositories [wiki](https://github.com/ditrytus/noam/wiki).

## FAQ

##### Parsing strings? Why not using regular expressions?

In many cases regular expressions are the right tool to use. Whenever you just want to check if a string matches a certain pattern than you should use regular expression. However what a regular expression wont give you is the tree representing of the internal structure. Whenever you are more interested in the structure of string rather than a specific value than you should use a parser.

##### Why not using YACC or Bison instead?

Noam is intended to be a lot simpler and faster to use. You are not required to integrate any additional tools or steps in your build process and defining a simple grammar is just a few lines of code. Additionally since grammars are built in run-time you can generate them dynamically. Because of that Noam is suited for simple scenarios, if you are aiming to create your own programming language than YACC and Bison would be a tools for you. 

##### Why "Noam"?

To honor american linguist, philosopher and political activist [Noam Chomsky](https://en.wikipedia.org/wiki/Noam_Chomsky) whose theoretical work on computer linguistics and programming languages is a foundation of all modern compilers.

