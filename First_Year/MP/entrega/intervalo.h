#ifndef _INTERVALO_H
#define _INTERVALO_H


class Intervalo{
private:
    bool cerradoInf;
    bool cerradoSup;
    double cotaInf;
    double cotaSup;
    
    /**
     * @brief comprueba que los argumentos definen un intervalo correcto
     * cotaInferior <= cotaSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @return @retval true si correcto
     */
    bool valido(double cotaInferior,double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);

public:
    /** 
     *  @brief Intervalo vacio por defectoSup
     *  valorInf = valorSup & abiertoInf + abierto
     */
    Intervalo();
    /** 
     * @brief Crea un Intervalo  cerrado por defecto
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior);
    /** 
     * @brief Crea Intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    double getCotaInf()const;
	
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double getCotaSup()const;
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaInf()const;
	
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaSup()const;
    /** 
     * @brief Define los valores del intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    void setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior);
    /** 
     * @brief Consulta si el intervalo almacenado es vac????o o no. 
     * @return @retval true si es un intervalo vac????o, @retval false en otro caso 
     */
    bool esVacio()const;
    /** 
     * @brief Consulta si un determinado valor est???? dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool estaDentro(double n)const;
};

/******************************/

/** 
* @brief Imprime los valores de un intervalo de forma visual seg????n lo indicado en el gui????n
* @param  El intervalo
*/
void escribir(const Intervalo &i);

/** 
* @brief Lee los valores del intervalo seg????n el formato indicado en el gui????n
* @param i El intervalo
*/
void leer(Intervalo &i);
/** 
* @brief Muestra un mensaje en pantalla indicando si el intervalo es vac????o o no
* @param i El intervalo
*/

void comprobarVacio(Intervalo i);

#endif


