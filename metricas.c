//agregamos librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//longitudes maximas 
#define MAX_LINE_LENGTH 1024
#define MAX_DATE_LENGTH 20
#define MAX_TIME_LENGTH 20
#define MAX_NAME_LENGTH 100  //incluye pizza_name pizza_size y pizza_category
#define MAX_INGREDIENTS_LENGTH 200
#define MAX_ORDERS 10000 //maximo de pedidos que podemos manejar

//definimos estructura 
struct order {
    int pizza_id;                        //ID de la pizza
    int order_id;                        //ID de la orden
    int pizza_name_id;                   //ID del nombre de la pizza
    int quantity;                        //cantidad de pizzas en la orden
    char order_date[MAX_DATE_LENGTH];      //fecha del pedido (YYYY-MM-DD)
    char order_time[MAX_TIME_LENGTH];        //hora del pedido (HH:MM:SS)
    float unit_price;                       //precio unitario de la pizza
    float total_price;                     //precio total (quantity * unit_price)
    char pizza_size[MAX_NAME_LENGTH];      //tamaño de la pizza (S, M, L, XL)
    char pizza_category[MAX_NAME_LENGTH];  //categoría de la pizza (Clásica, Vegetariana, etc.)
    char pizza_ingredients[MAX_INGREDIENTS_LENGTH];  //ingredientes de la pizza
    char pizza_name[MAX_NAME_LENGTH];   //nombre completo de la pizza
};

//funcion para dividir el CSV y almacenar los datos en la estructura order
void parse_csv(FILE *csv_file, struct order *orders, int *order_count) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), csv_file)) {
        // Separar los valores por coma (",")
        char *token = strtok(line, ",");
        
        // Parsear los valores y asignarlos a la estructura `order`
        orders[*order_count].pizza_id = atoi(token); // pizza_id
        token = strtok(NULL, ",");
        
        orders[*order_count].order_id = atoi(token); // order_id
        token = strtok(NULL, ",");
        
        orders[*order_count].pizza_name_id = atoi(token); // pizza_name_id
        token = strtok(NULL, ",");
        
        orders[*order_count].quantity = atoi(token); // quantity
        token = strtok(NULL, ",");
        
        strcpy(orders[*order_count].order_date, token); // order_date
        token = strtok(NULL, ",");
        
        strcpy(orders[*order_count].order_time, token); // order_time
        token = strtok(NULL, ",");
        
        orders[*order_count].unit_price = atof(token); // unit_price
        token = strtok(NULL, ",");
        
        orders[*order_count].total_price = atof(token); // total_price
        token = strtok(NULL, ",");
        
        strcpy(orders[*order_count].pizza_size, token); // pizza_size
        token = strtok(NULL, ",");
        
        strcpy(orders[*order_count].pizza_category, token); // pizza_category
        token = strtok(NULL, ",");
        
        strcpy(orders[*order_count].pizza_ingredients, token); // pizza_ingredients
        token = strtok(NULL, """");
        
        strcpy(orders[*order_count].pizza_name, token); // pizza_name
        
        // Aumentar el contador de órdenes
        (*order_count)++;
    }
}

//definicion de funcion para cada metrica
// Función para obtener la pizza más vendida
char* pizza_mas_vendida(int *size, struct order *orders) {
    static char result[100];
    int max_sales = 0;
    char pizza_name[50];
    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity > max_sales) {
            max_sales = orders[i].quantity;
            strcpy(pizza_name, orders[i].pizza_name);
        }
    }
    sprintf(result, "Pizza más vendida: %s", pizza_name);
    return result;
}


//funcion para pizza menos vendida
char* pizza_menos_vendida(int *size, struct order *orders) {
    // Implementación para encontrar la pizza menos vendida
    // Devolver el nombre de la pizza menos vendida
}

// Función para obtener la fecha con más ventas en términos de dinero
char* fecha_mas_ventas_dinero(int *size, struct order *orders) {
    // Implementación para encontrar la fecha con más ventas en dinero
    // Devolver la fecha con la cantidad de dinero recaudado
}

// Función para obtener la fecha con menos ventas en términos de dinero
char* fecha_menos_ventas_dinero(int *size, struct order *orders) {
    // Implementación para encontrar la fecha con menos ventas en dinero
    // Devolver la fecha con la cantidad de dinero recaudado
}

// Función para obtener la fecha con más ventas en términos de cantidad de pizzas
char* fecha_mas_ventas_pizzas(int *size, struct order *orders) {
    // Implementación para encontrar la fecha con más ventas en cantidad de pizzas
    // Devolver la fecha con la cantidad de pizzas vendidas
}

// Función para obtener la fecha con menos ventas en términos de cantidad de pizzas
char* fecha_menos_ventas_pizzas(int *size, struct order *orders) {
    // Implementación para encontrar la fecha con menos ventas en cantidad de pizzas
    // Devolver la fecha con la cantidad de pizzas vendidas
}

// Función para obtener el promedio de pizzas por orden
char* promedio_pizzas_por_orden(int *size, struct order *orders) {
    // Implementación para calcular el promedio de pizzas por orden
    // Devolver el promedio como una cadena formateada
}

// Función para obtener el promedio de pizzas por día
char* promedio_pizzas_por_dia(int *size, struct order *orders) {
    // Implementación para calcular el promedio de pizzas por día
    // Devolver el promedio como una cadena formateada
}

// Función para obtener el ingrediente más vendido
char* ingrediente_mas_vendido(int *size, struct order *orders) {
    // Implementación para encontrar el ingrediente más vendido
    // Devolver el nombre del ingrediente más vendido
}

// Función para obtener la cantidad de pizzas por categoría vendidas
char* cantidad_pizzas_por_categoria(int *size, struct order *orders) {
    // Implementación para contar la cantidad de pizzas por categoría vendidas
    // Devolver las cantidades por categoría como una cadena formateada
}

//arreglo de punteros a funciones para cada métrica, llamamos en funcion de la metrica solicitada 
char* (*metrics[])(int *, struct order *) = {
    pizza_mas_vendida,
    pizza_menos_vendida,
    fecha_mas_ventas_dinero,
    fecha_menos_ventas_dinero,
    fecha_mas_ventas_pizzas,
    fecha_menos_ventas_pizzas,
    promedio_pizzas_por_orden,
    promedio_pizzas_por_dia,
    ingrediente_mas_vendido,
    cantidad_pizzas_por_categoria
};


//FUNCION PRINCIPAL lee CSV y aplica metricas
//argc ----> cantidad de argimentos
//argv ----> arreglo de argumentos en foemato txt
int main(int argc, char *argv[]) {
    //si no hay argumentos  suficientes mostramos error
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo_csv> <metrica1> <metrica2> ...\n", argv[0]);
        return 1;
    }


    //ABRIMOS CSV
    char *csv_filename = argv[1];
    FILE *csv_file = fopen(csv_filename, "r");
    if (!csv_file) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", csv_filename);
        return 1;
    }

    //leemos ordenes del csv 
    char line[MAX_LINE_LENGTH];  //almacenamos temporalmente cad alinea del csv
    struct order orders[MAX_ORDERS];  //asumimos un maximo de ordenes
    int order_count = 0;

    // Llamamos a la función de parseo
    parse_csv(csv_file, orders, &order_count);


    //fgets lee cada linea
    while (fgets(line, sizeof(line), csv_file)) {
        //implementacion para leer cada linea para separar los valores y almacenar los datos en la estructura order
        order_count++;
    }

    

    //calculamos y mostramos las metricas pedidas
    int num_metrics = argc - 2;
    for (int i = 0; i < num_metrics; i++) {
        int size;
        char *result = metrics[i](&size, orders);
        printf("%s\n", result);
    }

    

    return 0;
}

