#ifndef SERVICIOPARTIDO_H
#define SERVICIOPARTIDO_H

#include "../entidades/partido.h"
#include "../entidades/equipo.h"
#include <string>
#include <vector>
#include "../lib/HashMap/HashMap.h"
#include "../lib/Cola/ColaPrioridad.h"
#include <iostream>
class ServicioPartido {
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
        HashMap<std::string, ColaPrioridad<Partido>> competiciones;

    public:
        // Constructor
        ServicioPartido(unsigned int tamanioHash) : competiciones(tamanioHash, hashCompeticion) {}

        void registrarPartidoEnHash(Partido partido){
            std::string competicion = partido.getLiga();
            int goles = partido.getGolesLocal() + partido.getGolesVisitante();
            try {
                competiciones.get(competicion).encolarPrioridad(partido, goles);
            } catch (int e) {
                ColaPrioridad<Partido> cola;
                std::cout<< "Cola creada" << std::endl;
                cola.encolarPrioridad(partido, goles);
                competiciones.put(competicion, cola);
                std::cout << "Cola guardada con éxito." << std::endl;
            }
        }


        ColaPrioridad<Partido> getCola(std::string competicion){
            return competiciones.get(competicion);
        };
};

#endif