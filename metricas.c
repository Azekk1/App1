#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NAME_LENGTH 100
#define MAX_DATE_LENGTH 20
#define MAX_TIME_LENGTH 20
#define MAX_INGREDIENTS_LENGTH 200
#define MAX_ORDERS 10000

struct order {
    int pizza_id;
    int order_id;
    char pizza_name_id[MAX_NAME_LENGTH];
    int quantity;
    char order_date[MAX_DATE_LENGTH];
    char order_time[MAX_TIME_LENGTH];
    float unit_price;
    float total_price;
    char pizza_size[MAX_NAME_LENGTH];
    char pizza_category[MAX_NAME_LENGTH];
    char pizza_ingredients[MAX_INGREDIENTS_LENGTH];
    char pizza_name[MAX_NAME_LENGTH];
};

void limpiar_entrada(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

//CREANDO CALCULO PIZZA MAS VENDIDA - pms
char* pms(int *size, struct order *orders) {
    int max_cantidad = 0;
    int index_mas_vendida = -1;

    char nombres[MAX_ORDERS][MAX_NAME_LENGTH];
    int cantidades[MAX_ORDERS];
    int n_distintas = 0;

    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < n_distintas; j++) {
            if (strcmp(nombres[j], orders[i].pizza_name_id) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            strncpy(nombres[n_distintas], orders[i].pizza_name_id, MAX_NAME_LENGTH);
            cantidades[n_distintas] = orders[i].quantity;
            n_distintas++;
        }
    }

    //buscar indice de la pizza mas vendida
    for (int i = 0; i < n_distintas; i++) {
        if (cantidades[i] > max_cantidad) {
            max_cantidad = cantidades[i];
            index_mas_vendida = i;
        }
    }

    //buscamos el nombre completo de la pizza mas vendida
    for (int i = 0; i < *size; i++) {
        if (strcmp(orders[i].pizza_name_id, nombres[index_mas_vendida]) == 0) {
            char* resultado = malloc(strlen(orders[i].pizza_name) + 1);
            strcpy(resultado, orders[i].pizza_name);
            return resultado;
        }
    }

    return NULL;
}

//CALCULAMOS PIZZA MENOS VENDIDA - pls
char* pls(int *size, struct order *orders) {
    int cantidades[MAX_ORDERS];
    char nombres[MAX_ORDERS][MAX_NAME_LENGTH];
    int n_distintas = 0;

    //ver cuaantas unidades se vendieron de cada pizza
    for (int i = 0; i < *size; i++) {
        int encontrado = 0;
        for (int j = 0; j < n_distintas; j++) {
            if (strcmp(nombres[j], orders[i].pizza_name_id) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strncpy(nombres[n_distintas], orders[i].pizza_name_id, MAX_NAME_LENGTH);
            cantidades[n_distintas] = orders[i].quantity;
            n_distintas++;
        }
    }

    //encontrar indice de la pizza menos vendida
    int min_cantidad = cantidades[0];
    int index_menos_vendida = 0;
    for (int i = 1; i < n_distintas; i++) {
        if (cantidades[i] < min_cantidad) {
            min_cantidad = cantidades[i];
            index_menos_vendida = i;
        }
    }

    //buscar el nombre completo 
    for (int i = 0; i < *size; i++) {
        if (strcmp(orders[i].pizza_name_id, nombres[index_menos_vendida]) == 0) {
            char* resultado = malloc(strlen(orders[i].pizza_name) + 1);
            if (resultado) {
                strcpy(resultado, orders[i].pizza_name);
            }
            return resultado;
        }
    }

    return NULL;
}

//FECHA CON MAS VENTAS DINERO RECAUDADO
char* dms(int *size, struct order *orders) {
    char fechas[MAX_ORDERS][MAX_DATE_LENGTH];
    float montos[MAX_ORDERS];
    int n_fechas = 0;

    //agrupar por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < n_fechas; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                montos[j] += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada) {
            strncpy(fechas[n_fechas], orders[i].order_date, MAX_DATE_LENGTH);
            montos[n_fechas] = orders[i].total_price;
            n_fechas++;
        }
    }

    //encontrar la fecha con mas dinero recaudado
    float max_monto = 0.0;
    int index_max = -1;
    for (int i = 0; i < n_fechas; i++) {
        if (montos[i] > max_monto) {
            max_monto = montos[i];
            index_max = i;
        }
    }

    if (index_max == -1) return NULL;

    //crear el resultado como string dinámico
    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "%s - $%.2f", fechas[index_max], max_monto);
    }

    return resultado;
}

//FECHA CON MENOS VENTAS EN DINERO
char* dls(int *size, struct order *orders) {
    char fechas[MAX_ORDERS][MAX_DATE_LENGTH];
    float montos[MAX_ORDERS];
    int n_fechas = 0;

    // Agrupar montos por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < n_fechas; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                montos[j] += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada) {
            strncpy(fechas[n_fechas], orders[i].order_date, MAX_DATE_LENGTH);
            montos[n_fechas] = orders[i].total_price;
            n_fechas++;
        }
    }

    if (n_fechas == 0) return NULL;

    // Buscar la fecha con menor recaudación
    float min_monto = montos[0];
    int index_min = 0;

    for (int i = 1; i < n_fechas; i++) {
        if (montos[i] < min_monto) {
            min_monto = montos[i];
            index_min = i;
        }
    }

    // Formatear y retornar resultado
    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "%s - $%.2f", fechas[index_min], min_monto);
    }

    return resultado;
}

//FECHA CON MAS VENTAS EN CANTIDAD - dmsp
char* dmsp(int *size, struct order *orders) {
    char fechas[MAX_ORDERS][MAX_DATE_LENGTH];
    int cantidades[MAX_ORDERS];
    int n_fechas = 0;

    // Agrupar cantidades por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < n_fechas; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada) {
            strncpy(fechas[n_fechas], orders[i].order_date, MAX_DATE_LENGTH);
            cantidades[n_fechas] = orders[i].quantity;
            n_fechas++;
        }
    }

    if (n_fechas == 0) return NULL;

    // Buscar la fecha con más pizzas
    int max_pizzas = cantidades[0];
    int index_max = 0;

    for (int i = 1; i < n_fechas; i++) {
        if (cantidades[i] > max_pizzas) {
            max_pizzas = cantidades[i];
            index_max = i;
        }
    }

    // Formatear resultado
    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "%s - %d pizzas", fechas[index_max], max_pizzas);
    }

    return resultado;
}

//FECHA CON MENOS VENTAS EN CANTIDAD
char* dlsp(int *size, struct order *orders) {
    char fechas[MAX_ORDERS][MAX_DATE_LENGTH];
    int cantidades[MAX_ORDERS];
    int n_fechas = 0;

    // Agrupar cantidades por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < n_fechas; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }
        if (!encontrada) {
            strncpy(fechas[n_fechas], orders[i].order_date, MAX_DATE_LENGTH);
            cantidades[n_fechas] = orders[i].quantity;
            n_fechas++;
        }
    }

    if (n_fechas == 0) return NULL;

    // Buscar la fecha con menos pizzas
    int min_pizzas = cantidades[0];
    int index_min = 0;

    for (int i = 1; i < n_fechas; i++) {
        if (cantidades[i] < min_pizzas) {
            min_pizzas = cantidades[i];
            index_min = i;
        }
    }

    // Formatear resultado
    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "%s - %d pizzas", fechas[index_min], min_pizzas);
    }

    return resultado;
}

//PROMEDIO DE PIZZAS POR ORDEN
char* apo(int *size, struct order *orders) {
    int total_pizzas = 0;
    int ordenes_unicas[MAX_ORDERS];
    int total_ordenes = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        int ya_registrada = 0;
        for (int j = 0; j < total_ordenes; j++) {
            if (ordenes_unicas[j] == orders[i].order_id) {
                ya_registrada = 1;
                break;
            }
        }

        if (!ya_registrada) {
            ordenes_unicas[total_ordenes++] = orders[i].order_id;
        }
    }

    if (total_ordenes == 0) return NULL;

    float promedio = (float) total_pizzas / total_ordenes;

    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "Promedio de pizzas por orden: %.2f", promedio);
    }

    return resultado;
}

// PROMEDIO PIZZAS POR DIA (cantidad de pizzas/fechas)
char* apd(int *size, struct order *orders) {
    int total_pizzas = 0;
    char fechas_unicas[MAX_ORDERS][MAX_DATE_LENGTH];
    int total_fechas = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        int ya_esta = 0;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(fechas_unicas[j], orders[i].order_date) == 0) {
                ya_esta = 1;
                break;
            }
        }

        if (!ya_esta) {
            strncpy(fechas_unicas[total_fechas++], orders[i].order_date, MAX_DATE_LENGTH);
        }
    }

    if (total_fechas == 0) return NULL;

    float promedio = (float) total_pizzas / total_fechas;

    char* resultado = malloc(100);
    if (resultado) {
        snprintf(resultado, 100, "Promedio de pizzas por día: %.2f", promedio);
    }

    return resultado;
}

//INGGREDIENTE MAS VENDIDO
char* ims(int *size, struct order *orders) {
    char ingredientes[MAX_ORDERS * 5][MAX_NAME_LENGTH];
    int cantidades[MAX_ORDERS * 5];
    int n_ingredientes = 0;

    for (int i = 0; i < *size; i++) {
        char ingredientes_local[MAX_INGREDIENTS_LENGTH];
        strncpy(ingredientes_local, orders[i].pizza_ingredients, MAX_INGREDIENTS_LENGTH);

        // Separar por coma
        char* token = strtok(ingredientes_local, ",");
        while (token != NULL) {
            // Limpiar espacios al inicio
            while (*token == ' ') token++;

            int encontrado = 0;
            for (int j = 0; j < n_ingredientes; j++) {
                if (strcmp(ingredientes[j], token) == 0) {
                    cantidades[j] += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                strncpy(ingredientes[n_ingredientes], token, MAX_NAME_LENGTH);
                cantidades[n_ingredientes] = orders[i].quantity;
                n_ingredientes++;
            }

            token = strtok(NULL, ",");
        }
    }

    // Buscar el ingrediente más vendido
    int max_cantidad = 0;
    int index_max = -1;

    for (int i = 0; i < n_ingredientes; i++) {
        if (cantidades[i] > max_cantidad) {
            max_cantidad = cantidades[i];
            index_max = i;
        }
    }

    if (index_max == -1) return NULL;

    char* resultado = malloc(strlen(ingredientes[index_max]) + 1);
    if (resultado) {
        strcpy(resultado, ingredientes[index_max]);
    }

    return resultado;
}


//CANTIDAD DE PIZZAS POR CATEGORIA VENDIDAS
char* hp(int *size, struct order *orders) {
    char categorias[MAX_ORDERS][MAX_NAME_LENGTH];
    int cantidades[MAX_ORDERS];
    int n_categorias = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < n_categorias; j++) {
            if (strcmp(categorias[j], orders[i].pizza_category) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strncpy(categorias[n_categorias], orders[i].pizza_category, MAX_NAME_LENGTH);
            cantidades[n_categorias] = orders[i].quantity;
            n_categorias++;
        }
    }

    // Construir el resultado en un string
    char* resultado = malloc(n_categorias * 50);  // asumimos hasta 50 caracteres por línea
    if (!resultado) return NULL;
    resultado[0] = '\0';  // inicializar cadena vacía

    for (int i = 0; i < n_categorias; i++) {
        char linea[150];
        snprintf(linea, sizeof(linea), "%s: %d\n", categorias[i], cantidades[i]);
        strcat(resultado, linea);
    }

    return resultado;
}




//leemos CSV que puede o no estar entre comillas
char* leer_campo_csv(char** cursor) {
    static char buffer[MAX_LINE_LENGTH];
    char* ptr = buffer;
    int entre_comillas = 0;

    if (**cursor == '"') {
        entre_comillas = 1;
        (*cursor)++;
    }

    while (**cursor) {
        if (entre_comillas) {
            if (**cursor == '"' && *((*cursor)+1) == ',') {
                (*cursor) += 2;  //saltar comilla y coma
                break;
            }
        } else {
            if (**cursor == ',') {
                (*cursor)++;
                break;
            }
        }

        *ptr++ = *(*cursor)++;
    }

    *ptr = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {

    // Verifica si se cumplen los requisitos para correr el código en el terminal
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <comando1> [comando2] ...\n", argv[0]);
        return 1;
    }

    // Abrir archivo CSV especificado en el terminal
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error al abrir el archivo: %s\n", argv[1]);
        return 1;
    }

    struct order* orders = malloc(sizeof(struct order) * MAX_ORDERS);
    if (!orders) {
        perror("Error al asignar memoria");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    //saltamos primera linea
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && count < MAX_ORDERS) {
        limpiar_entrada(line);
        struct order temp;

        char* cursor = line;

        temp.pizza_id = atoi(leer_campo_csv(&cursor));
        temp.order_id = atoi(leer_campo_csv(&cursor));
        strncpy(temp.pizza_name_id, leer_campo_csv(&cursor), MAX_NAME_LENGTH);
        temp.quantity = atoi(leer_campo_csv(&cursor));
        strncpy(temp.order_date, leer_campo_csv(&cursor), MAX_DATE_LENGTH);
        strncpy(temp.order_time, leer_campo_csv(&cursor), MAX_TIME_LENGTH);
        temp.unit_price = atof(leer_campo_csv(&cursor));
        temp.total_price = atof(leer_campo_csv(&cursor));
        strncpy(temp.pizza_size, leer_campo_csv(&cursor), MAX_NAME_LENGTH);
        strncpy(temp.pizza_category, leer_campo_csv(&cursor), MAX_NAME_LENGTH);
        strncpy(temp.pizza_ingredients, leer_campo_csv(&cursor), MAX_INGREDIENTS_LENGTH);
        strncpy(temp.pizza_name, leer_campo_csv(&cursor), MAX_NAME_LENGTH);

        orders[count++] = temp;

        
    }

    printf("Se procesaron %d pedidos correctamente.\n", count);

    // Comandos que se desean correr desde el terminal
    for (int j = 2; j < argc; j++) {
        //entrega pizza mas vendida
        if (strcmp(argv[j], "pms") == 0) {
            char* mas_vendida = pms(&count, orders);
            if (mas_vendida) {
            printf("Pizza más vendida: %s\n", mas_vendida);
            free(mas_vendida); // liberar memoria reservada por pms  
            }
        }
        //entrega pizza menos vendida 
        if (strcmp(argv[j], "pls") == 0) {
            char* menos_vendida = pls(&count, orders);
            if (menos_vendida) {
            printf("Pizza menos vendida: %s\n", menos_vendida);
            free(menos_vendida);
            }
        }
        //fecha con mas ventas $$$$
        if (strcmp(argv[j], "dms") == 0) {
            char* fecha_mayor_ventas = dms(&count, orders);
            if (fecha_mayor_ventas) {
            printf("Día con más ventas: %s\n", fecha_mayor_ventas);
            free(fecha_mayor_ventas);
            }
        }
        //fecha con menos ventas $$$
        if (strcmp(argv[j], "dls") == 0){
            char* fecha_menor_ventas = dls(&count, orders);
            if (fecha_menor_ventas) {
            printf("Día con menos ventas: %s\n", fecha_menor_ventas);
            free(fecha_menor_ventas);   
            }
        }
        //fecha con mas ventas en cantidad
        if (strcmp(argv[j], "dmsp") == 0){
            char* fecha_mas_pizzas = dmsp(&count, orders);
            if (fecha_mas_pizzas) {
            printf("Fecha con más pizzas vendidas: %s\n", fecha_mas_pizzas);
            free(fecha_mas_pizzas);
            }
        }
        //fecha con menos ventas en cantidad
        if (strcmp(argv[j], "dlsp") == 0){
            char* fecha_menos_pizzas = dlsp(&count, orders);
            if (fecha_menos_pizzas) {
                printf("Fecha con menos pizzas vendidas: %s\n", fecha_menos_pizzas);
                free(fecha_menos_pizzas);
            }
        }
        //promedio de pizzas por orden
        if (strcmp(argv[j], "apo") == 0){
            char* promedio_pizzas = apo(&count, orders);
            if (promedio_pizzas) {
                printf("%s\n", promedio_pizzas);
                free(promedio_pizzas);
            }
        }
        //promedio pizzas por dia
        if (strcmp(argv[j], "apd") == 0){
            char* promedio_por_dia = apd(&count, orders);
            if (promedio_por_dia) {
                printf("%s\n", promedio_por_dia);
                free(promedio_por_dia);
            }
        }
        //ingrediente mas vendido
        if (strcmp(argv[j], "ims") == 0){
            char* ingrediente_mas_vendido = ims(&count, orders);
            if (ingrediente_mas_vendido) {
                printf("Ingrediente más vendido: %s\n", ingrediente_mas_vendido);
                free(ingrediente_mas_vendido);
            }
        }
        //cantidad de pizzas por categoria
        if (strcmp(argv[j], "hp") == 0){
            char* pizzas_por_categoria = hp(&count, orders);
            if (pizzas_por_categoria) {
                printf("Cantidad de pizzas por categoría:\n%s", pizzas_por_categoria);
                free(pizzas_por_categoria);
            }
        }
    }
    free(orders);
    fclose(file);
    return 0;
}
