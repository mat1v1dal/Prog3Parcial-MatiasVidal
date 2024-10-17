#ifndef SERVICIOPARTIDOTREE_H
#define SERVICIOPARTIDOTREE_H

#include "../entidades/partido.h"
#include "../entidades/equipo.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "../lib/Arbol/ArbolBinarioAVL.h"
#include <iostream>
#include <vector>

class ServicioPartidoTree {
private:
    std::unordered_map<std::string, ArbolBinarioAVL<Partido>> competiciones;
    std::unordered_map<std::string, std::unordered_map<std::string, Equipo>> equipos;

public:
    ServicioPartidoTree() {
    }

    void registrarEquipo(std::string liga, Equipo equipo) {
            try {
                equipos[liga].at(equipo.getNombre());
                equipos[liga].at(equipo.getNombre());
            } catch (const std::out_of_range&) {
                equipos[liga].insert({equipo.getNombre(), equipo});
            }
        }
    void actualizarEstadisticasPorCompeticion(Partido& partido) {
        std::string liga = partido.getLiga();

        // Acceder directamente al equipo local
        Equipo& equipoLocal = equipos[liga][partido.getEquipoLocal()];
        equipoLocal.aumentarGolesAFavor(liga, partido.getGolesLocal());
        equipoLocal.aumentarGolesEnContra(liga, partido.getGolesVisitante());
        equipoLocal.aumentarPartidosJugados(liga);

        // Acceder directamente al equipo visitante
        Equipo& equipoVisitante = equipos[liga][partido.getEquipoVisitante()];
        equipoVisitante.aumentarGolesAFavor(liga, partido.getGolesVisitante());
        equipoVisitante.aumentarGolesEnContra(liga, partido.getGolesLocal());
        equipoVisitante.aumentarPartidosJugados(liga);
    }

    
    void registrarPartidoEnHash(const Partido& partido) {
        std::string key = partido.getLiga();
        try {
            competiciones.at(key).put(partido);  // Aquí no se necesita copiar
        } catch (const std::out_of_range&) {
            ArbolBinarioAVL<Partido> arbolAVL;
            arbolAVL.put(partido);
            competiciones.insert({key, arbolAVL});
        }
    }

    void cargarResultados(Partido& partido) {

        int golesLocal = partido.getGolesLocal();
        int golesVisitante = partido.getGolesVisitante();

        partido.getEquipoLocalObj().aumentarGolesAFavor(golesLocal);
        partido.getEquipoLocalObj().aumentarGolesEnContra(golesVisitante);

        partido.getEquipoVisitanteObj().aumentarGolesAFavor(golesVisitante);
        partido.getEquipoVisitanteObj().aumentarGolesEnContra(golesLocal);
    }
    const std::unordered_map<std::string, std::unordered_map<std::string, Equipo>>& getEquipos() const {
        return equipos;
    }
    Equipo& getEquipo(const std::string& competicion, const std::string& equipoNombre) {
        try {
            return equipos.at(competicion).at(equipoNombre);
        } catch (const std::out_of_range&) {
            throw std::runtime_error("Equipo no encontrado en la competición.");
        }
    }

    ArbolBinarioAVL<Partido> getPartidos(std::string competicion) {
        try {
            return competiciones.at(competicion);
        } catch (const std::out_of_range&) {
            throw std::runtime_error("No se encontraron partidos para la competición.");
        }
    }
};

#endif
