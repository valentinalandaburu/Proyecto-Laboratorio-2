
#include "loginFuncionando.h"

///DECLARACION DE VARIABLES
const char ARCHIVO_USUARIOS[]="empleados.bin";
const char ARCHIVO_BAJAS[]="empleadosBajas.bin";
Usuario usuarioActual = {0, "", "", "", "sin_perfil"};
//celda *misCeldas;

///FUNCIONES

void menuInicial()
{
    char repite = 1;
    int opcion = -1;
    char linea[MAX];
    do
    {
        system("cls");
        printf("\n\t\t\tMENU INICIAL\n");
        printf("\t\t\t============\n");
        printf("\n\t\t[1]. Ver usuarios registrados\n");
        printf("\t\t[2]. Alta usuario nuevo\n");
        printf("\t\t[3]. Ingresar al sistema\n");
        printf("\t\t[0]. Salir\n");
        printf("\n\t\tIngrese su opcion: [ ]\b\b");
        leerLinea(linea, MAX);
        sscanf(linea, "%d", &opcion);

        switch (opcion)
        {
        case 1:
            mostrarContenidoArchivo();
            system("pause");
            break;

        case 2:
            menuRegistrarUsuario(ARCHIVO_USUARIOS);
            system("pause");
            break;

        case 3:
            menuIniciarSesion();
            break;

        case 0:
            repite = 0;
            break;
        }

    }
    while (repite == 1);
}

void mostrarContenidoArchivo()
{
    FILE *archivo;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo empleados.bin.\n");
        return;
    }

    // Leer y mostrar cada registro en el archivo
    Usuario empleado;
    printf("\nContenido del archivo empleados.bin:\n");
    while (fread(&empleado, sizeof(Usuario), 1, archivo) == 1)
    {
        printf("DNI: %d\n", empleado.dni);
        printf("Apellido y Nombre: %s\n", empleado.Apellidoynombre);
        printf("Usuario: %s\n", empleado.nombreUsuario);
        printf("Contrasena: %s\n", empleado.password);
        printf("Perfil: %s\n", empleado.perfil);
        printf("-----------------------------------------\n");
    }

    fclose(archivo);
}
///FUNCION PARA ALTA NUEVO USUARIO
void darAltaEmpleado(FILE *archivo)
{
    Usuario nuevoEmpleado;

    // Obtener los datos del nuevo empleado
    printf("Ingrese el DNI: ");
    scanf("%d", &nuevoEmpleado.dni);

    // Verificar si el empleado ya existe
    printf("Ingrese Apellido y Nombre: ");
    getchar();  // Limpiar el buffer de entrada
    fgets(nuevoEmpleado.Apellidoynombre, sizeof(nuevoEmpleado.Apellidoynombre), stdin);
    nuevoEmpleado.Apellidoynombre[strcspn(nuevoEmpleado.Apellidoynombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea

    // Verifica si el nombre de usuario ya existe
    if (!existeUsuarioPorApellidoYNombre(ARCHIVO_USUARIOS, nuevoEmpleado.Apellidoynombre))
    {

        printf("Ingrese Usuario: ");
        fgets(nuevoEmpleado.nombreUsuario, sizeof(nuevoEmpleado.nombreUsuario), stdin);
        nuevoEmpleado.nombreUsuario[strcspn(nuevoEmpleado.nombreUsuario, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        printf("Ingrese Contraseña: ");
        fgets(nuevoEmpleado.password, sizeof(nuevoEmpleado.password), stdin);
        nuevoEmpleado.password[strcspn(nuevoEmpleado.password, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        printf("Ingrese Perfil: ");
        fgets(nuevoEmpleado.perfil, sizeof(nuevoEmpleado.perfil), stdin);
        nuevoEmpleado.perfil[strcspn(nuevoEmpleado.perfil, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        // Llamar a la función para insertar el nuevo empleado en el archivo
        if (insertarUsuario(archivo, nuevoEmpleado))
        {
            printf("Empleado dado de alta exitosamente.\n");
        }
        else
        {
            printf("Error al dar de alta al empleado.\n");
        }
    }
    else
    {
        printf("El empleado \"%s\" ya ha sido registrado previamente\n", nuevoEmpleado.Apellidoynombre);
        printf("No puede registrar dos empleados con el mismo nombre.\n");
    }
}

int insertarUsuario( FILE*archivo, Usuario usuario)
{
    archivo = fopen(ARCHIVO_USUARIOS, "ab");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo empleados.bin\n");
        return 0; // Error al abrir el archivo
    }

    fwrite(&usuario, sizeof(Usuario), 1, archivo);


    return 1; // Éxito al insertar el usuario en el archivo
}

int existeUsuarioPorApellidoYNombre( FILE *archivo,char Apellidoynombre[])
{
    int existe = 0;
    Usuario usuario;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    Usuario empleado;
    // Verificar si el archivo es nulo
    if (archivo == NULL)
    {
        perror("Error: Archivo nulo");
        return 0;
    }

    // Posicionar el cursor al principio del archivo
    fseek(archivo, 0, SEEK_SET);

    // Recorrer el archivo
    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(usuario.Apellidoynombre, Apellidoynombre) == 0)
        {
            existe = 1;
            break;  // Se encontró una coincidencia, salir del bucle
        }
    }
    // Verificar si se produjo un error durante la lectura
    if (ferror(archivo))
    {
        clearerr(archivo);  // Limpiar el indicador de error
        perror("Error al leer el archivo");
        existe = 0;  // Marcar como no existente debido a un error
    }
    fclose(archivo);

    return existe;
}

void menuRegistrarUsuario(FILE *archivo)
{
    Usuario usuario;
    char respuesta[40];
    char repite = 1;

    archivo = fopen(ARCHIVO_USUARIOS, "ab");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    do
    {
        system("cls");
        printf("\n\t\t\tREGISTRAR USUARIO\n");
        printf("\t\t\t=================\n");

        printf("\n\tIngrese Apellido y Nombre del nuevo usuario: ");
        leerLinea(usuario.Apellidoynombre, sizeof(usuario.Apellidoynombre));

        // Verifica si el nombre de usuario ya existe
        if (existeUsuarioPorApellidoYNombre(ARCHIVO_USUARIOS, usuario.Apellidoynombre) == 0)
        {
            printf("\n\tIngrese usuario: ");
            leerLinea(usuario.nombreUsuario, sizeof(usuario.nombreUsuario));

            printf("\tIngrese la contrasena: ");
            leerLinea(usuario.password, sizeof(usuario.password));

            printf("\tIngrese dni: ");
            scanf("%d", &usuario.dni);

            // Limpiar el búfer de entrada
            getchar();

            printf("\tIngrese perfil: ");
            leerLinea(usuario.perfil, sizeof(usuario.perfil));

            // Se inserta el usuario en el archivo de empleados
            if (insertarEmpleado(archivo, usuario))
            {
                printf("\n\tEl usuario fue registrado satisfactoriamente!\n");
            }
            else
            {
                printf("\n\tOcurrio un error al registrar el usuario\n");
                printf("\nIntentelo mas tarde\n");
            }
        }
        else
        {
            printf("\n\tEl usuario \"%s\" ya ha sido registrado previamente\n", usuario.Apellidoynombre);
            printf("\tNo puede registrar dos usuarios con el mismo nombre de usuario.\n");
        }

        printf("\n\tDesea seguir registrando usuarios? [S/N]: ");
        leerLinea(respuesta, sizeof(respuesta));

        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0))
        {
            repite = 0;
        }
    }
    while (repite == 1);

    fclose(archivo);
}

int insertarEmpleado(FILE *archivo, Usuario usuario)
{
    int insercion = 0;

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return insercion;
    }

    // Registra el struct usuario en el archivo
    if (fwrite(&usuario, sizeof(usuario), 1, archivo) == 1)
    {
        insercion = 1;
    }
    else
    {
        perror("Error al escribir en el archivo");
    }

    return insercion;
}

void menuListarUsuarios()
{

    int numeroUsuarios = 0;
    Usuario datos;

    system("cls");

    // Abre el archivo en modo lectura
    FILE*  archivo = fopen(ARCHIVO_USUARIOS, "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }


    printf("\n\t\t    ==> LISTADO DE USUARIOS REGISTRADOS <==\n");
    printf(" -----------------------------------------------------------------------------------------------------------------\n");
    while (fread(&datos, sizeof(Usuario), 1, archivo) >0)
    {
        printf("Perfil: %s\n",datos.perfil);
        printf("Apellido y Nombre del Empleado : %s\n",datos.Apellidoynombre);
        printf("DNI: %d\n",datos.dni);
        printf("Nombre de Usuario: %s\n",datos.nombreUsuario);
        printf("Password: %d\n",datos.password);
        printf(" -----------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(archivo);


    if (numeroUsuarios == 0)
    {
        printf("\n\tNo existe ningun usuario registrado!\n");
    }

    getchar();
}



void menuIniciarSesion()
{
    char nombreUsuario[MAX];
    char password[MAX];
    int intento = 0;
    int loginExitoso = 0;
    char linea[MAX];
    do
    {
        system("cls");
        printf("\n\t\t\tINGRESAR AL SISTEMA\n");
        printf("\t\t\t===================\n");

        printf("\n\t\tUSUARIO: ");
        leerLinea(linea, MAX);
        sscanf(linea, "%s", nombreUsuario);

        printf("\t\Contrasena: ");
        leerClave(password);

        if (logearDesdeArchivo( nombreUsuario,  password))
        {
            loginExitoso = 1;
        }
        else
        {
            printf("\n\n\t\tUsuario y/o password incorrectos");
            intento++;
            getchar();
        }
    }
    while (intento < MAX_INTENTOS && loginExitoso == 0);

    if (loginExitoso == 1)
    {
        menuSistema();

    }
    else
    {
        printf("\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
        getchar();
    }
}
///FUNCION PARA BUSCAR UN EMPLEADO EN EL ARCHIVO empleados.bin POR DNI
void buscarEmpleadoPorDNI(int dniBuscado)
{
    FILE *archivo;
    Usuario usuario;

    // Abre el archivo en modo lectura
    archivo = fopen(ARCHIVO_USUARIOS, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo empleados.bin\n");
        return;
    }

    // Busca el empleado por DNI en el archivo
    int encontrado = 0;
    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (usuario.dni == dniBuscado)
        {
            encontrado = 1;
            // Muestra la información del empleado
            printf("Empleado encontrado:\n");
            printf("DNI: %d\n", usuario.dni);
            printf("Nombre y Apellido: %s\n", usuario.Apellidoynombre);
            printf("Nombre de Usuario: %s\n", usuario.nombreUsuario);
            printf("Perfil: %s\n", usuario.perfil);
            break;
        }
    }

    // Si no se encuentra el empleado
    if (!encontrado)
    {
        printf("No se encontró un empleado con el DNI proporcionado.\n");
    }

    // Cierra el archivo
    fclose(archivo);
}

void menuSistema()
{
    char repite = 1;
    ListaEnlazada lista;
    lista.cabeza = NULL;
    int dniBuscado;
    int dniAEliminar;

    system("cls"); // Limpiar la pantalla

    printf("\n     ======================================================================\n");
    printf("\t\t\t     BIENVENIDO AL SISTEMA\n");
    printf("\t\t    Gestion de Analisis Clinicos\n");
    printf("\t\t    Copyright 2023 | CliniData\n");
    printf("     ======================================================================\n");

    if (strcmpi(usuarioActual.perfil, "admin") == 0)
    {
        // Menú específico para usuarios con perfil "admin"
        printf("\n\t\tMENU PARA ADMINISTRADORES\n");
        printf("\t\t[1].  Dar alta a un nuevo Usuario\n");//revisada
        printf("\t\t[2].  Dar de baja un empleado\n");
        printf("\t\t[3].  Modificar empleado\n");//revisada
        printf("\t\t[4].  Listado General de Empleados ordenados por Apellido y Nombre\n");//revisada
        printf("\t\t[5].  Realizar consulta de empleado por DNI\n");//revisada
        printf("\t\t[6].  Listado de empleados eliminados\n");
        printf("\t\t[7].  Carga de un Paciente\n"); //si existe dni no te deja cargar paciente
        printf("\t\t[8].  Ingreso de Practicas por DNI \n");
        printf("\t\t[9].  Modificacion de un Paciente\n");//tambien se modifican ingresos 1.modificar ingresos 2 modificar info del paciente
        printf("\t\t[10]. Listado de Pacientes\n");
        printf("\t\t[11]. Buscar Paciente por DNI\n");
        printf("\t\t[12]. Eliminar Paciente\n");
        printf("\t\t[13]. Carga de Resultados de practicas por Paciente\n");
        printf("\t\t[14]. Lista de Practicas por fecha \n");
        printf("\t\t[0].  Salir\n");
    }
    else if ( strcmp(usuarioActual.perfil, "secretaria") == 0)

    {
        // Menú específico para usuarios con perfil "secretaria"
        printf("\n\t\tMENU PARA SECRETARIAS\n");
        printf("\t\t[7]. Carga de un Paciente\n"); //si existe dni no te deja cargar paciente
        printf("\t\t[8]. Ingreso de Practicas por DNI \n");
        printf("\t\t[9]. Modificacion de un Paciente\n");//tambien se modifican ingresos 1.modificar ingresos 2 modificar info del paciente
        printf("\t\t[10]. Listado de Pacientes\n");
        printf("\t\t[11]. Buscar Paciente por DNI\n");
        printf("\t\t[12]. Eliminar Paciente\n");
        printf("\t\t[0].  Salir\n");
    }
    else  if ( strcmp(usuarioActual.perfil, "profesional") == 0)

    {
        // Menú específico para usuarios con perfil "profesional"
        printf("\n\t\tMENU PARA PROFESIONAL\n");
        printf("\t\t[13]. Carga de Resultados de practicas por Paciente\n");
        printf("\t\t[14]. Lista de Practicas por fecha \n");
        printf("\t\t[0].  Salir\n");

    }

    printf("\n\t\tSeleccione una opcion: ");

    char opcion[3];  // Puedes ajustar el tamaño según tus necesidades
    scanf("%s", opcion);

// Convierte la cadena a un número entero
    int numeroOpcion = atoi(opcion);

    int cantidadUsuarios;
    int numPerfiles = 3;
    int validos;
    Usuario *usuariosLeidos;
    int numUsuariosLeidos;
    int numCeldas;
    int dniEliminado;
    Usuario usuarios;
    int numUsuarios;
    switch (numeroOpcion)
    {
    case 1:
        darAltaEmpleado(ARCHIVO_USUARIOS);

        break;
    case 2:
        pasarArchivoAListaOrdenada(&lista);
        printf("Cargando la Lista.....");
        getchar();
        system("cls");
        printf("Ingrese el DNI a eliminar: ");
        scanf("%d", &dniAEliminar);
        printf("Buscando DNI....");
        getchar();
        system("cls");
        // Llama a la función para eliminar el empleado de la lista
        eliminarEmpleadoPorDNI(&lista, dniAEliminar);
        printf("Eliminacion exitosa!");
        getchar();
        system("cls");
        // Llama a la función para actualizar el archivo de usuarios
        actualizarArchivoUsuarios(&lista);
        printf("Actualizacion exitosa!");
        getchar();
        system("cls");

        break;
    case 3:
        modificarEmpleadoPorApellidoYNombre(ARCHIVO_USUARIOS);
        getchar();
        system("cls");
        break;
    case 4:


        pasarArchivoAListaOrdenada(&lista);
        printf("Cargando la lista.....");
        getchar();  // Espera a que el usuario presione Enter
        system("cls");
        mostrarListaOrdenada(&lista);
        getchar();  // Espera a que el usuario presione Enter
        system("cls");


        break;
    case 5:
        pasarArchivoAListaOrdenada(&lista);
        printf("Ingrese el DNI a buscar: ");
        scanf("%d", &dniBuscado);
        getchar();
        system("cls");
        // Llama a la función para mostrar el empleado por DNI
        mostrarEmpleadoPorDNI(&lista, dniBuscado);
        getchar();
        system("cls");
        break;
    case 6:
// Llamada a la función para mostrar el contenido del archivo de bajas
        getchar();
        system("cls");
        mostrarContenidoArchivoBajas();
        getchar();
        system("cls");
        break;
    case 7:

        getchar();
        system("cls");
        break;
    case 8:

        getchar();
        system("cls");
        break;
    case 9:

        getchar();
        system("cls");
        break;
    case 10:

        getchar();
        system("cls");
        break;
    case 11:

        getchar();
        system("cls");
        break;
    case 12:

        getchar();
        system("cls");
        break;
    case 13:

        getchar();
        system("cls");
        break;
    case 14:

        getchar();
        system("cls");
        break;
    case 0:
        repite = 0;
        break;
    default:
        printf("Opcion no valida.\n");
        break;
    }

    // Pausa para que el usuario vea el resultado
    printf("Presione Enter para continuar...");
    while (getchar() != '\n'); // Vaciar el buffer
    getchar(); // Esperar a que el usuario presione Enter para continuar
}


int logearDesdeArchivo(char nombreUsuario[], char password[])
{
    int logeoExitoso = 0;
    Usuario usuario;

    // Abre el archivo en modo de lectura
    FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        printf("Error: No se pudo abrir el archivo de usuarios.\n");
        return 0;
    }

    // Lee secuencialmente del archivo de usuarios
    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(usuario.nombreUsuario, nombreUsuario) == 0 && strcmp(usuario.password, password) == 0)
        {
            // Encuentra un usuario del archivo con el nombre de usuario y contraseña buscados
            logeoExitoso = 1;
            break;
        }
    }

    // Cierra el archivo
    fclose(archivo);

    if (logeoExitoso)
    {
        // Si el inicio de sesión es exitoso, almacenar los detalles del usuario en usuarioActual
        usuarioActual = usuario;
    }

    return logeoExitoso;
}

/// Retorna 1 si existe el nombre de usuario. Retorna el usuario buscado si existe
char existeUsuario( FILE*archivo, Usuario *usuario)
{
    archivo=fopen(ARCHIVO_USUARIOS,"rb");
    char existe = 0;
    Usuario tempUsuario;

    if (archivo == NULL || usuario == NULL)
    {
        printf("Error: Archivo o usuario nulo.\n");
        return 0;
    }

    fseek(archivo, 0, SEEK_SET);

    while (fread(&tempUsuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(tempUsuario.Apellidoynombre, usuario->Apellidoynombre) == 0)
        {
            *usuario = tempUsuario;  // Actualizar el usuario con los detalles existentes
            existe = 1;
            break;
        }
    }
    fclose(archivo);
    return existe;
}

Usuario *obtenerUsuarios(int *n)
{

    Usuario usuario;
    Usuario *usuarios;  ///Vector dinámico de usuarios
    int i;

///	 Abre el archivo en modo lectura
    FILE *ARCHIVO_USUARIOS = fopen(ARCHIVO_USUARIOS, "rb");

    if (ARCHIVO_USUARIOS == NULL)   /// Si no se pudo abrir el archivo, el valor de archivo es NULL
    {
        *n = 0; /// No se pudo abrir. Se considera n = 0
        usuarios = NULL;

    }
    else
    {

        fseek(ARCHIVO_USUARIOS, 0, SEEK_END); /// Posiciona el cursor al final del archivo
        *n = ftell(ARCHIVO_USUARIOS) / sizeof(Usuario); /// # de usuarios almacenados en el archivo. (# de registros)
        usuarios = (Usuario *)malloc((*n) * sizeof(Usuario));///  Se asigna memoria para todos los usuarios almacenados en el archivo

        /// Se recorre el archivo secuencialmente
        fseek(ARCHIVO_USUARIOS, 0, SEEK_SET);  ///Posiciona el cursor al principio del archivo
        fread(&usuario, sizeof(usuario), 1, ARCHIVO_USUARIOS);
        i = 0;
        while (!feof(ARCHIVO_USUARIOS))
        {
            usuarios[i++] = usuario;
            fread(&usuario, sizeof(usuario), 1, ARCHIVO_USUARIOS);
        }

///		 Cierra el archivo
        fclose(ARCHIVO_USUARIOS);
    }

    return usuarios;
}

int leerLinea(char *cad, int n)///revisado
{
    int i, c;

    /// 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER
    c = getchar();
    if (c == EOF)
    {
        cad[0] = '\0';
        return 0;
    }

    if (c == '\n')
    {
        i = 0;
    }
    else
    {
        cad[0] = c;
        i = 1;
    }

    /// 2. LECTURA DE LA CADENA
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        cad[i] = c;
    }
    cad[i] = '\0';

    ///3. LIMPIEZA DEL BUFFER
    if (c != '\n' && c != EOF) /// es un caracter
        while ((c = getchar()) != '\n' && c != EOF);

    return 1;
}

void leerClave(char *password)  ///revisado
{
    char caracter;
    int i = 0;

    while (caracter = getch())
    {
        if (caracter == TECLA_ENTER)
        {
            password[i] = '\0';
            break;

        }
        else if (caracter == TECLA_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }

        }
        else
        {
            if (i < MAX)
            {
                printf("*");
                password[i] = caracter;
                i++;
            }
        }
    }
}
///FUNCIONES PARA ARREGLO DE LISTAS

Nodo*inicLista()//revisada
{
    return NULL;
}
///FUNCION PARA MODIFICAR EL ARCHIVO//revisada
void modificarEmpleadoPorApellidoYNombre(const char *archivoNombre)
{
    FILE *archivo = fopen(archivoNombre, "r+b");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char apellidoNombreBuscar[MAX];
    printf("Ingrese Apellido y Nombre del empleado a buscar: ");
    scanf(" %[^\n]s", apellidoNombreBuscar);

    Usuario empleado;

    while (fread(&empleado, sizeof(Usuario), 1, archivo) == 1)
    {
        if (strcmp(empleado.Apellidoynombre, apellidoNombreBuscar) == 0)
        {
            // Mostrar información del empleado
            printf("\nInformacion del empleado:\n");
            printf("DNI: %d\n", empleado.dni);
            printf("Apellido y Nombre: %s\n", empleado.Apellidoynombre);
            printf("Usuario: %s\n", empleado.nombreUsuario);
            printf("Perfil: %s\n", empleado.perfil);

            // Ofrecer opciones de modificación
            int opcion;
            printf("\n¿Que desea modificar?\n");
            printf("1. Nombre de Usuario\n");
            printf("2. Contrasena\n");
            printf("3. Perfil\n");
            printf("4. Salir\n");
            printf("Ingrese el numero de la opcion: ");
            scanf("%d", &opcion);

            switch (opcion)
            {
            case 1:
                printf("Ingrese el nuevo nombre de usuario: ");
                scanf(" %[^\n]s", empleado.nombreUsuario);
                break;
            case 2:
                printf("Ingrese la nueva contrasena: ");
                scanf(" %[^\n]s", empleado.password);
                break;
            case 3:
                printf("Ingrese el nuevo perfil: ");
                scanf(" %[^\n]s", empleado.perfil);
                break;
            case 4:
                // Salir sin hacer modificaciones
                fclose(archivo);
                return;
            default:
                printf("Opcion no valida. Saliendo sin hacer modificaciones.\n");
                fclose(archivo);
                return;
            }

            // Posicionarse en el registro correspondiente y escribir las modificaciones
            fseek(archivo, -sizeof(Usuario), SEEK_CUR);
            fwrite(&empleado, sizeof(Usuario), 1, archivo);
            printf("Modificaciones guardadas exitosamente.\n");
            fclose(archivo);
            return;
        }
    }

    // Si se llega aquí, no se encontró el empleado
    printf("Empleado con Apellido y Nombre '%s' no encontrado.\n", apellidoNombreBuscar);
    fclose(archivo);
}
///funcion para mostrar lista en orden alfabetico
Nodo* crearNodo(Usuario empleado)  //revisada
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        // Manejo de error: no se pudo asignar memoria
        return NULL;
    }

    nuevoNodo->dato = empleado;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

// Función para insertar un nodo en la lista enlazada ordenada alfabéticamente por Apellidoynombre//revisada
void insertarOrdenado(ListaEnlazada* lista, const Usuario* empleado)
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        perror("Error al asignar memoria para el nodo");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = *empleado;
    nuevoNodo->siguiente = NULL;

    Nodo* actual = lista->cabeza;
    Nodo* anterior = NULL;

    // Buscar la posición adecuada en la lista
    while (actual != NULL && strcmp(actual->dato.Apellidoynombre, empleado->Apellidoynombre) < 0)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Insertar el nuevo nodo en la posición adecuada
    if (anterior == NULL)
    {
        // El nuevo nodo será la cabeza de la lista
        nuevoNodo->siguiente = lista->cabeza;
        lista->cabeza = nuevoNodo;
    }
    else
    {
        // El nuevo nodo se inserta entre dos nodos existentes
        anterior->siguiente = nuevoNodo;
        nuevoNodo->siguiente = actual;
    }
}

// Función para pasar la información del archivo "empleados.bin" a una lista enlazada ordenada//revisada
void pasarArchivoAListaOrdenada(ListaEnlazada* lista)
{
    FILE* archivo = fopen("empleados.bin", "rb");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    Usuario empleado;

    while (fread(&empleado, sizeof(Usuario), 1, archivo) == 1)
    {
        insertarOrdenado(lista, &empleado);
    }

    fclose(archivo);
}

// Función para mostrar la lista enlazada ordenada//revisada
void mostrarListaOrdenada(const ListaEnlazada* lista)
{
    Nodo* actual = lista->cabeza;

    printf("Lista de empleados ordenada alfabéticamente:\n");

    while (actual != NULL)
    {
        printf("Apellido y Nombre: %s, DNI: %d, Usuario: %s, Perfil: %s\n",
               actual->dato.Apellidoynombre, actual->dato.dni, actual->dato.nombreUsuario, actual->dato.perfil);

        actual = actual->siguiente;
    }
}
// Función para buscar un empleado por DNI en la lista enlazada//revisado
Nodo* buscarEmpleadoPorDNIenLista(const ListaEnlazada* lista, int dniBuscado)
{
    Nodo* actual = lista->cabeza;

    while (actual != NULL)
    {
        if (actual->dato.dni == dniBuscado)
        {
            return actual; // Se encontró el empleado, devuelve el nodo
        }
        actual = actual->siguiente;
    }

    return NULL; // No se encontró el empleado
}

// Función para mostrar los datos de un empleado//revisado
void mostrarEmpleado(Usuario empleado)
{
    printf("DNI: %d\n", empleado.dni);
    printf("Apellido y Nombre: %s\n", empleado.Apellidoynombre);
    printf("Nombre de Usuario: %s\n", empleado.nombreUsuario);
    printf("Contraseña: %s\n", empleado.password);
    printf("Perfil: %s\n", empleado.perfil);
}

// Función para mostrar los datos de un nodo (empleado) por DNI//revisado
void mostrarEmpleadoPorDNI(const ListaEnlazada* lista, int dniBuscado)
{
    Nodo* empleadoBuscado = buscarEmpleadoPorDNIenLista(lista, dniBuscado);

    if (empleadoBuscado != NULL)
    {
        printf("Empleado encontrado:\n");
        mostrarEmpleado(empleadoBuscado->dato);
    }
    else
    {
        printf("Empleado con DNI %d no encontrado en la lista.\n", dniBuscado);
    }
}
///FUNCIONES DE ELIMINACION
// Función para eliminar un empleado por DNI desde la lista y escribirlo en el archivo de bajas
void eliminarEmpleadoPorDNI(ListaEnlazada* lista, int dniAEliminar)  //revisada
{
    Nodo* actual = lista->cabeza;
    Nodo* anterior = NULL;

    while (actual != NULL)
    {
        if (actual->dato.dni == dniAEliminar)
        {
            // Crear el archivo de bajas y escribir el empleado eliminado
            FILE* archivoBajas = fopen(ARCHIVO_BAJAS, "ab");
            if (archivoBajas != NULL)
            {
                fwrite(&actual->dato, sizeof(Usuario), 1, archivoBajas);
                fclose(archivoBajas);
                printf("Empleado copiado al archivo de bajas.\n");
            }
            else
            {
                printf("Error al abrir el archivo de bajas.\n");
            }

            // Eliminar el nodo de la lista
            if (anterior != NULL)
            {
                anterior->siguiente = actual->siguiente;
            }
            else
            {
                lista->cabeza = actual->siguiente;
            }

            free(actual); // Liberar la memoria del nodo eliminado
            printf("Empleado eliminado de la lista.\n");
            break; // Salir del bucle después de la eliminación
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}
// Función para actualizar el archivo de usuarios con la lista modificada//revisada
void actualizarArchivoUsuarios(const ListaEnlazada* lista)
{
    FILE* archivoUsuarios = fopen(ARCHIVO_USUARIOS, "wb");
    if (archivoUsuarios != NULL)
    {
        Nodo* actual = lista->cabeza;
        while (actual != NULL)
        {
            fwrite(&actual->dato, sizeof(Usuario), 1, archivoUsuarios);
            actual = actual->siguiente;
        }
        fclose(archivoUsuarios);
        printf("Archivo de usuarios actualizado.\n");
    }
    else
    {
        printf("Error al abrir el archivo de usuarios para actualizar.\n");
    }
}
//MOSTRAR ARCHIVO BAJAS
void mostrarContenidoArchivoBajas()
{
    FILE* archivoBajas = fopen(ARCHIVO_BAJAS, "rb");

    if (archivoBajas == NULL)
    {
        perror("Error al abrir el archivo de bajas");
        return;
    }

    Usuario empleado;

    printf("\nContenido del archivo de bajas:\n");

    while (fread(&empleado, sizeof(Usuario), 1, archivoBajas) == 1)
    {
        printf("DNI: %d, Apellido y Nombre: %s, Usuario: %s, Perfil: %s\n",
               empleado.dni, empleado.Apellidoynombre, empleado.nombreUsuario, empleado.perfil);
    }

    fclose(archivoBajas);
}
