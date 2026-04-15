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
