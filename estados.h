#ifndef TIPO_ENUM_H
#define TIPO_ENUM_H

#define CANT_ESTADOS 8
#define CANT_CLASES_CARACTERES 7
#define ESTADO_INICIAL Q0
#define ESTADO_FINAL_DECIMAL Q2
#define ESTADO_FINAL_OCTAL_CERO Q1
#define ESTADO_FINAL_OCTAL_OTROS Q5
#define ESTADO_FINAL_HEXADECIMAL Q4
#define CENTINELA '#'

typedef enum {
    Q0, Q1, Q2, Q3, Q4, Q5, Q6, Q7
} t_estado;

typedef enum {
    COL1,COL2,COL3,COL4,COL5,COL6,COL7
} t_caracter;

/*
    Columna 1: 0
    Columna 2: [1-7]
    Columna 3: [8-9]
    Columna 4: [a-fA-F]
    Columna 5: [xX]
    Columna 6: Otros caracteres
*/

#endif // TIPO_ENUM_H
