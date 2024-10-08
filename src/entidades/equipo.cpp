#include "equipo.h"

Equipo::Equipo(const std::string& nombre) : nombre(nombre), victorias(0), derrotas(0), empates(0), partidosJugados(0) {}
Equipo::Equipo(const std::string& nombre, int partidosJugados, int empates, int victorias, int derrotas) 
        : nombre(nombre), 
        partidosJugados(partidosJugados), 
        empates(empates), 
        victorias(victorias), 
        derrotas(derrotas) {}

        
std::string Equipo::getNombre() const {
    return nombre;
}

int Equipo::getVictorias() const {
    return victorias;
}

int Equipo::getDerrotas() const {
    return derrotas;
}


