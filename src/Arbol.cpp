#include "../includes/Arbol.h"
#include <vector>
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

Arbol::PreorderIterator Arbol::begin() {
  PreorderIterator it;
  it.current = &this->raiz; // ponemos la raiz
  if (it.current->tengoHijoIzq()) {
    ++it;
  }
  return it;
}
ostream & operator<<(ostream & output, Arbol const& arbol){
  string buffer;
  unsigned char aux;
  unsigned int tam;
  Byte aux2;

  for(Arbol::ConstPreorderIterator it = arbol.cbegin(); it != arbol.cend(); ++it){
    buffer = *it;
    tam = (unsigned int)buffer.size();
    aux = tam / 16777216;
    output << aux;
    aux = tam / 65536;
    output << aux;
    aux = tam / 256;
    output << aux;
    aux = tam % 256;
    output << aux;

    for(unsigned int i = 0; i < tam; i+=8){
      aux2.fromString(buffer);
      output << aux2.valor;
    }
  }
  return output;
}
/*
istream & operator>>(istream & input, Arbol & arbol){

}
*/

Arbol::ConstPreorderIterator &Arbol::ConstPreorderIterator::operator++(){
  do {
    nextnodo();
  } while (this->current->tengoPadre() && (this->current)->tengoHijoIzq());
  if (!this->current->tengoPadre()) {
    this->current = nullptr;
  }
  return *this;
}

void Arbol::ConstPreorderIterator::nextnodo(){
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

Arbol::ConstPreorderIterator Arbol::cbegin() const{
  Arbol::ConstPreorderIterator it;
  it.current = new Node(this->raiz); // ponemos la raiz
  if (it.current->tengoHijoIzq()){
    ++it;
  }
  return it;
}

void Arbol::ConstPreorderIterator::subir() {
  while (this->current->tengoPadre() && this->huffman_code.back() == '1'){
    this->huffman_code.pop_back();
    this->current = this->current->getPadre();
  }
}
