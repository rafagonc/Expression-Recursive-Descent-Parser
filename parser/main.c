//
//  main.c
//  parser
//
//  Rafael Gonçalves
//  TIA: 31304427
//
//  Alfabeto:
//  E = {1, 2, 3, 4, 5, 6, 7, 8, 9, (, ), +, -, *, /}
//
//  Regras de produção
//
//  S -> A S
//  S -> (palavra-vazia)
//  A -> L S
//  A -> N T
//  T -> O N
//  N -> 1, 2, 3, 4, 5, 6, 7, 8, 9
//  N -> N N
//  O -> +, -, *, /
//  R -> )
//  L -> (
//
// S - A S - L A R S - L N T R
//
//  Created by Rafael Gonzalves on 11/6/17.
//  Copyright © 2017 Rafael Gonzalves. All rights reserved.
//

#include <stdio.h>

typedef enum E  {
    mais = '+',
    menos = '-',
    multiplica = '*',
    divide = '/',
    pare = '(',
    pard = ')',
    zero = '0',
    um = '1',
    dois = '2',
    tres = '3',
    quatro = '4',
    cinco = '5',
    seis = '6',
    sete = '7',
    oito = '8',
    nove = '9',
    
} E;

E atual;
int i;
const char * sequencia;

void proximo() {
    i++;
    atual = sequencia[i];
}

void error() {
    printf("Erro no token %c, posicao %i", atual, i);
    abort();
}

int aceita(E e) {
    if (atual == e) {
        return 1;
    }
    return 0;
}

void L() {
    if (aceita(pare)) {
        proximo();
    } else {
        error();
    }
}

void O() {
    if (aceita(mais) ||
        aceita(menos) ||
        aceita(multiplica) ||
        aceita(divide)) {
        proximo();
    } else {
        error();
    }
}

void R() {
    if (aceita(pard)) {
        proximo();
    } else {
        error();
    }
}

void N() {
    if (aceita(um) ||
           aceita(dois) ||
           aceita(tres) ||
           aceita(quatro) ||
           aceita(cinco) ||
           aceita(seis) ||
           aceita(sete) ||
           aceita(oito) ||
           aceita(nove)) {
        while (aceita(um) ||
               aceita(dois) ||
               aceita(tres) ||
               aceita(quatro) ||
               aceita(cinco) ||
               aceita(seis) ||
               aceita(sete) ||
               aceita(oito) ||
               aceita(nove)) {
            proximo();
        }
    } else {
        error();
    }
}

void T() {
    N();
    O();
    N();
}

void A1() {
    L();
    T();
    R();
}

void A2() {
    T();
}

void A() {
    if (aceita(pare /* = ( */)) {
        A1();
    } else {
        A2();
    }
}



int S() {
    if (atual == NULL) {
        return 1;
    }
    A();
    return S();
}

int parse(const char * sequence) {
    sequencia = sequence;
    i = 0;
    atual = sequence[0];
    if (S()) {
        printf("Linguagem reconhecida \n");
    }
    return 1;
}

int main(int argc, const char * argv[]) {
    parse("(123+3)1+3");
    return 0;
}


