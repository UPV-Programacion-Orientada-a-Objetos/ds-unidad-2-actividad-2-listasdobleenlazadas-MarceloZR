/**
 * @file TramaLoad.h
 * @brief Trama L,X: decodifica X con el rotor actual y lo guarda en la carga.
 */
#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

class TramaLoad : public TramaBase {
    char x;
public:
    explicit TramaLoad(char c) : x(c) {}
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        char dec = rotor->getMapeo(x);
        carga->insertarAlFinal(dec);
    }
};

#endif // TRAMA_LOAD_H
