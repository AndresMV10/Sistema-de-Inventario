#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fd;

struct producto {
    char nombre[20];
    float precio;
    int cantidad;
} producto;

void agregarProducto() {
    char rpt;
    fd = fopen("productos.txt", "at"); // add text - añadir un texto
    if (fd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    // Verificar si el archivo está vacío
    fseek(fd, 0, SEEK_END);
    long fileSize = ftell(fd);
    if (fileSize == 0) {
        // Insertar "Inventario" en medio del archivo
        fseek(fd, 0, SEEK_END);  // Ir al final del archivo
        long halfSize = fileSize / 2;  // Calcular la mitad del tamaño
        // Calcular la mitad del tamaño y restar un poco para asegurar que esté al principio de una línea
        halfSize = (fileSize / 2) - 10;  

        fseek(fd, halfSize, SEEK_SET);  // Ir a la mitad del archivo
        fprintf(fd, "Inventario\n");

        // Volver al final del archivo para agregar productos
        fseek(fd, 0, SEEK_END);

        // Agregar etiquetas de columna al principio de cada línea
        fprintf(fd, "%-20s%-15s%-10s\n", "Nombre", "Precio", "Cantidad");
        fprintf(fd, "---------------------------------------------\n");
    }
    printf("\n\t.:Agregando producto:.\n");
    do {
        fflush(stdin);
        printf("\nNombre : ");
        scanf("%s", producto.nombre);
        printf("Precio : ");
        scanf("%f", &producto.precio);
        printf("Cantidad : ");
        scanf("%d", &producto.cantidad);
        fprintf(fd, "%-20s%-15.2f%-10d\n", producto.nombre, producto.precio, producto.cantidad);
        printf("\nDesea agregar más productos (s) : ");
        scanf(" %c", &rpt);
    } while (rpt == 's');
    fclose(fd);
}

void visualizarProductos() {
    int c;
    fd = fopen("productos.txt", "r"); // read text - leer texto

    if (fd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    // Leer y omitir las líneas de encabezado
    char buffer[100];
    fgets(buffer, sizeof(buffer), fd); // Leer "Inventario" y avanzar a la siguiente línea
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de etiquetas de columna
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de separación

    printf("\n%-20s%-15s%-10s\n", "Nombre", "Precio", "Cantidad");
    printf("---------------------------------------------\n");

    while (fscanf(fd, "%s%f%d", producto.nombre, &producto.precio, &producto.cantidad) != EOF) {
        printf("%-20s%-15.2f%-10d\n", producto.nombre, producto.precio, producto.cantidad);
    }

    fclose(fd);
}

void editarProducto() {
    char nombreEditar[20];
    fd = fopen("productos.txt", "r+"); // Cambiar a "r+" para lectura y escritura

    if (fd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }
    // Leer y omitir las líneas de encabezado
    char buffer[100];
    fgets(buffer, sizeof(buffer), fd); // Leer "Inventario" y avanzar a la siguiente línea
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de etiquetas de columna
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de separación
    printf("\n\t.:Editar producto:.\n");
    printf("Ingrese el nombre del producto a editar: ");
    scanf("%s", nombreEditar);
    FILE *tempFd = fopen("temp.txt", "w");

    // Escribir "Inventario" y el encabezado en el archivo temporal
    fprintf(tempFd, "Inventario\n");
    fprintf(tempFd, "%-20s%-15s%-10s\n", "Nombre", "Precio", "Cantidad");
    fprintf(tempFd, "---------------------------------------------\n");

    while (fscanf(fd, "%s%f%d", producto.nombre, &producto.precio, &producto.cantidad) != EOF) {
        if (strcmp(producto.nombre, nombreEditar) == 0) {
            printf("Nuevo precio para %s: ", producto.nombre);
            scanf("%f", &producto.precio);
            printf("Nueva cantidad para %s: ", producto.nombre);
            scanf("%d", &producto.cantidad);
        }
        fprintf(tempFd, "%-20s%-15.2f%-10d\n", producto.nombre, producto.precio, producto.cantidad);
    }

    fclose(fd);
    fclose(tempFd);

    remove("productos.txt");
    rename("temp.txt", "productos.txt");

    printf("Producto editado exitosamente.\n");
}

void eliminarProducto() {
    char nombreEliminar[20];
    fd = fopen("productos.txt", "r");
    if (fd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }
    // Leer y omitir las líneas de encabezado
    char buffer[100];
    fgets(buffer, sizeof(buffer), fd); // Leer "Inventario" y avanzar a la siguiente línea
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de etiquetas de columna
    fgets(buffer, sizeof(buffer), fd); // Leer la línea de separación

    printf("\n\t.:Eliminar producto:.\n");
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombreEliminar);

    FILE *tempFd = fopen("temp.txt", "w");
    int encontrado = 0;
    // Escribir "Inventario" y el encabezado en el archivo temporal
    fprintf(tempFd, "Inventario\n");
    fprintf(tempFd, "%-20s%-15s%-10s\n", "Nombre", "Precio", "Cantidad");
    fprintf(tempFd, "---------------------------------------------\n");

    while (fscanf(fd, "%s%f%d", producto.nombre, &producto.precio, &producto.cantidad) != EOF) {
        if (strcmp(producto.nombre, nombreEliminar) != 0) {
            fprintf(tempFd, "%-20s%-15.2f%-10d\n", producto.nombre, producto.precio, producto.cantidad);
        } else {
            encontrado = 1;
        }
    }

    fclose(fd);
    fclose(tempFd);
    remove("productos.txt");
    rename("temp.txt", "productos.txt");
    if (encontrado) {
        printf("Producto eliminado exitosamente.\n");
    } else {
        printf("No se encontró el producto con ese nombre.\n");
    }
}
