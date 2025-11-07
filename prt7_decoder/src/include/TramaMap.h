/**
 * @file TramaMap.h
 * @brief Trama M,N: rota el rotor N posiciones.
 */
#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"
#include "RotorDeMapeo.h"

class TramaMap : public TramaBase {
    int n;
public:
    explicit TramaMap(int N) : n(N) {}
    void procesar(ListaDeCarga* /*carga*/, RotorDeMapeo* rotor) override {
        rotor->rotar(n);
    }
};

#endif // TRAMA_MAP_H
