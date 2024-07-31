#include <stdio.h>
#include <stdlib.h>
#include <libserialport.h>

#define SERIAL_PORT "/dev/ttyACM0" // ver el puerto serial
#define BAUDRATE 9600

void check_port(struct sp_port *port) {
    if (port == NULL) {
        fprintf(stderr, "Error al abrir el puerto\n");
        exit(EXIT_FAILURE);
    }
}

void check_error(enum sp_return result) {
    if (result != SP_OK) {
        fprintf(stderr, "Error de puerto serie: %d\n", result);
        exit(EXIT_FAILURE);
    }
}

int main() {
    struct sp_port *port;
    enum sp_return result;
    
    // Abre el puerto
    result = sp_get_port_by_name(SERIAL_PORT, &port);
    check_port(port);
    result = sp_open(port, SP_MODE_READ);
    check_error(result);

    // Configura la velocidad del puerto
    result = sp_set_baudrate(port, BAUDRATE);
    check_error(result);

    // Configura las demás opciones del puerto (paridad, bits de datos, bits de parada)
    result = sp_set_bits(port, 8);
    check_error(result);
    result = sp_set_parity(port, SP_PARITY_NONE);
    check_error(result);
    result = sp_set_stopbits(port, 1);
    check_error(result);

    char buffer[256];
    int bytes_read;

    while (1) {
        // Lee datos del puerto serial
        bytes_read = sp_nonblocking_read(port, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s\n", buffer);
        }

        // Dormir por un corto tiempo para evitar alta carga de CPU
        usleep(100000);
    }

    // Cierra el puerto
    sp_close(port);
    sp_free_port(port);

    return 0;
}

 