#include "ServicioPartido.h"
#include <stdexcept>

Partido ServicioPartido::registrarPartido(Equipo equipoLocal, Equipo equipoVisitante, int golesLocal, int golesVisitante) {
    try
    {
        Equipo equipoLocal(equipoLocal);
        Equipo equipoVisitante(equipoVisitante);
        Partido partido(equipoLocal, equipoVisitante, golesLocal, golesVisitante, "Liga");
        return partido;
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("Error al registrar el partido");
    }
    
}


