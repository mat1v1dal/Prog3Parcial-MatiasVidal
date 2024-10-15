#ifndef DATA_CONTROL
#define DATA_CONTROL

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../entidades/partido.h"
#include <stdexcept>
#include <iostream>
class DataControl{
    public:
        std::vector<Partido> obtenerPartidos(std::string rutaArchivo){
            std::ifstream archivo(rutaArchivo);
            std::string linea;
            std::vector <Partido> partidos;
            if (!archivo.is_open()) {
                throw std::runtime_error("Error al abrir el archivo: " + rutaArchivo);
            }

            std::getline(archivo, linea);

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

        }

};

#endif