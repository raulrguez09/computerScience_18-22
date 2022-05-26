#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(){}

Textura::Textura(std::string archivo){
    // Declaro un puntero a imagen (pimg)
    jpg::Imagen * pimg = NULL;

    // Cargo la imagen 
    pimg = new jpg::Imagen(archivo);

    // Usar con
    width = pimg->tamX();
    height = pimg->tamY();

    unsigned char * pixel;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            pixel = pimg->leerPixel(j, height-i-1); // leemos de arriba a abajo
        
            data.push_back(*pixel);         //R
            data.push_back(*(pixel+1));     //G
            data.push_back(*(pixel+2));     //B
        }
    }
}

void Textura::activar(){
    glEnable(GL_TEXTURE_2D);

    if(textura_id == 0){
        glGenTextures(1, &textura_id);
        glBindTexture(GL_TEXTURE_2D, textura_id );
        gluBuild2DMipmaps( GL_TEXTURE_2D ,GL_RGB ,width,height , GL_RGB , GL_UNSIGNED_BYTE , data.data());
    }
    
    glBindTexture(GL_TEXTURE_2D, textura_id );
    
    // Para coordenadas fuera del rango {[0,0], [1,1]}
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    // Cómo se selecciona el texel o texels a partir de una coordenada de textura
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_LINEAR
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


}