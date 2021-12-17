#include <stdio.h>
#include <stdlib.h>
#include "psinfo.h"
#include "dynamicArray.h"

void printFile();

int main()
{
    Array arrayPsinfos;
    printFile(arrayPsinfos);
    return 0;
}

// Recibe como argumento un array de psinfos
void printFile(Array arrayPsinfos){ // <- Pasarle el array
    // Crea y abre el archivo en modo escritura. (Falta pasarle los PIDs como parametros para que los ponga en el nombre del archivo)
    int i = 0;
    FILE *fPtr;

    //for para sacar los pids
    fPtr = fopen("./psinfo-report-pids.info", "w");

    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    
    fputs("-- Información recolectada!!!\n", fPtr);
    for(i = 0; i < arrayPsinfos.size ; i++){
    //fputs(data, fPtr); //Representa uno de los atributos, se ponen uno a uno los atributos del psinfo[i]
    fputs("Info del psinfo", fPtr);
    fputs("\n", fPtr); //Se agrega esta para el salto de linea
    };


    fclose(fPtr);
    printf("Archivo de salida generado: psinfo-report-pid.info \n");
};