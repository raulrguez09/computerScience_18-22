#include <iostream>
using namespace std;

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
    bool valido(double cotaInferior,double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
    	if (cotaInferior>cotaSuperior || (cotaInferior==cotaSuperior && (!cerradoInferior || !cerradoSuperior)))
    		return false;
    	else	
    		return true;
	}

public:
    /** 
     *  @brief Intervalo vacio por defectoSup
     *  valorInf = valorSup & abiertoInf + abierto
     */
    Intervalo()
    : cotaInf(0), cotaSup(0), cerradoInf(false), cerradoSup(false) {}
    /** 
     * @brief Crea un Intervalo  cerrado por defecto
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior)
    : cotaInf(cotaInferior), cotaSup(cotaSuperior), cerradoInf(true), cerradoSup(true) {}
    /** 
     * @brief Crea Intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior)
    : cotaInf(cotaInferior), cotaSup(cotaSuperior), cerradoInf(cerradoInferior), cerradoSup(cerradoSuperior) {}
    /** 
     * @brief Devuelve la cota inferior del intervalo
     * @return El valor de la cota
     */
    double getCotaInf(){
    	return cotaInf;
	}
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double getCotaSup(){
    	return cotaSup;
	}
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaInf(){
    	return cerradoInf;
	}
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaSup(){
    	return cerradoSup;
	}
    /** 
     * @brief Define los valores del intervalo
     * @param cerradoInferior
     * @param cerradoSuperior
     * @param cotaInferior
     * @param cotaSuperior
     * @precond cotaInferior <= cotaSuperior
     */
    void setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
    	Intervalo auxiliar(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior);
    	if (!auxiliar.esVacio()){
    		cotaInf=cotaInferior;
    		cotaSup=cotaSuperior;
    		cerradoInf=cerradoInferior;
    		cerradoSup=cerradoSuperior;
		}
    		
    	
	}
    /** 
     * @brief Consulta si el intervalo almacenado es vacío o no. ~CONSIDERAMOS VAC�O A NO VALIDO, Y NO VAC�O A VALIDO~
     * @return @retval true si es un intervalo vacío, @retval false en otro caso 
     */
    bool esVacio(){
    	return !valido(cotaInf, cotaSup, cerradoInf, cerradoSup);
	}
    /** 
     * @brief Consulta si un determinado valor está dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool estaDentro(double n){
    	bool pertenece=false;
    	if (!esVacio()){
    		if (n==cotaInf && cerradoInf)
    			pertenece=true;
    		else if (n>cotaInf && n<cotaSup)
    			pertenece=true;
    			else if (n==cotaSup && cerradoSup)
    				pertenece=true;
		}
		
		return pertenece;
		
	}
};

/******************************/

/** 
* @brief Imprime los valores de un intervalo de forma visual según lo indicado en el guión
* @param  El intervalo
*/
void escribir(const Intervalo &i);

/** 
* @brief Lee los valores del intervalo según el formato indicado en el guión
* @param i El intervalo
*/
void leer(Intervalo &i);
/** 
* @brief Muestra un mensaje en pantalla indicando si el intervalo es vacío o no
* @param i El intervalo
*/

void comprobarVacio(Intervalo i);

void escribir(Intervalo &obj) {
    if (obj.esVacio())
        cout << "(0)";
    else {
        if (obj.dentroCotaInf())
         cout << '[';
        else cout << '(';
        cout << obj.getCotaInf() << "," << obj.getCotaSup();
        if (obj.dentroCotaSup())
            cout << ']';
        else cout << ')';
    }
}

void leer(Intervalo & obj){
    // Formato de lectura del intervalo: [|( x,y )|]
    bool cerradoInf = true;
    bool cerradoSup = true;
    double cotaInf, cotaSup;
    char car;
    cin >> car;
    if (car == '(')
        cerradoInf = false;
    cin >> cotaInf;
    cin >> car;
    cin >> cotaSup;
    cin >> car;
    if (car == ')')
        cerradoSup = false;
    obj.setIntervalo(cotaInf, cotaSup, cerradoInf, cerradoSup);
}

void comprobarVacio(Intervalo obj){
	 escribir(obj);
    if (obj.esVacio())
        cout << " Vacio";
    else  cout << " NO Vacio";
    cout << endl;
}


int main(){
    const int CAPACIDAD = 10;
    int i, nintervalos, nvalores;
    Intervalo vacio;
    Intervalo punto(1,1); // intervalo formado por un punto
    Intervalo interv[CAPACIDAD];
    double v[CAPACIDAD];
    
    cout << "Cuantos intervalos (max 10):";
    do{
        cin >> nintervalos;
    } while (nintervalos >10);
    
    cout << "Introduce [ o ( cotaInferior, cotaSuperior ) o ]";
    for(i=0; i < nintervalos; i++)
        leer(interv[i]);

    cout << "Cuantos valores reales (max 10):";
    do{
        cin >> nvalores;
    } while (nvalores >10);
    
    cout << "Introduce valor real: ";
    for(i = 0; i < nvalores; i++)
        cin >> v[i];
    
    for(i = 0; i < nintervalos; i++){
      escribir(interv[i]);
      cout << " : ";
      for (int j = 0; j < nvalores; j++){
        if (interv[i].estaDentro(v[j]))
            cout << v[j] <<" ";
      }
      cout << endl;
    }
}
