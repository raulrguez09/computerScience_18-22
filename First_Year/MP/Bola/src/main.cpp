// decsai.ugr.es
// 25/04/19

#include "miniwin.h"
#include "definiciones.h"
#include "utilidades.h"
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <string>
#include <queue>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
using namespace miniwin;
			

int main() {
   vredimensiona(800, 600);
  // Bola P = { 50.0, 100.0, 50.0, -50.0, PColor::ROJO };
   Pelota P2(33,11);
   Pelota P3(444,333);
   Pelota P5(343,123, 1, -5, PColor::VERDE);
   Pelota P6(99,700);

   Pelotas Peloticas(0);
   Pelotas Pelots(2);
   
   Pelots.aniadir(P2);

   Peloticas.aniadir(P3);
      
      Peloticas.aniadir(P5);

      Peloticas.borrar(1);
      
      std::cout << Peloticas.getUtil();
      
   while (tecla() != ESCAPE) {
      borra();

      Peloticas.mover();
      Pelots.mover();
      Pelots.pintarPelotas();
      Peloticas.pintarPelotas();
      refresca();
      espera(25);
      Peloticas.colisionarPelotas();
      colisionarPelotas(Pelots,Peloticas);
   }
   vcierra();

   Peloticas.~Pelotas();
   Pelots.~Pelotas();
   return 0;
}



