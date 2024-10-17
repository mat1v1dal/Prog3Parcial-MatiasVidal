#ifndef DATA_CONTROL_H
#define DATA_CONTROL_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../entidades/Partido.h"
#include <stdexcept>
#include <iostream>

class DataControl {
public:
    // Función para obtener los partidos desde un archivo CSV
    std::vector<Partido> obtenerPartidos(const std::string& rutaArchivo) {
        std::ifstream archivo(rutaArchivo);
        std::string linea;
        std::vector<Partido> partidos;

        // Verificar si el archivo se abrió correctamente
        if (!archivo.is_open()) {
            throw std::runtime_error("Error al abrir el archivo: " + rutaArchivo);
        }

        // Omitir la primera línea (encabezados)
        std::getline(archivo, linea);

        // Leer línea por línea el archivo CSV
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string jornada, fechaStr, equipoLocal, equipoVisitante, golesLocalStr, golesVisitanteStr, competicion;

            // Leer los campos de la línea separados por comas
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

                // Convertir la fecha a un objeto de la clase Fecha
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

                // Crear los objetos Equipo para local y visitante
                Equipo equipoLocalObj(equipoLocal);
                Equipo equipoVisitanteObj(equipoVisitante);

                // Crear el objeto Partido
                Partido partido(equipoLocalObj, equipoVisitanteObj, golesLocal, golesVisitante, competicion, fecha);

                // Almacenar el partido en el vector
                partidos.push_back(partido);
            } 
            catch (const std::invalid_argument& e) {
                std::cerr << "Error al convertir goles o fecha en la línea: " << linea << std::endl;
                std::cerr << "Excepción: " << e.what() << std::endl;
            } 
            catch (const std::out_of_range& e) {
                std::cerr << "Error: El número está fuera del rango permitido en la línea: " << linea << std::endl;
                std::cerr << "Excepción: " << e.what() << std::endl;
            }
        }

        archivo.close(); // Cerrar el archivo al terminar
        return partidos; // Retornar el vector de partidos
    }
};

#endif
