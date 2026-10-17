#include "MedidorRecursos.h"
#include <iostream>

unsigned long long MedidorRecursos::iteraciones = 0;
unsigned long long MedidorRecursos::memoriaRegistrada = 0;

void MedidorRecursos::iniciarMedicion()
{
    iteraciones = 0;
}

void MedidorRecursos::registrarIteracion()
{
    ++iteraciones;
}

void MedidorRecursos::registrarMemoria(unsigned long long bytes)
{
    memoriaRegistrada += bytes;
}

void MedidorRecursos::liberarMemoria(unsigned long long bytes)
{
    if (bytes <= memoriaRegistrada)
    {
        memoriaRegistrada -= bytes;
    }else{
        std::cout << "Advertencia: se intentan liberar "
                  << bytes << " bytes, pero solo hay "
                  << memoriaRegistrada
                  << " bytes registrados.\n";

        memoriaRegistrada = 0;
    }
}

unsigned long long MedidorRecursos::getIteraciones()
{
    return iteraciones;
}

unsigned long long MedidorRecursos::getMemoriaRegistrada()
{
    return memoriaRegistrada;
}

void MedidorRecursos::mostrarReporte()
{
    std::cout << "\n=== MEDICION DE RECURSOS ===\n";
    std::cout << "Iteraciones: " << iteraciones << '\n';
    std::cout << "Memoria registrada: "
              << memoriaRegistrada << " bytes\n";
}
