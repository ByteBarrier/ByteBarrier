#include "../includes/Arbol.h"
#include <assert.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string.h>
using namespace std;
map<int, int>::const_iterator encuentra_menor(const map<int, int> &tabla) {
  auto resultado = tabla.cbegin();
  for (auto it = tabla.cbegin(); it != tabla.cend(); ++it) {
    if (it->second < resultado->second) {
      resultado = it;
    }
  }
  return resultado;
}

void inserta_ficticio(LinkedNode *nodo, LinkedNode *ficticio) {
  bool colocado = false;
  while (!colocado) {
    if (nodo->getSig() != nullptr &&
        nodo->getSig()->getN() > ficticio->getN()) {
      ficticio->setSig(nodo->getSig());
      nodo->setSig(ficticio);
      colocado = true;
    } else if (nodo->getSig() == nullptr) {
      nodo->setSig(ficticio);
      colocado = true;
    }
    nodo = nodo->getSig();
  }
  if (ficticio->getSig() == nullptr && ficticio != nodo) {
    nodo->setSig(ficticio);
  }
}
int main(int argv, char **argc) {
  ifstream archivoLectura;
  if (argv != 3) {
    cout << "El formato debe ser ./main.out {dirección del fichero}, "
            "{nombreDelFicheroDeSalida}"
         << endl;
  } else {
    string filename = argc[1], outputFilename = argc[2];
    archivoLectura.open(filename);
    if (archivoLectura.is_open()) {


      string cadena;

      while (archivoLectura) {
        cadena.push_back(archivoLectura.get());
      }

      archivoLectura.close();
      // cout << "Introduce la cadena: ";
      // while(getline(cin, cadena));

      // Paso 1: Contar la cantidad de ocurrencias de cada carácter.
      map<int, int> tabla;
      for (unsigned long i = 0; i < cadena.size(); i++) {
        tabla[cadena.at(i)]++;
      }

      for (auto it = tabla.cbegin(); it != tabla.cend(); ++it) {
        cout << (char)it->first << " " << it->second << endl;
      }

      // Paso 2: Crear una lista enlazada ordenada de menor a mayor según la
      // cantidad de veces que aparece.

      auto it = encuentra_menor(tabla);
      LinkedNode inicial(LinkedNode(it->first, it->second));
      LinkedNode *aux1 = &inicial;
      tabla.erase(it);
      while (tabla.size() != 0) {
        it = encuentra_menor(tabla);
        LinkedNode *aux2 = new LinkedNode(LinkedNode(it->first, it->second));
        aux1->setSig(aux2);
        aux1 = aux2;
        tabla.erase(it);
      }

      // Paso 3: convertir la lista enlazada en un árbol de Huffman.
      int contador = 0;
      LinkedNode *nodo = &inicial, *ficticio;
      LinkedNode raiz;
      while (nodo->getSig() != nullptr) {
        ficticio = new LinkedNode();
        ficticio->setDer(nodo);
        nodo = nodo->getSig();
        ficticio->getDer()->setSig(nullptr);
        ficticio->setIzq(nodo);
        ficticio->setN(ficticio->getIzq()->getN() + ficticio->getDer()->getN());

        if (nodo->getSig() != nullptr) {
          nodo = nodo->getSig();
          inserta_ficticio(nodo, ficticio);
        }
        ficticio->getIzq()->setSig(nullptr);

        // lista.push_back(aux);
        contador++;
      }
      raiz = *ficticio;
      cout << "Contador vale " << contador << endl;
      cout << raiz.getN() << endl;
      cout << raiz.getC() << endl;

      // Paso 4: Creacion del TDA arbol.
      Arbol arbol;
      arbol.creaArbol(raiz);

      string nombreFichero = "output/" + outputFilename + ".zscod";
      ofstream archivoSalida;

      archivoSalida.open(nombreFichero);

      archivoSalida << arbol;

      archivoSalida.close();

      nombreFichero = "output/" + outputFilename + ".zsdat";
      archivoSalida.open(nombreFichero);

      unsigned char tamano[4];
      int tam1;

      // Compresión de texto.
      map<char, string> codigoHuffman;
      pair<char, string> pareja;
      for (auto it = arbol.begin(); it != arbol.end(); ++it) {
        pareja.first = it.getCurrentChar();
        pareja.second = *it;
        codigoHuffman.insert(pareja);
        cout << "Código: " << *it << "\nLetra: " << it.getCurrentChar() << endl
             << endl;
      }
      Byte byte;
      string Str = "10000000", resultado = "", resultado2;

      byte.fromString(Str);

      while (cadena.size() != 0) {
        resultado += codigoHuffman[cadena[0]];
        cadena.erase(0, 1);
      }

      tam1 = resultado.size();
      for (int i = 0; i < 3; i++) {
        tamano[i] = tam1 / pow(256, 3 - i);
        tam1 -= tamano[i] * pow(256, 3 - i);
      }
      tamano[3] = tam1;
      for (int i = 0; i < 4; i++) {
        //    cout << (int)tamano[i] << " ";
        archivoSalida << (unsigned char)tamano[i];
      }

      resultado2 = resultado;
      while (resultado2.size() != 0) {
        byte.fromString(resultado2);
        archivoSalida << byte.valor;
      }

      archivoSalida.close();

      ifstream archivoEntrada;
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
      Node auxNodo = arbol.getRaiz();
      while (tam != 0) {
        while (auxNodo.tengoHijoIzq()) {
          if (result[0] == '1') {
            auxNodo = *(auxNodo.getHijoDer());
          } else {
            auxNodo = *(auxNodo.getHijoIzq());
          }
          result.erase(0, 1);
          tam--;
        }
        cout << auxNodo.getCaracter();
        auxNodo = arbol.getRaiz();
      }
      cout << "\nFIn";
    } else {
      cout << "Error abriendo el archivo";
    }
  }
  return 0;
}
