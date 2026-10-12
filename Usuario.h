#ifndef USUARIO_H
#define USUARIO_H

#include "Album.h"
#include "Mensajes.h"
#include "Solicitud.h"
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

    Usuario** amigos;
    int cantidadAmigos;
    int capacidadAmigos;

    Mensajes** mensajesEnviados;
    int cantidadMensajesEnviados;
    int capacidadMensajesEnviados;

    Mensajes** mensajesRecibidos;
    int cantidadMensajesRecibidos;
    int capacidadMensajesRecibidos;

    Solicitud** solicitudAmistad;
    int cantidadSolicitudes;
    int capacidadSolicitudes;

    Album** albumes;
    int cantidadAlbumes;
    int capacidadAlbumes;

public:
    Usuario();
    Usuario(const std::string& apodo,
            const std::string& fechaDeNacimiento,
            const std::string& correo,
            const std::string& fotoDePerfil,
            const std::string& pais,
            const std::string& ciudad,
            const std::string& fechaDeInscripcion);

    bool esAmigo(const Usuario* usuario) const;
    bool agregarAmigo(Usuario* usuario);
    int getCantidadAmigos() const;

    bool agregarMensajeEnviado(Mensajes* mensaje);
    bool agregarMensajeRecibido(Mensajes* mensaje);
    bool enviarMensaje(Usuario* destinatario,const std::string& contenido,const std::string& fecha);
    Mensajes* getMensajeRecibido(int indice) const;
    bool marcarMensajeComoLeido(int indice);
    int getCantidadMensajesEnviados() const;
    int getCantidadMensajesRecibidos() const;

    //getters
    const std::string& getApodo() const;
    const std::string& getFechaDeNacimiento() const;
    const std::string& getCorreo() const;
    const std::string& getFotoDePerfil() const;
    const std::string& getPais() const;
    const std::string& getCiudad() const;
    const std::string& getFechaDeInscripcion() const;

    //Setters
    void setApodo(const std::string& apodo);
    void setFechaDeNacimiento(const std::string& fechaDeNacimiento);
    void setCorreo(const std::string& correo);
    void setFotoDePerfil(const std::string& fotoDePerfil);
    void setPais(const std::string& pais);
    void setCiudad(const std::string& ciudad);
    void setFechaDeInscripcion(const std::string& fechaDeInscripcion);

    ~Usuario();
    Usuario(const Usuario& otro);
    Usuario& operator=(const Usuario& otro);
};


#endif // USUARIO_H
