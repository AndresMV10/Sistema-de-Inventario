/*llamamos a la libreria que creamos en la que guardamos las funciones necesarias para
el correcto funcionamiento del programa*/
#include "sistema.h"

int main() {
    int opc;

    do {
        printf("\n\t.:MENU:.\n");
        printf("1. Agregar Producto\n");
        printf("2. Visualizar Productos\n");
        printf("3. Editar Producto\n");
        printf("4. Eliminar Producto\n");
        printf("5. Salir\n");

        printf("Opcion : ");
        if (scanf("%i", &opc) != 1) {
            // Limpiar el búfer de entrada en caso de entrada no válida
            scanf("%*s");
            printf("Por favor, ingrese un número válido.\n");
            continue;  // Vuelve al principio del bucle
        }

        switch (opc) {
            case 1:
                agregarProducto();
                break;
            case 2:
                visualizarProductos();
                break;
            case 3:
                editarProducto();
                break;
            case 4:
                eliminarProducto();
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Por favor, elija una opción del 1 al 5.\n");
        }

    } while (opc != 5);

    return 0;
}