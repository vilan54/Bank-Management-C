#include "hash.h"

unsigned long concat_ulong(unsigned long num1, unsigned long num2) {
    // Obtenemos la cantidad de dígitos en num2
    unsigned long temp = num2;
    int digitCount = 0;
    while (temp != 0) {
        temp /= 10;
        digitCount++;
    }

    // Multiplicamos num1 por 10 elevado a la cantidad de dígitos en num2 y luego sumamos num2
    unsigned long result = num1 * (unsigned long)pow(10, digitCount) + num2;
    return result;
}

unsigned long hashFNV1a(unsigned char *str) {
    unsigned long hash = 14695981039346656037UL; // Valor inicial del hash
    int c;

    while ((c = *str++)) {
        hash ^= (unsigned long)c; // Operación XOR con el siguiente byte
        hash *= 1099511628211UL; // Multiplicación por un primo grande
        // Puedes agregar más operaciones aquí si lo deseas
    }

    return hash;
}

void hashUserPassword(User *user) {
    unsigned long hashPassword = hashFNV1a((unsigned char*)user->password);
    snprintf(user->password, sizeof(user->password), "%lu", hashPassword);
}

unsigned long hashDJB2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) ^ (hash >> 27) ^ c; // Ronda 1 de mezcla de bits y XOR
        hash = ((hash << 5) + hash) ^ (hash >> 27) ^ c; // Ronda 2 de mezcla de bits y XOR
        // Agregar más rondas si es necesario para aumentar la complejidad
    }

    return hash;
}

void generateUserId(User *user) {
    // Aplicar el hash al string concatenado
    unsigned long hashValue = hashDJB2((unsigned char*)user->dni);
                              


    user->id = hashValue;
}

int validateDateFormat(char *cadena) {
    // Compilar la expresión regular
    const char *patron = "^\\d{2}/\\d{2}/\\d{4}$";
    pcre *re;
    const char *error;
    int erroffset;
    re = pcre_compile(patron, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        printw("Error al compilar la expresión regular: %s\n", error);
        return -1;
    }

    // Ejecutar la expresión regular sobre la cadena
    int rc;
    int ovector[30]; // Suficientemente grande para contener información de coincidencias
    rc = pcre_exec(re, NULL, cadena, strlen(cadena), 0, 0, ovector, 30);
    if (rc >= 0) {
        // La cadena coincide con el formato
        pcre_free(re);
        return 1;
    } else {
        // La cadena no coincide con el formato
        pcre_free(re);
        return 0;
    }
}
