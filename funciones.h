#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constantes
#define MAX_VEHICULOS 100
#define MAX_CLIENTES 100
#define MAX_MARCA 50
#define MAX_MODELO 50
#define MAX_NOMBRE 100
#define MAX_TELEFONO 20
#define MAX_EMAIL 100

// Enumeración para tipo de vehículo
typedef enum {
    NUEVO,
    USADO
} TipoVehiculo;

// Enumeración para tipo de carro (categoría)
typedef enum {
    SEDAN,
    HATCHBACK,
    SUV,
    CROSSOVER,
    FAMILIAR,
    DEPORTIVO,
    MONOVOLUMEN,
    PICKUP
} TipoCarro;

// Estructura para Vehículo
typedef struct {
    int id;
    char marca[MAX_MARCA];
    char modelo[MAX_MODELO];
    int anio;
    double precio;
    TipoVehiculo tipo;
    TipoCarro tipoCarro; // Categoría del vehículo
    int disponible; // 1 = disponible, 0 = vendido
    int reservado; // 1 = reservado, 0 = no reservado
    int idClienteReserva; // ID del cliente que reservó el vehículo
    int kilometraje; // Solo para usados
} Vehiculo;

// Estructura para Cliente
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char telefono[MAX_TELEFONO];
    char email[MAX_EMAIL];
    double presupuesto;
} Cliente;

// Estructura para estadísticas
typedef struct {
    int vehiculosVendidos;
    int vehiculosReservados;
    double ganancias;
} Estadisticas;

// Estructura para gestión del sistema
typedef struct {
    Vehiculo vehiculos[MAX_VEHICULOS];
    Cliente clientes[MAX_CLIENTES];
    int numVehiculos;
    int numClientes;
    int siguienteIdVehiculo;
    int siguienteIdCliente;
    Estadisticas estadisticas;
} Sistema;

// Prototipos de funciones - Gestión del Sistema
void inicializarSistema(Sistema *sistema);
void cargarDatos(Sistema *sistema);
void guardarDatos(Sistema *sistema);

// Prototipos de funciones - Gestión de Vehículos
void agregarVehiculo(Sistema *sistema);
void listarVehiculos(Sistema *sistema);
void buscarVehiculo(Sistema *sistema);
void modificarVehiculo(Sistema *sistema);
void eliminarVehiculo(Sistema *sistema);
void buscarPorCriterios(Sistema *sistema);
void mostrarVehiculo(Vehiculo v);
const char* obtenerNombreTipoCarro(TipoCarro tipo);
void venderVehiculosReservados(Sistema *sistema);

// Prototipos de funciones - Gestión de Clientes
void agregarCliente(Sistema *sistema);
void listarClientes(Sistema *sistema);
void buscarCliente(Sistema *sistema);
void modificarCliente(Sistema *sistema);
void eliminarCliente(Sistema *sistema);
void vehiculosEnPresupuesto(Sistema *sistema);

// Prototipos de funciones - Estadísticas
void mostrarEstadisticas(Sistema *sistema);

// Prototipos de funciones - Utilidades
void limpiarBuffer();
void pausar();
void limpiarPantalla();
int validarEntero(const char *mensaje);
double validarDouble(const char *mensaje);
void convertirAMinusculas(char *str);
int validarNombreSinNumeros(const char *nombre);
int validarTelefonoSoloNumeros(const char *telefono);

// Prototipos de funciones - Menús
void mostrarMenuPrincipal();
void menuVehiculos(Sistema *sistema);
void menuClientes(Sistema *sistema);
void menuBusqueda(Sistema *sistema);

#endif