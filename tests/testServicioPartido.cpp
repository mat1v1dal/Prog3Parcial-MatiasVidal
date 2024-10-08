#include <iostream>
#include "../src/servicios/ServicioPartido.h" 
#include "../src/entidades/equipo.h"

int main() {
    // Crear instancia del servicio
    ServicioPartido servicioPartido(10); // Tamaño del hash

    // Crear equipos
    Equipo equipoLocal("Equipo A");
    Equipo equipoVisitante("Equipo B");
    Equipo equipoLocal2("Equipo C");
    Equipo equipoVisitante2("Equipo D");

    // Crear partidos
    Partido partido1(equipoLocal, equipoVisitante, 2, 1, "Liga 1");
    Partido partido2(equipoLocal2, equipoVisitante2, 1, 3, "Liga 1");

    // Registrar partidos
    servicioPartido.registrarPartidoEnHash(partido1);
    servicioPartido.registrarPartidoEnHash(partido2);

    // Mostrar resultados de la competición "Liga 1"
    std::cout << "Resultados en Liga 1:" << std::endl;

    // Supongamos que tienes un método para obtener la cola de resultados
    ColaPrioridad<Partido> colaCompeticion = servicioPartido.getCola("Liga 1");

    while (!colaCompeticion.esVacia()) {
        std::cout << colaCompeticion.desencolar().getGolesTotales() << std::endl; // Muestra cada resultado
    }

    return 0;
}
