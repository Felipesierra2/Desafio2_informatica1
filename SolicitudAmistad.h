#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H

#include "Foto.h"
#include <string>
class SolicitudAmistad
{
    std::string remitente;
    std::string destinatario;
    std::string estado;
    std::string fechaSolicitud;
public:
    SolicitudAmistad();
};

#endif // SOLICITUDAMISTAD_H
