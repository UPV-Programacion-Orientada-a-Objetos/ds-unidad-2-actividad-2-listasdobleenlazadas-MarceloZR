/**
 * @file main.cpp
 * @brief Lector del puerto serial y decodificador PRT-7.
 *
 * Uso:
 *   ./prt7_decoder /dev/ttyUSB0 9600
 *
 * Formato de líneas esperadas desde Arduino:
 *   L,H
 *   L,Space
 *   M,2
 *   M,-2
 *   ...
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "TramaLoad.h"
#include "TramaMap.h"

static int open_serial(const char* path, int baud) {
    int fd = ::open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) return -1;

    termios tty {};
    if (tcgetattr(fd, &tty) != 0) {
        ::close(fd);
        return -1;
    }

    speed_t speed;
    switch (baud) {
        case 9600:   speed = B9600; break;
        case 19200:  speed = B19200; break;
        case 38400:  speed = B38400; break;
        case 57600:  speed = B57600; break;
        case 115200: speed = B115200; break;
        default:     speed = B9600; break;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag = IGNPAR;
    tty.c_oflag = 0;
    tty.c_lflag = 0;               // modo raw
    tty.c_cc[VTIME] = 1;           // 100ms
    tty.c_cc[VMIN]  = 0;

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        ::close(fd);
        return -1;
    }

    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
    return fd;
}

static bool read_line(int fd, std::string& out) {
    out.clear();
    char c;
    while (true) {
        ssize_t n = ::read(fd, &c, 1);
        if (n == 0) { // EOF
            return !out.empty();
        }
        if (n < 0) {
            if (errno == EINTR) continue;
            if (errno == EAGAIN) {
                usleep(1000);
                continue;
            }
            return false;
        }
        if (c == '\r') continue;
        if (c == '\n') break;
        out.push_back(c);
    }
    return true;
}

static bool parse_trama(const std::string& s, TramaBase*& out) {
    out = nullptr;
    if (s.size() < 3 || s[1] != ',') return false;

    if (s[0] == 'L') {
        if (s.compare(2, 5, "Space") == 0) {
            out = new TramaLoad(' ');
            return true;
        }
        char x = s[2];
        out = new TramaLoad(x);
        return true;
    } else if (s[0] == 'M') {
        int n = std::atoi(s.c_str() + 2);
        out = new TramaMap(n);
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <puerto> <baud>\n"
                  << "Ejemplo: " << argv[0] << " /dev/ttyUSB0 9600\n";
        return 1;
    }

    const char* port = argv[1];
    int baud = std::atoi(argv[2]);

    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto COM...\n";

    int fd = open_serial(port, baud);
    if (fd < 0) {
        std::cerr << "No se pudo abrir el puerto: " << port << "\n";
        return 2;
    }

    std::cout << "Conexión establecida. Esperando tramas...\n";

    RotorDeMapeo rotor;
    ListaDeCarga carga;

    std::string line;
    while (read_line(fd, line)) {
        if (line.empty()) continue;

        TramaBase* trama = nullptr;
        if (!parse_trama(line, trama) || !trama) {
            continue;
        }

        trama->procesar(&carga, &rotor);
        delete trama;
    }

    std::cout << "---\nFlujo de datos terminado.\nMENSAJE OCULTO ENSAMBLADO: ";
    carga.imprimirMensaje(std::cout);
    std::cout << "---\nLiberando memoria... Sistema apagado.\n";

    ::close(fd);
    return 0;
}
