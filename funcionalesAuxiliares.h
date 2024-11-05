#include "tipoEnum.h"

#ifndef F_AUXILIARES_H
#define F_AUXILIARES_H
int cant_decimal = 0;
int cant_octal = 0;
int cant_hexa = 0;

int tablaDeTransicion[CANT_ESTADOS][CANT_CLASES_CARACTERES] = {
// COL1:'0',COL2: '1-7', COL3: '8-9', COL4: 'a-f/A-F', COL5: 'x/X', COL6: '+/-', COL7: otro
    {Q1, Q2, Q2, Q7, Q7, Q6, Q7},
    {Q5, Q5, Q7, Q7, Q3, Q7, Q7},
    {Q2, Q2, Q2, Q7, Q7, Q7, Q7},
    {Q4, Q4, Q4, Q4, Q7, Q7, Q7},
    {Q4, Q4, Q4, Q4, Q7, Q7, Q7},
    {Q5, Q5, Q7, Q7, Q7, Q7, Q7},
    {Q7, Q7, Q7, Q7, Q7, Q7, Q7}
};


// Prototipos de las funciones
t_caracter seleccionar_COL_en_TT(char);

void lexer(FILE*, FILE*);

void tipoDeConstante (int, FILE*);

// Definiciones de las funciones

/**
 * @brief Seleccionar columna de la tabla de la TT
 * 
 * Dado un caracter selecciona una columna de la tabla principal
 * 
 * @param c Caracter leído
 * @return Columna seleccionada 
 */
t_caracter seleccionar_COL_en_TT(char c){
    switch(c){
        case '0':
            return COL1;
        case '1'...'7': 
            return COL2;
        case '8'...'9':
            return COL3;
        case 'a'...'f': case 'A'...'F':
            return COL4;
        case 'x': case 'X':
            return COL5;  
        case '+': case '-': 
            return COL6;   
        default:
            return COL7;
    }
}

/**
 * @brief Analizador léxico
 * 
 * Dados un archivo con palabras separadas por "," devuelve un archivo formateado con las
 * palabras e indicando si se reconoció como constante real.
 * 
 * @param input Archivo de entrada con las palabras a reconocer
 * @param output Archivo de salida formateado con los resultados de reconocimiento
 */
void lexer(FILE* input, FILE* output) {
    char c;
    char palabra [100] = "";
    int i = 0;
    int estado = ESTADO_INICIAL;
    while((c = fgetc(input)) != EOF){
        if(c != CENTINELA){
            palabra [i] = c;
            estado = tablaDeTransicion[estado][seleccionar_COL_en_TT(c)];
        }
        else{
            fprintf(output, "%-10s",palabra);
            tipoDeConstante(estado,output);
            estado = ESTADO_INICIAL;
            while (i >= 0){
                palabra [i] = '\0';
                i--;
            }
        }
        ++i;
    }
    fprintf(output, "%-10s",palabra);
    tipoDeConstante(estado,output);
}

/**
 * @brief Tipo de constante
 * 
 * Dado el estado final se escribe en el archivo el tipo de constante o si no fue reconocida
 * 
 * @param estadoFinal El estado final del que depende el tipo de constante
 * @param output Archivo de salida en el que se escriben si se reconocieron las palabras o no
 */
void tipoDeConstante (int estadoFinal, FILE* output){
    switch (estadoFinal){
        case ESTADO_FINAL_DECIMAL:
            fprintf(output, "%-27s\n", "DECIMAL");
            cant_decimal++;
            break;
        case ESTADO_FINAL_OCTAL_CERO:
            fprintf(output, "%-27s\n", "OCTAL");
            cant_octal++;
            break;
        case ESTADO_FINAL_OCTAL_OTROS:
            fprintf(output, "%-27s\n", "OCTAL");
            cant_octal++;
            break;
        case ESTADO_FINAL_HEXADECIMAL:
            fprintf(output, "%-27s\n", "HEXADECIMAL");
            cant_hexa++;
            break;
        default:
            fprintf(output, "%-27s\n", "NO RECONOCIDA");
            break;
    }
}

#endif // F_AUXILIARES_H
