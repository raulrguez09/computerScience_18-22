#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
using namespace std;

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************
Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 5*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;
   
   // Creamos las camaras de la escena
   Camara camara_0({0.0,50.0,300.0},{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, 1, -1.0, 1.0, 1.0,-1.0,0.5, 1000.0); //PERSPECTIVA
   Camara camara_1({-200.0,200.0,300.0},{0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, 0, -750.0, 750.0, 750.0,-750.0,0.5, 2000.0); //ORTOGONAL
   Camara camara_2({100.0,100.0,-60.0},{0.0, -50.0, 0.0}, {0.0, 1.0, 0.0}, 1, -1.0, 1.0, 1.0,-1.0,0.5, 2000.0); //PERSPECTIVA

   camaras.push_back(camara_0);
   camaras.push_back(camara_1);
   camaras.push_back(camara_2);

   ejes.changeAxisSize(5000);
   
   // Creamos los objetos de la escena
   tanque = new Tanque();
   lata = new ObjRevolucion("plys/lata-pcue.ply", 50, true, true, true);
   lata_sup = new ObjRevolucion("plys/lata-psup.ply", 50, false, true, true);
   lata_inf = new ObjRevolucion("plys/lata-pinf.ply", 50, false, true, true);
   casc = new Esfera(9, 100, true, 20, 'y');
   
   cuadro = new Cuadro(300);
   mesa = new Mesa(300);

   // Creamos las luces de la escena (AMBIENTE - ESPECULAR - DIFUSO)
   luz1 = new LuzDireccional({40.0, 180.0}, GL_LIGHT1, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
   luz2 = new LuzPosicional({100.0, 0.0, 100.0}, GL_LIGHT2, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0});
   
   // Creamos los materiales de la escena (AMBIENTE - DIFUSO - ESPECULAR)
   Material emerald({0.0215, 0.1745, 0.0215, 1.0}, {0.07568, 0.61424, 0.07568, 1.0}, {0.633, 0.727811, 0.633 , 1.0}, 0.6);
   Material ruby({0.1745, 0.01175, 0.01175, 0.55}, {0.61424, 0.04136, 0.04136, 0.55}, {0.727811, 0.626959, 0.626959, 0.55}, 76.8);
   Material gold({0.24725, 0.1995, 0.0745, 1.0 }, {0.75164, 0.60648, 0.22648, 1.0}, {0.628281, 0.555802, 0.366065, 1.0}, 51.2);
   Material jade({0.135, 0.2225, 0.1575, 0.95}, {0.54, 0.89, 0.63, 0.95}, {0.316228, 0.316228, 0.316228, 0.95}, 12.8);

   Material mdifuso({0.8, 0.8, 0.8, 0.8}, {0.9, 0.9, 0.9, 0.9}, {0.0, 0.0, 0.0, 0.0}, 0.0);
   Material mespecular({0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}, 1.0);
   Material verde_plastico({0.0,0.0,0.0,1.0}, {0.1,0.35,0.1,1.0}, {0.45,0.55,0.45,1.0 }, 32.0);
   
   // Creamos las texturas de la escena
   text_cuadro = new Textura("imag/gotele.jpg");
   text_mesa = new Textura("imag/text-madera.jpg");
   text_lata = new Textura("imag/text-lata-1.jpg");
   text_pelota = new Textura("imag/mundo.jpg");
   
   // Asociamos el material a los objetos
   tanque->setMaterial();
   lata->setMaterial(mespecular);
   casc->setMaterial(mespecular);
   cuadro->setMaterial(mespecular);
   mesa->setMaterial(mespecular);
   
   // Asociamos la textura a los objetos
   lata->setTextura(text_lata);
   casc->setTextura(text_pelota);
   cuadro->setTextura(text_cuadro);
   mesa->setTextura(text_mesa);

   // Establecemos el color de los objetos seleccionados
   casc->setColoresSeleccion({0.0, 1.0, 0.0});
   //tanque->setColoresSeleccion({0,0,0.45});
   lata->setColoresSeleccion({1.0, 0.0, 0.0});
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************
void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );    // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );             // Se habilita el z-bufer
   glEnable(GL_CULL_FACE);                // Se habilita el cull_face, el cual hace que no se muestren las caras traseras
	glPointSize(10);
   
   Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

void Escena::visualizacion(int obj){
   int modDibujo = 0, modLuz = 1;
   if(modoDibujo == DIFERIDO){
      modDibujo = 1;
   }
   if(mLuz == PLANO){
      modLuz = 2;
   }
   
   switch(obj){
      case 0:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            cubo->draw(modDibujo, false, 0, AJEDREZ);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            cubo->draw(modDibujo, false, 1, AJEDREZ);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            cubo->draw(modDibujo, false, 2, AJEDREZ);
         }

         if(AJEDREZ){
            cubo->draw(modDibujo, false, -1, AJEDREZ);
         }

         if(ILUMIN){
            cubo->draw(modDibujo, true, -1, AJEDREZ);
         }
      break;

      case 1:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            tetraedro->draw(modDibujo, false, 0, AJEDREZ);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            tetraedro->draw(modDibujo, false, 1, AJEDREZ);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            tetraedro->draw(modDibujo, false, 2, AJEDREZ);
         }

         if(AJEDREZ){
            tetraedro->draw(modDibujo, false, -1, AJEDREZ);
         }
         if(ILUMIN){
            tetraedro->draw(modDibujo, true, -1, AJEDREZ);
         }
      break;

      case 2:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            objply->draw(modDibujo, false, 0, AJEDREZ);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            objply->draw(modDibujo, false, 0, AJEDREZ);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            objply->draw(modDibujo, false, 0, AJEDREZ);
         }
         if(AJEDREZ){
            objply->draw(modDibujo, false, -1, AJEDREZ);
         }
         if(ILUMIN){
            objply->draw(modDibujo, true, -1, AJEDREZ);
         }                  
      break;

      case 3:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            objrev->draw(modDibujo, false, 0, AJEDREZ, tapaSup, tapaInf);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            objrev->draw(modDibujo, false, 1, AJEDREZ, tapaSup, tapaInf);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            objrev->draw(modDibujo, false, 2, AJEDREZ, tapaSup, tapaInf);
         }
         if(AJEDREZ){
            objrev->draw(modDibujo, false, -1, AJEDREZ, tapaSup, tapaInf);
         }    
         if(ILUMIN){
            objrev->draw(modDibujo, true, -1, AJEDREZ, tapaSup, tapaInf);
         }               
      break;

      case 4:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            cilindro->draw(modDibujo, false, 0, AJEDREZ, tapaSup, tapaInf);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            cilindro->draw(modDibujo, false, 1, AJEDREZ, tapaSup, tapaInf);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            cilindro->draw(modDibujo, false, 2, AJEDREZ, tapaSup, tapaInf);
         }
         if(AJEDREZ){
            cilindro->draw(modDibujo, false, -1, AJEDREZ, tapaSup, tapaInf);
         }
         if(ILUMIN){
            cilindro->draw(modDibujo, true, -1, AJEDREZ, tapaSup, tapaInf);
         }  
      break;

      case 5:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            cono->draw(modDibujo, false, 0, AJEDREZ, true, tapaCono);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            cono->draw(modDibujo, false, 1, AJEDREZ, true, tapaCono);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            cono->draw(modDibujo, false, 2, AJEDREZ, true, tapaCono);
         }
         if(AJEDREZ){
            cono->draw(modDibujo, false, -1, AJEDREZ, true, tapaCono);
         }
         if(ILUMIN){
            cono->draw(modDibujo, true, -1, AJEDREZ, true, tapaCono);
         }  
      break;
      case 6:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            esfera->draw(modDibujo, false, 0, AJEDREZ, tapaSup, tapaInf);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            esfera->draw(modDibujo, false, 1, AJEDREZ, tapaSup, tapaInf);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            esfera->draw(modDibujo, false, 2, AJEDREZ, tapaSup, tapaInf);
         }
         if(AJEDREZ){
            esfera->draw(modDibujo, false, -1, AJEDREZ, tapaSup, tapaInf);
         }
         if(ILUMIN){
            esfera->draw(modDibujo, true, -1, AJEDREZ, tapaSup, tapaInf);
         }  
      break;
      case 7:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            peonBlanco->draw(modDibujo, false, 0, AJEDREZ, tapaSup, tapaInf);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            peonBlanco->draw(modDibujo, false, 1, AJEDREZ, tapaSup, tapaInf);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            peonBlanco->draw(modDibujo, false, 2, AJEDREZ, tapaSup, tapaInf);
         }
         if(AJEDREZ){
            peonBlanco->draw(modDibujo, false, -1, AJEDREZ, tapaSup, tapaInf);
         }
         if(ILUMIN){
            peonBlanco->draw(modDibujo, true, -1, AJEDREZ, tapaSup, tapaInf);
         }  
      break;
      case 8:
         if(SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            peonNegro->draw(modDibujo, false, 0, AJEDREZ, tapaSup, tapaInf);
         }

         if(PUNTOS){
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            peonNegro->draw(modDibujo, false, 1, AJEDREZ, tapaSup, tapaInf);
         }

         if(LINEA){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            peonNegro->draw(modDibujo, false, 2, AJEDREZ, tapaSup, tapaInf);
         }
         if(AJEDREZ){
            peonNegro->draw(modDibujo, false, -1, AJEDREZ, tapaSup, tapaInf);
         }
         if(ILUMIN){
            peonNegro->draw(modDibujo, true, -1, AJEDREZ, tapaSup, tapaInf);
         }  
      break;
   }
}

// **************************************************************************
// Método para leer los pixeles al hacer click en nuestra escena
// **************************************************************************
Tupla3f leerPixel(int x,int y){
   GLint viewport[4];
   GLfloat pixel[3];
   
   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,(void *)pixel);

   Tupla3f pixels;
   pixels[0]=pixel[0];
   pixels[1]=pixel[1];
   pixels[2]=pixel[2];

   return pixels;
}

// **************************************************************************
// Método para dibujar la escena únicamente con el colorSeleccion
// **************************************************************************
void Escena::dibujar_seleccion(int x, int y){
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   
   bool act_dit = false;
   
   glDisable(GL_LIGHTING);
   glDisable(GL_LIGHT1);
   glDisable(GL_LIGHT2);

   if(glIsEnabled(GL_DITHER)){
      glDisable(GL_DITHER);
      act_dit = true;
   }
   
   int aux = modoColor;
   modoColor = 3; 

   casc->setTextura(nullptr);
   lata->setTextura(nullptr);

   tanque->draw(0, false, modoColor, false, false, false);
   //tanque->transformarCentro(0, 0, 0, 1, 1, 1);

   glPushMatrix();
      glTranslatef(200, -20, 0);
      glScalef(1.5, 1.5, 1.5);
      casc->draw(0, false, modoColor, false, true, true);
   glPopMatrix();

   casc->transformarCentro(200, -20, 0, 1.5, 1.5, 1.5);

   glPushMatrix();
      glTranslatef(-200, -50, 0);
      glScalef(30, 30, 30);
      lata_sup->draw(0, false, 0, false, true, true);
      lata->draw(0, false, modoColor, false, true, true);
      lata_inf->draw(0, false, 0, false, true, true);
   glPopMatrix();

   lata->transformarCentro(-200, -50, 0, 30, 30, 30);

   glPushMatrix();
      glTranslatef(-450, -100, -100);
      glScalef(3, 2, 3);
      cuadro->draw(0, false, 0, false);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(450, -50, -100);
      glScalef(3, 3, 3);
      glRotatef(180.0, 0.0, 0.0, 1.0);
      mesa->draw(0, false, 0, false);
   glPopMatrix();


   enfocarObjeto(leerPixel(x,y));
   modoColor = 0;

   lata->setTextura(text_lata);
   casc->setTextura(text_pelota);

   if(act_dit){
      glEnable(GL_DITHER);
   }
}

// **************************************************************************
// Método para enfocar los objetos que han sido seleccionados para examinar
// **************************************************************************
void Escena::enfocarObjeto(Tupla3f pixel){
   cout << "pixel 0 --> " << pixel(0) << endl;
   cout << "pixel 1 --> " << pixel(1) << endl;
   cout << "pixel 2 --> " << pixel(2) << endl;
   cout << "**************************" << endl;
   cout << "casc 0 --> " << casc->getColorSeleccion()(0) << endl;
   cout << "casc 1--> " << casc->getColorSeleccion()(1) << endl;
   cout << "casc 2--> " << casc->getColorSeleccion()(2) << endl;

   if(pixel(0) == casc->getColorSeleccion()(0) && pixel(1) == casc->getColorSeleccion()(1) && pixel(2) == casc->getColorSeleccion()(2)){
         camaras[camaraActiva].setSeleccion(BALA);
         camaras[camaraActiva].setAt(casc->getCentroSeleccion());
         std::cout << "ESFERA SELECCIONADA (MANTEN PARA EXAMINAR)" <<std::endl;
   }
   else if(pixel(0) == lata->getColorSeleccion()(0) && pixel(1) == lata->getColorSeleccion()(1) && pixel(2) == lata->getColorSeleccion()(2)){
         camaras[camaraActiva].setSeleccion(LATA);
         camaras[camaraActiva].setAt(lata->getCentroSeleccion());
         std::cout << "LATA SELECCIONADA (MANTEN PARA EXAMINAR)" <<std::endl;

   }
   // else if(pixel(1)==tanque->getColorSeleccion()(1)){
   //       camaras[camaraActiva].setSeleccion(TANQUE);
   //       camaras[camaraActiva].setAt(tanque.getCentroSeleccion());
   //       std::cout << "TANQUE SELECCIONADO (MANTEN PARA EXAMINAR)" <<std::endl;

   // }
   else{
      if(camaras[camaraActiva].getObjetoSeleccionado() != NO_SELECCION)
            camaras[camaraActiva].reestablecerEye();

      camaras[camaraActiva].setSeleccion(NO_SELECCION);
      camaras[camaraActiva].setAt({0,0,0});
   }

}

// **************************************************************************
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
// **************************************************************************
void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   if(glIsEnabled(GL_LIGHTING)){
      glDisable(GL_LIGHTING);
      ejes.draw();
   }else{
      ejes.draw();
   }

   glEnable(GL_NORMALIZE);

   if(ILUMIN){
      glShadeModel(GL_SMOOTH);
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      if(luces[1] == true){
         luz1->activar();
      } 
      else{ 
         luz1->desactivar();     
      }

      if(luces[2] == true){
         luz2->activar();
      } 
      else{ 
         luz2->desactivar();     
      }
   }

   tanque->draw(0, ILUMIN, 0, false, false, false);
   //tanque.transformasCentro(0, 0, 0, 1, 1, 1);
   //glTranslatef(200, -20, 0)

   glEnable(GL_TEXTURE_2D);
   glPushMatrix();
      glTranslatef(200, -20, 0);
      glScalef(1.5, 1.5, 1.5);
      casc->draw(0, ILUMIN, modoColor, false, true, true);
   glPopMatrix();

   casc->transformarCentro(200, -20, 0, 1.5, 1.5, 1.5);

   glPushMatrix();
      glTranslatef(-200, -50, 0);
      glScalef(30, 30, 30);
      lata_sup->draw(0, ILUMIN, 0, false, true, true);
      lata->draw(0, ILUMIN, modoColor, false, true, true);
      lata_inf->draw(0, ILUMIN, 0, false, true, true);
   glPopMatrix();

   lata->transformarCentro(-200, -50, 0, 30, 30, 30);

   glPushMatrix();
      glTranslatef(-450, -100, -100);
      glScalef(3, 2, 3);
      cuadro->draw(0, false, 0, false);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(450, -50, -100);
      glScalef(3, 3, 3);
      glRotatef(180.0, 0.0, 0.0, 1.0);
      mesa->draw(0, false, 0, false);
   glPopMatrix();

}

//**************************************************************************
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//**************************************************************************
bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   
   switch( toupper(tecla) ){
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout << "Selecciona un objeto: " << endl << "'C' : Cubo" << endl 
                                                  << "'T' : Tetraedro" << endl
                                                  << "'P' : Objply" << endl
                                                  << "'R' : ObjRev" << endl
                                                  << "'I' : Cilindro" << endl
                                                  << "'N' : Cono" << endl
                                                  << "'E' : Esfera" << endl
                                                  << "'Q' : Salir" << endl; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         if(ILUMIN){
            cout << "Selecciona el modo de visualización: " << endl << "'0' : Activar luz cero" << endl 
                                          << "'1' : Activar luz uno (dir)" << endl << "'2' : Activar luz dos (pos)" << endl
                                          << "'A' : Modo variacion Alpha" << endl << "'B' : Modo variacion Beta" << endl
                                          << "'+' : Incrementar angulo" << endl << "'-' : Decrementar angulo" << endl
                                          << "'Q' : Salir" << endl;
         }else{
            cout << "Selecciona el modo de visualización: " << endl << "'P' : Puntos" << endl 
                                          << "'L' : Lineas" << endl << "'S' : Solido" << endl
                                          << "'A' : Ajedrez" << endl << "'I' : Iluminacion" << endl
                                          << "'Q' : Salir" << endl; 
         }
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Selecciona el modo de dibujado: " << endl << "'1' : Inmediato" << endl 
                                                    << "'2' : Diferido" << endl; 
         break ;
      case 'K' :
         // ESTAMOS EN MODO CON/SIN TAPAS
         modoMenu=CONTAPAS;
         cout << "Selecciona el modo de dibujado: " << endl << "'3' : conTapa" << endl 
                                                    << "'4' : sinTapa" << endl; 
         break ;
      case 'M' :
         //ESTAMOS EN MODO MANUAL
         modoMenu=MANUAL;
         cout << "Selecciona las opciones del modo manual: " << endl << "'0' : Grado0" << endl << "'1' : Grado1" << endl
                                                             << "'2' : Grado2" << endl << "'3' : Grado3" << endl
                                                             << "'+' : aumentar_valor" << endl
                                                             << "'-' : disminuir_valor" << endl  << "'Q' : Salir" << endl;
      break;
      case 'U' :
         //ESTAMOS EN MODO AUTO
         modoMenu=AUTO;
         cout << "Selecciona las opciones del modo auto: " << endl << "'+' : Aumentar velocidad" << endl
                                                           << "'-' : Disminuir velocidad" << endl  
                                                           << "'Q' : Salir" << endl;
      break;
      case 'C' :
         // ESTAMOS EN MODO ILUMINACION
         modoMenu=MODOCAMARA;
         cout << "SELECCIONA LA OPERACION DE CAMARA: (0-1 ACTIVAR CAMARAS, Q SALIR)" << endl;
      break ;                                            
   }

   if(modoMenu == SELOBJETO){
      switch( toupper(tecla) ){
         case 'C' :
            // VISUALIZA/DESACTIVA EL CUBO
            if(!CUBO){
               CUBO = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'CUBO'" << endl;
            }
            else{
               CUBO = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'CUBO'" << endl;               
            }
            break ;
         case 'T' :
            // VISUALIZA/DESACTIVA EL TETRAEDRO
            if(!TETRAEDRO){
               TETRAEDRO = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'TETRAEDRO'" << endl;
            }
            else{
               TETRAEDRO = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'TETRAEDRO'" << endl;
            }
            break;
         case 'P' :
            //VISUALIZA/DESACTIVA EL OBJETO PLY
            if(!OBJPLY){
               OBJPLY = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'OBJPLY'" << endl;
            }
            else{
               OBJPLY = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'OBJPLY'" << endl;
            }
            break;
         case 'R' :
            //VISUALIZA/DESACTIVA EL OBJETO REVOLUCION
            if(!OBJREV){
               OBJREV = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'OBJREV'" << endl;
            }
            else{
               OBJREV = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'OBJREV'" << endl;
            }
            break;
         case 'I' :
            //VISUALIZA/DESACTIVA EL OBJETO CILINDRO
            if(!CILINDRO){
               CILINDRO = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'CILINDRO'" << endl;
            }
            else{
               CILINDRO = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'CILINDRO'" << endl;
            }
            break;
         case 'N' :
            //VISUALIZA/DESACTIVA EL OBJETO CONO
            if(!CONO){
               CONO = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'CONO'" << endl;
            }
            else{
               CONO = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'CONO'" << endl;
            }
            break;
         case 'E' :
            //VISUALIZA/DESACTIVA EL OBJETO ESFERA
            if(!ESFERA){
               ESFERA = true;
               dibujar();
               cout << "Se ha seleccionado el objeto: 'ESFERA'" << endl;
            }
            else{
               ESFERA = false;
               dibujar();
               cout << "Se ha desactivado el objeto: 'ESFERA'" << endl;
            }
            break;
         case 'Q' :
            modoMenu = NADA;
            break;
      }        
   }

   if(modoMenu == SELVISUALIZACION){
      if(ILUMIN){
         switch( toupper(tecla) ){
            case '0' :
               // ACTIVAR LUZ 0
               if(!luces[0]){
                  luces[0] = true;

                  dibujar();

                  cout << "Se ha activado la visualización de: 'LUZ 0'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización de: 'LUZ 0'" << endl;
                  luces[0] = false;
               }
               break;
            case '1' :
               // ACTIVAR LUZ 1
               if(!luces[1]){
                  luces[1] = true;

                  dibujar();

                  cout << "Se ha activado la visualización de: 'LUZ 1'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización de: 'LUZ 1'" << endl;
                  luces[1] = false;
               }
               break;
            case '2' :
               // ACTIVAR LUZ 2
               if(!luces[2]){
                  luces[2] = true;

                  dibujar();

                  cout << "Se ha activado la visualización de: 'LUZ 2'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización de: 'LUZ 2'" << endl;
                  luces[2] = false;
               }
               break;
            case 'A' :
               // MODO VARIACION ALPHA
               if(!ALPHA){
                  ALPHA = true;
                  BETA = false;
                  cout << "Se ha activado el modo variacion de: 'ALPHA'" << endl;
               }
               else{
                  cout << "Se ha desactivado el modo variacion de: 'ALPHA'" << endl;
                  ALPHA = false;
               }
               break;
            case 'B' :
               // MODO VARIACION ALPHA
               if(!BETA){
                  BETA = true;
                  ALPHA = false;
                  cout << "Se ha activado el modo variacion de: 'BETA'" << endl;
               }
               else{
                  cout << "Se ha desactivado el modo variacion de: 'BETA'" << endl;
                  BETA = false;
               }
               break;
            case '+' :
               // MODO INCREMENTO DE ANGULO
               if(ALPHA){
                  luz1->variarAnguloAlpha(5);
                  dibujar();
                  cout << "Se ha incrementado el angulo: 'ALPHA'" << endl;
               }
               else if(BETA){
                  luz1->variarAnguloBeta(5);
                  dibujar();
                  cout << "Se ha incrementado el angulo: 'BETA'" << endl;
               }
               break;
            case '-' :
               // MODO DECREMENTO DE ANGULO
               if(ALPHA){
                  luz1->variarAnguloAlpha(-5);
                  dibujar();
                  cout << "Se ha decrementado el angulo: 'ALPHA'" << endl;
               }
               else if(BETA){
                  luz1->variarAnguloBeta(-5);
                  dibujar();
                  cout << "Se ha decrementado el angulo: 'BETA'" << endl;
               }
               break;            
            case 'Q' :
               modoMenu = NADA;
               break;                  
         }
      } else{
         switch( toupper(tecla) ){
            case 'P' :
               // VISUALIZA/DESACTIVA EL MODO PUNTOS
               if(!PUNTOS){
                  PUNTOS = true;
                  
                  //Activamos con glPolygonmode la visualización en modo puntos
                  glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                  dibujar();

                  cout << "Se ha activado la visualización en modo: 'PUNTOS'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización en modo: 'PUNTOS'" << endl;
                  PUNTOS = false;
               }
               break;
            case 'L' :
               // VISUALIZA/DESACTIVA EL MODO LINEAS
               if(!LINEA){
                  LINEA = true;
                  
                  //Activamos con glPolygonmode la visualización en modo lineas
                  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                  dibujar();

                  cout << "Se ha activado la visualización en modo: 'LINEA'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización en modo: 'LINEA'" << endl;
                  LINEA = false;
               }
               break;
            case 'S' :
               // VISUALIZA/DESACTIVA EL MODO SOLIDO
               if(!SOLIDO){
                  SOLIDO = true;
                  
                  //Activamos con glPolygonmode la visualización en modo solido
                  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                  dibujar();

                  cout << "Se ha activado la visualización en modo: 'SOLIDO'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización en modo: 'SOLIDO'" << endl;
                  SOLIDO = false;
               }
               break;
            case 'A' :
               // VISUALIZA/DESACTIVA EL MODO AJEDREZ
               if(!AJEDREZ){
                  AJEDREZ = true;
                  SOLIDO = false, LINEA = false, PUNTOS = false;
                  
                  //Activamos la visualización en modo ajedrez
                  dibujar();
                  cout << "Se ha activado la visualización en modo: 'AJEDREZ'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización en modo: 'AJEDREZ'" << endl;
                  AJEDREZ = false;
               }
               break;
            case 'I' :
               // VISUALIZA/DESACTIVA EL MODO ILUMINACION
               if(!ILUMIN){
                  ILUMIN = true;
                  
                  //Activamos la visualización en modo ILUMINACION
                  dibujar();
                  cout << "Se ha activado la visualización en modo: 'ILUMINACION'" << endl;
               }
               else{
                  cout << "Se ha desactivado la visualización en modo: 'ILUMINACION'" << endl;
                  ILUMIN = false;
               }
               break;
            case 'Q' :
               modoMenu = NADA;
               break;                    
         }
      }   
   }

   if(modoMenu == SELDIBUJADO){
      switch( toupper(tecla) ){
         case '1' :
            // ACTIVA EL DIBUJADO EN MODO INMEDIATO
            if(modoDibujo != INMEDIATO){
               modoDibujo = INMEDIATO;
               dibujar();

               cout << "Se ha activado el dibujado en modo: 'INMEDIATO'" << endl;
            }
            else{
               cout << "El modo de dibujado 'INMEDIATO' ya estaba activado" << endl;
            }
            break;
         case '2' :
            // ACTIVA EL DIBUJADO EN MODO DIFERIDO
            if(modoDibujo != DIFERIDO){
               modoDibujo = DIFERIDO;
               dibujar();

               cout << "Se ha activado el dibujado en modo: 'DIFERIDO'" << endl;
            }
            else{
               cout << "El modo de dibujado 'DIFERIDO' ya estaba activado" << endl;
            }
            break;
         case 'Q' :
            modoMenu = NADA;
            break;
      }
   }

   if(modoMenu == CONTAPAS){
      switch( toupper(tecla) ){
         case '3' :
            // ACTIVA EL DIBUJADO CON TAPA
            if(!tapaSup && !tapaInf){
               tapaCono = true;
               tapaSup = true;
               tapaInf = true;
               dibujar();

               cout << "Se ha activado el dibujado en modo: 'conTapa'" << endl;
            }
            else{
               cout << "El modo de dibujado 'conTapa' ya estaba activado" << endl;
            }
         break;
         case '4' :
            // ACTIVA EL DIBUJADO EN sinTapa
            if(tapaSup && tapaInf){
               tapaCono = false;
               tapaSup = false;
               tapaInf = false;
               dibujar();

               cout << "Se ha activado el dibujado en modo: 'sinTapa'" << endl;
            }
            else{
               cout << "El modo de dibujado 'sinTapa' ya estaba activado" << endl;
            }
            break;
         case 'Q' :
            modoMenu = NADA;
            break;
      }
   } 
   
   if(modoMenu == MANUAL){
      switch(toupper(tecla)){
         case '0':
            if(!GRADO0){
               cout << "GIRO CASCO ACTIVADO" << endl;
               GRADO0 = true;
               GRADO1 = false;
               GRADO2 = false;
               GRADO3 = false;
            }
         break;

         case '1':
            if(!GRADO1){
               cout << "ELEVACION CANON ACTIVADO" << endl;
               GRADO1 = true;
               GRADO0 = false;
               GRADO2 = false;
               GRADO3 = false;
            }
         break;

         case '2':
            if(!GRADO2){
               cout << "TRASLACION DE CANON ACTIVADO" << endl;
               GRADO2 = true;
               GRADO0 = false;
               GRADO1 = false;
               GRADO3 = false;
            }
         break;

         case '3':
            if(!GRADO3){
               cout << "TRASLACION DE CANON ACTIVADO" << endl;
               GRADO3 = true; 
               GRADO2 = false;
               GRADO0 = false;
               GRADO1 = false;
            }
         break;

         case '+':
            if(GRADO0){
               tanque->seleccionaModifGrados(0, '+');
            }

            if(GRADO1){
               tanque->seleccionaModifGrados(1, '+');
            }

            if(GRADO2){
               tanque->seleccionaModifGrados(2, '+');
            }
            
            if(GRADO3){
               tanque->seleccionaModifGrados(3, '+');
            }
         break;

         case '-':
            if(GRADO0){
               tanque->seleccionaModifGrados(0, '-');
            }

            if(GRADO1){
               tanque->seleccionaModifGrados(1, '-');
            }

            if(GRADO2){
               tanque->seleccionaModifGrados(2, '-');
            }

            if(GRADO3){
               tanque->seleccionaModifGrados(3, '-');
            }
         break;

         case 'Q':
            modoMenu = NADA;
         break;
      }
   }
   
   if(modoMenu == AUTO){
      switch(toupper(tecla)){
         case 'U':
            if(!ANIMACION)
               ANIMACION = true;
            else
               ANIMACION = false;
         break;
      }
   }

   if(modoMenu==MODOCAMARA){
      switch (toupper(tecla)){
       case '0' : //ACTIVA CAMARA 0
           if(camaraActiva!=0){
               camaraActiva=0;
               activarCamara(0);
               cout << "Activando camara 0" << endl;
           }
           else{
               cout << "La camara 0 ya esta activa" << endl;
           }
         break ;

       case '1' : //ACTIVA CAMARA 1
           if(camaraActiva!=1){
               camaraActiva=1;
               activarCamara(1);
               cout << "Activando camara 1" << endl;
           }
           else{
               cout << "La camara 1 ya esta activa" << endl;
           }
         break ;

         case '2':
           if(camaraActiva!=2){
               camaraActiva=2;
               activarCamara(2);
               cout << "Activando camara 2" << endl;
           }
           else{
               cout << "La camara 2 ya esta activa" << endl;
           }
         break ;
      case 'Q' :
            modoMenu=NADA;            
      break ;
   }
   
}
   return salir;
}


//**************************************************************************
void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         mouseWheel(0,-1,0,0);
         std::cout << "Haciendo zoom in con la camara: " << camaraActiva <<std::endl; 
         break;
	   case GLUT_KEY_PAGE_DOWN:
         mouseWheel(0,1,0,0);
         std::cout << "Haciendo zoom out con la camara: " << camaraActiva <<std::endl; 
         break;

	}

	//std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//***************************************************************************
void Escena::change_projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   camaras[camaraActiva].setProyeccion();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************
void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;

   float ratio = (float)newWidth/float(newHeight);

   for(int i=0; i < camaras.size(); i++){
      camaras[i].setLeft(camaras[i].getBottom()*ratio);
      camaras[i].setRight(camaras[i].getTop()*ratio);
   }

   //change_projection( float(newHeight)/float(newWidth) );

   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************
void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva].setObserver();
   // glTranslatef( 0.0, 0.0, -Observer_distance );
   // glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   // glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

// **************************************************************************
// Método para animar el modelo jerarquico y la luz posicional
// **************************************************************************
void Escena::animarModeloJerarquico(){
   if(ANIMACION){
      tanque->animacion();
   }

   if(ANIMAR_LUZ){
      luz2->animarLuz();
   }
}

// **************************************************************************
// Método necesarios para la realizacion de la P6
// **************************************************************************
void Escena::ratonMovido(int x, int y){
   if(estado_raton == MOV_CAMARA_1PERSONA){
      camaras[camaraActiva].girar(x-xRaton,y-yRaton);
      xRaton = x;
      yRaton = y;
   }

   if(estado_raton == MOV_CAMARA_EXAMINAR){
      //Invirtiendo el orden de parámetros, conseguimos una respuesta de ratón mejor:
      //IZQyDCHA: EJE X, ARRIBAyABAJO: EJE Y
      camaras[camaraActiva].girar_Examinar(y-yRaton,x-xRaton); 
      xRaton = x;
      yRaton = y;
   }
}

void Escena::clickRaton(int boton,int estado, int x, int y){
   if(boton == GLUT_RIGHT_BUTTON){
      if(estado == GLUT_DOWN)
         estado_raton = MOV_CAMARA_1PERSONA;
      else
         estado_raton = DEFAULT; 
   }
   else if(boton == GLUT_LEFT_BUTTON){
      if(estado == GLUT_DOWN){
         estado_raton = MOV_CAMARA_EXAMINAR;
         dibujar_seleccion(x,y);
         change_projection();
         change_observer();
      }
      else
         estado_raton = DEFAULT; 
   }
}

void Escena::mouseWheel(int wheel, int direction, int x, int y){
   if(direction > 0)
      camaras[camaraActiva].zoom(1.1);
   else
      camaras[camaraActiva].zoom(-1.1);

   change_projection();
}

void Escena::activarCamara(int camaraActual){
   camaraActiva = camaraActual;
   change_projection();
   change_observer();
}

