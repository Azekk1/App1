#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>

#define MAX_FECHAS 1000
#define MAX_PIZZAS 1000
#define MAX_INGREDIENTES 1000
#define MAX_CATEGORIAS 100

typedef struct {
    char fecha[200];
    int cantidad_pizzas;
    double total_dinero;
} VentaDia;

typedef struct {
    char nombre[1000];
    int cantidad_vendida;
} VentaPizza;

typedef struct {
    char ingrediente[1000];
    int cantidad_vendida;
} VentaIngrediente;

typedef struct {
    char categoria[1000];
    int cantidad_vendida;
} VentaCategoria;

int main(int argc, char *argv[]) {
    // Verificación de argumentos
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <comando1> [comando2] ...\n", argv[0]);
        return 1;
    }

    // Abrir archivo CSV
    FILE *archivo = fopen(argv[1], "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo: %s\n", argv[1]);
        return 1;
    }

    char *linea = NULL;
    size_t len = 0;
    ssize_t read;
    int primeraLinea = 1;

    VentaDia ventasPorFecha[MAX_FECHAS];
    int totalFechas = 0;
    VentaPizza ventasPorPizza[MAX_PIZZAS];
    int totalPizzas = 0;
    VentaIngrediente ventasPorIngrediente[MAX_INGREDIENTES];
    int totalIngredientes = 0;
    VentaCategoria ventasPorCategoria[MAX_CATEGORIAS];
    int totalCategorias = 0;
    int totalOrdenes = 0, totalPizzasVendidas = 0;

    // Leer archivo línea por línea
    while ((read = getline(&linea, &len, archivo)) != -1) {
        if (primeraLinea) { 
            primeraLinea = 0;
            continue;
        }

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
        char *pizza_ingredients = strtok(NULL, ",\n");
        char *pizza_name = strtok(NULL, "\n");

        int cantidad = atoi(quantity);
        double precio_total = atof(total_price);

        // Ventas por fecha
        int i, fechaIndex = -1;
        for (i = 0; i < totalFechas; i++) {
            if (strcmp(ventasPorFecha[i].fecha, order_date) == 0) {
                fechaIndex = i;
                break;
            }
        }
        if (fechaIndex == -1) {
            fechaIndex = totalFechas;
            strcpy(ventasPorFecha[totalFechas].fecha, order_date);
            ventasPorFecha[totalFechas].cantidad_pizzas = 0;
            ventasPorFecha[totalFechas].total_dinero = 0;
            totalFechas++;
        }
        ventasPorFecha[fechaIndex].cantidad_pizzas += cantidad;
        ventasPorFecha[fechaIndex].total_dinero += precio_total;

        // Ventas por pizza
        int pizzaIndex = -1;
        for (i = 0; i < totalPizzas; i++) {
            if (strcmp(ventasPorPizza[i].nombre, pizza_name) == 0) {
                pizzaIndex = i;
                break;
            }
        }
        if (pizzaIndex == -1) {
            pizzaIndex = totalPizzas;
            strcpy(ventasPorPizza[totalPizzas].nombre, pizza_name);
            ventasPorPizza[totalPizzas].cantidad_vendida = 0;
            totalPizzas++;
        }
        ventasPorPizza[pizzaIndex].cantidad_vendida += cantidad;

        // Ventas por ingrediente
        char *ingrediente = strtok(pizza_ingredients, ",");
        while (ingrediente != NULL) {
            int ingredienteIndex = -1;
            for (i = 0; i < totalIngredientes; i++) {
                if (strcmp(ventasPorIngrediente[i].ingrediente, ingrediente) == 0) {
                    ingredienteIndex = i;
                    break;
                }
            }
            if (ingredienteIndex == -1) {
                ingredienteIndex = totalIngredientes;
                strcpy(ventasPorIngrediente[totalIngredientes].ingrediente, ingrediente);
                ventasPorIngrediente[totalIngredientes].cantidad_vendida = 0;
                totalIngredientes++;
            }
            ventasPorIngrediente[ingredienteIndex].cantidad_vendida += cantidad;
            ingrediente = strtok(NULL, ",");
        }

        // Ventas por categoría
        int categoriaIndex = -1;
        for (i = 0; i < totalCategorias; i++) {
            if (strcmp(ventasPorCategoria[i].categoria, pizza_category) == 0) {
                categoriaIndex = i;
                break;
            }
        }
        if (categoriaIndex == -1) {
            categoriaIndex = totalCategorias;
            strcpy(ventasPorCategoria[totalCategorias].categoria, pizza_category);
            ventasPorCategoria[totalCategorias].cantidad_vendida = 0;
            totalCategorias++;
        }
        ventasPorCategoria[categoriaIndex].cantidad_vendida += cantidad;
    }

    // Procesar comandos desde la línea de argumentos
    for (int j = 2; j < argc; j++) {
        if (strcmp(argv[j], "pms") == 0) {
            VentaPizza masVendida = ventasPorPizza[0];
            for (int i = 1; i < totalPizzas; i++) {
                if (ventasPorPizza[i].cantidad_vendida > masVendida.cantidad_vendida) {
                    masVendida = ventasPorPizza[i];
                }
            }
            printf("Pizza más vendida: %s con %d ventas\n", masVendida.nombre, masVendida.cantidad_vendida);
        } 
        else if (strcmp(argv[j], "pls") == 0) {
            VentaPizza menosVendida = ventasPorPizza[0];
            for (int i = 1; i < totalPizzas; i++) {
                if (ventasPorPizza[i].cantidad_vendida < menosVendida.cantidad_vendida) {
                    menosVendida = ventasPorPizza[i];
                }
            }
            printf("Pizza menos vendida: %s con %d ventas\n", menosVendida.nombre, menosVendida.cantidad_vendida);
        } 
        else if (strcmp(argv[j], "ims") == 0) {
            VentaIngrediente masVendidoIngrediente = ventasPorIngrediente[0];
            for (int i = 1; i < totalIngredientes; i++) {
                if (ventasPorIngrediente[i].cantidad_vendida > masVendidoIngrediente.cantidad_vendida) {
                    masVendidoIngrediente = ventasPorIngrediente[i];
                }
            }
            printf("Ingrediente más vendido: %s con %d ventas\n", masVendidoIngrediente.ingrediente, masVendidoIngrediente.cantidad_vendida);
        } 
        else if (strcmp(argv[j], "hp") == 0) {
            for (int i = 0; i < totalCategorias; i++) {
                printf("Categoría %s: %d pizzas vendidas\n", ventasPorCategoria[i].categoria, ventasPorCategoria[i].cantidad_vendida);
            }
        }
    }

    free(linea);
    fclose(archivo);
    return 0;
}
