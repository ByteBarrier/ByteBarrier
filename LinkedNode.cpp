#ifndef LINKEDNODE_H_
#define LINKEDNODE_H_

class LinkedNode {
private:
  char c;
  int n;

  LinkedNode *izq;
  LinkedNode *der;
  LinkedNode *sig;
  void copia(const LinkedNode &other) {
    this->c = other.c;
    this->sig = &(*(other.sig));
    this->der = other.der;
    this->izq = other.izq;
    this->n = other.n;
  }
  void clear() {
    this->sig = nullptr;
    this->der = nullptr;
    this->izq = nullptr;
  }

public:
  LinkedNode() {
    this->c = 0;
    this->n = 0;
    clear();
  }
  LinkedNode(int caracter, int veces) {
    c = caracter;
    n = veces;
    clear();
  }
  LinkedNode(LinkedNode const &other) { copia(other); }
  LinkedNode &operator=(const LinkedNode other) {
    clear();
    copia(other);
    return *this;
  }
  ~LinkedNode() { clear(); }
  bool isNull() {
    return this->izq == nullptr && this->der == nullptr && this->sig == nullptr;
  }
  int getC() const { return c; }
  int getN() const { return n; }
  LinkedNode *getIzq() const { return izq; }
  LinkedNode *getDer() const { return der; }
  LinkedNode *getSig() const { return sig; }
  void setC(char c) { this->c = c; }
  void setN(int n) { this->n = n; }
  void setIzq(LinkedNode *izq) { this->izq = izq; }
  void setDer(LinkedNode *der) { this->der = der; }
  void setSig(LinkedNode *sig) { this->sig = sig; }
};

#endif // LINKEDNODE_H_
