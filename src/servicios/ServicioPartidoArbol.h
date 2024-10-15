#ifndef SERVICIOPARTIDOTREE_H
#define SERVICIOPARTIDOTREE_H

#include "../entidades/partido.h"
#include "../entidades/equipo.h"
#include <string>
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

    public:
        // Constructor
        ServicioPartidoTree(unsigned int tamanioHash) : competiciones(tamanioHash, hashCompeticion) {}

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

        ArbolBinarioAVL<Partido> getPartidos(std::string competicion){
            return competiciones.get(competicion);
        };
};

#endif