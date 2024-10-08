#ifndef EQUIPO_H
#define EQUIPO_H
#include <string>

class Equipo{
    private:
        std::string nombre;
        int partidosJugados;
        int empates;
        int victorias;
        int derrotas;

    public:
        Equipo(const std::string& nombre) : nombre(nombre), victorias(0), derrotas(0), empates(0), partidosJugados(0) {}
        Equipo(const std::string& nombre, int partidosJugados, int empates, int victorias, int derrotas) 
            : nombre(nombre), 
            partidosJugados(partidosJugados), 
            empates(empates), 
            victorias(victorias), 
            derrotas(derrotas) {}
            std::string getNombre() const;
            int getVictorias() const;
            int getDerrotas() const;

        // Métodos para cálculos adicionales
        float obtenerPromedioGolesAFavor() const;
        float obtenerPromedioGolesEnContra() const;
};

#endif