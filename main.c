#include "funciones.h"

int main() {
    Sistema sistema;
    int opcion;
    
    // Inicializar el sistema
    inicializarSistema(&sistema);
    
    // Cargar datos de archivos
    printf("\n");
    printf("===============================================\n");
    printf("    CONCESIONARIA RUEDAS DE ORO - SGIC\n");
    printf("    Sistema de Gestion de Inventario y Clientes\n");
    printf("===============================================\n\n");
    printf("Cargando datos del sistema...\n\n");
    cargarDatos(&sistema);
    
    printf("\nSistema inicializado correctamente.\n");
    pausar();
    
    // Menú principal
    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        opcion = validarEntero("Seleccione una opcion: ");
        
        switch (opcion) {
            case 1:
                menuVehiculos(&sistema);
                break;
            case 2:
                menuClientes(&sistema);
                break;
            case 3:
                menuBusqueda(&sistema);
                break;
            case 4:
                mostrarEstadisticas(&sistema);
                pausar();
                break;
            case 5:
                printf("\nGuardando datos...\n");
                guardarDatos(&sistema);
                pausar();
                break;
            case 0:
                printf("\nGuardando datos antes de salir...\n");
                guardarDatos(&sistema);
                printf("\nGracias por usar el Sistema de Gestion de Ruedas de Oro!\n");
                printf("Hasta pronto.\n\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                pausar();
        }
    } while (opcion != 0);
    
    return 0;
}
