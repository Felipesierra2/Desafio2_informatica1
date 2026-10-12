#ifndef SOLICITUD_H
#define SOLICITUD_H

#include "Foto.h"
#include <string>
class Solicitud
{
    std::string remitente;
    std::string destinatario;
    std::string estado;
    std::string fechaSolicitud;
public:
    Solicitud();
};

#endif // SOLICITUD_H
