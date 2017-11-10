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
//  S -> A
//  A -> I T
//  I -> N
//  I -> L N T R
//  T -> O I
//  T -> T T
//  T -> (palavra-vazia)
//  N -> 1, 2, 3, 4, 5, 6, 7, 8, 9
//  N -> N N
//  O -> +, -, *, /
//  R -> )
//  L -> (
//
//  PALAVRA A SER RECONHECIDA
//

const char * PALAVRA = "(33+(4-(3*(4*31231+(331231*3+3+3*(8732+32))))))";

//
//


#include <stdio.h>

void I();
void T();
void S();
void N();
void R();
void L();
void O();
void A();

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
int i = 0;

void proximo() {
    i++;
    atual = PALAVRA[i];
}

void error() {
    printf("Erro no token %c, posicao %i", atual, i + 1);
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

void I() {
    if (aceita(pare)) {
        L();
        N();
        T();
        R();
    } else {
        N();
    }
}

void T() {
    if (aceita(NULL)) { //palavra vazia
        printf("Linguagem reconhecida \n");
        return;
    } else if (aceita(pard)) {
        ;
    } else {
        O();
        I();
        T();
    }
}

void A() {
    I();
    T();
}

void S() {
    A();
}

void reconhece() {
    atual = PALAVRA[0];
    S();
}

int main(int argc, const char * argv[]) {
    reconhece();
    return 0;
}


