#include "Usuario.h"

/*Constructor que define la estrcutura del usuario, se declara vació por defecto
 */

Usuario::Usuario()
    : apodo(""),
    fechaDeNacimiento(""),
    correo(""),
    fotoDePerfil(""),
    pais(""),
    ciudad(""),
    fechaDeInscripcion(""),
    mensajesEnviados(nullptr),
    cantidadMensajesEnviados(0),
    capacidadMensajesEnviados(0),
    mensajesRecibidos(nullptr),
    cantidadMensajesRecibidos(0),
    capacidadMensajesRecibidos(0),
    solicitudAmistad(nullptr),
    cantidadSolicitudes(0),
    capacidadSolicitudes(0),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
}


/*Constructor parametrizado del usuario*/
Usuario::Usuario(const std::string& apodo,
                 const std::string& fechaDeNacimiento,
                 const std::string& correo,
                 const std::string& fotoDePerfil,
                 const std::string& pais,
                 const std::string& ciudad,
                 const std::string& fechaDeInscripcion)
    : apodo(apodo),
    fechaDeNacimiento(fechaDeNacimiento),
    correo(correo),
    fotoDePerfil(fotoDePerfil),
    pais(pais),
    ciudad(ciudad),
    fechaDeInscripcion(fechaDeInscripcion),
    mensajesEnviados(nullptr),
    cantidadMensajesEnviados(0),
    capacidadMensajesEnviados(0),
    mensajesRecibidos(nullptr),
    cantidadMensajesRecibidos(0),
    capacidadMensajesRecibidos(0),
    solicitudAmistad(nullptr),
    cantidadSolicitudes(0),
    capacidadSolicitudes(0),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
}

bool Usuario::esAmigo(const Usuario* usuario) const
{
    for (int i = 0; i < cantidadAmigos; ++i) {
        if (amigos[i] == usuario) {
            return true;
        }
    }
    return false;
}

bool Usuario::agregarAmigo(Usuario* usuario){
    if (usuario == nullptr || usuario == this || esAmigo(usuario)) {
        return false;
    }

    if (cantidadAmigos == capacidadAmigos) {
        int nuevaCapacidad = (capacidadAmigos == 0) ? 4 : capacidadAmigos * 2;

        Usuario** nuevo = new Usuario*[nuevaCapacidad];

        for (int i = 0; i < cantidadAmigos; ++i) {
            nuevo[i] = amigos[i];
        }

        delete[] amigos;
        amigos = nuevo;
        capacidadAmigos = nuevaCapacidad;
    }

    amigos[cantidadAmigos] = usuario;
    ++cantidadAmigos;
    return true;
}

int Usuario::getCantidadAmigos() const
{
    return cantidadAmigos;
}

//Getters
const std::string& Usuario::getApodo() const
{
    return apodo;
}

const std::string& Usuario::getFechaDeNacimiento() const
{
    return fechaDeNacimiento;
}

const std::string& Usuario::getCorreo() const
{
    return correo;
}

const std::string& Usuario::getFotoDePerfil() const
{
    return fotoDePerfil;
}

const std::string& Usuario::getPais() const
{
    return pais;
}

const std::string& Usuario::getCiudad() const
{
    return ciudad;
}

const std::string& Usuario::getFechaDeInscripcion() const
{
    return fechaDeInscripcion;
}

//Setters
void Usuario::setApodo(const std::string& apodo)
{
    this->apodo = apodo;
}

void Usuario::setFechaDeNacimiento(const std::string& fechaDeNacimiento)
{
    this->fechaDeNacimiento = fechaDeNacimiento;
}

void Usuario::setCorreo(const std::string& correo)
{
    this->correo = correo;
}

void Usuario::setFotoDePerfil(const std::string& fotoDePerfil)
{
    this->fotoDePerfil = fotoDePerfil;
}

void Usuario::setPais(const std::string& pais)
{
    this->pais = pais;
}

void Usuario::setCiudad(const std::string& ciudad)
{
    this->ciudad = ciudad;
}

void Usuario::setFechaDeInscripcion(const std::string& fechaDeInscripcion)
{
    this->fechaDeInscripcion = fechaDeInscripcion;
}

/* libera el arreglo, pero no los Usuario* que contiene
 */
Usuario::~Usuario(){
    delete[] amigos;
    delete[] mensajesEnviados;
    delete[] mensajesRecibidos;
    delete[] solicitudAmistad;
    delete[] albumes;
}


/*Realiza una copia técnica de los datos del usuario y sus referencias
 */
Usuario::Usuario(const Usuario& otro)
    : apodo(otro.apodo),
    fechaDeNacimiento(otro.fechaDeNacimiento),
    correo(otro.correo),
    fotoDePerfil(otro.fotoDePerfil),
    pais(otro.pais),
    ciudad(otro.ciudad),
    fechaDeInscripcion(otro.fechaDeInscripcion),
    amigos(nullptr),
    cantidadAmigos(otro.cantidadAmigos),
    capacidadAmigos(otro.capacidadAmigos),
    mensajesEnviados(nullptr),
    cantidadMensajesEnviados(otro.cantidadMensajesEnviados),
    capacidadMensajesEnviados(otro.capacidadMensajesEnviados),
    mensajesRecibidos(nullptr),
    cantidadMensajesRecibidos(otro.cantidadMensajesRecibidos),
    capacidadMensajesRecibidos(otro.capacidadMensajesRecibidos),
    solicitudAmistad(nullptr),
    cantidadSolicitudes(otro.cantidadSolicitudes),
    capacidadSolicitudes(otro.capacidadSolicitudes),
    albumes(nullptr),
    cantidadAlbumes(otro.cantidadAlbumes),
    capacidadAlbumes(otro.capacidadAlbumes)
{
    try {
        if (capacidadAmigos > 0) {
            amigos = new Usuario*[capacidadAmigos];
            for (int i = 0; i < cantidadAmigos; ++i) {
                amigos[i] = otro.amigos[i];
            }
        }

        if (capacidadMensajesEnviados > 0) {
            mensajesEnviados = new Mensajes*[capacidadMensajesEnviados];
            for (int i = 0; i < cantidadMensajesEnviados; ++i) {
                mensajesEnviados[i] = otro.mensajesEnviados[i];
            }
        }

        if (capacidadMensajesRecibidos > 0) {
            mensajesRecibidos = new Mensajes*[capacidadMensajesRecibidos];
            for (int i = 0; i < cantidadMensajesRecibidos; ++i) {
                mensajesRecibidos[i] = otro.mensajesRecibidos[i];
            }
        }

        if (capacidadSolicitudes > 0) {
            solicitudAmistad = new Solicitud*[capacidadSolicitudes];
            for (int i = 0; i < cantidadSolicitudes; ++i) {
                solicitudAmistad[i] = otro.solicitudAmistad[i];
            }
        }

        if (capacidadAlbumes > 0) {
            albumes = new Album*[capacidadAlbumes];
            for (int i = 0; i < cantidadAlbumes; ++i) {
                albumes[i] = otro.albumes[i];
            }
        }
    } catch (...) {
        delete[] amigos;
        delete[] mensajesEnviados;
        delete[] mensajesRecibidos;
        delete[] solicitudAmistad;
        delete[] albumes;
        throw;
    }
}

Usuario& Usuario::operator=(const Usuario& otro)
{
    if (this == &otro) {
        return *this;
    }

    Usuario copia(otro);

    std::swap(apodo, copia.apodo);
    std::swap(fechaDeNacimiento, copia.fechaDeNacimiento);
    std::swap(correo, copia.correo);
    std::swap(fotoDePerfil, copia.fotoDePerfil);
    std::swap(pais, copia.pais);
    std::swap(ciudad, copia.ciudad);
    std::swap(fechaDeInscripcion, copia.fechaDeInscripcion);

    std::swap(amigos, copia.amigos);
    std::swap(cantidadAmigos, copia.cantidadAmigos);
    std::swap(capacidadAmigos, copia.capacidadAmigos);

    std::swap(mensajesEnviados, copia.mensajesEnviados);
    std::swap(cantidadMensajesEnviados, copia.cantidadMensajesEnviados);
    std::swap(capacidadMensajesEnviados, copia.capacidadMensajesEnviados);

    std::swap(mensajesRecibidos, copia.mensajesRecibidos);
    std::swap(cantidadMensajesRecibidos, copia.cantidadMensajesRecibidos);
    std::swap(capacidadMensajesRecibidos, copia.capacidadMensajesRecibidos);

    std::swap(solicitudAmistad, copia.solicitudAmistad);
    std::swap(cantidadSolicitudes, copia.cantidadSolicitudes);
    std::swap(capacidadSolicitudes, copia.capacidadSolicitudes);

    std::swap(albumes, copia.albumes);
    std::swap(cantidadAlbumes, copia.cantidadAlbumes);
    std::swap(capacidadAlbumes, copia.capacidadAlbumes);

    return *this;
}
