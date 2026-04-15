#include "file_reader.h"

#include <fstream>
#include <string>
#include <stdexcept>

// Implementación simple y robusta para leer números reales desde un fichero.
std::vector<double> read_real_numbers_from_file(const std::string& filename)
{
    std::vector<double> values;
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string token;
    while (ifs >> token) {
        size_t pos = 0;
        try {
            double v = std::stod(token, &pos);
            if (pos == token.size()) {
                values.push_back(v);
            } else {
                // Token contiene caracteres adicionales -> no es convertible entero
                throw std::invalid_argument("Invalid token: " + token);
            }
        } catch (const std::invalid_argument&) {
            // Re-lanzar incluyendo el token problemático
            throw std::invalid_argument(std::string("Invalid token: ") + token);
        } catch (const std::out_of_range&) {
            // Número fuera de rango para double -> considerarlo inválido
            throw std::invalid_argument(std::string("Invalid token: ") + token);
        }
    }

    return values;
}

// Normaliza los valores al rango [0,1] según la especificación en el header.
std::vector<double> normalize_to_unit_range(const std::vector<double>& y)
{
    std::vector<double> out;
    out.reserve(y.size());

    if (y.empty()) {
        return out; // vector vacío -> devolver vacío
    }

    double minv = y[0];
    double maxv = y[0];
    for (const double v : y) {
        if (v < minv) minv = v;
        if (v > maxv) maxv = v;
    }

    if (maxv == minv) {
        // Todos los valores idénticos: devolver vector del mismo tamaño con ceros.
        out.assign(y.size(), 0.0);
        return out;
    }

    const double denom = maxv - minv;
    for (const double v : y) {
        out.push_back((v - minv) / denom);
    }

    return out;
}
