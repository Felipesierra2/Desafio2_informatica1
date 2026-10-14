#ifndef ALBUM_H
#define ALBUM_H

#include "Foto.h"
#include <string>
class Album
{
private:
    std::string nombre;
    std::string ruta;
public:
    Album(const std::string& nombre,
          const std::string& ruta);

    const std::string& getNombre() const;
    const std::string& getRuta() const;
};

#endif // ALBUM_H
