/**
 * @file TramaBase.h
 * @brief Clase base abstracta para tramas del protocolo PRT-7.
 */
#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

class ListaDeCarga;
class RotorDeMapeo;

class TramaBase {
public:
    virtual ~TramaBase() = default;
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H
