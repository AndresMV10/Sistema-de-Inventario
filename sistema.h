#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCTOS_MAXIMOS 100


char nombres[PRODUCTOS_MAXIMOS][100];
int cantidades[PRODUCTOS_MAXIMOS];
float precios[PRODUCTOS_MAXIMOS];
int numero_productos = 0;

void añadir_producto() {
    if (numero_productos == PRODUCTOS_MAXIMOS) {
        printf("No se pueden ingresar mas productos.\n");
        return;
    }

    char nombre[100];
    int cantidad;
    float precio;

    printf("\nIngrese el nombre del producto: ");
    scanf("%s", nombre);
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &cantidad);
    printf("Ingrese el precio del producto: ");
    scanf("%f", &precio);

    strcpy(nombres[numero_productos], nombre);
    cantidades[numero_productos] = cantidad;
    precios[numero_productos] = precio;

    numero_productos++;

    printf("\nProducto ingresado exitosamente.\n");
    FILE *archivo_productos = fopen("productos.txt", "a");
    if (archivo_productos == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }
    fprintf(archivo_productos, "%s %d %.2f\n", nombre, cantidad, precio);
    fclose(archivo_productos);
}

void editar_producto() {
    if (numero_productos == 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    int producto_ingresado;
    printf("\nIngrese el índice del producto que desea editar: ");
    scanf("%d", &producto_ingresado);

    if (producto_ingresado < 0 || producto_ingresado >= numero_productos) {
        printf("Índice de producto inválido.\n");
        return;
    }

    char nombre[100];
    int cantidad;
    float precio;

    printf("\nIngrese el nuevo nombre del producto: ");
    scanf("%s", nombre);
    printf("Ingrese la nueva cantidad del producto: ");
    scanf("%d", &cantidad);
    printf("Ingrese el nuevo precio del producto: ");
    scanf("%f", &precio);

    strcpy(nombres[producto_ingresado], nombre);
    cantidades[producto_ingresado] = cantidad;
    precios[producto_ingresado] = precio;

    printf("\nProducto editado exitosamente.\n");
    FILE *archivo_productos = fopen("productos.txt", "w");
    if (archivo_productos == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }

    for (int i = 0; i < numero_productos; i++) {
        fprintf(archivo_productos, "%s %d %.2f\n", nombres[i], cantidades[i], precios[i]);
    }

    fclose(archivo_productos);
}

void eliminar_producto() {


    int producto_ingresado;
    printf("\nIngrese el índice del producto que desea eliminar: ");
    scanf("%d", &producto_ingresado);

    if (producto_ingresado < 0 || producto_ingresado >= numero_productos) {
        printf("Índice de producto inválido.\n");
        return;
    }

    for (int i = producto_ingresado; i < numero_productos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        precios[i] = precios[i + 1];
    }

    numero_productos--;

    printf("\nProducto eliminado exitosamente.\n");
    FILE *archivo_productos = fopen("productos.txt", "w");
    if (archivo_productos == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }

    for (int i = 0; i < numero_productos; i++) {
        fprintf(archivo_productos, "%s %d %.2f\n", nombres[i], cantidades[i], precios[i]);
    }

    fclose(archivo_productos);
}

void mostrar_productos() {
    if (numero_productos == 0) {
        printf("No hay productos ingresados.\n");
        return;
    }

    FILE *archivo_productos = fopen("productos.txt", "w");
    if (archivo_productos == NULL) {
        printf("Error al abrir el archivo de productos.\n");
        return;
    }

    fprintf(archivo_productos, "Inventario de productos\n\n");
    fprintf(archivo_productos, "Índice\tProducto\tCantidad\tPrecio\n");

    for (int i = 0; i < numero_productos; i++) {
        fprintf(archivo_productos, "%d\t%s\t\t%d\t\t%.2f\n", i, nombres[i], cantidades[i], precios[i]);
    }

    fclose(archivo_productos);

    printf("Datos guardados en el archivo productos.txt\n");
}