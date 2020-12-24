# tiny-compiler
A tiny compiler that compiles or interprets simple mathematical expressions.

tiny-compiler uses a very simple grammar, the BNF is currently as follows:
```
expression = term {('+'|'-') term}
term = factor {('*'|'/') factor}

factor = '(' expr ')'
       | number
       | float
```
