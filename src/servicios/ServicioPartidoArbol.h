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
            try{
                equipos.get(liga).put(equipo.getNombre(), equipo);
            } catch(int e){
                if(e == 404){
                    HashMap<std::string, Equipo> equiposLiga(10, hashCompeticion);
                    equipos.put(liga, equiposLiga);
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

        void actualizarEquipos(const Partido& partido) {
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