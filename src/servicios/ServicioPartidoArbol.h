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

class ServicioPartidoTree {
    private:
        // Cambiar a función estática o libre para usarla como hash
        static unsigned int hashCompeticion(std::string competicion) {
            unsigned int hash = 0;
            for (char c : competicion) {
                hash += c;
            }
            return hash;  // Asegurarse de que retorne un valor
        }

        // Corregir el tipo de HashMapList
        HashMap<std::string, ArbolBinarioAVL<Partido>> competiciones;
        HashMap<std::string, HashMap<std::string, Equipo>> equipos;
    public:
        // Constructor
        ServicioPartidoTree(unsigned int tamanioHash) : competiciones(tamanioHash, hashCompeticion), equipos(tamanioHash, hashCompeticion){}

        void registrarEquipo(std::string liga, Equipo equipo) {
            // Verificamos si la liga ya existe en el HashMap
            HashMap<std::string, Equipo>* equiposLiga;

            try {
                equiposLiga = &equipos.get(liga);
            } catch(int e) {
                if (e == 404) {
                    // Si no existe la liga, creamos un nuevo HashMap para esa liga
                    HashMap<std::string, Equipo> nuevaLiga(100, hashCompeticion);
                    equipos.put(liga, nuevaLiga);
                    equiposLiga = &equipos.get(liga); // Actualizamos el puntero
                } else {
                    throw; // Re-lanzamos cualquier otro error que no sea 404
                }
            }

            // Ahora tratamos de insertar el equipo en la liga correspondiente
            try {
                equiposLiga->get(equipo.getNombre());
                std::cerr << "El equipo ya existe en la liga." << std::endl;
            } catch(int e) {
                if (e == 404) {
                    equiposLiga->put(equipo.getNombre(), equipo); // Insertamos el equipo
                } else {
                    throw; // Re-lanzamos cualquier otro error que no sea 404
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

        void actualizarEquipos(Partido& partido) {
            std::string equipoLocal = partido.getEquipoLocal();
            std::string equipoVisitante = partido.getEquipoVisitante();
            
            int golesLocal = partido.getGolesLocal();
            int golesVisitante = partido.getGolesVisitante();

            partido.getEquipoLocalObj().aumentarGolesAFavor(golesLocal);
            partido.getEquipoLocalObj().aumentarGolesEnContra(golesVisitante);

            partido.getEquipoVisitanteObj().aumentarGolesAFavor(golesVisitante);
            partido.getEquipoVisitanteObj().aumentarGolesEnContra(golesLocal);
        }

        ArbolBinarioAVL<Partido> getPartidos(std::string competicion){
            return competiciones.get(competicion);
        };
};

#endif