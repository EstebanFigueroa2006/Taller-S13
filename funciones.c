#include "funciones.h"

// ============================================================================
// FUNCIONES DE GESTIÓN DEL SISTEMA
// ============================================================================

void inicializarSistema(Sistema *sistema) {
    sistema->numVehiculos = 0;
    sistema->numClientes = 0;
    sistema->siguienteIdVehiculo = 1;
    sistema->siguienteIdCliente = 1;
    sistema->estadisticas.vehiculosVendidos = 0;
    sistema->estadisticas.vehiculosReservados = 0;
    sistema->estadisticas.ganancias = 0.0;
}

void cargarDatos(Sistema *sistema) {
    FILE *archivo;
    
    // Cargar vehículos
    archivo = fopen("vehiculos.txt", "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d\n", &sistema->numVehiculos);
        fscanf(archivo, "%d\n", &sistema->siguienteIdVehiculo);
        
        for (int i = 0; i < sistema->numVehiculos; i++) {
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].id);
            fgets(sistema->vehiculos[i].marca, MAX_MARCA, archivo);
            sistema->vehiculos[i].marca[strcspn(sistema->vehiculos[i].marca, "\n")] = 0;
            fgets(sistema->vehiculos[i].modelo, MAX_MODELO, archivo);
            sistema->vehiculos[i].modelo[strcspn(sistema->vehiculos[i].modelo, "\n")] = 0;
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].anio);
            fscanf(archivo, "%lf\n", &sistema->vehiculos[i].precio);
            int tipo;
            fscanf(archivo, "%d\n", &tipo);
            sistema->vehiculos[i].tipo = (TipoVehiculo)tipo;
            int tipoCarro;
            fscanf(archivo, "%d\n", &tipoCarro);
            sistema->vehiculos[i].tipoCarro = (TipoCarro)tipoCarro;
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].disponible);
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].reservado);
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].idClienteReserva);
            fscanf(archivo, "%d\n", &sistema->vehiculos[i].kilometraje);
        }
        
        fclose(archivo);
        printf("Se cargaron %d vehiculos del archivo.\n", sistema->numVehiculos);
    } else {
        printf("No se encontro archivo de vehiculos. Iniciando con inventario vacio.\n");
    }
    
    // Cargar clientes
    archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d\n", &sistema->numClientes);
        fscanf(archivo, "%d\n", &sistema->siguienteIdCliente);
        
        for (int i = 0; i < sistema->numClientes; i++) {
            fscanf(archivo, "%d\n", &sistema->clientes[i].id);
            fgets(sistema->clientes[i].nombre, MAX_NOMBRE, archivo);
            sistema->clientes[i].nombre[strcspn(sistema->clientes[i].nombre, "\n")] = 0;
            fgets(sistema->clientes[i].telefono, MAX_TELEFONO, archivo);
            sistema->clientes[i].telefono[strcspn(sistema->clientes[i].telefono, "\n")] = 0;
            fgets(sistema->clientes[i].email, MAX_EMAIL, archivo);
            sistema->clientes[i].email[strcspn(sistema->clientes[i].email, "\n")] = 0;
            fscanf(archivo, "%lf\n", &sistema->clientes[i].presupuesto);
            // Leer edad si está disponible, si no, asignar 0
            if (fscanf(archivo, "%d\n", &sistema->clientes[i].edad) != 1) {
                sistema->clientes[i].edad = 0;
            }
        }
        
        fclose(archivo);
        printf("Se cargaron %d clientes del archivo.\n", sistema->numClientes);
    } else {
        printf("No se encontro archivo de clientes. Iniciando sin clientes.\n");
    }
    
    // Cargar estadísticas
    archivo = fopen("estadisticas.txt", "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d\n", &sistema->estadisticas.vehiculosVendidos);
        fscanf(archivo, "%d\n", &sistema->estadisticas.vehiculosReservados);
        fscanf(archivo, "%lf\n", &sistema->estadisticas.ganancias);
        fclose(archivo);
        printf("Se cargaron estadisticas del sistema.\n");
    } else {
        printf("No se encontro archivo de estadisticas. Iniciando en cero.\n");
        sistema->estadisticas.vehiculosVendidos = 0;
        sistema->estadisticas.vehiculosReservados = 0;
        sistema->estadisticas.ganancias = 0.0;
    }
}

void guardarDatos(Sistema *sistema) {
    FILE *archivo;
    
    // Guardar vehículos
    archivo = fopen("vehiculos.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%d\n", sistema->numVehiculos);
        fprintf(archivo, "%d\n", sistema->siguienteIdVehiculo);
        
        for (int i = 0; i < sistema->numVehiculos; i++) {
            fprintf(archivo, "%d\n", sistema->vehiculos[i].id);
            fprintf(archivo, "%s\n", sistema->vehiculos[i].marca);
            fprintf(archivo, "%s\n", sistema->vehiculos[i].modelo);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].anio);
            fprintf(archivo, "%.2f\n", sistema->vehiculos[i].precio);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].tipo);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].tipoCarro);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].disponible);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].reservado);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].idClienteReserva);
            fprintf(archivo, "%d\n", sistema->vehiculos[i].kilometraje);
        }
        
        fclose(archivo);
        printf("Vehiculos guardados correctamente.\n");
    } else {
        printf("Error al guardar vehiculos.\n");
    }
    
    // Guardar clientes
    archivo = fopen("clientes.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%d\n", sistema->numClientes);
        fprintf(archivo, "%d\n", sistema->siguienteIdCliente);
        
        for (int i = 0; i < sistema->numClientes; i++) {
            fprintf(archivo, "%d\n", sistema->clientes[i].id);
            fprintf(archivo, "%s\n", sistema->clientes[i].nombre);
            fprintf(archivo, "%s\n", sistema->clientes[i].telefono);
            fprintf(archivo, "%s\n", sistema->clientes[i].email);
            fprintf(archivo, "%.2f\n", sistema->clientes[i].presupuesto);
            fprintf(archivo, "%d\n", sistema->clientes[i].edad);
        }
        
        fclose(archivo);
        printf("Clientes guardados correctamente.\n");
    } else {
        printf("Error al guardar clientes.\n");
    }
    
    // Guardar estadísticas
    archivo = fopen("estadisticas.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "%d\n", sistema->estadisticas.vehiculosVendidos);
        fprintf(archivo, "%d\n", sistema->estadisticas.vehiculosReservados);
        fprintf(archivo, "%.2f\n", sistema->estadisticas.ganancias);
        fclose(archivo);
        printf("Estadisticas guardadas correctamente.\n");
    } else {
        printf("Error al guardar estadisticas.\n");
    }
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE VEHÍCULOS
// ============================================================================

const char* obtenerNombreTipoCarro(TipoCarro tipo) {
    switch(tipo) {
        case SEDAN: return "Sedan";
        case HATCHBACK: return "Hatchback";
        case SUV: return "SUV";
        case CROSSOVER: return "Crossover";
        case FAMILIAR: return "Familiar";
        case DEPORTIVO: return "Deportivo";
        case MONOVOLUMEN: return "Monovolumen";
        case PICKUP: return "Pickup";
        default: return "Desconocido";
    }
}

void agregarVehiculo(Sistema *sistema) {
    if (sistema->numVehiculos >= MAX_VEHICULOS) {
        printf("\nInventario lleno. No se pueden agregar mas vehiculos.\n");
        return;
    }
    
    Vehiculo nuevo;
    nuevo.id = sistema->siguienteIdVehiculo++;
    
    printf("\n=== AGREGAR NUEVO VEHICULO ===\n");
    
    printf("Marca: ");
    fgets(nuevo.marca, MAX_MARCA, stdin);
    nuevo.marca[strcspn(nuevo.marca, "\n")] = 0;
    
    printf("Modelo: ");
    fgets(nuevo.modelo, MAX_MODELO, stdin);
    nuevo.modelo[strcspn(nuevo.modelo, "\n")] = 0;
    
    nuevo.anio = validarEntero("Anio: ");
    nuevo.precio = validarDouble("Precio: ");
    
    int tipoVeh;
    do {
        tipoVeh = validarEntero("Tipo (0=Nuevo, 1=Usado): ");
        if (tipoVeh < 0 || tipoVeh > 1) {
            printf("Opcion invalida. Ingrese 0 o 1.\n");
        }
    } while (tipoVeh < 0 || tipoVeh > 1);
    
    nuevo.tipo = (TipoVehiculo)tipoVeh;
    
    // Selección de categoría del vehículo
    printf("\n+-----+---------------+\n");
    printf("| No. | Categoria     |\n");
    printf("+-----+---------------+\n");
    printf("|  0  | Sedan         |\n");
    printf("|  1  | Hatchback     |\n");
    printf("|  2  | SUV           |\n");
    printf("|  3  | Crossover     |\n");
    printf("|  4  | Familiar      |\n");
    printf("|  5  | Deportivo     |\n");
    printf("|  6  | Monovolumen   |\n");
    printf("|  7  | Pickup        |\n");
    printf("+-----+---------------+\n");
    
    int tipoCarro;
    do {
        tipoCarro = validarEntero("Seleccione la categoria del vehiculo (0-7): ");
        if (tipoCarro < 0 || tipoCarro > 7) {
            printf("Opcion invalida. Ingrese un numero entre 0 y 7.\n");
        }
    } while (tipoCarro < 0 || tipoCarro > 7);
    
    nuevo.tipoCarro = (TipoCarro)tipoCarro;
    
    if (nuevo.tipo == USADO) {
        nuevo.kilometraje = validarEntero("Kilometraje: ");
    } else {
        nuevo.kilometraje = 0;
    }
    
    nuevo.disponible = 1;
    nuevo.reservado = 0;
    nuevo.idClienteReserva = 0; // 0 significa sin reserva
    
    sistema->vehiculos[sistema->numVehiculos++] = nuevo;
    
    printf("\nVehiculo agregado exitosamente con ID: %d\n", nuevo.id);
    guardarDatos(sistema);
}

void mostrarVehiculo(Vehiculo v) {
    printf("ID: %d | %s %s | Anio: %d | Precio: $%.2f | Tipo: %s | Categoria: %s",
           v.id, v.marca, v.modelo, v.anio, v.precio,
           v.tipo == NUEVO ? "Nuevo" : "Usado",
           obtenerNombreTipoCarro(v.tipoCarro));
    
    if (v.tipo == USADO) {
        printf(" | KM: %d", v.kilometraje);
    }
    
    char *estado = v.disponible ? (v.reservado ? "Reservado" : "Disponible") : "Vendido";
    printf(" | Estado: %s\n", estado);
}

void listarVehiculos(Sistema *sistema) {
    printf("\n=== LISTA DE VEHICULOS ===\n");
    
    if (sistema->numVehiculos == 0) {
        printf("No hay vehiculos en el inventario.\n");
        return;
    }
    
    printf("\nTotal de vehiculos: %d\n\n", sistema->numVehiculos);
    
    for (int i = 0; i < sistema->numVehiculos; i++) {
        mostrarVehiculo(sistema->vehiculos[i]);
    }
}

void buscarVehiculo(Sistema *sistema) {
    if (sistema->numVehiculos == 0) {
        printf("\nNo hay vehiculos en el inventario.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del vehiculo a buscar: ");
    
    int encontrado = 0;
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (sistema->vehiculos[i].id == id) {
            printf("\n=== VEHICULO ENCONTRADO ===\n");
            mostrarVehiculo(sistema->vehiculos[i]);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nNo se encontro ningun vehiculo con ID: %d\n", id);
    }
}

void modificarVehiculo(Sistema *sistema) {
    if (sistema->numVehiculos == 0) {
        printf("\nNo hay vehiculos en el inventario.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del vehiculo a modificar: ");
    
    int indice = -1;
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (sistema->vehiculos[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("\nNo se encontro ningun vehiculo con ID: %d\n", id);
        return;
    }
    
    printf("\n=== MODIFICAR VEHICULO ===\n");
    printf("Vehiculo actual:\n");
    mostrarVehiculo(sistema->vehiculos[indice]);
    
    printf("\n1. Modificar marca\n");
    printf("2. Modificar modelo\n");
    printf("3. Modificar anio\n");
    printf("4. Modificar precio\n");
    printf("5. Cambiar disponibilidad\n");
    printf("6. Modificar kilometraje (solo usados)\n");
    printf("7. Modificar categoria\n");
    printf("0. Cancelar\n");
    
    int opcion = validarEntero("\nSeleccione opcion: ");
    
    switch (opcion) {
        case 1:
            printf("Nueva marca: ");
            fgets(sistema->vehiculos[indice].marca, MAX_MARCA, stdin);
            sistema->vehiculos[indice].marca[strcspn(sistema->vehiculos[indice].marca, "\n")] = 0;
            break;
        case 2:
            printf("Nuevo modelo: ");
            fgets(sistema->vehiculos[indice].modelo, MAX_MODELO, stdin);
            sistema->vehiculos[indice].modelo[strcspn(sistema->vehiculos[indice].modelo, "\n")] = 0;
            break;
        case 3:
            sistema->vehiculos[indice].anio = validarEntero("Nuevo anio: ");
            break;
        case 4:
            sistema->vehiculos[indice].precio = validarDouble("Nuevo precio: ");
            break;
        case 5:
            sistema->vehiculos[indice].disponible = !sistema->vehiculos[indice].disponible;
            printf("Disponibilidad cambiada a: %s\n", 
                   sistema->vehiculos[indice].disponible ? "Disponible" : "Vendido");
            break;
        case 6:
            if (sistema->vehiculos[indice].tipo == USADO) {
                sistema->vehiculos[indice].kilometraje = validarEntero("Nuevo kilometraje: ");
            } else {
                printf("Este vehiculo es nuevo, no tiene kilometraje.\n");
            }
            break;
        case 7:
            printf("\n+-----+---------------+\n");
            printf("| No. | Categoria     |\n");
            printf("+-----+---------------+\n");
            printf("|  0  | Sedan         |\n");
            printf("|  1  | Hatchback     |\n");
            printf("|  2  | SUV           |\n");
            printf("|  3  | Crossover     |\n");
            printf("|  4  | Familiar      |\n");
            printf("|  5  | Deportivo     |\n");
            printf("|  6  | Monovolumen   |\n");
            printf("|  7  | Pickup        |\n");
            printf("+-----+---------------+\n");
            
            int tipoCarro;
            do {
                tipoCarro = validarEntero("Seleccione la nueva categoria (0-7): ");
                if (tipoCarro < 0 || tipoCarro > 7) {
                    printf("Opcion invalida. Ingrese un numero entre 0 y 7.\n");
                }
            } while (tipoCarro < 0 || tipoCarro > 7);
            
            sistema->vehiculos[indice].tipoCarro = (TipoCarro)tipoCarro;
            printf("Categoria cambiada a: %s\n", obtenerNombreTipoCarro(sistema->vehiculos[indice].tipoCarro));
            break;
        case 0:
            printf("Modificacion cancelada.\n");
            return;
        default:
            printf("Opcion invalida.\n");
            return;
    }
    
    printf("\nVehiculo modificado exitosamente.\n");
    guardarDatos(sistema);
}

void eliminarVehiculo(Sistema *sistema) {
    if (sistema->numVehiculos == 0) {
        printf("\nNo hay vehiculos en el inventario.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del vehiculo a eliminar: ");
    
    int indice = -1;
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (sistema->vehiculos[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("\nNo se encontro ningun vehiculo con ID: %d\n", id);
        return;
    }
    
    printf("\nVehiculo a eliminar:\n");
    mostrarVehiculo(sistema->vehiculos[indice]);
    
    printf("\n¿Esta seguro que desea eliminar este vehiculo? (S/N): ");
    char confirmacion[10];
    fgets(confirmacion, 10, stdin);
    
    if (confirmacion[0] == 'S' || confirmacion[0] == 's') {
        // Desplazar elementos
        for (int i = indice; i < sistema->numVehiculos - 1; i++) {
            sistema->vehiculos[i] = sistema->vehiculos[i + 1];
        }
        sistema->numVehiculos--;
        
        printf("\nVehiculo eliminado exitosamente.\n");
        guardarDatos(sistema);
    } else {
        printf("\nEliminacion cancelada.\n");
    }
}

void venderVehiculosReservados(Sistema *sistema) {
    if (sistema->numVehiculos == 0) {
        printf("\nNo hay vehiculos en el inventario.\n");
        return;
    }
    
    // Contar y mostrar vehículos reservados
    int reservados = 0;
    int indicesReservados[MAX_VEHICULOS];
    
    printf("\n=== VEHICULOS RESERVADOS ===\n\n");
    
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (sistema->vehiculos[i].reservado && sistema->vehiculos[i].disponible) {
            // Buscar el cliente que lo reservó
            char nombreCliente[MAX_NOMBRE] = "Cliente no encontrado";
            for (int j = 0; j < sistema->numClientes; j++) {
                if (sistema->clientes[j].id == sistema->vehiculos[i].idClienteReserva) {
                    strcpy(nombreCliente, sistema->clientes[j].nombre);
                    break;
                }
            }
            
            printf("%d. ", reservados + 1);
            mostrarVehiculo(sistema->vehiculos[i]);
            printf("   Reservado por: %s (ID: %d)\n\n", nombreCliente, sistema->vehiculos[i].idClienteReserva);
            indicesReservados[reservados] = i;
            reservados++;
        }
    }
    
    if (reservados == 0) {
        printf("No hay vehiculos reservados en este momento.\n");
        return;
    }
    
    printf("Total de vehiculos reservados: %d\n", reservados);
    printf("\nDesea vender un vehiculo reservado? (S/N): ");
    char respuesta[10];
    fgets(respuesta, 10, stdin);
    
    if (respuesta[0] != 'S' && respuesta[0] != 's') {
        printf("Operacion cancelada.\n");
        return;
    }
    
    printf("\nSeleccione el numero de vehiculo reservado (1-%d): ", reservados);
    int seleccion = validarEntero("");
    
    if (seleccion < 1 || seleccion > reservados) {
        printf("Seleccion invalida.\n");
        return;
    }
    
    int indiceVehiculo = indicesReservados[seleccion - 1];
    int idCliente = sistema->vehiculos[indiceVehiculo].idClienteReserva;
    
    // Buscar índice del cliente
    int indiceCliente = -1;
    for (int i = 0; i < sistema->numClientes; i++) {
        if (sistema->clientes[i].id == idCliente) {
            indiceCliente = i;
            break;
        }
    }
    
    if (indiceCliente == -1) {
        printf("\nError: No se encontro el cliente asociado a esta reserva.\n");
        printf("Desea continuar con la venta de todas formas? (S/N): ");
        fgets(respuesta, 10, stdin);
        
        if (respuesta[0] != 'S' && respuesta[0] != 's') {
            printf("Operacion cancelada.\n");
            return;
        }
    }
    
    // Confirmar venta
    printf("\n=== CONFIRMACION DE VENTA ===\n");
    printf("Vehiculo: %s %s - $%.2f\n", 
           sistema->vehiculos[indiceVehiculo].marca, 
           sistema->vehiculos[indiceVehiculo].modelo,
           sistema->vehiculos[indiceVehiculo].precio);
    
    if (indiceCliente != -1) {
        printf("Cliente: %s\n", sistema->clientes[indiceCliente].nombre);
        printf("Telefono: %s\n", sistema->clientes[indiceCliente].telefono);
    }
    
    printf("Vendedor: %s\n", sistema->vendedorActual);
    
    printf("\nEsta operacion eliminara el vehiculo y el cliente.\n");
    printf("Confirma la venta? (S/N): ");
    fgets(respuesta, 10, stdin);
    
    if (respuesta[0] != 'S' && respuesta[0] != 's') {
        printf("Venta cancelada.\n");
        return;
    }
    
    // Guardar precio antes de eliminar
    double precioVendido = sistema->vehiculos[indiceVehiculo].precio;
    
    // Registrar la venta en el log
    FILE *logVentas = fopen("ventas.txt", "a");
    if (logVentas != NULL) {
        fprintf(logVentas, "Vendedor: %s | Vehiculo: %s %s | Precio: $%.2f | Cliente: %s\n",
                sistema->vendedorActual,
                sistema->vehiculos[indiceVehiculo].marca,
                sistema->vehiculos[indiceVehiculo].modelo,
                precioVendido,
                (indiceCliente != -1) ? sistema->clientes[indiceCliente].nombre : "N/A");
        fclose(logVentas);
    }
    
    // Actualizar estadísticas
    sistema->estadisticas.vehiculosVendidos++;
    sistema->estadisticas.vehiculosReservados--;
    sistema->estadisticas.ganancias += precioVendido;
    
    printf("\nProcesando venta...\n");
    
    // Eliminar vehículo
    for (int i = indiceVehiculo; i < sistema->numVehiculos - 1; i++) {
        sistema->vehiculos[i] = sistema->vehiculos[i + 1];
    }
    sistema->numVehiculos--;
    
    // Eliminar cliente si se encontró
    if (indiceCliente != -1) {
        for (int i = indiceCliente; i < sistema->numClientes - 1; i++) {
            sistema->clientes[i] = sistema->clientes[i + 1];
        }
        sistema->numClientes--;
        printf("Cliente eliminado del sistema.\n");
    }
    
    printf("Vehiculo vendido exitosamente.\n");
    printf("Ganancia registrada: $%.2f\n", precioVendido);
    printf("Ganancias totales: $%.2f\n", sistema->estadisticas.ganancias);
    
    guardarDatos(sistema);
}

void buscarPorCriterios(Sistema *sistema) {
    if (sistema->numVehiculos == 0) {
        printf("\nNo hay vehiculos en el inventario.\n");
        return;
    }
    
    printf("\n=== BUSQUEDA AVANZADA ===\n");
    printf("Ingrese los criterios de busqueda (dejar en blanco o 0 para omitir):\n\n");
    
    // Solicitar marca
    char marcaBuscar[MAX_MARCA];
    printf("Marca: ");
    fgets(marcaBuscar, MAX_MARCA, stdin);
    marcaBuscar[strcspn(marcaBuscar, "\n")] = 0;
    int buscarPorMarca = (strlen(marcaBuscar) > 0);
    if (buscarPorMarca) {
        convertirAMinusculas(marcaBuscar);
    }
    
    // Solicitar año
    printf("\nAño (dejar en blanco para omitir): ");
    char lineaAnio[20];
    fgets(lineaAnio, 20, stdin);
    int anioBuscar = atoi(lineaAnio);
    int buscarPorAnio = (anioBuscar > 0);
    
    // Solicitar rango de precio
    printf("\nRango de precio:\n");
    double precioMin = validarDouble("  Precio minimo (0 para omitir): ");
    double precioMax = validarDouble("  Precio maximo (0 para omitir): ");
    int buscarPorPrecio = (precioMin > 0 || precioMax > 0);
    if (precioMax == 0 && precioMin > 0) {
        precioMax = 999999999.0; // Sin límite superior
    }
    if (precioMin == 0 && precioMax > 0) {
        precioMin = 0;
    }
    
    // Solicitar kilometraje
    printf("\nKilometraje maximo (0 para omitir): ");
    int kmMax = validarEntero("");
    int buscarPorKm = (kmMax > 0);
    
    // Solicitar tipo (Nuevo/Usado/Cualquiera)
    printf("\nTipo de vehiculo:\n");
    printf("  1. Nuevo\n");
    printf("  2. Usado\n");
    printf("  3. Cualquiera\n");
    int opcionTipo = validarEntero("  Seleccione opcion: ");
    int buscarPorTipo = (opcionTipo >= 1 && opcionTipo <= 2);
    TipoVehiculo tipoBuscar = (opcionTipo == 1) ? NUEVO : USADO;
    
    // Realizar búsqueda
    int encontrados = 0;
    printf("\n=== RESULTADOS DE BUSQUEDA ===\n");
    
    for (int i = 0; i < sistema->numVehiculos; i++) {
        int cumple = 1; // Asumimos que cumple todos los criterios
        
        // Verificar marca
        if (buscarPorMarca) {
            char marcaTemp[MAX_MARCA];
            strcpy(marcaTemp, sistema->vehiculos[i].marca);
            convertirAMinusculas(marcaTemp);
            if (strstr(marcaTemp, marcaBuscar) == NULL) {
                cumple = 0;
            }
        }
        
        // Verificar año
        if (buscarPorAnio && cumple) {
            if (sistema->vehiculos[i].anio != anioBuscar) {
                cumple = 0;
            }
        }
        
        // Verificar precio
        if (buscarPorPrecio && cumple) {
            if (sistema->vehiculos[i].precio < precioMin || sistema->vehiculos[i].precio > precioMax) {
                cumple = 0;
            }
        }
        
        // Verificar kilometraje
        if (buscarPorKm && cumple) {
            if (sistema->vehiculos[i].kilometraje > kmMax) {
                cumple = 0;
            }
        }
        
        // Verificar tipo
        if (buscarPorTipo && cumple) {
            if (sistema->vehiculos[i].tipo != tipoBuscar) {
                cumple = 0;
            }
        }
        
        // Si cumple todos los criterios, mostrarlo
        if (cumple) {
            mostrarVehiculo(sistema->vehiculos[i]);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron vehiculos que cumplan con los criterios.\n");
    } else {
        printf("\nTotal de vehiculos encontrados: %d\n", encontrados);
    }
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE CLIENTES
// ============================================================================

int validarNombreSinNumeros(const char *nombre) {
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (isdigit(nombre[i])) {
            return 0; // Contiene números
        }
    }
    return 1; // Válido
}

int validarTelefonoSoloNumeros(const char *telefono) {
    for (int i = 0; telefono[i] != '\0'; i++) {
        if (!isdigit(telefono[i]) && telefono[i] != ' ' && telefono[i] != '-' && telefono[i] != '+') {
            return 0; // Contiene caracteres no permitidos
        }
    }
    return 1; // Válido
}

void agregarCliente(Sistema *sistema) {
    if (sistema->numClientes >= MAX_CLIENTES) {
        printf("\nBase de datos de clientes llena.\n");
        return;
    }
    
    Cliente nuevo;
    nuevo.id = sistema->siguienteIdCliente++;
    
    printf("\n=== AGREGAR NUEVO CLIENTE ===\n");
    
    do {
        printf("Nombre completo: ");
        fgets(nuevo.nombre, MAX_NOMBRE, stdin);
        nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;
        
        if (!validarNombreSinNumeros(nuevo.nombre)) {
            printf("Error: El nombre no puede contener numeros. Intente nuevamente.\n");
        }
    } while (!validarNombreSinNumeros(nuevo.nombre));
    
    do {
        printf("Telefono: ");
        fgets(nuevo.telefono, MAX_TELEFONO, stdin);
        nuevo.telefono[strcspn(nuevo.telefono, "\n")] = 0;
        
        if (!validarTelefonoSoloNumeros(nuevo.telefono)) {
            printf("Error: El telefono solo puede contener numeros, espacios, - y +. Intente nuevamente.\n");
        }
    } while (!validarTelefonoSoloNumeros(nuevo.telefono));
    
    printf("Email: ");
    fgets(nuevo.email, MAX_EMAIL, stdin);
    nuevo.email[strcspn(nuevo.email, "\n")] = 0;
    
    nuevo.presupuesto = validarDouble("Presupuesto: ");
    
    do {
        nuevo.edad = validarEntero("Edad: ");
        if (nuevo.edad < 18 || nuevo.edad > 120) {
            printf("Error: La edad debe estar entre 18 y 120 años. Intente nuevamente.\n");
        }
    } while (nuevo.edad < 18 || nuevo.edad > 120);
    
    sistema->clientes[sistema->numClientes++] = nuevo;
    
    printf("\nCliente agregado exitosamente con ID: %d\n", nuevo.id);
    guardarDatos(sistema);
}

void listarClientes(Sistema *sistema) {
    printf("\n=== LISTA DE CLIENTES ===\n");
    
    if (sistema->numClientes == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }
    
    printf("\nTotal de clientes: %d\n\n", sistema->numClientes);
    
    for (int i = 0; i < sistema->numClientes; i++) {
        printf("ID: %d | %s | Edad: %d | Tel: %s | Email: %s | Presupuesto: $%.2f\n",
               sistema->clientes[i].id,
               sistema->clientes[i].nombre,
               sistema->clientes[i].edad,
               sistema->clientes[i].telefono,
               sistema->clientes[i].email,
               sistema->clientes[i].presupuesto);
    }
}

void buscarCliente(Sistema *sistema) {
    if (sistema->numClientes == 0) {
        printf("\nNo hay clientes registrados.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del cliente a buscar: ");
    
    int encontrado = 0;
    for (int i = 0; i < sistema->numClientes; i++) {
        if (sistema->clientes[i].id == id) {
            printf("\n=== CLIENTE ENCONTRADO ===\n");
            printf("ID: %d\n", sistema->clientes[i].id);
            printf("Nombre: %s\n", sistema->clientes[i].nombre);
            printf("Edad: %d\n", sistema->clientes[i].edad);
            printf("Telefono: %s\n", sistema->clientes[i].telefono);
            printf("Email: %s\n", sistema->clientes[i].email);
            printf("Presupuesto: $%.2f\n", sistema->clientes[i].presupuesto);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nNo se encontro ningun cliente con ID: %d\n", id);
    }
}

void modificarCliente(Sistema *sistema) {
    if (sistema->numClientes == 0) {
        printf("\nNo hay clientes registrados.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del cliente a modificar: ");
    
    int indice = -1;
    for (int i = 0; i < sistema->numClientes; i++) {
        if (sistema->clientes[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("\nNo se encontro ningun cliente con ID: %d\n", id);
        return;
    }
    
    printf("\n=== MODIFICAR CLIENTE ===\n");
    printf("Cliente actual:\n");
    printf("ID: %d\n", sistema->clientes[indice].id);
    printf("Nombre: %s\n", sistema->clientes[indice].nombre);
    printf("Edad: %d\n", sistema->clientes[indice].edad);
    printf("Telefono: %s\n", sistema->clientes[indice].telefono);
    printf("Email: %s\n", sistema->clientes[indice].email);
    printf("Presupuesto: $%.2f\n", sistema->clientes[indice].presupuesto);
    
    printf("\n1. Modificar nombre\n");
    printf("2. Modificar edad\n");
    printf("3. Modificar telefono\n");
    printf("4. Modificar email\n");
    printf("5. Modificar presupuesto\n");
    printf("0. Cancelar\n");
    
    int opcion = validarEntero("\nSeleccione opcion: ");
    
    switch (opcion) {
        case 1:
            do {
                printf("Nuevo nombre: ");
                fgets(sistema->clientes[indice].nombre, MAX_NOMBRE, stdin);
                sistema->clientes[indice].nombre[strcspn(sistema->clientes[indice].nombre, "\n")] = 0;
                
                if (!validarNombreSinNumeros(sistema->clientes[indice].nombre)) {
                    printf("Error: El nombre no puede contener numeros. Intente nuevamente.\n");
                }
            } while (!validarNombreSinNumeros(sistema->clientes[indice].nombre));
            break;
        case 2:
            do {
                sistema->clientes[indice].edad = validarEntero("Nueva edad: ");
                if (sistema->clientes[indice].edad < 18 || sistema->clientes[indice].edad > 120) {
                    printf("Error: La edad debe estar entre 18 y 120 años. Intente nuevamente.\n");
                }
            } while (sistema->clientes[indice].edad < 18 || sistema->clientes[indice].edad > 120);
            break;
        case 3:
            do {
                printf("Nuevo telefono: ");
                fgets(sistema->clientes[indice].telefono, MAX_TELEFONO, stdin);
                sistema->clientes[indice].telefono[strcspn(sistema->clientes[indice].telefono, "\n")] = 0;
                
                if (!validarTelefonoSoloNumeros(sistema->clientes[indice].telefono)) {
                    printf("Error: El telefono solo puede contener numeros, espacios, - y +. Intente nuevamente.\n");
                }
            } while (!validarTelefonoSoloNumeros(sistema->clientes[indice].telefono));
            break;
        case 4:
            printf("Nuevo email: ");
            fgets(sistema->clientes[indice].email, MAX_EMAIL, stdin);
            sistema->clientes[indice].email[strcspn(sistema->clientes[indice].email, "\n")] = 0;
            break;
        case 5:
            sistema->clientes[indice].presupuesto = validarDouble("Nuevo presupuesto: ");
            break;
        case 0:
            printf("Modificacion cancelada.\n");
            return;
        default:
            printf("Opcion invalida.\n");
            return;
    }
    
    printf("\nCliente modificado exitosamente.\n");
    guardarDatos(sistema);
}

void eliminarCliente(Sistema *sistema) {
    if (sistema->numClientes == 0) {
        printf("\nNo hay clientes registrados.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del cliente a eliminar: ");
    
    int indice = -1;
    for (int i = 0; i < sistema->numClientes; i++) {
        if (sistema->clientes[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("\nNo se encontro ningun cliente con ID: %d\n", id);
        return;
    }
    
    printf("\nCliente a eliminar:\n");
    printf("ID: %d | %s | Tel: %s | Email: %s | Presupuesto: $%.2f\n",
           sistema->clientes[indice].id,
           sistema->clientes[indice].nombre,
           sistema->clientes[indice].telefono,
           sistema->clientes[indice].email,
           sistema->clientes[indice].presupuesto);
    
    printf("\n¿Esta seguro que desea eliminar este cliente? (S/N): ");
    char confirmacion[10];
    fgets(confirmacion, 10, stdin);
    
    if (confirmacion[0] == 'S' || confirmacion[0] == 's') {
        // Desplazar elementos
        for (int i = indice; i < sistema->numClientes - 1; i++) {
            sistema->clientes[i] = sistema->clientes[i + 1];
        }
        sistema->numClientes--;
        
        printf("\nCliente eliminado exitosamente.\n");
        guardarDatos(sistema);
    } else {
        printf("\nEliminacion cancelada.\n");
    }
}

void vehiculosEnPresupuesto(Sistema *sistema) {
    if (sistema->numClientes == 0) {
        printf("\nNo hay clientes registrados.\n");
        return;
    }
    
    int id = validarEntero("\nIngrese el ID del cliente: ");
    
    int indiceCliente = -1;
    for (int i = 0; i < sistema->numClientes; i++) {
        if (sistema->clientes[i].id == id) {
            indiceCliente = i;
            break;
        }
    }
    
    if (indiceCliente == -1) {
        printf("\nNo se encontro ningun cliente con ID: %d\n", id);
        return;
    }
    
    double presupuesto = sistema->clientes[indiceCliente].presupuesto;
    
    printf("\n=== VEHICULOS DISPONIBLES PARA %s ===\n", 
           sistema->clientes[indiceCliente].nombre);
    printf("Presupuesto: $%.2f\n\n", presupuesto);
    
    int encontrados = 0;
    int indicesVehiculos[MAX_VEHICULOS];
    
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (sistema->vehiculos[i].disponible && !sistema->vehiculos[i].reservado &&
            sistema->vehiculos[i].precio <= presupuesto) {
            printf("%d. ", encontrados + 1);
            mostrarVehiculo(sistema->vehiculos[i]);
            indicesVehiculos[encontrados] = i;
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("No hay vehiculos disponibles dentro del presupuesto.\n");
        return;
    }
    
    printf("\nTotal de opciones: %d\n", encontrados);
    printf("\nDesea que el cliente adquiera o reserve un vehiculo? (S/N): ");
    char respuesta[10];
    fgets(respuesta, 10, stdin);
    
    if (respuesta[0] != 'S' && respuesta[0] != 's') {
        printf("Operacion cancelada.\n");
        return;
    }
    
    printf("\nSeleccione el numero de vehiculo (1-%d): ", encontrados);
    int seleccion = validarEntero("");
    
    if (seleccion < 1 || seleccion > encontrados) {
        printf("Seleccion invalida.\n");
        return;
    }
    
    int indiceVehiculo = indicesVehiculos[seleccion - 1];
    
    printf("\n1. Adquirir vehiculo (elimina vehiculo y cliente)\n");
    printf("2. Reservar vehiculo (marca como reservado)\n");
    printf("0. Cancelar\n");
    
    int opcion = validarEntero("\nSeleccione opcion: ");
    
    switch (opcion) {
        case 1:
            // Adquirir: eliminar vehiculo y cliente
            printf("\nVehiculo adquirido por el cliente.\n");
            printf("Procesando venta...\n");
            
            // Guardar precio antes de eliminar
            double precioVendido = sistema->vehiculos[indiceVehiculo].precio;
            
            // Actualizar estadísticas
            sistema->estadisticas.vehiculosVendidos++;
            sistema->estadisticas.ganancias += precioVendido;
            
            // Eliminar vehículo
            for (int i = indiceVehiculo; i < sistema->numVehiculos - 1; i++) {
                sistema->vehiculos[i] = sistema->vehiculos[i + 1];
            }
            sistema->numVehiculos--;
            
            // Eliminar cliente
            for (int i = indiceCliente; i < sistema->numClientes - 1; i++) {
                sistema->clientes[i] = sistema->clientes[i + 1];
            }
            sistema->numClientes--;
            
            printf("Vehiculo vendido y cliente eliminado exitosamente.\n");
            printf("Ganancia registrada: $%.2f\n", precioVendido);
            guardarDatos(sistema);
            break;
            
        case 2:
            // Reservar: marcar como reservado
            sistema->vehiculos[indiceVehiculo].reservado = 1;
            sistema->vehiculos[indiceVehiculo].idClienteReserva = sistema->clientes[indiceCliente].id;
            sistema->estadisticas.vehiculosReservados++;
            
            printf("\nVehiculo reservado exitosamente para el cliente %s.\n", 
                   sistema->clientes[indiceCliente].nombre);
            guardarDatos(sistema);
            break;
            
        case 0:
            printf("Operacion cancelada.\n");
            break;
            
        default:
            printf("Opcion invalida.\n");
    }
}

// ============================================================================
// FUNCIONES DE ESTADÍSTICAS
// ============================================================================

void mostrarEstadisticas(Sistema *sistema) {
    printf("\n");
    printf("===============================================\n");
    printf("    GANANCIAS Y VEHICULOS VENDIDOS\n");
    printf("===============================================\n\n");
    
    printf("+-----------------------------------+----------+\n");
    printf("| Concepto                          | Cantidad |\n");
    printf("+-----------------------------------+----------+\n");
    printf("| Vehiculos Vendidos                | %8d |\n", sistema->estadisticas.vehiculosVendidos);
    printf("| Vehiculos Reservados              | %8d |\n", sistema->estadisticas.vehiculosReservados);
    printf("+-----------------------------------+----------+\n");
    printf("| Ganancias Totales                 | $%7.2f |\n", sistema->estadisticas.ganancias);
    printf("+-----------------------------------+----------+\n");
    
    printf("\n");
    printf("Detalles adicionales:\n");
    printf("- Vehiculos en inventario: %d\n", sistema->numVehiculos);
    printf("- Clientes registrados: %d\n", sistema->numClientes);
    
    int disponibles = 0, vendidos = 0, reservados = 0;
    for (int i = 0; i < sistema->numVehiculos; i++) {
        if (!sistema->vehiculos[i].disponible) {
            vendidos++;
        } else if (sistema->vehiculos[i].reservado) {
            reservados++;
        } else {
            disponibles++;
        }
    }
    
    printf("- Vehiculos disponibles: %d\n", disponibles);
    printf("- Vehiculos reservados actuales: %d\n", reservados);
}

// ============================================================================
// FUNCIONES UTILIDADES
// ============================================================================

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPresione Enter para continuar...");
    getchar();
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int validarEntero(const char *mensaje) {
    int valor;
    printf("%s", mensaje);
    while (scanf("%d", &valor) != 1) {
        printf("Error: Ingrese un numero entero valido.\n");
        limpiarBuffer();
        printf("%s", mensaje);
    }
    limpiarBuffer();
    return valor;
}

double validarDouble(const char *mensaje) {
    double valor;
    printf("%s", mensaje);
    while (scanf("%lf", &valor) != 1 || valor < 0) {
        printf("Error: Ingrese un numero valido (mayor o igual a 0).\n");
        limpiarBuffer();
        printf("%s", mensaje);
    }
    limpiarBuffer();
    return valor;
}

void convertirAMinusculas(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// ============================================================================
// FUNCIONES DE MENÚS
// ============================================================================

void mostrarMenuPrincipal() {
    printf("\n");
    printf("===============================================\n");
    printf("    CONCESIONARIA RUEDAS DE ORO - SGIC\n");
    printf("===============================================\n");
    printf("1. Gestion de Vehiculos\n");
    printf("2. Gestion de Clientes\n");
    printf("3. Busqueda Avanzada\n");
    printf("4. Ganancias y Vehiculos Vendidos\n");
    printf("5. Guardar datos\n");
    printf("0. Salir\n");
    printf("===============================================\n");
}

void menuVehiculos(Sistema *sistema) {
    int opcion;
    
    do {
        limpiarPantalla();
        printf("\n===============================================\n");
        printf("         GESTION DE VEHICULOS\n");
        printf("===============================================\n");
        printf("1. Agregar vehiculo\n");
        printf("2. Listar vehiculos\n");
        printf("3. Buscar vehiculo por ID\n");
        printf("4. Modificar vehiculo\n");
        printf("5. Eliminar vehiculo\n");
        printf("6. Vender vehiculos reservados\n");
        printf("0. Volver al menu principal\n");
        printf("===============================================\n");
        
        opcion = validarEntero("Seleccione una opcion: ");
        
        switch (opcion) {
            case 1:
                agregarVehiculo(sistema);
                pausar();
                break;
            case 2:
                listarVehiculos(sistema);
                pausar();
                break;
            case 3:
                buscarVehiculo(sistema);
                pausar();
                break;
            case 4:
                modificarVehiculo(sistema);
                pausar();
                break;
            case 5:
                eliminarVehiculo(sistema);
                pausar();
                break;
            case 6:
                venderVehiculosReservados(sistema);
                pausar();
                break;
            case 0:
                printf("\nVolviendo al menu principal...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                pausar();
        }
    } while (opcion != 0);
}

void menuClientes(Sistema *sistema) {
    int opcion;
    
    do {
        limpiarPantalla();
        printf("\n===============================================\n");
        printf("         GESTION DE CLIENTES\n");
        printf("===============================================\n");
        printf("1. Agregar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Buscar cliente por ID\n");
        printf("4. Modificar cliente\n");
        printf("5. Eliminar cliente\n");
        printf("6. Ver vehiculos en presupuesto de cliente\n");
        printf("0. Volver al menu principal\n");
        printf("===============================================\n");
        
        opcion = validarEntero("Seleccione una opcion: ");
        
        switch (opcion) {
            case 1:
                agregarCliente(sistema);
                pausar();
                break;
            case 2:
                listarClientes(sistema);
                pausar();
                break;
            case 3:
                buscarCliente(sistema);
                pausar();
                break;
            case 4:
                modificarCliente(sistema);
                pausar();
                break;
            case 5:
                eliminarCliente(sistema);
                pausar();
                break;
            case 6:
                vehiculosEnPresupuesto(sistema);
                pausar();
                break;
            case 0:
                printf("\nVolviendo al menu principal...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
                pausar();
        }
    } while (opcion != 0);
}

void menuBusqueda(Sistema *sistema) {
    limpiarPantalla();
    buscarPorCriterios(sistema);
    pausar();
}
