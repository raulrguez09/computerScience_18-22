#include "camara.h"
#include "math.h"

// *****************************************************************************
//
// Clase camara
//
// *****************************************************************************

Camara::Camara(){}

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float top, float bottom, float near, float far){
    this->eye = eye;
    eye_original = eye;
    this->at = at;
    this->up = up;
    this->tipo = tipo;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->near = near;
    this->far = far;
}

void Camara::rotarXExaminar(float angle){
    double coseno, seno;
    Tupla3f eye_ajustado = eye-at;
    Tupla3f aux = eye_ajustado;
    float mod = sqrt(eye_ajustado.lengthSq());

    if(angle > 360 || angle <- 360){
        do{
            angle /= 360;
        }while(angle > 360 || angle <- 360);
    }

    coseno = cos(2*M_PI*angle/360);
    seno = sin(2*M_PI*angle/360);

    eye_ajustado[1]=coseno*aux(1) - seno*aux(2);
    eye_ajustado[2]=coseno*aux(2) + seno*aux(1);

    eye_ajustado = eye_ajustado.normalized() * mod;
    eye = eye_ajustado + at;
}

void Camara::rotarYExaminar(float angle){
    double coseno, seno;
    Tupla3f eye_ajustado = eye-at;
    Tupla3f aux = eye_ajustado;
    float mod = sqrt(eye_ajustado.lengthSq());

    if(angle > 360 || angle <- 360){
        do{
            angle /= 360;
        }while(angle > 360 || angle <- 360);
    }

    coseno = cos(2*M_PI*angle/360);
    seno = sin(2*M_PI*angle/360);

    eye_ajustado[0]=coseno*aux(0) + seno*aux(2);
    eye_ajustado[2]=coseno*aux(2) - seno*aux(0);

    eye_ajustado = eye_ajustado.normalized() * mod;
    eye = eye_ajustado + at;
}

void Camara::rotarZExaminar(float angle){
    double coseno, seno;
    Tupla3f eye_ajustado = eye-at;
    Tupla3f aux = eye_ajustado;
    float mod = sqrt(eye_ajustado.lengthSq());

    if(angle > 360 || angle <- 360){
        do{
            angle /= 360;
        }while(angle > 360 || angle <- 360);
    }

    coseno = cos(2*M_PI*angle/360);
    seno = sin(2*M_PI*angle/360);

    eye_ajustado[0]=coseno*aux(0) - seno*aux(1);
    eye_ajustado[1]=coseno*aux(1) + seno*aux(0);

    eye_ajustado = eye_ajustado.normalized() * mod;
    eye = eye_ajustado + at;

}

void Camara::rotarXFirstPerson(float angle){
    at(0) = at(0) + angle;
}

void Camara::rotarYFirstPerson(float angle){
    at(1) = at(1) + angle;

}

void Camara::rotarZFirstPerson(float angle){
    at(2) = at(2) + angle;
}

void Camara::mover(float eje_x, float eje_y, float eje_z){
    at(0) += eje_x;
    at(1) += eje_y;
    at(2) += eje_z;

    eye(0) += eje_x;
    eye(1) += eje_y;
    eye(2) += eje_z;

}

void Camara::zoom(float factor){
    if(factor < 0){
        top /=- factor;
        bottom /=- factor;
        right /=- factor;
        left /=- factor;
    }
    else{
        top *= factor;
        bottom *= factor;
        right *= factor;
        left *= factor;
    }
}

void Camara::setObserver(){
    gluLookAt(eye(0), eye(1), eye(2), at(0), at(1), at(2), up(0), up(1), up(2));
}

void Camara::setProyeccion(){
    if(tipo == 1)
        glFrustum(left, right, bottom, top, near, far);
    else
        glOrtho(left, right, bottom, top, near, far);    
}

void Camara::setAt(Tupla3f at){
    this->at(0) = at(0);
    this->at(1) = at(1);
    this->at(2) = at(2);
}

void Camara::girar(float angX, float angY){
    rotarXFirstPerson(angX);
    rotarYFirstPerson(angY);
}

void Camara::girar_Examinar(float angX, float angY){
    rotarXExaminar(angX);
    rotarYExaminar(angY);
}

