/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada A-Z que rota y mapea caracteres.
 */
#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

#include <cctype>

class RotorDeMapeo {
    struct Nodo {
        char letra;
        Nodo* prev;
        Nodo* next;
        explicit Nodo(char c) : letra(c), prev(nullptr), next(nullptr) {}
    };
    Nodo* cabeza;   // posición 'cero' actual
    int tam;        // debería ser 26 (A-Z)

public:
    RotorDeMapeo() : cabeza(nullptr), tam(0) {
        // Construye A..Z
        Nodo* first = nullptr;
        Nodo* prev = nullptr;
        for (char c = 'A'; c <= 'Z'; ++c) {
            Nodo* nd = new Nodo(c);
            if (!first) first = nd;
            if (prev) {
                prev->next = nd;
                nd->prev = prev;
            }
            prev = nd;
            ++tam;
        }
        // cierra el círculo
        if (first && prev) {
            prev->next = first;
            first->prev = prev;
        }
        cabeza = first; // 'A' al inicio
    }

    ~RotorDeMapeo() {
        if (!cabeza) return;
        // Romper el círculo y liberar
        Nodo* p = cabeza->next;
        cabeza->next = nullptr;
        while (p) {
            Nodo* nx = p->next;
            delete p;
            p = nx;
        }
        delete cabeza;
        cabeza = nullptr;
        tam = 0;
    }

    // Rota N pasos (positivo = derecha; negativo = izquierda)
    void rotar(int N) {
        if (!cabeza || tam == 0 || N == 0) return;
        int k = N % tam;
        if (k < 0) k += tam;
        while (k--) cabeza = cabeza->next;
    }

    // Dado un char in (A-Z), devuelve el mapeo actual en la posición 'cero'.
    // Si es espacio, regresa ' '. Si no es A-Z, regresa el mismo char.
    char getMapeo(char in) const {
        if (in == ' ') return ' ';
        char up = static_cast<char>(std::toupper(static_cast<unsigned char>(in)));
        if (up < 'A' || up > 'Z' || !cabeza) return in;

        // busca 'up' y mide offset respecto a 'cabeza'
        const Nodo* p = cabeza;
        for (int i = 0; i < tam; ++i) {
            if (p->letra == up) {
                // el carácter que está en la posición cero (cabeza) es el mapeo
                return cabeza->letra;
            }
            p = p->next;
        }
        return in;
    }
};

#endif // ROTOR_DE_MAPEO_H
