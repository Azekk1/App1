#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main() {
    //abrir el CSV en modo lectura
    FILE *archivo = fopen("ventas.csv", "r"); 
    //en caso que no este el archivo
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char *linea = NULL; //puntero para almacenar la línea, con NULL no apunta a ninguna direccion valida de memoria
    size_t len = 0;     //tamaño inicial
    ssize_t read;       //tamaño de la línea leída
    int primeraLinea = 1; //saltar primera linea

    //leer línea por línea usando getline (ajusta automáticamente el tamaño de línea)
    while ((read = getline(&linea, &len, archivo)) != -1) {  // mientras no sea = a -1 el bucle sigue, quiere decir que hay mas lineas por leer
        if (primeraLinea) { 
            primeraLinea = 0; //saltar la primera linea 
            continue;
        }

        //variables para almacenar cada campo
        char *pizza_id = strtok(linea, ",");
        char *order_id = strtok(NULL, ",");
        char *pizza_name_id = strtok(NULL, ",");
        char *quantity = strtok(NULL, ",");
        char *order_date = strtok(NULL, ",");
        char *order_time = strtok(NULL, ",");
        char *unit_price = strtok(NULL, ",");
        char *total_price = strtok(NULL, ",");
        char *pizza_size = strtok(NULL, ",");
        char *pizza_category = strtok(NULL, ",");
        char *pizza_ingredients = strtok(NULL, ",");
        char *pizza_name = strtok(NULL, "\n"); // Último campo hasta el salto de línea

        //convertir los valores numéricos 
        int cantidad = atoi(quantity);
        double precio_unitario = atof(unit_price);
        double precio_total = atof(total_price);

        // Mostrar los datos leídos
        printf("ID: %s, Orden: %s, Nombre: %s, Cantidad: %d, Fecha: %s, Precio Total: %.2f, Categoría: %s, Pizza: %s\n",
               pizza_id, order_id, pizza_name_id, cantidad, order_date, precio_total, pizza_category, pizza_name);
    }

    free(linea); //liberar memoria de getline()
    fclose(archivo); //cerramos el archivo
    return 0;
}
