#ifndef SOLICITUD_H
#define SOLICITUD_H

#include "Foto.h"
#include <string>

class Usuario;

class Solicitud
{
    Usuario* remitente;
    Usuario* destinatario;
    int estado;//0: pendiente, 1: aceptada, 2: rechazad
public:
    Solicitud(Usuario* remitente, Usuario* destinatario);
    Usuario* getRemitente() const;
    Usuario* getDestinatario() const;
    int getEstado() const;

    void aceptar();
    void rechazar();
};

#endif // SOLICITUD_H
