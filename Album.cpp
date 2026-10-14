#include "Album.h"

Album::Album(const std::string& nombre,
             const std::string& ruta)
    : nombre(nombre),
    ruta(ruta)
{
}

const std::string& Album::getNombre() const
{
    return nombre;
}

const std::string& Album::getRuta() const
{
    return ruta;
}
