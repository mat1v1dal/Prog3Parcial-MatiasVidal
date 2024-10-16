#include "../src/servicios/ServicioPartidoArbol.h"  // Incluye tu servicio para manejar partidos
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>  // Para std::invalid_argument

// Función para leer el archivo CSV y almacenar los partidos en un vector
std::vector<Partido> leerCSV(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Abrir el archivo CSV
    std::string linea;
    std::vector<Partido> partidos;  // Vector para almacenar partidos

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + nombreArchivo);
    }

    // Omitir la primera línea (encabezados)
    std::getline(archivo, linea);

    // Leer línea por línea el archivo CSV
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string jornada, fechaStr, equipoLocal, equipoVisitante, golesLocalStr, golesVisitanteStr, competicion;

        // Leer los campos de la línea separada por comas
        std::getline(ss, jornada, ',');
        std::getline(ss, fechaStr, ',');
        std::getline(ss, equipoLocal, ',');
        std::getline(ss, golesLocalStr, ',');
        std::getline(ss, golesVisitanteStr, ',');
        std::getline(ss, equipoVisitante, ',');
        std::getline(ss, competicion, ',');

        // Validar y convertir goles a enteros
        try {
            int golesLocal = std::stoi(golesLocalStr);
            int golesVisitante = std::stoi(golesVisitanteStr);

            // Convertir fecha a una clase Fecha
            std::stringstream fechaStream(fechaStr);
            std::string diaStr, mesStr, anioStr;

            std::getline(fechaStream, diaStr, '/');
            std::getline(fechaStream, mesStr, '/');
            std::getline(fechaStream, anioStr);

            // Convertir los valores de fecha a enteros
            int dia = std::stoi(diaStr);
            int mes = std::stoi(mesStr);
            int anio = std::stoi(anioStr);
            Fecha fecha(dia, mes, anio);

            // Crear los equipos
            Equipo equipoLocalObj(equipoLocal);
            Equipo equipoVisitanteObj(equipoVisitante);

            // Crear el partido
            Partido partido(equipoLocalObj, equipoVisitanteObj, golesLocal, golesVisitante, competicion, fecha);

            // Almacenar el partido en el vector
            partidos.push_back(partido);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error al convertir goles o fecha en la línea: " << linea << std::endl;
            std::cerr << "Excepción: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: El número está fuera del rango permitido en la línea: " << linea << std::endl;
            std::cerr << "Excepción: " << e.what() << std::endl;
        }
    }

    archivo.close(); // Cerrar el archivo al terminar
    return partidos; // Retornar el vector de partidos
}

// Función para registrar los partidos en el servicio a partir del vector
void registrarPartidosEnServicio(const std::vector<Partido>& partidos, ServicioPartidoTree& servicio) {
    for (const auto& partido : partidos) {
        servicio.registrarPartidoEnHash(partido);
    }
}

int main() {
    std::vector<Partido> partidos = leerCSV("../data/datos.csv");

    clock_t begin;

    std::cout << "Comenzando a medir Tiempo\n" << std::endl;

    begin = clock();
    try {
        // Crear un servicio para manejar partidos con un tamaño de hash adecuado
        ServicioPartidoTree servicio(10);

        // Leer el archivo CSV y almacenar los partidos en un vector
        // Registrar los partidos en el servicio
        registrarPartidosEnServicio(partidos, servicio);
        std::vector<Partido> partidosLaLiga = servicio.getPartidos("Premier League").inorder();
        
    } catch (const std::exception& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
    }


    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Tiempo transcurrido: " << elapsed_secs << " segundos\n" << std::endl;
    return 0;
}
