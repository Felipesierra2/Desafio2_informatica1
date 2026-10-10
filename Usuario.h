#ifndef USUARIO_H
#define USUARIO_H

#include "Album.h"
#include "Mensajes.h"
#include "SolicitudAmistad.h"
#include <string>

class Usuario
{
private:
    std::string apodo;
    std::string fechaDeNacimiento;
    std::string correo;
    std::string fotoDePerfil;
    std::string pais;
    std::string ciudad;
    std::string fechaDeInscripcion;
    Usuario* amigos;
    Mensajes* mensajesEnviados;
    Mensajes* mensajesRecibidos;
    SolicitudAmistad* solicitudAmistad;
    Album* albumes;
public:
    Usuario();
    Usuario(std::string apodo,std::string fechaDeNacimiento,std::string correo,
            std::string fotoDePerfil,std::string pais, std::string ciudad, std::string fechaDeInscripción);

};

#endif // USUARIO_H
