#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include "equipo.h"
#include "fecha.h"
class Partido{
    public:
        Partido() : equipoLocal(Equipo("N/A")), equipoVisitante(Equipo("N/A")), golesLocal(0), golesVisitante(0), liga("N/A"), fecha(0,0,0)  {}
        Partido(Equipo equipoLocal, Equipo equipoVisitante, int golesLocal, int golesVisitante, const std::string& liga, Fecha fechaPartido)
            :
            equipoLocal(equipoLocal),
            equipoVisitante(equipoVisitante),
            golesLocal(golesLocal),
            golesVisitante(golesVisitante),
            liga(liga),
            fecha(fechaPartido) {}

        Equipo& getEquipoLocalObj() {
            return equipoLocal;
        };
        Equipo& getEquipoVisitanteObj() {
            return equipoVisitante;
        };

        std::string getEquipoLocal() const {
            return equipoLocal.getNombre();
        };
        std::string getEquipoVisitante() const {
            return equipoVisitante.getNombre();
        };
        Fecha getFecha() const {
            return fecha;
        }
        int getGolesLocal() const{
            return golesLocal;
        };
        int getGolesVisitante() const{
            return golesVisitante;
        };
        int getGolesTotales() const{
            return golesLocal + golesVisitante;
        };
        std::string getLiga() const{
            return liga;
        };
        std::string obtenerResultado() const{
            if(golesLocal > golesVisitante){
                return "Local";
            }else if(golesLocal < golesVisitante){
                return "Visitante";
            }else{
                return "Empate";
            }
        }

    bool operator<(const Partido& partido) const {
        if (golesLocal + golesVisitante == partido.getGolesTotales()) {
            if (fecha == partido.getFecha()) {
                if (equipoLocal.getNombre() == partido.getEquipoLocal()) {
                    return equipoVisitante.getNombre() < partido.getEquipoVisitante(); // Compara el equipo visitante si todo lo demás es igual
                }
                return equipoLocal.getNombre() < partido.getEquipoLocal(); // Compara el equipo local si las fechas son iguales
            }
            return fecha < partido.getFecha();
        }
        return golesLocal + golesVisitante < partido.getGolesTotales();
    }

    // Sobrecarga de operador >
    bool operator>(const Partido& partido) const {
        if (golesLocal + golesVisitante == partido.getGolesTotales()) {
            if (fecha == partido.getFecha()) {
                if (equipoLocal.getNombre() == partido.getEquipoLocal()) {
                    return equipoVisitante.getNombre() > partido.getEquipoVisitante(); // Compara el equipo visitante si todo lo demás es igual
                }
                return equipoLocal.getNombre() > partido.getEquipoLocal(); // Compara el equipo local si las fechas son iguales
            }
            return fecha > partido.getFecha();
        }
        return golesLocal + golesVisitante > partido.getGolesTotales();
    }

    // Sobrecarga de operador ==
    bool operator==(const Partido& partido) const {
        return golesLocal + golesVisitante == partido.getGolesTotales() 
            && fecha == partido.getFecha() 
            && equipoLocal.getNombre() == partido.getEquipoLocal() 
            && equipoVisitante.getNombre() == partido.getEquipoVisitante();
    }


    private:
        std::string liga;
        Equipo equipoLocal;
        Equipo equipoVisitante;
        int golesLocal;
        int golesVisitante;
        Fecha fecha;
};

#endif