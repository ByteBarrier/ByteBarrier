#ifndef ARBOL_H_
#define ARBOL_H_

#include "../src/LinkedNode.cpp"
#include "../src/Node.cpp"
#include <iostream>
#include <string>

using namespace std;

struct Byte {
  const int MAX_BIT = 7;
  const int MIN_BIT = 0;

  unsigned char valor = 0x0;

  void onBit(const int &pos) {
    unsigned char mask = 0x1;
    mask = (mask << pos);
    valor = mask | valor;
  }
  void offBit(const int &pos) {
    unsigned char mask = 0x1;
    mask = (mask << pos);
    mask = ~mask;
    valor = mask & valor;
  }
  void fromString(string &input) {
    valor = 0x0;
    for (int i = 0; i <= MAX_BIT && input.size() > 0; ++i) {
      if (input[0] == '1') {
        onBit(i);
      }
      input.erase(0, 1);
    }
  }
  bool getBit(const int &pos) const {
    unsigned char b = valor;
    unsigned char mask = 0x1;
    mask = mask << pos;
    b = mask & b;
    if (b != 0x0) {
      return true;
    } else {
      return false;
    }
  }
  string toString() const {
    string resultado = "";
    for (int i = 0; i <= MAX_BIT; ++i) {
      if (getBit(i)) {
        resultado += '1';
      } else {
        resultado += '0';
      }
    }
    return resultado;
  }
};

class Arbol {
  private:
    Node raiz;

  public:
    inline Arbol() {}
    inline Node getRaiz() { return this->raiz; }
    friend class LinkedNode;
    void creaArbol(const LinkedNode &nodo);
    class PreorderIterator {
      private:
        Node *current;
        string huffman_code;
        bool equal(const PreorderIterator &other) const{
          return this->current == other.current &&
            this->huffman_code == other.huffman_code;
        }

      public:
        inline PreorderIterator() {
          this->current = nullptr;
          this->huffman_code = "";
        }

        inline bool operator==(const PreorderIterator &other) const {
          return this->equal(other);
        }
        inline bool operator!=(const PreorderIterator &other) const {
          return !this->equal(other);
        }
        inline string &operator*() { return this->huffman_code; }
        PreorderIterator &operator++();

        char getCurrentChar() { return this->current->getCaracter(); }
        void subir();
        void nextnodo();
        friend class Arbol;
    };

    class ConstPreorderIterator{
      private:
        Node *current;
        string huffman_code;
        bool equal(const ConstPreorderIterator &other) const{
          return this->current == other.current &&
            this->huffman_code == other.huffman_code;
        }
      public:
        inline ConstPreorderIterator(){
          this->current = nullptr;
          this->huffman_code = "";
        }
        inline const string &operator*() const{
          return this->huffman_code;
        }
        ConstPreorderIterator &operator++();
        void nextnodo();
        void subir();
        inline bool operator==(const ConstPreorderIterator &other) const {
          return this->equal(other);
        }
        inline bool operator!=(const ConstPreorderIterator &other) const {
          return !this->equal(other);
        }
        friend class Arbol;
    };

    PreorderIterator begin();
    inline PreorderIterator end() { return PreorderIterator(); }

    ConstPreorderIterator cbegin() const;
    inline ConstPreorderIterator cend() const { return ConstPreorderIterator(); }

    friend ostream &operator<<(ostream &output,Arbol const &arbol);
    friend istream &operator>>(istream &input, Arbol &arbol);
};

#endif // ARBOL_H_
