#ifndef SERVICIOPARTIDOTREE_H
#define SERVICIOPARTIDOTREE_H

#include "../entidades/partido.h"
#include "../entidades/equipo.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "../lib/HashMap/HashMap.h"
#include "../lib/Arbol/ArbolBinarioAVL.h"
#include <iostream>
#include <vector>

unsigned int hashCompeticion(std::string competicion) {
    unsigned int hash = 0;
    for (char c : competicion) {
        hash += c;
    }
    return hash;
}

class ServicioPartidoTree {
    private:
        // Cambiar a función estática o libre para usarla como hash

        // Corregir el tipo de HashMapList
        HashMap<std::string, ArbolBinarioAVL<Partido>> competiciones;
        HashMap<std::string, HashMap<std::string, Equipo>> equipos;
    public:
        // Constructor
        ServicioPartidoTree(unsigned int tamanioHash) : competiciones(tamanioHash, hashCompeticion), equipos(tamanioHash, hashCompeticion){}

        void registrarEquipo(std::string liga, Equipo equipo) {
            try{
                equipos.get(liga).put(equipo.getNombre(), equipo);
            } catch(int e){
                if(e == 404){
                    HashMap<std::string, Equipo> equiposLiga(100, hashCompeticion);
                    equiposLiga.put(equipo.getNombre(), equipo);
                    equipos.put(liga, equiposLiga);
                }
                if(e == 410){
                    equipos.get(liga).get(equipo.getNombre()).aumentarGolesAFavor(equipo.getGolesAFavor());
                    equipos.get(liga).get(equipo.getNombre()).aumentarGolesEnContra(equipo.getGolesEnContra());
                }
            }
        }



        void registrarPartidoEnHash(Partido partido){

            std::string key = partido.getLiga();
            try
            {
                competiciones.get(key).put(partido);
            }
            catch(int e)
            {
                if(e == 404){
                    ArbolBinarioAVL<Partido> arbolAVL;
                    arbolAVL.put(partido);
                    competiciones.put(key, arbolAVL);
                }
             }
        }

        void cargarResultados(Partido& partido) {
            int golesLocal = partido.getGolesLocal();
            int golesVisitante = partido.getGolesVisitante();

            // Modificar los equipos directamente, ya que estamos trabajando con referencias
            partido.getEquipoLocalObj().aumentarGolesAFavor(golesLocal);
            partido.getEquipoLocalObj().aumentarGolesEnContra(golesVisitante);

            partido.getEquipoVisitanteObj().aumentarGolesAFavor(golesVisitante);
            partido.getEquipoVisitanteObj().aumentarGolesEnContra(golesLocal);
        }

        Equipo getEquipo(const std::string& competicion, const std::string& equipoNombre){
            try {
                return equipos.get(competicion).get(equipoNombre);  // Devuelve una copia
            } catch (int e) {
                if (e == 404) {
                    throw std::runtime_error("Equipo no encontrado en la competición.");
                } else {
                    throw std::runtime_error("Error al intentar obtener el equipo.");
                }
            }
        }

        ArbolBinarioAVL<Partido> getPartidos(std::string competicion){
            return competiciones.get(competicion);
        };
};

#endif