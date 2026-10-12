#include "Usuario.h"
#include "Mensajes.h"
#include <iostream>

using namespace std;

int main()
{
    Usuario usuario1(
        "Felipe",
        "2000-05-15",
        "felipe@gmail.com",
        "felipe.jpg",
        "Colombia",
        "Medellin",
        "2026-10-12"
        );

    Usuario usuario2(
        "Carlos",
        "2001-08-20",
        "carlos@gmail.com",
        "carlos.jpg",
        "Colombia",
        "Bogota",
        "2026-10-12"
        );

    cout << "=== PRUEBA DE ENVIO DE MENSAJES ===\n\n";

    bool enviado = usuario1.enviarMensaje(
        &usuario2,
        "Hola Carlos, como estas?",
        "2026-10-12"
        );

    if (enviado)
    {
        cout << "Mensaje enviado correctamente.\n\n";

        cout << "Remitente: "
             << usuario1.getApodo() << '\n';

        cout << "Destinatario: "
             << usuario2.getApodo() << '\n';

        cout << "Mensajes enviados por Felipe: "
             << usuario1.getCantidadMensajesEnviados() << '\n';

        cout << "Mensajes recibidos por Carlos: "
             << usuario2.getCantidadMensajesRecibidos() << '\n';
    }
    else
    {
        cout << "No se pudo enviar el mensaje.\n";
    }

    Mensajes* mensaje = usuario2.getMensajeRecibido(0);

    if (mensaje != nullptr){
        std::cout << "Remitente: "
                  << mensaje->getRemitente()->getApodo()
                  << std::endl;

        std::cout << "Contenido: "
                  << mensaje->getContenido()
                  << std::endl;

        std::cout << "Fecha: "
                  << mensaje->getFecha()
                  << std::endl;

        std::cout << "Leido: "
                  << (mensaje->getLeido() ? "Si" : "No")
                  << std::endl;
    }

    if (usuario2.marcarMensajeComoLeido(0))
    {
        std::cout << "Mensaje marcado como leido." << std::endl;
    }

    if (mensaje != nullptr)
    {
        std::cout << "Leido: "
                  << (mensaje->getLeido() ? "Si" : "No")
                  << std::endl;
    }
    return 0;
}
