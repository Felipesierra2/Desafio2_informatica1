#include "Solicitud.h"

Solicitud::Solicitud(Usuario* remitente, Usuario* destinatario)
    : remitente(remitente),
    destinatario(destinatario),
    estado(0)
{
}

Usuario* Solicitud::getRemitente() const
{
    return remitente;
}

Usuario* Solicitud::getDestinatario() const
{
    return destinatario;
}

int Solicitud::getEstado() const
{
    return estado;
}

void Solicitud::aceptar()
{
    estado = 1;
}

void Solicitud::rechazar()
{
    estado = 2;
}

