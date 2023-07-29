#include <fstream>
#include "../includes/Arbol.h"
#include <map>
#include <chrono>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>

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

map<int, int> tablaRepeticiones(const string & cadena){
    map<int, int> tabla;
    for (unsigned long i = 0; i < cadena.size(); i++) {
        tabla[cadena.at(i)]++;
    }

    for (auto it = tabla.cbegin(); it != tabla.cend(); ++it) {
        cout << (char)it->first << " " << it->second << endl;
    }
    return tabla;
}

LinkedNode crearListaEnlazada(map<int,int> & tabla){
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
    return inicial;
}
LinkedNode convertirListaEnHuffman(LinkedNode & inicial){
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
    }
    raiz = *ficticio;
    return raiz;
}

map<char, string> crearCódigoHuffman(const Arbol & arbol){
    map<char, string> codigoHuffman;
    pair<char, string> pareja;
    
    for (auto it = arbol.cbegin(); it != arbol.cend(); ++it) {
        pareja.first = it.getCurrentChar();
        pareja.second = *it;
        codigoHuffman.insert(pareja);
        cout << "Código: " << *it << "\nLetra: " << it.getCurrentChar() << endl
            << endl;
    }

    return codigoHuffman;
}

bool comprimir(const string & filename, const string & outputFilename, Arbol &arbolSalida){
    ifstream archivoLectura;
    string cadena;
    map<int, int> tabla;
    LinkedNode inicial, raiz;
    Arbol arbol;
    ofstream archivoSalida;
    string nombreFichero;
    unsigned char tamano[4];
    int tam1;
    map<char, string> codigoHuffman;

    archivoLectura.open(filename);

    if (archivoLectura.is_open()) {

        while (archivoLectura) {
            cadena.push_back(archivoLectura.get());
        }

        archivoLectura.close();
        // cout << "Introduce la cadena: ";
        // while(getline(cin, cadena));

        // Paso 1: Contar la cantidad de ocurrencias de cada carácter.
        tabla = tablaRepeticiones(cadena);
        // Paso 2: Crear una lista enlazada ordenada de menor a mayor según la
        // cantidad de veces que aparece.
        inicial = crearListaEnlazada(tabla);
        // Paso 3: convertir la lista enlazada en un árbol de Huffman.
        raiz = convertirListaEnHuffman(inicial);
        // Paso 4: Creacion del TDA arbol.
        arbol.creaArbol(raiz);

        // Paso 5: Subimos el arbol a un fichero.
        nombreFichero = "output/" + outputFilename + ".zscod";
        mkdir("output/",0755);

        archivoSalida.open(nombreFichero);

        archivoSalida << arbol;
        archivoSalida.close();

        nombreFichero = "output/" + outputFilename + ".zsdat";
        archivoSalida.open(nombreFichero);


        // Paso 6: Compresión de texto.
        codigoHuffman = crearCódigoHuffman(arbol);

        Byte byte;
        string resultado = "";

        int tamanio = cadena.size();
        
        // Comprimimos la cadena hacia resultado
        for(int i = 0; i < tamanio; ++i) {
            resultado += codigoHuffman.find(cadena[i])->second;
        }

        // Subimos el tamaño de la cadena antes del propio código.
        int indice = 0;
        tam1 = resultado.size();
        for (int i = 0; i < 3; ++i) {
            tamano[i] = tam1 / pow(256, 3 - i);
            tam1 -= tamano[i] * pow(256, 3 - i);
        }
        tamano[3] = tam1;
        for (int i = 0; i < 4; i++) {
            archivoSalida << (unsigned char)tamano[i];
        }

        // Subimos la cadena comprimida
        tam1 = resultado.size();
        for(int i = 0; i < tam1; i+=8) {
            byte.fromString(resultado,indice);
            archivoSalida << byte.valor;
        }

        archivoSalida.close();
        arbolSalida = arbol;
    }
    else{
        return false;
    }
    return true;
}

map<char,string> leerHuffman(istream &input) {

    string buffer, strAux;
    unsigned char aux;
    char caracter;
    unsigned int tam;
    Byte aux2;
    map<char, string> codigoHuffman;
    pair<char, string> parejita;

    while (input.peek() != -1){
        tam = 0;
        caracter = '\0';
        buffer.clear();
        strAux.clear();
        // Leemos el tamaño
        aux = input.get();
        tam += aux * 16777216;
        aux = input.get();
        tam += aux * 65536;
        aux = input.get();
        tam += aux * 256;
        aux = input.get();
        tam += aux;
        cout << endl << tam;
        // Durante tamaño bits, guardamos el código
        for (unsigned int i = 0; i < tam; i += 8) {

            // Guardamos en el valor de aux2 el byte siguiente.
            aux2.valor = input.get();

            // Guardamos el valor de aux2 en strAux como un string de binarios.
            strAux = aux2.toString();

            // Si quedan 8 bits o más por recorrer, pegamos strAux entero, sino cogemos solamente los que faltan.

            if (tam - i >= 8) {
                buffer += strAux;
            } else {
                for (int j = 0; j < tam - i; ++j)
                    buffer.push_back(strAux[j]);
            }
        }


        caracter = input.get();
        parejita = {caracter,buffer};
        codigoHuffman.insert(parejita);

    }
    return codigoHuffman;
}
