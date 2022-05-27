struct miVector{
    float vector<>;
};

program VECTORES_PROG{
    version VECTORES_VER{
        miVector SUMAR(miVector,miVector)=1;
        miVector RESTAR(miVector,miVector)=2;
        miVector DIVIDIR(miVector,miVector)=3;
        miVector MULTIPLICAR(miVector,miVector)=4;
    }=1;
}=0x20000001;
