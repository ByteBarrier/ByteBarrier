#include "../includes/Arbol.h"
#include "Compresor.cpp"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string.h>
using namespace std;

/*
   struct buffer{
   char * cadena;
   int tamanio;

   void (){

   }
   };
   */
int main(int argv, char **argc) {
    ifstream archivoLectura;
    if (argv != 3) {
        cout << "El formato debe ser ./main.out {dirección del fichero}, "
            "{nombreDelFicheroDeSalida}"
            << endl;
    } else {
        map<char, string> huffman;
        string filename = argc[1], outputFilename = argc[2];
        Arbol arbol;

        comprimir(filename,outputFilename, arbol);
        
        ifstream archivoEntrada;
        string nombreFichero = "output/" + outputFilename + ".zsdat";

        archivoEntrada.open(nombreFichero);

        string aux = "";
        while (archivoEntrada) {
            aux += archivoEntrada.get();
        }

        string result = "";
        unsigned int tam = 0;
        Byte aux_b;
        aux_b.valor = aux[0];
        tam += aux_b.valor * (pow(2, 24));
        aux_b.valor = aux[1];
        tam += aux_b.valor * (pow(2, 16));
        aux_b.valor = aux[2];
        tam += aux_b.valor * (pow(2, 8));
        aux_b.valor = aux[3];
        tam += aux_b.valor;
        for (int i = 4; i < aux.size(); i++) {
            aux_b.valor = aux[i];
            result += aux_b.toString();
        }
        //  cout << "tamano =" << tam << " bits" << endl;
        //  cout << result << endl;

        // Descompresión del texto.
        // Paso 1: Leer el arbol desde el archivo.

        archivoEntrada.close();

        nombreFichero = "output/" + outputFilename + ".zscod";

        archivoEntrada.open(nombreFichero);

        huffman = leerHuffman(archivoEntrada);

        // Falta paalsr a arbol.


        // Paso 2: Descomprimimos el archivo.
        Arbol arbol2(huffman);
        Node auxNodo = arbol2.getRaiz();
        int lugar = 0;
        while (tam != 0) {
            while (auxNodo.tengoHijoIzq()) {
                if (result[lugar] == '1') {
                    auxNodo = *(auxNodo.getHijoDer());
                } else {
                    auxNodo = *(auxNodo.getHijoIzq());
                }
                lugar++;
                tam--;
            }
            cout << auxNodo.getCaracter();
            auxNodo = arbol2.getRaiz();
        }
    }
    return 0;
}
