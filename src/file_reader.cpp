#include "file_reader.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

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

std::vector<double> calculate_distribution_by_intervals(const std::vector<double>& normalized)
{
    constexpr std::size_t kIntervals = 10;
    std::vector<double> distribution;
    if (normalized.empty()) {
        return distribution;
    }

    distribution.assign(kIntervals, 0.0);

    for (double v : normalized) {
        double val = v;
        if (val < 0.0) val = 0.0;
        if (val > 1.0) val = 1.0;

        std::size_t idx;
        if (val == 1.0) {
            idx = kIntervals - 1;
        } else {
            idx = static_cast<std::size_t>(val * static_cast<double>(kIntervals));
            if (idx >= kIntervals) idx = kIntervals - 1;
        }

        distribution[idx] += 1.0;
    }

    const double n = static_cast<double>(normalized.size());
    for (double& x : distribution) {
        x /= n;
    }

    // Ajuste por errores de redondeo para garantizar suma = 1.0
    double sum = 0.0;
    for (double x : distribution) sum += x;
    const double diff = 1.0 - sum;
    if (std::abs(diff) > 0.0) {
        distribution.back() += diff;
    }

    return distribution;
}

std::string format_distribution_as_string(const std::vector<double>& distribution)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);

    const std::size_t n = distribution.size();
    // Determine width for aligned indices (digits of last index)
    std::size_t width = 1;
    if (n > 0) {
        std::size_t max_index = n - 1;
        std::size_t tmp = max_index;
        while (tmp >= 10) {
            tmp /= 10;
            ++width;
        }
    }

    for (std::size_t i = 0; i < n; ++i) {
        oss << std::setw(static_cast<int>(width)) << i << ": " << distribution[i] << '\n';
    }

    return oss.str();
}

void print_distribution_to_console(const std::string& distribution_str)
{
    std::cout << distribution_str;
}
