#ifndef LOGINFUNCIONANDO_H_INCLUDED
#define LOGINFUNCIONANDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX 40
#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 5
#define MAX_INTENTOS 3
#define TOTAL_PERFILES 3
#define MAX_PERFIL 3

/* Estructura de cuentas de usuario */
typedef struct {
    int dni;
    char Apellidoynombre[MAX];
    char nombreUsuario[20];
    char password[20];
    char perfil[20];

} Usuario;
typedef struct{
int dni;
char Apellidoynombre[MAX];
char nombreUsuario[20];
char password[20];
}Empleado;
// Estructura
typedef struct nodo {
    Usuario dato;
    struct nodo* siguiente;
} Nodo;

// Estructura para la lista enlazada
typedef struct {
    Nodo* cabeza;
} ListaEnlazada;



//FUNCIONES DEL MENU
void menuInicial();
void menuListarUsuarios();
void menuRegistrarUsuario(FILE*archivo);//revisada
void menuIniciarSesion();
void menuSistema();

//FUNCIONES QUE MANIPULAN EL ARCHIVO


Usuario *obtenerUsuarios(int *numUsuarios);
int logearDesdeArchivo(char nombreUsuario[], char password[]);
int leerLinea(char *cad, int n);//revisada
void leerClave(char *password);//revisada
char linea[MAX];//revisada
void mostrarContenidoArchivo();//revisada
void darAltaEmpleado();//revisada
int insertarUsuario(FILE *archivo, Usuario usuario);//revisada
int existeUsuarioPorApellidoYNombre(FILE *archivo, char Apellidoynombre[]);//revisada
char existeUsuario(FILE*archivo, Usuario *usuario);//revisada
//FUNCIONES ARREGLO DE LISTAS
void modificarEmpleadoPorApellidoYNombre(const char *archivoNombre);//revisada
Nodo*inicLista();
Nodo* crearNodo(Usuario empleado)  ;
Nodo*agregarAlFinalLista(Nodo*lista, Nodo*nuevo);
Nodo*buscarUltimoNodo(Nodo*lista);
void mostrarListaOrdenada(const ListaEnlazada* lista);
void insertarOrdenado(ListaEnlazada* lista, const Usuario* empleado);
void pasarArchivoAListaOrdenada(ListaEnlazada* lista);
Nodo* buscarEmpleadoPorDNIenLista(const ListaEnlazada* lista, int dniBuscado);
void mostrarEmpleado(Usuario empleado) ;
void mostrarEmpleadoPorDNI(const ListaEnlazada* lista, int dniBuscado);
void eliminarEmpleadoPorDNI( ListaEnlazada* lista, int dniAEliminar);
void actualizarArchivoUsuarios(const ListaEnlazada* lista);
void mostrarContenidoArchivoBajas() ;
#endif // LIBRERIALOGIN_H_INCLUDED
