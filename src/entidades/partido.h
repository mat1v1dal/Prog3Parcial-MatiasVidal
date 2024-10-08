#include <string>
#include "equipo.h"
class Partido{
    public:
        Partido(Equipo equipoLocal, Equipo equipoVisitante, int golesLocal, int golesVisitante, const std::string& liga) 
            : equipoLocal(equipoLocal), equipoVisitante(equipoVisitante), 
            golesLocal(golesLocal), golesVisitante(golesVisitante), liga(liga) {}
        std::string getEquipoLocal() const {
            return equipoLocal.getNombre();
        };
        std::string getEquipoVisitante() const { 
            return equipoVisitante.getNombre();
        };
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
        };
    private:
        std::string liga;
        Equipo equipoLocal;
        Equipo equipoVisitante;
        int golesLocal;
        int golesVisitante;

};  