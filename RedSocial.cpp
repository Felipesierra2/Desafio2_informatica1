#include "Usuario.h"
#include "RedSocial.h"
#include "MedidorRecursos.h"
#include <new>

RedSocial::RedSocial()
    : usuarios(nullptr),
    cantidadUsuarios(0),
    capacidadUsuarios(0),
    mensajes(nullptr),
    cantidadMensajes(0),
    capacidadMensajes(0),
    solicitudes(nullptr),
    cantidadSolicitudes(0),
    capacidadSolicitudes(0)
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
    for (int i = 0; i < cantidadMensajes; ++i)
    {
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensajes[i];
    }

    for (int i = 0; i < cantidadSolicitudes; ++i)
    {
        MedidorRecursos::liberarMemoria(sizeof(Solicitud));
        delete solicitudes[i];
    }

    for (int i = 0; i < cantidadUsuarios; ++i) {
        MedidorRecursos::liberarMemoria(sizeof(Usuario));
        delete usuarios[i];
    }

    MedidorRecursos::liberarMemoria(capacidadUsuarios * sizeof(Usuario*));
    MedidorRecursos::liberarMemoria(capacidadMensajes * sizeof(Mensajes*));
    MedidorRecursos::liberarMemoria(capacidadSolicitudes * sizeof(Solicitud*));

    delete[] usuarios;
    delete[] mensajes;
    delete[] solicitudes;
}

bool RedSocial::agregarMensajeAdministrado(Mensajes* mensaje)
{
    if (mensaje == nullptr)
    {
        return false;
    }

    if (cantidadMensajes == capacidadMensajes)
    {
        int nuevaCapacidad;

        if (capacidadMensajes == 0)
        {
            nuevaCapacidad = 2;
        }
        else
        {
            nuevaCapacidad = capacidadMensajes * 2;
        }

        Mensajes** nuevoArreglo = new Mensajes*[nuevaCapacidad];

        for (int i = 0; i < cantidadMensajes; ++i)
        {
            MedidorRecursos::registrarIteracion();
            nuevoArreglo[i] = mensajes[i];
        }

        MedidorRecursos::registrarMemoria(
            nuevaCapacidad * sizeof(Mensajes*)
            );

        MedidorRecursos::liberarMemoria(
            capacidadMensajes * sizeof(Mensajes*)
            );

        delete[] mensajes;

        mensajes = nuevoArreglo;
        capacidadMensajes = nuevaCapacidad;
    }

    mensajes[cantidadMensajes] = mensaje;
    cantidadMensajes++;

    return true;
}

bool RedSocial::enviarMensaje(
    Usuario* remitente,
    Usuario* destinatario,
    const std::string& contenido,
    const std::string& fecha)
{
    if (remitente == nullptr ||
        destinatario == nullptr ||
        remitente == destinatario)
    {
        return false;
    }

    Mensajes* mensaje = new Mensajes(
        remitente,
        destinatario,
        contenido,
        fecha
        );

    MedidorRecursos::registrarMemoria(sizeof(Mensajes));

    if (!agregarMensajeAdministrado(mensaje))
    {
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensaje;
        return false;
    }

    if (!remitente->registrarMensajeEnviado(mensaje))
    {
        cantidadMensajes--;
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensaje;
        return false;
    }

    if (!destinatario->agregarMensajeRecibido(mensaje))
    {
        cantidadMensajes--;
        remitente->quitarUltimoMensajeEnviado();
        MedidorRecursos::liberarMemoria(sizeof(Mensajes));
        delete mensaje;
        return false;
    }

    return true;
}

bool RedSocial::agregarSolicitudAdministrada(Solicitud* solicitud)
{
    if (solicitud == nullptr)
    {
        return false;
    }

    if (cantidadSolicitudes == capacidadSolicitudes)
    {
        int nuevaCapacidad;

        if (capacidadSolicitudes == 0)
        {
            nuevaCapacidad = 2;
        }
        else
        {
            nuevaCapacidad = capacidadSolicitudes * 2;
        }

        Solicitud** nuevoArreglo = new Solicitud*[nuevaCapacidad];

        for (int i = 0; i < cantidadSolicitudes; ++i)
        {
            MedidorRecursos::registrarIteracion();
            nuevoArreglo[i] = solicitudes[i];
        }

        MedidorRecursos::registrarMemoria(nuevaCapacidad * sizeof(Solicitud*));
        MedidorRecursos::liberarMemoria(capacidadSolicitudes * sizeof(Solicitud*));

        delete[] solicitudes;

        solicitudes = nuevoArreglo;
        capacidadSolicitudes = nuevaCapacidad;
    }

    solicitudes[cantidadSolicitudes] = solicitud;
    cantidadSolicitudes++;

    return true;
}

bool RedSocial::administraSolicitud(
    const Solicitud* solicitud) const
{
    if (solicitud == nullptr)
    {
        return false;
    }

    for (int i = 0; i < cantidadSolicitudes; ++i)
    {
        MedidorRecursos::registrarIteracion();

        if (solicitudes[i] == solicitud)
        {
            return true;
        }
    }

    return false;
}

bool RedSocial::aceptarSolicitud(Solicitud* solicitud)
{
    if (!administraSolicitud(solicitud) ||
        solicitud->getEstado() != 0)
    {
        return false;
    }

    Usuario* remitente = solicitud->getRemitente();
    Usuario* destinatario = solicitud->getDestinatario();

    if (remitente == nullptr ||
        destinatario == nullptr ||
        remitente == destinatario)
    {
        return false;
    }

    bool amistadRemitente = remitente->esAmigo(destinatario);
    bool amistadDestinatario = destinatario->esAmigo(remitente);

    bool agregadoRemitente = false;

    if (!amistadRemitente)
    {
        if (!remitente->agregarAmigo(destinatario))
        {
            return false;
        }

        agregadoRemitente = true;
    }

    if (!amistadDestinatario)
    {
        if (!destinatario->agregarAmigo(remitente))
        {
            if (agregadoRemitente)
            {
                remitente->quitarAmigo(destinatario);
            }

            return false;
        }
    }

    solicitud->aceptar();
    return true;
}

bool RedSocial::rechazarSolicitud(Solicitud* solicitud){
    if (!administraSolicitud(solicitud) ||
        solicitud->getEstado() != 0)
    {
        return false;
    }

    solicitud->rechazar();
    return true;
}

bool RedSocial::enviarSolicitud(
    Usuario* remitente,
    Usuario* destinatario)
{
    if (remitente == nullptr ||
        destinatario == nullptr ||
        remitente == destinatario)
    {
        return false;
    }

    if (remitente->esAmigo(destinatario) ||
        destinatario->esAmigo(remitente))
    {
        return false;
    }

    for (int i = 0; i < cantidadSolicitudes; ++i)
    {
        MedidorRecursos::registrarIteracion();

        Solicitud* actual = solicitudes[i];

        if (actual->getRemitente() == remitente &&
            actual->getDestinatario() == destinatario &&
            actual->getEstado() == 0)
        {
            return false;
        }
    }

    Solicitud* solicitud = new Solicitud(
        remitente,
        destinatario
        );

    MedidorRecursos::registrarMemoria(sizeof(Solicitud));

    if (!agregarSolicitudAdministrada(solicitud))
    {
        MedidorRecursos::liberarMemoria(sizeof(Solicitud));
        delete solicitud;
        return false;
    }

    if (!destinatario->agregarSolicitud(solicitud))
    {
        cantidadSolicitudes--;

        MedidorRecursos::liberarMemoria(sizeof(Solicitud));
        delete solicitud;

        return false;
    }

    return true;
}
