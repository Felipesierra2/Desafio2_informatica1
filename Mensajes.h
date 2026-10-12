#ifndef MENSAJES_H
#define MENSAJES_H

#include <string>
class Usuario;

class Mensajes
{
private:
    Usuario* remitente;
    Usuario* destinatario;
    std::string contenido;
    std::string fecha;
    bool leido;

public:
    Mensajes(Usuario* remitente,
             Usuario* destinatario,
             const std::string& contenido,
             const std::string& fecha);

    Usuario* getRemitente() const;
    Usuario* getDestinatario() const;
    const std::string& getContenido() const;
    const std::string& getFecha() const;
    bool getLeido() const;

    void marcarComoLeido();
};

#endif // MENSAJES_H
