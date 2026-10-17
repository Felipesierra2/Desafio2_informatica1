#ifndef REDSOCIAL_H
#define REDSOCIAL_H
#include "Mensajes.h"
#include "Solicitud.h"
#include <string>
#include <new>

class Usuario;

class RedSocial
{
private:
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    Mensajes** mensajes;
    int cantidadMensajes;
    int capacidadMensajes;

    Solicitud** solicitudes;
    int cantidadSolicitudes;
    int capacidadSolicitudes;

    bool agregarSolicitudAdministrada(Solicitud* solicitud);
    bool administraSolicitud(const Solicitud* solicitud) const;
    bool agregarMensajeAdministrado(Mensajes* mensaje);

public:
    RedSocial();
    ~RedSocial();
    Usuario* buscarUsuario(const std::string& apodo) const;
    bool registrarUsuario(Usuario* usuario);
    bool enviarMensaje(Usuario* remitente,Usuario* destinatario,const std::string& contenido,
        const std::string& fecha);
    bool enviarSolicitud(Usuario* remitente, Usuario* destinatario);
    bool aceptarSolicitud(Solicitud* solicitud);
    bool rechazarSolicitud(Solicitud* solicitud);

    int getCantidadUsuarios() const;
};

#endif // REDSOCIAL_H
