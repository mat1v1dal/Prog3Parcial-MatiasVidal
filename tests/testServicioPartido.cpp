#include "../src/servicios/ServicioPartidoArbol.h"  // Incluye tu servicio para manejar partidos
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

// Función para leer el archivo CSV y registrar los partidos en el servicio
void leerCSVYRegistrarPartidos(const std::string& nombreArchivo, ServicioPartidoTree& servicio) {
    std::ifstream archivo(nombreArchivo); // Abrir el archivo CSV
    std::string linea;

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
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

            // Registrar el partido en el servicio
            servicio.registrarPartidoEnHash(partido);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error al convertir goles o fecha en la línea: " << linea << std::endl;
            std::cerr << "Excepción: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: El número está fuera del rango permitido en la línea: " << linea << std::endl;
            std::cerr << "Excepción: " << e.what() << std::endl;
        }
    }

    archivo.close(); // Cerrar el archivo al terminar
}


int main() {
    try {
        // Crear un servicio para manejar partidos con un tamaño de hash adecuado
        ServicioPartidoTree servicio(100);  // Ajusta el tamaño si necesitas manejar más datos

        // Medir el tiempo para registrar partidos desde el archivo CSV
        auto startCSV = std::chrono::high_resolution_clock::now();

        // Leer el archivo CSV y registrar los partidos
        leerCSVYRegistrarPartidos("../data/datos.csv", servicio);

        auto endCSV = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> tiempoCSV = endCSV - startCSV;
        std::cout << "Tiempo de registro de partidos desde CSV: " << tiempoCSV.count() << " segundos" << std::endl;


    } catch (int e) {
        std::cerr << "Excepción capturada: " << e << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Excepción estándar capturada: " << e.what() << std::endl;
    }

    return 0;
}
