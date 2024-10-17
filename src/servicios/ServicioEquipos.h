#ifndef SERVICIO_EQUIPOS
#define SERVICIO_EQUIPOS
#include "../lib/Grafos/Grafo.h"
#include "../entidades/equipo.h"
#include <stdexcept>
class ServicioEquipo{
    private:
        Grafo<Equipo> grafo;
    public:
        void agregarEquipo(const Equipo& equipo){
            grafo.agregarNodo(equipo);
        }

        void agregarRelacion(const Equipo& equipo1, const Equipo& equipo2){
            if (!grafo.buscarNodo(equipo1)) {
                throw std::invalid_argument("El equipo 1 no existe en el grafo.");
            }
            if (!grafo.buscarNodo(equipo2)) {
                throw std::invalid_argument("El equipo 2 no existe en el grafo.");
            }
            grafo.agregarArista(equipo1, equipo2);
        }
};

#endif