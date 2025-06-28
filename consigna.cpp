// Una empresa de electrodomésticos cuenta con vendedores en diferentes sucursales. Al finalizar el mes se cuenta con los datos de cada venta ordenados por 
// código de vendedor en forma ascendente:

// - Código de vendedor
// - Fecha de venta
// - Producto vendido  
// - Monto de la venta
// - Comisión ganada

// Y en forma separada, los datos de cada vendedor:

// - Código de vendedor
// - Nombre
// - Apellido
// - Sucursal (1: Centro, 2: Shopping)

// Los datos ya están cargados en vectores estáticos y que cada vector tiene una variable asociada que indica la cantidad de elementos cargados.

// Se asume que cada vendedor realiza al menos una venta en el mes.

// ---

// ## Se pide:

// **1)** Definir las estructuras de datos necesarias para soportar la solución del problema.

// **2)** Escribir una función que ordene el vector de vendedores por sucursal (ordenamiento burbuja).

// **3)** Escribir una función que busque en el vector de vendedores por código y devuelva la posición en el vector (búsqueda binaria).

// **4)** Escribir una función que genere un nuevo vector con cada vendedor y su total de comisiones del mes, utilizando apareo entre ambos vectores. 
// **Importante:** Si el monto de la venta supera los $20.000 y la sucursal es Centro (1), se debe aumentar la comisión en un 15% antes de sumarla al total.

// **5)** Escribir una función que muestre un reporte por sucursal indicando: nombre de la sucursal, cantidad total de ventas y el vendedor con mayor total 
// de comisiones (usar corte de control).



#include <iostream>
#include <string>
using namespace std;

// **1)** Definir las estructuras de datos necesarias para soportar la solución del problema.

struct Vendedor{
    int codigo_vendedor;    // - Código de vendedor
    string nombre;          // - Nombre
    string apellido;        // - Apellido
    int sucursal;           // - Sucursal (1: Centro, 2: Shopping)
};

struct Venta{
    int codigo_vendedor;    // - Código de vendedor
    int fecha_venta;        // - Fecha de venta
    string producto_vendido;// - Producto vendido  
    float monto;            // - Monto de la venta
    float comision;         // - Comisión ganada
};

// **2)** Escribir una función que ordene el vector de vendedores por sucursal (ordenamiento burbuja).

void ordenar_por_sucursal(Vendedor vendedores[], int len_vendedores){
    bool ordenado = false;
    for(int i=0; (i<len_vendedores && !ordenado); i++){
        ordenado = true;
        for(int j=0; j<len_vendedores-i-1; j++){
            if(vendedores[j].sucursal > vendedores[j+1].sucursal){
                Vendedor aux = vendedores[j];
                vendedores[j] = vendedores[j+1];
                vendedores[j+1] = aux;
                ordenado = false;
            }
        }
    }
    return;
}

// Necesario para probar los ej. de busqueda.
void ordenar_vendedores_por_codigo(Vendedor vendedores[], int len_vendedores){
    bool ordenado = false;
    for(int i=0; (i<len_vendedores && !ordenado); i++){
        ordenado = true;
        for(int j=0; j<len_vendedores-i-1; j++){
            if(vendedores[j].codigo_vendedor > vendedores[j+1].codigo_vendedor){
                Vendedor aux = vendedores[j];
                vendedores[j] = vendedores[j+1];
                vendedores[j+1] = aux;
                ordenado = false;
            }
        }
    }
    return;
}

// Necesario para probar los ej. de corte.
void ordenar_ventas_por_codigo(Venta ventas[], int len_ventas){
    bool ordenado = false;
    for(int i=0; (i<len_ventas && !ordenado); i++){
        ordenado = true;
        for(int j=0; j<len_ventas-i-1; j++){
            if(ventas[j].codigo_vendedor > ventas[j+1].codigo_vendedor){
                Venta aux = ventas[j];
                ventas[j] = ventas[j+1];
                ventas[j+1] = aux;
                ordenado = false;
            }
        }
    }
    return;
}

// **3)** Escribir una función que busque en el vector de vendedores por código y devuelva la posición en el vector (búsqueda binaria).
int buscar_indice_por_codigo (Vendedor vendedores[], int len_vendedores, int codigo){
    int ret=-1;
    int inicio = 0, fin = len_vendedores-1;
    while(fin >= inicio && ret==-1){
        int medio = inicio + (fin-inicio)/2;
        if(vendedores[medio].codigo_vendedor == codigo){
            ret = medio;
        } else if(vendedores[medio].codigo_vendedor > codigo){
            inicio = medio+1;
        } else {
            fin = medio-1;
        }
    }
    return ret;
}

// **4)** Escribir una función que genere un nuevo vector con cada vendedor y su total de comisiones del mes, utilizando apareo entre ambos vectores. 
// **Importante:** Si el monto de la venta supera los $20.000 y la sucursal es Centro (1), se debe aumentar la comisión en un 15% antes de sumarla al total.

struct VendedorConTotal{
    int codigo_vendedor;    // - Código de vendedor
    string nombre;          // - Nombre
    string apellido;        // - Apellido
    int sucursal;           // - Sucursal (1: Centro, 2: Shopping)
    float total_comision;   // - Total de las comisiones del mes.
    int cantidad_ventas;    // - Cantidad de ventas en el mes
};

void ordenar_por_sucursal_con_total_comisiones(VendedorConTotal vendedores_con_total[], int len_vendedores_con_total){
    bool ordenado = false;
    for(int i=0; (i<len_vendedores_con_total && !ordenado); i++){
        ordenado = true;
        for(int j=0; j<len_vendedores_con_total-i-1; j++){
            if(vendedores_con_total[j].sucursal > vendedores_con_total[j+1].sucursal){
                VendedorConTotal aux = vendedores_con_total[j];
                vendedores_con_total[j] = vendedores_con_total[j+1];
                vendedores_con_total[j+1] = aux;
                ordenado = false;
            }
        }
    }
    return;
}

int obtener_vendedores_con_total_de_comisiones(Vendedor vendedores[], int len_vendedores, Venta ventas[], int len_ventas, VendedorConTotal vendedores_con_total[]){
    int j=0; //indices de "Ventas" y "Ventas_Con_Total".
    //cout << "\n\nobtener_vendedores_con_total_de_comisiones"<< endl;
    // Recorro el array de vendedores:
    for(int i=0;i<len_vendedores; i++){
        float suma_comisiones = 0;
        int cantidad_ventas_por_vendedor = 0;
        int key = vendedores[i].codigo_vendedor;
        //cout << "\nVendedor " << i << " : " << vendedores[i].codigo_vendedor << endl;
        while( j<len_ventas && key == ventas[j].codigo_vendedor){
            //cout << "ventas[" << j << "].monto: " << ventas[j].monto << " ; ventas[" << j << "].comision: " << ventas[j].comision ;
            if((ventas[j].monto > 20000) && (vendedores[i].sucursal == 1)){
                suma_comisiones += (ventas[j].comision * 1.15);
            } else {
                suma_comisiones += ventas[j].comision;
            }
            //cout << " ; suma_comisiones: " << suma_comisiones << endl;
            cantidad_ventas_por_vendedor++;
            j++;
        }
        // Utilizo i como indice de "vendedores_con_total", ya que hay un "vendedor_con_total" por cada "vendedor".
        vendedores_con_total[i].codigo_vendedor = vendedores[i].codigo_vendedor;
        vendedores_con_total[i].nombre = vendedores[i].nombre;
        vendedores_con_total[i].apellido = vendedores[i].apellido;
        vendedores_con_total[i].sucursal = vendedores[i].sucursal;
        vendedores_con_total[i].total_comision = suma_comisiones;
        vendedores_con_total[i].cantidad_ventas = cantidad_ventas_por_vendedor;
    }

    return len_vendedores;
}

// **5)** Escribir una función que muestre un reporte por sucursal indicando: nombre de la sucursal, cantidad total de ventas y el vendedor con mayor total 
// de comisiones (usar corte de control).

void reporte_por_sucursal(Vendedor vendedores[], int len_vendedores, VendedorConTotal vendedores_con_total[]){
    int cantidad_ventas_por_sucursal=0;
    int indice_vendedor_mayor_total_de_comisiones = 0;
    float mayor_total_comision = -1;
    bool cambio_de_sucursal = false;
    for(int i=0;i<len_vendedores; i++){
        
        if(!cambio_de_sucursal && vendedores[i].sucursal == 2){
            cout << "\nReporte de sucursal Centro:" << endl;
            cout << "   - Cantidad total de ventas de la sucursal: " << cantidad_ventas_por_sucursal << endl;
            cout << "   - El vendedor con mayor total de comisiones es: " << vendedores[indice_vendedor_mayor_total_de_comisiones].nombre << " " << vendedores[indice_vendedor_mayor_total_de_comisiones].apellido << " con un total de: $" << mayor_total_comision << endl;
            
            cantidad_ventas_por_sucursal = 0;
            indice_vendedor_mayor_total_de_comisiones = 0;
            mayor_total_comision = -1;
            cambio_de_sucursal = true;
        }

        if(vendedores_con_total[i].total_comision > mayor_total_comision){
            mayor_total_comision = vendedores_con_total[i].total_comision;
            indice_vendedor_mayor_total_de_comisiones = i;
        }

        cantidad_ventas_por_sucursal += vendedores_con_total[i].cantidad_ventas;
    }
    cout << "\nReporte de sucursal Shopping:" << endl;
    cout << "   - Cantidad total de ventas de la sucursal: " << cantidad_ventas_por_sucursal << endl;
    cout << "   - El vendedor con mayor total de comisiones es: " << vendedores[indice_vendedor_mayor_total_de_comisiones].nombre << " " << vendedores[indice_vendedor_mayor_total_de_comisiones].apellido << " con un total de: $" << mayor_total_comision << endl;
    return;
}

void mostrar_vendedores(Vendedor vendedores[], int len_vendedores){
    cout << "\nVendedores: [";
    for(int i=0; i<len_vendedores; i++){
        cout << "\n     (Codigo de vendedor de vendedor numero " << i+1 << " : " << vendedores[i].codigo_vendedor;
        cout << "; nombre : " << vendedores[i].nombre;
        cout << "; apellido : " << vendedores[i].apellido;
        if(i==len_vendedores-1){
            cout << "; sucursal :" << vendedores[i].sucursal <<")\n]" << endl;
        } else {
            cout << "; sucursal :" << vendedores[i].sucursal <<"),";
        }
    }
    return;
}

void mostrar_ventas(Venta ventas[], int len_ventas){
    cout << "\nVentas: [";
    for(int i=0; i<len_ventas; i++){
        cout << "\n     (Codigo de vendedor de venta numero " << i+1 << " : " << ventas[i].codigo_vendedor;
        cout << "; fecha_venta : " << ventas[i].fecha_venta;
        cout << "; producto_vendido : " << ventas[i].producto_vendido;
        cout << "; monto : " << ventas[i].monto;
        if(i==len_ventas-1){
            cout << "; comision :" << ventas[i].comision <<")\n]" << endl;
        } else {
            cout << "; comision :" << ventas[i].comision <<"),";
        }
    }
    return;
}

void mostrar_vendedores_con_total(VendedorConTotal vendedores_con_total[], int len_vendedores_con_total){
    cout << "\nVendedores con total de comisiones por mes: [";
    for(int i=0; i<len_vendedores_con_total; i++){
        cout << "\n     (Codigo de vendedor de vendedor con total " << i+1 << " : " << vendedores_con_total[i].codigo_vendedor;
        cout << "; nombre : " << vendedores_con_total[i].nombre;
        cout << "; apellido : " << vendedores_con_total[i].apellido;
        cout << "; sucursal : " << vendedores_con_total[i].sucursal;
        if(i==len_vendedores_con_total-1){
            cout << "; total_comision :" << vendedores_con_total[i].total_comision <<")\n]" << endl;
        } else {
            cout << "; total_comision :" << vendedores_con_total[i].total_comision <<"),";
        }
    }
    return;
}

// Variables globales con datos precargados
const int MAX_VENDEDORES = 100;
const int MAX_VENTAS = 500;
const int MAX_RESULTADO = 100;

// Vector de vendedores (ordenado por código ascendente)
Vendedor vendedores[MAX_VENDEDORES] = {
    {101, "Juan", "Perez", 1},
    {103, "Ana", "Lopez", 1},
    {105, "Carlos", "Ruiz", 2},
    {107, "Maria", "Garcia", 2},
    {109, "Luis", "Martinez", 1}};
int cantVendedores = 5;

// Vector de ventas (ordenado por código de vendedor ascendente)
Venta ventas[MAX_VENTAS] = {
    {101, 15032024, "Heladera", 15000.0, 450.0},
    {101, 16032024, "Microondas", 25000.0, 750.0},
    {101, 18032024, "Lavarropas", 30000.0, 900.0},
    {103, 17032024, "Televisor", 18000.0, 540.0},
    {103, 20032024, "Aire Acond.", 22000.0, 660.0},
    {105, 19032024, "Cocina", 12000.0, 360.0},
    {105, 21032024, "Freezer", 16000.0, 480.0},
    {105, 22032024, "Lavavajillas", 28000.0, 840.0},
    {107, 23032024, "Heladera", 35000.0, 1050.0},
    {107, 25032024, "Televisor", 40000.0, 1200.0},
    {109, 26032024, "Microondas", 8000.0, 240.0},
    {109, 28032024, "Cocina", 45000.0, 1350.0}};
int cantVentas = 12;

// Vector resultado del apareo
int main(){
    VendedorConTotal resultado[MAX_RESULTADO];
    int cantResultado = 0;

    cout << "--- Inicio de Pruebas ---" << endl;
    cout << "\nLista de ventas:" << endl;
    mostrar_ventas(ventas, cantVentas);

    cout << "\n2) Ordeno vendedores por sucursal:" << endl;
    cout << "\nLista de vendedores antes de ordenar:" << endl;
    mostrar_vendedores(vendedores, cantVendedores);
    ordenar_por_sucursal(vendedores, cantVendedores);
    cout << "\nLista de vehiculos despues de ordenar:" << endl;
    mostrar_vendedores(vendedores, cantVendedores);


    cout << "\n3) Busco vendedor con codigo 105:" << endl;
    // Ordeno vendedores por codigo para que funcione correctamente.
    ordenar_vendedores_por_codigo(vendedores, cantVendedores);
    int indice = buscar_indice_por_codigo (vendedores, cantVendedores, 105);
    if (indice != -1) {
        cout << "   Vendedor encontrada en indice " << indice << ". Nombre: " << vendedores[indice].nombre << endl;
    } else {
        cout << "   Vendedor no encontrado." << endl;
    }

    cout << "\n Busco vendedor con codigo 130:" << endl;
    indice = buscar_indice_por_codigo (vendedores, cantVendedores, 130);
    if (indice != -1) {
        cout << "   Vendedor encontrada en indice " << indice << ". Nombre: " << vendedores[indice].nombre << endl;
    } else {
        cout << "   Vendedor no encontrado." << endl;
    }

    cout << "\n4) Genero nuevo vector con ventas totales por mes:" << endl;
    // Ordeno ambos por codigo para que funcione "obtener_vendedores_con_total_de_comisiones"
    ordenar_ventas_por_codigo(ventas,cantVentas);
    ordenar_vendedores_por_codigo(vendedores, cantVendedores);
    //mostrar_vendedores(vendedores, cantVendedores);
    //mostrar_ventas(ventas,cantVentas);
    cantResultado = obtener_vendedores_con_total_de_comisiones(vendedores, cantVendedores, ventas, cantVentas, resultado);
    mostrar_vendedores_con_total(resultado, cantResultado);

    cout << "\n5) Reporte por sucursal:" << endl;
    ordenar_por_sucursal(vendedores, cantVendedores);
    ordenar_por_sucursal_con_total_comisiones(resultado, cantResultado);
    reporte_por_sucursal(vendedores, cantVendedores, resultado);

    cout << "\n--- Fin de Pruebas ---" << endl;

    return 0;
}