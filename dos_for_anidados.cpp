#include <iostream>
#include <ctime>
#include <fstream>
//Construccion de la comparacion de algoritmos
using namespace std;
void llenarMatriz(double**&arreglo,int cantidad);
void llenarArreglo(double*&arreglo,int valor,int cantidad);

typedef void (*pf)(double**,double*,double*, int);
void primerMetodo(double**,double*,double*,int);
void segundoMetodo(double**,double*,double*,int);

void escribirComparacion(string nombres[],string nombre,double** tiempoRegistrado,int cantidadMetodos,int repeticion,int n,int incremento);
void escribir(string nombre,double** tiempoRegistrado,int fila,int repeticion,int n,int incremento);

int main(){
    double t0, t1;
    int cantidadMetodos=2;//Cantidad de metodos de cache a analizar
    int repeticion=20;//Cantidad de veces que creamos arreglos y los analizamos
    double** tiempoRegistrado=new double*[cantidadMetodos];
    for(int i=0;i<cantidadMetodos;i++){
        tiempoRegistrado[i]=new double[repeticion];//Creando columnas
    }
    double** arreglo=nullptr;//A
    double* x=nullptr;
    double* y=nullptr;
    int n=20;//Cantidad de datos
    int incremento=50;//Incremento de datos
    
    int empieza=n;

    pf fun1[] = {primerMetodo, segundoMetodo};
    string nombre[] = {"primerMetodo","segundoMetodo"};


    for(int p=0;p<cantidadMetodos;p++){//Recorre la cantidad de metodos de ordenamiento
        std::cout<<endl;
        std::cout<<nombre[p]<<endl;
        for(int k=0;k<repeticion;k++){//Modificando el tamaño de los arreglos
            llenarMatriz(arreglo,n);
            llenarArreglo(x,1,n);
            llenarArreglo(y,0,n);
            //std::cout<<"Arreglo imprimido"<<endl;
            //imprimir<int>(arreglo,n);

            t0=clock();
            fun1[p](arreglo,x,y,n);
            
            t1=clock();

            //std::cout<<"Arreglo ordenado"<<endl;
            //imprimir<int>(arreglo,n);

            //Borraando matriz
            for(int i=0;i<n;i++) {
                delete [] arreglo[i];
            }
            delete[] arreglo;

            delete[] x;
            delete[] y;
 
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            tiempoRegistrado[p][k]=time;
 
            n=n+incremento;
        }
        //std::cout<<"Tiempo Registrado"<<endl;
        escribir(nombre[p],tiempoRegistrado,p,repeticion,empieza,incremento);//empieza con 1000 datos
        n=empieza;
        
    }
    escribirComparacion(nombre,nombre[0],tiempoRegistrado,cantidadMetodos,repeticion,empieza,incremento);
    for(int i=0;i<cantidadMetodos;i++) {//Borraando matriz
        delete [] tiempoRegistrado[i];
    }
    delete[] tiempoRegistrado;

    return 0;
}

void llenarMatriz(double**&arreglo,int cantidad){
    int limite=10;
    arreglo=new double*[cantidad];
    for(int i=0;i<cantidad;i++){
        arreglo[i]=new double[cantidad];//Creando columnas
    }

    srand(time(0));
    for(int i=0;i<cantidad;i++){
        for(int j=0;j<cantidad;j++){
            arreglo[i][j]=1+rand()%(limite+1-1);
        }
        
    }
}
void primerMetodo(double** A,double*x,double* y, int cantidad){
    for (int i = 0; i < cantidad; i++)
        for (int j = 0; j < cantidad; j++)
            y[i] += A[i][j]*x[j];
    //cout<<"xxdxd";
}
void segundoMetodo(double** A,double*x,double* y, int cantidad){
    for (int j = 0; j < cantidad; j++)
        for (int i = 0; i < cantidad; i++)
            y[i] += A[i][j]*x[j];
    //cout<<"ferere";
}
void llenarArreglo(double*&arreglo,int valor,int cantidad){
    arreglo=new double[cantidad];
    
    srand(time(0));
    for(int i=0;i<cantidad;i++){
        arreglo[i]=(double)valor;
    }
}
void escribirComparacion(string nombres[],string nombre,double** tiempoRegistrado,int cantidadMetodos,int repeticion,int n,int incremento){
    ofstream archivo;
    //cout<<"hahaha"<<endl;
    archivo.open("dos_for_anidados_carpeta/comparacionMetodos.py",ios::out);
    if(archivo.fail()){
        std::cout<<"No se puedo abrir el archivo";
        exit(1);
    }
   
    archivo<<"import pylab as pl\n"
           <<"import numpy as np\n"
           <<"x = np.array([";
    for(int i=0;i<repeticion-1;i++){
        archivo<<n<<",";
        n=n+incremento;
    }
    archivo<<n;
    
    archivo<<"])";

    for(int j=0;j<cantidadMetodos;j++){
        archivo<<"\n"+nombres[j]+" = np.array([";
        for(int i=0;i<repeticion-1;i++){
            archivo<<tiempoRegistrado[j][i]<<",";
        }
    
        archivo<<tiempoRegistrado[j][repeticion-1];
        archivo<<"])";
    }

    for(int i=0;i<cantidadMetodos;i++){
        archivo<<"\npl.plot(x," + nombres[i];
        archivo<<", linewidth=1.0, linestyle=\"-\",";
        archivo<<"label=\"" + nombres[i];
        archivo<<"\")";
    }
    archivo<<"\npl.legend(loc='upper left')"
            <<"\npl.title('repeticiones="
            <<repeticion
            <<" incremento="
            <<incremento
            <<"')\n";
    //archivo<<"\npl.xlabel('Cantidad de datos (n)')";
    //archivo<<"\npl.ylabel('Tiempo (segundos)')";
    archivo<<"\npl.show()";
    archivo.close();


}
void escribir(string nombre,double** tiempoRegistrado,int fila,int repeticion,int n,int incremento){
    ofstream archivo;

    archivo.open("dos_for_anidados_carpeta/"+nombre+".py",ios::out);
    if(archivo.fail()){
        std::cout<<"No se puedo abrir el archivo";
        exit(1);
    }
    
    archivo<<"import matplotlib.pyplot as plt\n"
           <<"import numpy as np\n"
           <<"x = np.array([";
    for(int i=0;i<repeticion-1;i++){
        archivo<<n<<",";
        n=n+incremento;
    }
    archivo<<n;
    
    archivo<<"])";

    archivo<<"\ny = np.array([";
    for(int i=0;i<repeticion-1;i++){
        archivo<<tiempoRegistrado[fila][i]<<",";
    }
    
    archivo<<tiempoRegistrado[fila][repeticion-1];
    archivo<<"])";

    archivo<<"\nplt.plot(x,y)\n";
    archivo<<"plt.xlabel(\'n\')\n";
    archivo<<"plt.ylabel('Tiempo(sec)')\n";
    archivo<<"plt.title(\'K="<<repeticion<<"\')\n";
    archivo<<"plt.show()\n";

    archivo.close();


}