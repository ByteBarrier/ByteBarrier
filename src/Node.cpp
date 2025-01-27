#include "LinkedNode.cpp"

class Node {
private:
  int nivel;
  Node *padre;
  char caracter;
  Node *hijo_izq;
  Node *hijo_der;
  void clear() {
    this->nivel = 0;
    this->caracter = 0;
    this->padre = nullptr;
    this->hijo_izq = nullptr;
    this->hijo_der = nullptr;
  }

public:
  Node(LinkedNode nodo, int nivel, Node *padre) {
    this->padre = padre;
    this->nivel = nivel;
    hijo_izq = nullptr;
    hijo_der = nullptr;

    if (nodo.getIzq() != nullptr) {
      hijo_izq = new Node(*nodo.getIzq(), this->nivel + 1, this);
      hijo_der = new Node(*nodo.getDer(), this->nivel + 1, this);
    } else {
      this->caracter = nodo.getC();
    }
  }
  Node(const Node &nodo){
    this->caracter = nodo.caracter;
    this->setHijoIzq(nodo.hijo_izq);
    this->setHijoDer(nodo.hijo_der);
    this->setPadre(nodo.padre);
    this->setNivel(nodo.nivel);
  }
  Node() { clear(); }
  int getNivel() { return this->nivel; }
  char getCaracter() { return this->caracter; }
  Node *getPadre() { return this->padre; }
  Node *getHijoDer() { return this->hijo_der; }
  Node *getHijoIzq() { return this->hijo_izq; }

  void setNivel(int nivel) { this->nivel = nivel; }
  void setPadre(Node *padre) { this->padre = padre; }
  void setHijoDer(Node *hijoDer) { this->hijo_der = hijoDer; }
  void setHijoIzq(Node *hijoIzq) { this->hijo_izq = hijoIzq; }
  void setCaracter(char caracter) { this->caracter = caracter; }

  bool soyHijoDer() { return this->getPadre()->getHijoDer() == this; }
  bool soyHijoIzq() { return this->getPadre()->getHijoIzq() == this; }
  bool tengoPadre() { return this->getPadre() != nullptr; }
  bool tengoHijoIzq() { return this->getHijoIzq() != nullptr; }

    inline Node & operator=(const Node & nodo){
      if(this != &nodo){
        this->caracter = nodo.caracter;
        this->setHijoIzq(nodo.hijo_izq);
        this->setHijoDer(nodo.hijo_der);
        this->setPadre(nodo.padre);
        this->setNivel(nodo.nivel);
      }
      return *this;
    }
};
