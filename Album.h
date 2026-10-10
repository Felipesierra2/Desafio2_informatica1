#ifndef ALBUM_H
#define ALBUM_H

#include "Foto.h"
#include <string>
class Album
{
private:
    std::string nombre;
    std::string rutaDeAlmacenamiento;
    std::string privacidad;
    Foto* fotos;
public:
    Album();
};

#endif // ALBUM_H
