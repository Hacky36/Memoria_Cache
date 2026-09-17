#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include<iostream>

//Construccion de la comparacion de algoritmos
using namespace std;
void llenarMatriz(double**&arreglo,int cantidad);
void llenarArreglo(double*&arreglo,int valor,int cantidad);
void primerMetodo(int nROWS_1, int nCOLUMNS_2, int BLOCK_SIZE,int n,double**blocks_product_A_B,double**A,double**B);
void segundoMetodo(int nROWS_1, int nCOLUMNS_2, int BLOCK_SIZE,int n,double**blocks_product_A_B,double**A,double**B);
typedef void (*pf)(int nROWS_1, int nCOLUMNS_2, int BLOCK_SIZE,int n,double**blocks_product_A_B,double**A,double**B);


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
    double** A=nullptr;
    double** B=nullptr;
    int n=50;//Cantidad de datos
    int incremento=10;//Incremento de datos
    
    int empieza=n;

    pf fun1[] = {primerMetodo, segundoMetodo};
    string nombre[] = {"primerMetodoClasico","segundoMetodoBloques"};
    
    
    int nROWS_1= n;
    int nCOLUMNS_2= n;

    const int MAX_SIZE = 100; // Define el tamaño máximo de las matrices
    // 
    // Tamaño del bloque para la multiplicación por bloques



    int cacheSize = 32768; // Tamaño de la caché en bytes (ajusta esto según tu hardware)
    int elementSize = sizeof(double); // Tamaño de cada elemento en bytes

    // Calcula el tamaño máximo de bloque basado en el tamaño de la caché
    int MAX_BLOCK_SIZE = std::sqrt(cacheSize / (elementSize * 3));

    


    for(int p=0;p<cantidadMetodos;p++){//Recorre la cantidad de metodos de ordenamiento
        std::cout<<endl;
        std::cout<<nombre[p]<<endl;
        
        for(int k=0;k<repeticion;k++){//Modificando el tamaño de los arreglos
            nROWS_1= n;
            nCOLUMNS_2= n;
            A=new double*[nROWS_1];
            for(int i=0;i<nROWS_1;i++){
                A[i]=new double[n];//Creando columnas
            }
            B=new double*[n];
            for(int i=0;i<n;i++){
                B[i]=new double[nCOLUMNS_2];//Creando columnas
            }
            //Iniciamos B
            for(int i=0;i<nROWS_1;i++){
                for(int j=0;j<n;j++){
                    A[i][j]=rand()%5;
                    //cout<<A[i][j]<<" ";
                }
                //cout<<endl;
                
            }

            //Iniciamos B
            for(int i=0;i<n;i++){
                for(int j=0;j<nCOLUMNS_2;j++){
                    B[i][j]=rand()%5;
                    //cout<<B[i][j]<<" ";
                }
                //cout<<endl;
                
            }
            //cout<<"xdxd"<<endl;
            // Asegúrate de que el tamaño del bloque no exceda las dimensiones de las matrices
            int BLOCK_SIZE  = n;
            //imprimir<int>(arreglo,n);
            double**blocks_product_A_B;
            blocks_product_A_B=new double*[n];
            for(int i=0;i<n;i++){
                blocks_product_A_B[i]=new double[n];//Creando columnas
            }
            t0=clock();
            //cout<<"oye"<<endl;
            fun1[p](nROWS_1,nCOLUMNS_2, BLOCK_SIZE,n,blocks_product_A_B,A,B);//int nROWS_1, int nCOLUMNS_2, int BLOCK_SIZE,int n,int**blocks_product_A_B,int**A,int**B
            
            t1=clock();

            //imprimir<int>(arreglo,n);

            //Borraando matriz
            for(int i=0;i<nROWS_1;i++) {
                delete [] A[i];
            }
            for(int i=0;i<n;i++) {
                delete [] B[i];
            }
            for(int i=0;i<n;i++) {
                delete [] blocks_product_A_B[i];
            }
            delete[] A;
            delete[] B;
            delete[] blocks_product_A_B;

 
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            tiempoRegistrado[p][k]=time;
 
            n=n+incremento;
            //cout<<"repe "<<k<<endl;
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
void segundoMetodo(int nROWS_1, int nCOLUMNS_2, int BLOCK_SIZE,int n,double**blocks_product_A_B,double**A,double**B) {
    //Initializing Product A x B
    for(int i=0;i<nROWS_1;i++){
        for(int j=0;j<nCOLUMNS_2;j++){
            blocks_product_A_B[i][j]=0;
        }
        
    }
    //cout<<"aasassa"<<endl;
    for (int i = 0; i < nROWS_1; i += BLOCK_SIZE) {
        for (int j = 0; j < nCOLUMNS_2; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                // Multiplicación de bloques
                for (int ii = i; ii < std::min(i + BLOCK_SIZE, nROWS_1); ii++) {
                    for (int jj = j; jj < std::min(j + BLOCK_SIZE, nCOLUMNS_2); jj++) {
                        double sum = 0.0;
                        for (int kk = k; kk < std::min(k + BLOCK_SIZE, n); kk++) {
                            sum += A[ii][kk] * B[kk][jj];
                        }
                        blocks_product_A_B[ii][jj] += sum;
                    }
                }
            }
        }
    }
    //cout<<"uaaaa"<<endl;
}
void primerMetodo(int nROWS_1, int nCOLUMNS_2,int BLOCK_SIZE,int n,double**standard_product_A_B,double**A,double**B){
    
    //Initializing Product A x B
    for(int i=0;i<nROWS_1;i++){
        for(int j=0;j<nCOLUMNS_2;j++){
            standard_product_A_B[i][j]=0;
        }
        
    }



    
    //Product:

    for(int i=0;i<nROWS_1;i++){
        for(int j=0;j<nCOLUMNS_2;j++){

            for(int k=0;k<n;k++){

                standard_product_A_B[i][j]+=A[i][k]*B[k][j];
            }


        }
    
    }
    //cout<<"haaa"<<endl;
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
    archivo.open("seis_for_anidados_carpeta/comparacionMetodos.py",ios::out);
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

    archivo.open("seis_for_anidados_carpeta/"+nombre+".py",ios::out);
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