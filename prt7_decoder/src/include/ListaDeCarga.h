/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados.
 */
#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

#include <iostream>

class ListaDeCarga {
    struct Nodo {
        char dato;
        Nodo* prev;
        Nodo* next;
        explicit Nodo(char c) : dato(c), prev(nullptr), next(nullptr) {}
    };
    Nodo* head; // inicio
    Nodo* tail; // fin
    size_t n;

public:
    ListaDeCarga() : head(nullptr), tail(nullptr), n(0) {}
    ~ListaDeCarga() { limpiar(); }

    void insertarAlFinal(char c) {
        Nodo* nd = new Nodo(c);
        if (!tail) {
            head = tail = nd;
        } else {
            tail->next = nd;
            nd->prev = tail;
            tail = nd;
        }
        ++n;
    }

    void imprimirMensaje(std::ostream& os = std::cout) const {
        for (Nodo* p = head; p; p = p->next) os << p->dato;
        os << std::endl;
    }

    void limpiar() {
        Nodo* p = head;
        while (p) {
            Nodo* nx = p->next;
            delete p;
            p = nx;
        }
        head = tail = nullptr;
        n = 0;
    }

    size_t size() const { return n; }
};

#endif // LISTA_DE_CARGA_H
