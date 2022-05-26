#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"
#include "tanque.h"
#include "cuadro.h"
#include "mesa.h"
#include "textura.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,CONTAPAS, MANUAL, AUTO, MODOCAMARA} menu;
typedef enum {INMEDIATO, DIFERIDO} dibujo;
typedef enum {SUAVE, PLANO} modoLuz;
typedef enum {MOV_CAMARA_1PERSONA, MOV_CAMARA_EXAMINAR, DEFAULT} ESTADORATON;

class Escena
{

   private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection();
	void change_observer();
    void clear_window();
    
    // Variable para indicar el menu, el modo de visualización y los objetos
    menu modoMenu = NADA;
    dibujo modoDibujo = INMEDIATO;
    modoLuz mLuz = SUAVE;
    int modoColor = 0;
    bool CUBO = true, TETRAEDRO = true, SOLIDO = true, LINEA = false, PUNTOS = false, AJEDREZ = false, OBJPLY = true,
    OBJREV = true, CILINDRO = true, CONO = true, ESFERA = true, tapaSup = true, tapaInf = true, tapaCono = true, ILUMIN = false,
    ALPHA = false, BETA = false, ANIMAR_LUZ = true;
    
    bool GRADO0 = false, GRADO1 = false, GRADO2 = false, GRADO3 = false, AUM_VALOR = false, DISM_VALOR = false, ANIMACION = false;

    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
    ObjPLY * objply = nullptr;
    ObjRevolucion * objrev = nullptr;
    Cilindro * cilindro = nullptr;
    Cilindro * cilindro_ruedas = nullptr;
    Cilindro * cilindro_canon = nullptr;
    Cilindro * cilindro_ext = nullptr;
    Cono * cono = nullptr;
    Cono * cono2 = nullptr;
    Esfera * esfera = nullptr;
    Esfera * casc = nullptr;
    
    ObjRevolucion * lata = nullptr;
    ObjRevolucion * lata_sup = nullptr;
    ObjRevolucion * lata_inf = nullptr;

    Tanque * tanque = nullptr;
    Cuadro * cuadro = nullptr;
    Mesa * mesa = nullptr;

    Textura * text_cuadro = nullptr;
    Textura * text_lata = nullptr;
    Textura * text_mesa = nullptr;
    Textura* text_pelota = nullptr;

    std::vector<Camara> camaras;
    int camaraActiva = 0;

    // Elementos de las luces y objetos necesarios para la practica 3
    std::vector<bool> luces = {false, false, false};
    ObjRevolucion * peonBlanco = nullptr;
    ObjRevolucion * peonNegro = nullptr;
    LuzPosicional * luz0 = nullptr;
    LuzDireccional * luz1 = nullptr;
    LuzPosicional * luz2 = nullptr;
   
   public:
    ESTADORATON estado_raton = DEFAULT;
    int xRaton, yRaton;

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
    
	
    // Dibujar
	void dibujar();
    void animarModeloJerarquico();
    void dibujar_seleccion(int x, int y);

    // Método para activar flags de visualización
    void visualizacion(int obj);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    // Metodos para la p6
    void ratonMovido(int x, int y);
    void clickRaton(int boton,int estado, int x, int y);
    void mouseWheel(int wheel, int direction, int x, int y);
    void activarCamara(int camaraActual);
    void enfocarObjeto(Tupla3f pixel);
};
#endif
