#ifndef MENSAJES_H
#define MENSAJES_H

#include <string>
class Usuario;

class Mensajes
{
private:
    Usuario* remitente;
    Usuario* destinatario;
    std::string contenido;
    std::string fechaDeEnvio;
    std::string fechaRecepcion;
    bool leido;

public:
    Mensajes();
};

#endif // MENSAJES_H
