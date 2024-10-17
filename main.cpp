#include <iostream>
#include <string>
#include <chrono>
#include "./src/servicios/ServicioPartido.h"
#include "./src/dbcontroll/DataControl.h"
#include "./src/entidades/partido.h"
#include "./src/entidades/equipo.h"
#include "./src/entidades/fecha.h"

void mostrarMenu() {
    std::cout << "=== MENU ===\n";
    std::cout << "1. Mostrar los 5 partidos con mayor cantidad de goles\n";
    std::cout << "2. Mostrar goles totales a favor y en contra de un equipo por competición\n";
    std::cout << "3. Mostrar promedio de goles a favor y en contra de un equipo por competición\n";
    std::cout << "4. Cargar partidos desde un archivo CSV\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opción: ";
}

void mostrarTop5Partidos(ServicioPartidoTree& servicio) {
    std::string competicion;
    std::cout << "Ingrese la competición: ";
    std::cin.ignore();  // Para limpiar el buffer de entrada
    std::getline(std::cin, competicion);  // Leer toda la línea, incluyendo espacios

    auto start = std::chrono::high_resolution_clock::now();
    
    try {
        ArbolBinarioAVL<Partido> partidos = servicio.getPartidos(competicion);
        std::vector<Partido> partidosLista = partidos.inorder();  // Obtener los partidos en orden
        std::cout << "partidos obtenidos" << std::endl;

        std::cout << "Top 5 partidos con mayor cantidad de goles:\n";
        for (size_t i = 0; i < std::min(partidosLista.size(), size_t(5)); ++i) {
            std::cout << "Partido " << i + 1 << ": " << partidosLista[i].getEquipoLocal()
                      << " vs " << partidosLista[i].getEquipoVisitante()
                      << " - Goles: " << partidosLista[i].getGolesTotales()
                      << " - Fecha: " << partidosLista[i].getFecha().toString() << "\n";
        }
    } catch (...) {
        std::cout << "Error: No se pudo recuperar la competición.\n";
    }

    auto end = std::chrono::high_resolution_clock::now();  // Fin del cronómetro
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo transcurrido: " << duration.count() << " segundos\n";
}

void mostrarGolesTotalesPorEquipo(ServicioPartidoTree& servicio) {
      // Inicio del cronómetro

    std::string equipoNombre;
    std::cout << "Ingrese el nombre del equipo: ";
    std::cin.ignore();  // Para limpiar el buffer de entrada
    std::getline(std::cin, equipoNombre);  // Leer toda la línea
    auto start = std::chrono::high_resolution_clock::now();
    try {
        // Buscar el equipo en todas las competiciones
        bool equipoEncontrado = false;
        for (const auto& [competicion, equiposEnCompeticion] : servicio.getEquipos()) {
            auto it = equiposEnCompeticion.find(equipoNombre);
            if (it != equiposEnCompeticion.end()) {
                equipoEncontrado = true;
                const Equipo& equipo = it->second;
                Estadisticas stats = equipo.getEstadisticas(competicion);
                std::cout << "Competición: " << competicion << "\n";
                std::cout << "Equipo: " << equipo.getNombre() << "\n";
                std::cout << "Goles a favor: " << stats.golesAFavor << "\n";
                std::cout << "Goles en contra: " << stats.golesEnContra << "\n";
                std::cout << "Partidos jugados: " << stats.partidosJugados << "\n\n";
            }
        }
        if (!equipoEncontrado) {
            std::cout << "El equipo no fue encontrado en ninguna competición.\n";
        }
    } catch (...) {
        std::cout << "Error: No se pudo recuperar el equipo.\n";
    }

    auto end = std::chrono::high_resolution_clock::now();  // Fin del cronómetro
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo transcurrido: " << duration.count() << " segundos\n";
}

void mostrarPromedioGolesPorEquipo(ServicioPartidoTree& servicio) {
    auto start = std::chrono::high_resolution_clock::now();  // Inicio del cronómetro

    std::string equipoNombre;
    std::cout << "Ingrese el nombre del equipo: ";
    std::cin.ignore();  // Para limpiar el buffer de entrada
    std::getline(std::cin, equipoNombre);  // Leer toda la línea

    try {
        // Buscar el equipo en todas las competiciones
        bool equipoEncontrado = false;
        for (const auto& [competicion, equiposEnCompeticion] : servicio.getEquipos()) {
            auto it = equiposEnCompeticion.find(equipoNombre);
            if (it != equiposEnCompeticion.end()) {
                equipoEncontrado = true;
                const Equipo& equipo = it->second;
                Estadisticas stats = equipo.getEstadisticas(competicion);
                float promedioFavor = stats.partidosJugados > 0 ? static_cast<float>(stats.golesAFavor) / stats.partidosJugados : 0;
                float promedioContra = stats.partidosJugados > 0 ? static_cast<float>(stats.golesEnContra) / stats.partidosJugados : 0;
                std::cout << "Competición: " << competicion << "\n";
                std::cout << "Equipo: " << equipo.getNombre() << "\n";
                std::cout << "Promedio de goles a favor: " << promedioFavor << "\n";
                std::cout << "Promedio de goles en contra: " << promedioContra << "\n\n";
            }
        }
        if (!equipoEncontrado) {
            std::cout << "El equipo no fue encontrado en ninguna competición.\n";
        }
    } catch (...) {
        std::cout << "Error: No se pudo recuperar el equipo.\n";
    }

    auto end = std::chrono::high_resolution_clock::now();  // Fin del cronómetro
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo transcurrido: " << duration.count() << " segundos\n";
}

void cargarPartidosDesdeCSV(ServicioPartidoTree& servicio, const std::string& rutaArchivo) {
    auto start = std::chrono::high_resolution_clock::now();  // Inicio del cronómetro

    DataControl dataControl;
    try {
        std::vector<Partido> partidos = dataControl.obtenerPartidos(rutaArchivo);

        for (auto& partido : partidos) {
            // Registrar equipos
            servicio.registrarEquipo(partido.getLiga(), partido.getEquipoLocalObj());
            servicio.registrarEquipo(partido.getLiga(), partido.getEquipoVisitanteObj());
            // Registrar partidos
            servicio.registrarPartidoEnHash(partido);
            // Actualizar estadísticas por competición
            servicio.actualizarEstadisticasPorCompeticion(partido);
        }

        std::cout << "Se cargaron " << partidos.size() << " partidos correctamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar los partidos: " << e.what() << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();  // Fin del cronómetro
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo transcurrido: " << duration.count() << " segundos\n";
}

int main() {
    ServicioPartidoTree servicio;

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarTop5Partidos(servicio);
                break;
            case 2:
                mostrarGolesTotalesPorEquipo(servicio);
                break;
            case 3:
                mostrarPromedioGolesPorEquipo(servicio);
                break;
            case 4: {
                cargarPartidosDesdeCSV(servicio, "./data/datos.csv");
                break;
            }
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    }

    return 0;
}
