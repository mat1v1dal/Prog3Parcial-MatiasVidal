class Fecha{
    private:
        int dia;
        int mes;
        int anio;
    public:
        Fecha(int dia, int mes, int anio);
        int getDia() const { 
            return dia;
        };
        int getMes() const { 
            return mes;
        };
        int getAnio() const{
            return anio;
        };
        void setDia(int dia){
            this->dia = dia;
        };
        void setMes(int mes){
            this->mes = mes;
        };
        void setAnio(int anio){
            this->anio = anio;
        };

        bool operator==(const Fecha& fecha) const{
            return dia == fecha.dia && mes == fecha.mes && anio == fecha.anio;
        };

};