#include "Usuario.h"
#include "MedidorRecursos.h"

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

/*Itera sobre los amigos revisando si ya un usuario lo contiene*/
bool Usuario::esAmigo(const Usuario* usuario) const
{
    for (int i = 0; i < cantidadAmigos; ++i) {
        MedidorRecursos::registrarIteracion();
        if (amigos[i] == usuario) {
            return true;
        }
    }
    return false;
}

/*Metodo que recibe un usuario y valida si ya es amigo de otro usuario
 * si no son amigos retorna true
 */

bool Usuario::agregarAmigo(Usuario* usuario){
    if (usuario == nullptr || usuario == this || esAmigo(usuario)) {
        return false;
    }

    if (cantidadAmigos == capacidadAmigos) {
        int nuevaCapacidad = (capacidadAmigos == 0) ? 4 : capacidadAmigos * 2;

        Usuario** nuevo = new Usuario*[nuevaCapacidad];
        MedidorRecursos::registrarMemoria(nuevaCapacidad * sizeof(Usuario*));

        for (int i = 0; i < cantidadAmigos; ++i) {
            MedidorRecursos::registrarIteracion();
            nuevo[i] = amigos[i];
        }

        MedidorRecursos::liberarMemoria(capacidadAmigos * sizeof(Usuario*));

        delete[] amigos;
        amigos = nuevo;
        capacidadAmigos = nuevaCapacidad;
    }

    amigos[cantidadAmigos] = usuario;
    ++cantidadAmigos;
    return true;
}

/*Metodo con el que accedemos
 */
int Usuario::getCantidadAmigos() const
{
    return cantidadAmigos;
}

bool Usuario::agregarMensajeEnviado(Mensajes* mensaje){
    if (mensaje == nullptr)
    {
        return false;
    }

    if (cantidadMensajesEnviados == capacidadMensajesEnviados){
        int nuevaCapacidad = (capacidadMensajesEnviados == 0)
        ? 2
        : capacidadMensajesEnviados * 2;

        Mensajes** nuevosMensajes = new Mensajes*[nuevaCapacidad];

        MedidorRecursos::registrarMemoria(nuevaCapacidad * sizeof(Mensajes*));

        for (int i = 0; i < cantidadMensajesEnviados; i++)
        {
            MedidorRecursos::registrarIteracion();
            nuevosMensajes[i] = mensajesEnviados[i];
        }

        MedidorRecursos::liberarMemoria(capacidadMensajesEnviados * sizeof(Mensajes*));

        delete[] mensajesEnviados;

        mensajesEnviados = nuevosMensajes;
        capacidadMensajesEnviados = nuevaCapacidad;
    }

    mensajesEnviados[cantidadMensajesEnviados] = mensaje;
    cantidadMensajesEnviados++;

    return true;
}

bool Usuario::agregarMensajeRecibido(Mensajes* mensaje)
{
    if (mensaje == nullptr)
    {
        return false;
    }

    if (cantidadMensajesRecibidos == capacidadMensajesRecibidos)
    {
        int nuevaCapacidad = (capacidadMensajesRecibidos == 0)
        ? 2
        : capacidadMensajesRecibidos * 2;

        Mensajes** nuevosMensajes = new Mensajes*[nuevaCapacidad];

        MedidorRecursos::registrarMemoria(nuevaCapacidad * sizeof(Mensajes*));

        for (int i = 0; i < cantidadMensajesRecibidos; i++)
        {
            MedidorRecursos::registrarIteracion();
            nuevosMensajes[i] = mensajesRecibidos[i];
        }

        MedidorRecursos::liberarMemoria(capacidadMensajesRecibidos * sizeof(Mensajes*));

        delete[] mensajesRecibidos;

        mensajesRecibidos = nuevosMensajes;
        capacidadMensajesRecibidos = nuevaCapacidad;
    }

    mensajesRecibidos[cantidadMensajesRecibidos] = mensaje;
    cantidadMensajesRecibidos++;

    return true;
}

bool Usuario::enviarMensaje(Usuario* destinatario,const std::string& contenido,const std::string& fecha){
    MedidorRecursos::iniciarMedicion();

    if (destinatario == nullptr || destinatario == this)
    {
        MedidorRecursos::mostrarReporte();
        return false;
    }

    Mensajes* mensaje = new Mensajes(
        this,
        destinatario,
        contenido,
        fecha
        );
    MedidorRecursos::registrarMemoria(sizeof(Mensajes));

    if (!agregarMensajeEnviado(mensaje))
    {
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensaje;
        MedidorRecursos::mostrarReporte();
        return false;
    }

    if (!destinatario->agregarMensajeRecibido(mensaje))
    {
        cantidadMensajesEnviados--;
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensaje;
        MedidorRecursos::mostrarReporte();
        return false;
    }

    MedidorRecursos::mostrarReporte();
    return true;
}

Mensajes* Usuario::getMensajeRecibido(int indice) const
{
    if (indice < 0 || indice >= cantidadMensajesRecibidos)
    {
        return nullptr;
    }

    return mensajesRecibidos[indice];
}

bool Usuario::marcarMensajeComoLeido(int indice){
    Mensajes* mensaje = getMensajeRecibido(indice);

    if (mensaje == nullptr)
    {
        return false;
    }

    mensaje->marcarComoLeido();
    return true;
}

int Usuario::getCantidadMensajesEnviados() const
{
    return cantidadMensajesEnviados;
}

int Usuario::getCantidadMensajesRecibidos() const
{
    return cantidadMensajesRecibidos;
}


bool Usuario::agregarAlbum(Album* album)
{
    if (album == nullptr)
    {
        return false;
    }

    if (cantidadAlbumes == capacidadAlbumes)
    {
        int nuevaCapacidad = (capacidadAlbumes == 0)
        ? 2
        : capacidadAlbumes * 2;

        Album** nuevosAlbumes = new Album*[nuevaCapacidad];
        MedidorRecursos::registrarMemoria(nuevaCapacidad * sizeof(Album*));

        for (int i = 0; i < cantidadAlbumes; i++)
        {
            nuevosAlbumes[i] = albumes[i];
        }

        MedidorRecursos::liberarMemoria(capacidadAlbumes * sizeof(Album*));

        delete[] albumes;

        albumes = nuevosAlbumes;
        capacidadAlbumes = nuevaCapacidad;
    }

    albumes[cantidadAlbumes] = album;
    cantidadAlbumes++;

    return true;
}

Album* Usuario::getAlbum(int indice) const
{
    if (indice < 0 || indice >= cantidadAlbumes)
    {
        return nullptr;
    }

    return albumes[indice];
}

int Usuario::getCantidadAlbumes() const
{
    return cantidadAlbumes;
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
    MedidorRecursos::liberarMemoria(capacidadAmigos * sizeof(Usuario*));
    delete[] amigos;

    MedidorRecursos::liberarMemoria(capacidadMensajesEnviados * sizeof(Mensajes*));
    delete[] mensajesEnviados;

    MedidorRecursos::liberarMemoria(capacidadMensajesRecibidos * sizeof(Mensajes*));
    delete[] mensajesRecibidos;

    delete[] solicitudAmistad;

    for (int i = 0; i < cantidadAlbumes; i++){
        delete albumes[i];
    }
    MedidorRecursos::liberarMemoria(capacidadAlbumes * sizeof(Album*));

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

