#include "MedidorRecursos.h"
#include "RedSocial.h"
#include "Usuario.h"
#include "Mensajes.h"
#include <iostream>

using namespace std;

int main()
{
    {
        RedSocial redSocial;

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

        Usuario usuario3(
            "Ana",
            "2002-04-10",
            "ana@udea.edu.co",
            "fotos/ana.jpg",
            "Colombia",
            "Medellin",
            "2026-10-16"
            );

        bool agregado = usuario1.agregarAmigo(&usuario2);

        std::cout << "Amigo agregado: "
                  << (agregado ? "Si" : "No") << '\n';

        bool existe = usuario1.esAmigo(&usuario2);

        std::cout << "Es amigo: "
                  << (existe ? "Si" : "No") << '\n';

        MedidorRecursos::mostrarReporte();

        MedidorRecursos::iniciarMedicion();

        cout << "=== PRUEBA DE ENVIO DE MENSAJES ===\n\n";

        bool enviado = redSocial.enviarMensaje(
            &usuario1,
            &usuario2,
            "Hola Carlos, como estas?",
            "2026-10-14"
            );

        if (enviado)
        {
            Mensajes* mensaje = usuario2.getMensajeRecibido(0);

            cout << "Mensaje enviado correctamente.\n\n";

            cout << "Remitente: "
                 << mensaje->getRemitente()->getApodo() << '\n';

            cout << "Destinatario: "
                 << mensaje->getDestinatario()->getApodo() << '\n';

            cout << "Mensajes enviados por Felipe: "
                 << usuario1.getCantidadMensajesEnviados() << '\n';

            cout << "Mensajes recibidos por Carlos: "
                 << usuario2.getCantidadMensajesRecibidos() << '\n';

            cout << "Contenido: "
                 << mensaje->getContenido() << '\n';
            cout << "Fecha: "
                 << mensaje->getFecha() << endl;

            mensaje->marcarComoLeido();

            cout << "Leido: "
                 << (mensaje->getLeido() ? "Si":"No") << endl;
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

        bool enviada = redSocial.enviarSolicitud(&usuario1, &usuario3);

        std::cout << "Solicitud enviada: "
                  << (enviada ? "Si" : "No") << '\n';

        Solicitud* solicitud = nullptr;

        if (enviada)
        {
            solicitud = usuario3.getSolicitud(0);

            std::cout << "Estado inicial: "
                      << solicitud->getEstado() << '\n';

            bool aceptada = redSocial.aceptarSolicitud(solicitud);

            std::cout << "Solicitud aceptada: "
                      << (aceptada ? "Si" : "No") << '\n';

            std::cout << "Felipe es amigo de Ana: "
                      << (usuario1.esAmigo(&usuario3) ? "Si" : "No") << '\n';

            std::cout << "Ana es amiga de Felipe: "
                      << (usuario3.esAmigo(&usuario1) ? "Si" : "No") << '\n';
        }

        std::cout << "\n=== PRUEBA DE RECHAZO DE SOLICITUD ===\n";

        Usuario usuarioRechazo1(
            "Pedro", "2002-03-10", "pedro@correo.com",
            "", "Colombia", "Medellin", "2026-10-17"
            );

        Usuario usuarioRechazo2(
            "Laura", "2003-07-15", "laura@correo.com",
            "", "Colombia", "Medellin", "2026-10-17"
            );

        // 1. Enviar la solicitud
        bool enviada1 = redSocial.enviarSolicitud(
            &usuarioRechazo1,
            &usuarioRechazo2
            );

        std::cout << "Solicitud enviada: "
                  << (enviada1 ? "Si" : "No") << '\n';

        Solicitud* solicitudRechazo =
            usuarioRechazo2.getSolicitud(0);

        bool rechazada =
            redSocial.rechazarSolicitud(solicitudRechazo);

        std::cout << "Solicitud rechazada: "
                  << (rechazada ? "Si" : "No") << '\n';

        if (solicitudRechazo != nullptr) {
            std::cout << "Estado final: "
                      << solicitudRechazo->getEstado() << '\n';
        }

        std::cout << "Pedro es amigo de Laura: "
                  << (usuarioRechazo1.esAmigo(&usuarioRechazo2)
                          ? "Si" : "No") << '\n';

        std::cout << "Laura es amiga de Pedro: "
                  << (usuarioRechazo2.esAmigo(&usuarioRechazo1)
                          ? "Si" : "No") << '\n';

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

        Album* album1 = new Album("Vacaciones", "fotos/vacaciones");
        Album* album2 = new Album("Universidad", "fotos/universidad");

        usuario1.agregarAlbum(album1);
        usuario1.agregarAlbum(album2);

        std::cout << "Cantidad de albumes: "
                  << usuario1.getCantidadAlbumes()
                  << std::endl;

        Album* albumConsultado = usuario1.getAlbum(0);

        if (albumConsultado != nullptr)
        {
            std::cout << "Nombre: "
                      << albumConsultado->getNombre()
                      << std::endl;

            std::cout << "Ruta: "
                      << albumConsultado->getRuta()
                      << std::endl;
        }
    }

    MedidorRecursos::mostrarReporte();
    return 0;
}

