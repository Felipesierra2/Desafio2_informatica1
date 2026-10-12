#ifndef REDSOCIAL_H
#define REDSOCIAL_H
#include <string>
#include <new>

class Usuario;

class RedSocial
{
private:
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

public:
    RedSocial();
    Usuario* buscarUsuario(const std::string& apodo) const;
    bool registrarUsuario(Usuario* usuario);
    int getCantidadUsuarios() const;
    ~RedSocial();
};

#endif // REDSOCIAL_H
