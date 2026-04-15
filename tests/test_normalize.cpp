#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "file_reader.h"
#include "test_helpers.h"

int main()
{
    // Test 1: Caso normal
    {
        std::vector<double> in {2.0, 3.0, 5.0};
        auto out = normalize_to_unit_range(in);
        std::vector<double> exp {0.0, (3.0-2.0)/(5.0-2.0), 1.0};
        if (!vectors_equal(out, exp)) {
            std::cerr << "Normalizacion Test failed: caso normal\n";
            return 1;
        }
    }

    // Test 2: Caso valores idénticos
    {
        std::vector<double> in {1.0, 1.0, 1.0};
        auto out = normalize_to_unit_range(in);
        std::vector<double> exp {0.0, 0.0, 0.0};
        if (!vectors_equal(out, exp)) {
            std::cerr << "Normalizacion Test failed: valores idénticos\n";
            return 2;
        }
    }

    // Test 3: Caso vacío
    {
        std::vector<double> in;
        auto out = normalize_to_unit_range(in);
        if (!out.empty()) {
            std::cerr << "Normalizacion Test failed: vector vacío debe devolver vacío\n";
            return 3;
        }
    }

    // Test 4: Caso negativos y cero
    {
        std::vector<double> in {-1.0, 0.0, 1.0};
        auto out = normalize_to_unit_range(in);
        std::vector<double> exp {0.0, 0.5, 1.0};
        if (!vectors_equal(out, exp)) {
            std::cerr << "Normalizacion Test failed: negativos y cero\n";
            return 4;
        }
    }

    // Test 5: Normalización - casos normales con negativos, decimales y enteros
    {
        std::vector<double> input = {-5.0, -3.14, 0.0, 2.5, 10.0};
        try {
            auto out = normalize_to_unit_range(input);
            if (out.size() != input.size()) {
                std::cerr << "Test5 failed: tamaño distinto\n";
                return 24;
            }

            // Verificar que todos los valores están en [0,1] (con pequeña tolerancia)
            const double eps = 1e-12;
            for (size_t i = 0; i < out.size(); ++i) {
                if (out[i] < -eps || out[i] > 1.0 + eps) {
                    std::cerr << "Test5 failed: valor fuera de [0,1]: " << out[i] << "\n";
                    return 25;
                }
            }

            // Construir los valores esperados y comparar con tolerancia para double
            double minv = -5.0;
            double maxv = 10.0;
            double denom = maxv - minv;
            std::vector<double> expected;
            expected.reserve(input.size());
            for (double v : input) expected.push_back((v - minv) / denom);

            if (!vectors_equal(out, expected, 1e-9)) {
                std::cerr << "Test5 failed: valores normalizados no coinciden con los esperados\n";
                return 26;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test5 failed with exception: " << e.what() << "\n";
            return 27;
        }
    }

    // Test 6: Normalización - vector vacío -> devolver vector vacío
    {
        std::vector<double> input;
        try {
            auto out = normalize_to_unit_range(input);
            if (!out.empty()) {
                std::cerr << "Test6 failed: normalizar vector vacío devolvió elementos\n";
                return 28;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test6 failed with exception: " << e.what() << "\n";
            return 29;
        }
    }

    // Test 7: Normalización - todos los valores idénticos -> todos ceros
    {
        std::vector<double> input = {5.5, 5.5, 5.5, 5.5};
        try {
            auto out = normalize_to_unit_range(input);
            std::vector<double> expected(input.size(), 0.0);
            if (!vectors_equal(out, expected)) {
                std::cerr << "Test7 failed: valores idénticos no normalizados a ceros\n";
                return 30;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test7 failed with exception: " << e.what() << "\n";
            return 31;
        }
    }

    // Test 8: Lectura - números extremos pero dentro de rango (1e308, 1e307)
    {
        const std::string f = "tmp_extreme_large.txt";
        write_file(f, "1e308 1e307");
        try {
            auto v = read_real_numbers_from_file(f);
            std::vector<double> expected {1e308, 1e307};
            if (!vectors_equal(v, expected, 1e-12)) {
                std::cerr << "Test8 failed: lectura de números extremos no coincide\n";
                return 32;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test8 failed with exception: " << e.what() << "\n";
            return 33;
        }
    }

    // Test 9: Normalización - rango muy grande (1e-308 .. 1e308)
    {
        std::vector<double> input = {1e-308, 1e308};
        try {
            auto out = normalize_to_unit_range(input);
            if (out.size() != input.size()) {
                std::cerr << "Test9 failed: tamaño distinto\n";
                return 34;
            }
            // Esperamos aproximación a {0.0, 1.0}
            if (!double_equal(out[0], 0.0, 1e-12) || !double_equal(out[1], 1.0, 1e-12)) {
                std::cerr << "Test9 failed: normalización en rango extremo produjo valores inesperados: "
                          << out[0] << ", " << out[1] << "\n";
                return 35;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test9 failed with exception: " << e.what() << "\n";
            return 36;
        }
    }

    std::cout << "All normalization tests passed\n";
    return 0;
}
