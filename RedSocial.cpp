#include "RedSocial.h"
#include "Usuario.h"
#include <new>

RedSocial::RedSocial()
    : usuarios(nullptr),
    cantidadUsuarios(0),
    capacidadUsuarios(0)
{
}

Usuario* RedSocial::buscarUsuario(const std::string& apodo) const
{
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (usuarios[i]->getApodo() == apodo) {
            return usuarios[i];
        }
    }
    return nullptr;
}

bool RedSocial::registrarUsuario(Usuario* usuario)
{
    if (usuario == nullptr) {
        return false;
    }

    if (buscarUsuario(usuario->getApodo()) != nullptr) {
        return false;
    }

    if (cantidadUsuarios == capacidadUsuarios) {
        int nuevaCapacidad = (capacidadUsuarios == 0) ? 4 : capacidadUsuarios * 2;

        Usuario** nuevo = new (std::nothrow) Usuario*[nuevaCapacidad];
        if (nuevo == nullptr) {
            return false;
        }

        for (int i = 0; i < cantidadUsuarios; ++i) {
            nuevo[i] = usuarios[i];
        }

        delete[] usuarios;
        usuarios = nuevo;
        capacidadUsuarios = nuevaCapacidad;
    }

    usuarios[cantidadUsuarios] = usuario;
    ++cantidadUsuarios;
    return true;
}

int RedSocial::getCantidadUsuarios() const
{
    return cantidadUsuarios;
}

RedSocial::~RedSocial()
{
    for (int i = 0; i < cantidadUsuarios; ++i) {
        delete usuarios[i];
    }
    delete[] usuarios;
}
