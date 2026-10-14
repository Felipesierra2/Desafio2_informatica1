#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

class MedidorRecursos
{
private:
    static unsigned long long iteraciones;
    static unsigned long long memoriaRegistrada;

public:
    static void iniciarMedicion();
    static void registrarIteracion();
    static void registrarMemoria(unsigned long long bytes);
    static void liberarMemoria(unsigned long long bytes);
    static unsigned long long getIteraciones();
    static unsigned long long getMemoriaRegistrada();
    static void mostrarReporte();
};

#endif // MEDIDORRECURSOS_H
