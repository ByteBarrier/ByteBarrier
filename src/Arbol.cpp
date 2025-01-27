#include "../includes/Arbol.h"

// PRUEBA
void Arbol::creaArbol(const LinkedNode &nodo) {
    if (nodo.getIzq() != nullptr) {
        raiz.setHijoIzq(new Node(*nodo.getIzq(), raiz.getNivel() + 1, &raiz));
        raiz.setHijoDer(new Node(*nodo.getDer(), raiz.getNivel() + 1, &raiz));
    } else {
        raiz.setCaracter(nodo.getC());
    }
}

Arbol::PreorderIterator &Arbol::PreorderIterator::operator++() {
    do {
        nextnodo();
    } while (this->current->tengoPadre() && (this->current)->tengoHijoIzq());
    if (!this->current->tengoPadre()) {
        this->current = nullptr;
    }
    return *this;
}

void Arbol::PreorderIterator::subir() {
    while (this->current->tengoPadre() && this->huffman_code.back() == '1') {
        this->huffman_code.pop_back();
        this->current = this->current->getPadre();
    }
}

void Arbol::PreorderIterator::nextnodo() {
    if (!this->current->tengoHijoIzq()) {     // soy hoja
        if (this->huffman_code.back() == '1') { // somos hijo a la izquierda
            this->subir();
        }
        if (this->current->tengoPadre() && this->huffman_code.back() == '0') {
            this->current = this->current->getPadre()->getHijoDer();
            this->huffman_code.pop_back();
            this->huffman_code += '1'; // somos hijo a la derecha
        }
    } else { // Paso al hijo a la izquierda
        this->current = this->current->getHijoIzq();
        this->huffman_code += "0";
    }
}

Arbol::Arbol(const map<char,string> &huffman){
    Node raiz;
    Node * aux;
    string codigo;
    char caracter;
    int tam;

    for(auto it = huffman.cbegin(); it != huffman.cend(); ++it){
        aux = &raiz;

        codigo = it->second;
        caracter = it->first;

        tam = codigo.size();

        for(int i=0; i < tam; ++i){
            //Si no tengo hijo a la izq o a la der, lo creo.
            if(codigo[i]=='0'){
                if(!aux->tengoHijoIzq()){
                    aux->setHijoIzq(new Node(aux,aux->getNivel()+1));
                }
                aux = aux->getHijoIzq();
                // cambio nodo por el hijo a la izquierda.
            }else{
                if(!aux->tengoHijoDer()){
                    aux->setHijoDer(new Node(aux,aux->getNivel()+1));
                }
                aux = aux->getHijoDer();
            }
        }
        aux->setCaracter(caracter);
    }

    this->raiz = raiz;
}
Arbol::PreorderIterator Arbol::begin() {
    PreorderIterator it;
    it.current = &this->raiz; // ponemos la raiz
    if (it.current->tengoHijoIzq()) {
        ++it;
    }
    return it;
}

ostream &operator<<(ostream &output, Arbol const &arbol) {
    // buffer contendrá cada código huffman.
    string buffer;
    unsigned char aux;
    unsigned int tam;
    Byte aux2;

    for (Arbol::ConstPreorderIterator it = arbol.cbegin(); it != arbol.cend(); ++it) {
        // Guardamos el código huffman en el buffer.
        buffer = *it;
        // Cogemos el tamaño del buffer.
        tam = (unsigned int) buffer.size();
        // Dividimos el tamaño en cuatro partes (una por cada Byte).
        aux = tam / 16777216;
        output << aux;
        aux = tam / 65536;
        output << aux;
        aux = tam / 256;
        output << aux;
        aux = tam % 256;
        output << aux;

        // Durante el tamaño del código huffman.
        for (unsigned int i = 0; i < tam; i += 8) {
            // Pasamos las 8 primeras posiciones del buffer a un byte.
            aux2.fromString(buffer);
            // Subimos el valor del byte al archivo.
            output << aux2.valor;
        }
        // Ejemplo: 7. 0000000000...0111 - 1001101 0 - 10010101

        // Si tenemos 126 bits, el carácter hay que empezar a leerlo en la 128.
        // Subimos el carácter.
        output << it.getCurrentChar();
    }
    return output;
}

Arbol::ConstPreorderIterator &Arbol::ConstPreorderIterator::operator++() {
    do {
        nextnodo();
    } while (this->current->tengoPadre() && (this->current)->tengoHijoIzq());
    if (!this->current->tengoPadre()) {
        this->current = nullptr;
    }
    return *this;
}

void Arbol::ConstPreorderIterator::nextnodo() {
    if (!this->current->tengoHijoIzq()) {     // soy hoja
        if (this->huffman_code.back() == '1') { // somos hijo a la izquierda
            this->subir();
        }
        if (this->current->tengoPadre() && this->huffman_code.back() == '0') {
            this->current = this->current->getPadre()->getHijoDer();
            this->huffman_code.pop_back();
            this->huffman_code += '1'; // somos hijo a la derecha
        }
    } else { // Paso al hijo a la izquierda
        this->current = this->current->getHijoIzq();
        this->huffman_code.push_back('0');
    }
}

Arbol::ConstPreorderIterator Arbol::cbegin() const {
    Arbol::ConstPreorderIterator it;
    it.current = new Node(this->raiz); // ponemos la raiz
    if (it.current->tengoHijoIzq()) {
        ++it;
    }
    return it;
}

void Arbol::ConstPreorderIterator::subir() {
    while (this->current->tengoPadre() && this->huffman_code.back() == '1') {
        this->huffman_code.pop_back();
        this->current = this->current->getPadre();
    }
}
