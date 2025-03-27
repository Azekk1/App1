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

//pizza mas vendida - pms
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

    // Buscar índice de la pizza más vendida
    for (int i = 0; i < n_distintas; i++) {
        if (cantidades[i] > max_cantidad) {
            max_cantidad = cantidades[i];
            index_mas_vendida = i;
        }
    }

    // Buscar el nombre completo de la pizza más vendida
    for (int i = 0; i < *size; i++) {
        if (strcmp(orders[i].pizza_name_id, nombres[index_mas_vendida]) == 0) {
            char* resultado = malloc(strlen(orders[i].pizza_name) + 1);
            strcpy(resultado, orders[i].pizza_name);
            return resultado;
        }
    }

    return NULL;
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
                (*cursor) += 2;  // Saltar comilla y coma
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

int main() {
    FILE *file = fopen("ventas.csv", "r");
    if (!file) {
        perror("Error al abrir el archivo");
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

        //print de depuracion, lo podemos eliminar al ver que este todo bien
        printf("Pedido %d:\n", count);
        printf("  Pizza ID: %d\n", temp.pizza_id);
        printf("  Order ID: %d\n", temp.order_id);
        printf("  Pizza Name ID: %s\n", temp.pizza_name_id);
        printf("  Cantidad: %d\n", temp.quantity);
        printf("  Fecha: %s\n", temp.order_date);
        printf("  Hora: %s\n", temp.order_time);
        printf("  Precio unitario: %.2f\n", temp.unit_price);
        printf("  Precio total: %.2f\n", temp.total_price);
        printf("  Tamaño: %s\n", temp.pizza_size);
        printf("  Categoría: %s\n", temp.pizza_category);
        printf("  Ingredientes: %s\n", temp.pizza_ingredients);
        printf("  Nombre pizza: %s\n", temp.pizza_name);
        printf("-------------------------------------\n");
    }

    printf("Se procesaron %d pedidos correctamente.\n", count);
    char* mas_vendida = pms(&count, orders);
    if (mas_vendida) {
       printf("Pizza más vendida: %s\n", mas_vendida);
       free(mas_vendida); // liberar memoria reservada por pms
}



    free(orders);
    fclose(file);
    return 0;
}
