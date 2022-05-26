/** 
 * **
   @file intervalo.cpp
   @brief Se proporciona parte de la clase intervalo y es necesario definir ciertos métodos para darle operatividad 
   @author MP Grupos B, C de GIInformatica
   @warning Módulo no definitivo (creado para ser modificado)

   Un ejemplo de ejecución es:

    Cuantos intervalos (max 10):5 
    Introduce [ o ( cotaInferior, cotaSuperior ) o ]: [0,10] (0,10] [0,10) (0,10) (10,10)
    Cuantos valores reales (max 10):6
    Introduce valor real: -1 -0.001 0 5.7  9.6  10
    Da como salida: 
    
 [0,10] : 0 5.7 9.6 10 
 (0,10] : 5.7 9.6 10 
 [0,10) : 0 5.7 9.6 
 (0,10) : 5.7 9.6 
 (0) :

 */

// Alumno1: Sanchez Rodriguez Pepa
// Alumno2: Rodriguez Perez Pepe 
// meter esta cabecera en todos los .h

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
     * cotaInferior <= cotaSuperior y algo MAS
     * @param cotaInferior
     * @param cotaSuperior
     * @return @retval true si correcto
     */
     
    bool valido(double cotaInf,double cotaSup, bool cerradoInf, bool cerradoSup); 
    
   	
    	

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
    double getCotaInf()const ;
   
    /** 
     * @brief Devuelve la cota superior del intervalo
     * @return El valor de la cota
     */
    double getCotaSup()const ;
   
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota inferior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaInf()const ;
   
    /** 
     * @brief Consulta si el intervalo es cerrado en su cota superior
     * @return @retval true si es cerrado @retval false si es cerrado
     */
    bool dentroCotaSup()const ;

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
    
     * @brief Consulta si el intervalo almacenado es vacío o no
     * @return @retval true si es un intervalo vacío, @retval false en otro caso 
     */
    bool esVacio()const;
    /** 
     * @brief Consulta si un determinado valor está dentro del intervalo
     * @param n El valor consultado
     * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso 
     */
    bool estaDentro(double n)const ;

/******************************/
// funciones externas
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

// implementacion o definicion de metodos y funciones

 bool Intervalo::valido(double cinf,double csup, bool cerrinf, bool cerrsup){
return (( cinf < csup ) || ( cinf == csup && cerrinf == cerrsup));
 }

void escribir(const Intervalo & obj) {
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
	void Intervalo::setIntervalo(double cotaInferior, doule cotaSuperior, bool cerradoInferior, bool cerradoSuperior) {
	
    CotaInf=cotaInferior;
    CotaSup=cotaSuperior;
    cerradoInf=cerradoInferior;
    cerradoSup=cerradoSuperior;
	}
	
	Intervalo::Intervalo(){
		CotaInf=0;
		CotaSup=0;
		cerradoInf=false;
		cerradoSup=false;
	}
	
	Intervalo::Intervalo(double cotaInferior, double cotaSuperior) {
		CotaInf=cotaInferior;
		CotaSup=cotaSuperior;
		cerradoInf=true;
		cerradoSup=true;
	}
	
	Intervalo::Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior) {
		CotaInf=cotaInferior;
		CotaSup=cotaSuperior;
		cerradoInf= cerradoInferior;
		cerradoSup= cerradoSuperior;
	}
	
	double Intervalo::getCotaInf()const{
		return CotaInf;
	}
	
	double Intervalo::getCotaSup()const{
		return CotaSup;
	}
	
	bool Intervalo::dentroCotaInf()const{
		return dentroCotaInf;
	}
	
	bool Intervalo::dentroCotaSup()const{
		return dentroCotaSup;
	}
	
	bool Intervalo::esVacio()const{
	return 	(cotaInf==cotaSup && (!cerradoInf && !cerradoSup));
	}
	
	bool Intervalo::estaDentro(double n)const{
		bool pertenece=false;
		if (cerradoInf && cerradoSup) {
			if (cotaInf <=n && n<=CotaSup)
				pertenece=true;
		}
		else if (cerradoSup) {
			if(cotaInf<n && n<=cotaSup){
				pertenece=true;
			}
		}
		else if (cerradoInf){
			if(cotaInf <=n && n<cotaSup){
				pertenece=true;
			}
		}
		else{
			if(cotaInf<n && n<cotaSup)
				pertenece=true;
		}
		return pertenece;
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
