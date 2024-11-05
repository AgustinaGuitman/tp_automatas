#include <stdlib.h>
#include <stdio.h>
#include "fAuxiliares.h"

/**
 * @brief Función principal
 * 
 * 
 * @param argc Cantidad de argumentos que se agregan por línea de comando (terminal)
 * @param argv Direcciones de los argumentos
 * @return int 
 */
int main(int argc, char* argv[]){
    if(argc < 3) {
        printf("Error. No se ingresaron la cantidad necesaria de argumentos.\n");
        return EXIT_FAILURE;
    }

    /*int cant_decimal = 0;
    int cant_octal = 0;
    int cant_hexa = 0;*/

    FILE* input = fopen(argv[1], "r");
    if(input == NULL) {
        printf("Error al intentar abrir el archivo %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    FILE* output = fopen(argv[2], "w");

    lexer(input,output);

    fclose(input);
    fclose(output);

    printf("Se reconocieron %d numeros decimales, %d numeros octales y %d numeros hexadecimales\n", cant_decimal, cant_octal, cant_hexa);
    
    return EXIT_SUCCESS;
}
