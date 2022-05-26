#include <iostream>
#include "intervalo.h"
using namespace std;

bool Intervalo::valido(double cotaInferior,double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
return (( cotaInferior < cotaSuperior ) || ( cotaInferior == cotaSuperior && cerradoInferior == cerradoSuperior));
 }


Intervalo::Intervalo()
    : cotaInf(0), cotaSup(0), cerradoInf(false), cerradoSup(false) {}

Intervalo::Intervalo(double cotaInferior, double cotaSuperior){
	if (valido(cotaInferior, cotaSuperior, true, true)){
		cotaInf=cotaInferior;
		cotaSup=cotaSuperior;
		cerradoInf=true;
		cerradoSup=true;
	}
	}

Intervalo::Intervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
		if (valido(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior)){
		cotaInf=cotaInferior;
		cotaSup=cotaSuperior;
		cerradoInf=cerradoInferior;
		cerradoSup=cerradoSuperior;
	}
	}

double Intervalo::getCotaInf() const{
    	return cotaInf;
	}

double Intervalo::getCotaSup() const{
    	return cotaSup;
	}

bool Intervalo::dentroCotaInf() const{
    	return cerradoInf;
	}

bool Intervalo::dentroCotaSup() const{
    	return cerradoSup;
	}

void Intervalo::setIntervalo(double cotaInferior, double cotaSuperior, bool cerradoInferior, bool cerradoSuperior){
	if(valido(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior)){
		Intervalo auxiliar(cotaInferior, cotaSuperior, cerradoInferior, cerradoSuperior);
    	if (!auxiliar.esVacio()){
    		cotaInf=cotaInferior;
    		cotaSup=cotaSuperior;
    		cerradoInf=cerradoInferior;
    		cerradoSup=cerradoSuperior;
		}
    		
    	
	}
}

bool Intervalo::esVacio() const{
    	if (cotaInf==cotaSup && (!cerradoInf && !cerradoSup))
    		return true;
    	else	
    		return false;
	}

bool Intervalo::estaDentro(double n) const{
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

Intervalo Interseccion(Intervalo i1, Intervalo i2){
	Intervalo auxiliar;
	double inferior, superior;
	bool dentroinf, dentrosup;
	
	//MIRAMOS COTA INFERIOR
	if(i1.getCotaInf()>i2.getCotaInf())
		inferior=i1.getCotaInf();
	else if(i1.getCotaInf()<i2.getCotaInf())
			inferior=i2.getCotaInf();
			else if (i1.getCotaInf()==i2.getCotaInf())
					inferior=i1.getCotaInf();
					
	
	//MIRAMOS COTA SUPERIOR		
	if (i1.getCotaSup()<i2.getCotaSup())
		superior=i1.getCotaSup();
	else if (i1.getCotaSup()>i2.getCotaSup())
			superior=i2.getCotaSup();
			else if (i2.getCotaSup()==i1.getCotaSup())
				superior=i2.getCotaSup();
			
			
	//ESTABLECEMOS LA PERTENECENCIA DE COTAS
	
	if(i1.estaDentro(inferior) && i2.estaDentro(inferior))
		dentroinf=true;
	else
		dentroinf=false;
		
	if(i1.estaDentro(superior) && i2.estaDentro(superior))
		dentrosup=true;
	else
		dentrosup=false;
		
	//FINALMENTE, DEVOLVEMOS UN INTERVALO, COMPROBANDO PREVIAMENTE SI ES VALIDO:
	
	auxiliar.setIntervalo(inferior, superior, dentroinf, dentrosup);
	
	return auxiliar;
		
	
}


