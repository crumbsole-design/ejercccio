#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include "file_reader.h"
#include "test_helpers.h"
#include <sstream>
#include <cstdio>

int main()
{
    // Test 1: Caso normal - varios valores en diferentes intervalos
    {
        std::vector<double> input {0.05, 0.15, 0.15, 0.95};
        try {
            auto out = calculate_distribution_by_intervals(input);
            if (out.size() != 10) {
                return 41;
            }

            std::vector<double> expected_counts {1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
            const double n = static_cast<double>(input.size());
            std::vector<double> expected;
            expected.reserve(expected_counts.size());
            for (double c : expected_counts) expected.push_back(c / n);

            if (!vectors_equal(out, expected, 1e-12)) {
                return 42;
            }

            double sum = 0.0;
            for (double x : out) sum += x;
            if (!double_equal(sum, 1.0, 1e-12)) {
                return 43;
            }
        } catch (const std::exception&) {
            return 44;
        }
    }

    // Test 2: Caso vector vacío -> devolver vector vacío
    {
        std::vector<double> input;
        try {
            auto out = calculate_distribution_by_intervals(input);
            if (!out.empty()) {
                return 45;
            }
        } catch (const std::exception&) {
            return 46;
        }
    }

    // Test 3: Valores en los bordes exactos: 0.0, 0.1, ..., 1.0
    {
        std::vector<double> input;
        for (int i = 0; i <= 10; ++i) input.push_back(static_cast<double>(i) / 10.0);
        try {
            auto out = calculate_distribution_by_intervals(input);
            if (out.size() != 10) {
                return 47;
            }

            // Esperamos 1 elemento en los primeros 9 intervalos y 2 en el último
            std::vector<double> expected_counts(10, 1.0);
            expected_counts.back() = 2.0;
            const double n = static_cast<double>(input.size());
            std::vector<double> expected;
            expected.reserve(expected_counts.size());
            for (double c : expected_counts) expected.push_back(c / n);

            if (!vectors_equal(out, expected, 1e-12)) {
                return 48;
            }

            double sum = std::accumulate(out.begin(), out.end(), 0.0);
            if (!double_equal(sum, 1.0, 1e-12)) {
                return 49;
            }
        } catch (const std::exception&) {
            return 50;
        }
    }

    // Test 4: Todos los valores idénticos -> toda la masa en un único intervalo
    {
        std::vector<double> input(4, 0.5); // todos mapean al intervalo índice 5
        try {
            auto out = calculate_distribution_by_intervals(input);
            if (out.size() != 10) {
                return 51;
            }

            // Esperamos que la proporción sea 1.0 en el índice correspondiente (0.5 -> idx 5)
            std::vector<double> expected(10, 0.0);
            expected[5] = 1.0;

            if (!vectors_equal(out, expected, 1e-12)) {
                return 52;
            }

            double sum = std::accumulate(out.begin(), out.end(), 0.0);
            if (!double_equal(sum, 1.0, 1e-12)) {
                return 53;
            }
        } catch (const std::exception&) {
            return 54;
        }
    }

    // New tests for format_distribution_as_string
    // Test A: vector vacío -> string vacío
    {
        std::vector<double> dist;
        try {
            auto out = format_distribution_as_string(dist);
            if (!out.empty()) return 61;
        } catch (const std::exception&) {
            return 62;
        }
    }

    // Test B: todos ceros -> comprobación exacta de formato (10 intervalos)
    {
        std::vector<double> dist(10, 0.0);
        const std::string expected =
            "0: 0.0000\n"
            "1: 0.0000\n"
            "2: 0.0000\n"
            "3: 0.0000\n"
            "4: 0.0000\n"
            "5: 0.0000\n"
            "6: 0.0000\n"
            "7: 0.0000\n"
            "8: 0.0000\n"
            "9: 0.0000\n";
        try {
            auto out = format_distribution_as_string(dist);
            if (out != expected) return 63;
        } catch (const std::exception&) {
            return 64;
        }
    }

    // Test C: valores típicos -> 4 decimales exactos y salto de línea final
    {
        std::vector<double> dist {0.1, 0.2555, 12345.6789};
        const std::string expected =
            "0: 0.1000\n"
            "1: 0.2555\n"
            "2: 12345.6789\n";
        try {
            auto out = format_distribution_as_string(dist);
            if (out != expected) return 65;
        } catch (const std::exception&) {
            return 66;
        }
    }

    // Test D: anchura de índices (más de 10 elementos) -> alineación de dos dígitos
    {
        // 11 elementos -> índices de 0 a 10 -> anchura esperada = 2
        std::vector<double> dist(11);
        for (size_t i = 0; i < dist.size(); ++i) dist[i] = static_cast<double>(i) + 0.5; // valores evidentes

        const std::string expected =
            " 0: 0.5000\n"
            " 1: 1.5000\n"
            " 2: 2.5000\n"
            " 3: 3.5000\n"
            " 4: 4.5000\n"
            " 5: 5.5000\n"
            " 6: 6.5000\n"
            " 7: 7.5000\n"
            " 8: 8.5000\n"
            " 9: 9.5000\n"
            "10: 10.5000\n";
        try {
            auto out = format_distribution_as_string(dist);
            if (out != expected) return 67;
        } catch (const std::exception&) {
            return 68;
        }
    }

    // Integration tests: pipeline + captura de salida de consola
    {
        // Caso típico: fichero con 4 números -> distribución conocida
        {
            const std::string f = "tests/fixtures/tmp_integration_print_distribution.txt";
            write_file(f, "1 2 3 4");
            try {
                auto v = read_real_numbers_from_file(f);
                auto normalized = normalize_to_unit_range(v);
                auto dist = calculate_distribution_by_intervals(normalized);
                auto formatted = format_distribution_as_string(dist);

                std::ostringstream oss;
                std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());
                print_distribution_to_console(formatted);
                std::cout.rdbuf(old_buf);

                const std::string captured = oss.str();
                if (captured != formatted) {
                    std::cerr << "Integration typical failed: captured != formatted\n";
                    std::remove(f.c_str());
                    return 71;
                }
                std::remove(f.c_str());
            } catch (const std::exception& e) {
                std::cerr << "Integration typical failed with exception: " << e.what() << "\n";
                std::remove(f.c_str());
                return 72;
            }
        }

        // Caso extremo: fichero vacío -> salida vacía
        {
            const std::string f = "tests/fixtures/tmp_integration_empty.txt";
            write_file(f, "");
            try {
                auto v = read_real_numbers_from_file(f);
                auto normalized = normalize_to_unit_range(v);
                auto dist = calculate_distribution_by_intervals(normalized);
                auto formatted = format_distribution_as_string(dist);

                std::ostringstream oss;
                std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());
                print_distribution_to_console(formatted);
                std::cout.rdbuf(old_buf);

                const std::string captured = oss.str();
                if (captured != formatted) {
                    std::cerr << "Integration empty failed: captured != formatted\n";
                    std::remove(f.c_str());
                    return 73;
                }
                std::remove(f.c_str());
            } catch (const std::exception& e) {
                std::cerr << "Integration empty failed with exception: " << e.what() << "\n";
                std::remove(f.c_str());
                return 74;
            }
        }

        // Caso extremo: todos los valores idénticos -> normalización determinista
        {
            const std::string f = "tests/fixtures/tmp_integration_identical.txt";
            write_file(f, "5 5 5 5");
            try {
                auto v = read_real_numbers_from_file(f);
                auto normalized = normalize_to_unit_range(v);
                auto dist = calculate_distribution_by_intervals(normalized);
                auto formatted = format_distribution_as_string(dist);

                std::ostringstream oss;
                std::streambuf* old_buf = std::cout.rdbuf(oss.rdbuf());
                print_distribution_to_console(formatted);
                std::cout.rdbuf(old_buf);

                const std::string captured = oss.str();
                if (captured != formatted) {
                    std::cerr << "Integration identical failed: captured != formatted\n";
                    std::remove(f.c_str());
                    return 75;
                }
                std::remove(f.c_str());
            } catch (const std::exception& e) {
                std::cerr << "Integration identical failed with exception: " << e.what() << "\n";
                std::remove(f.c_str());
                return 76;
            }
        }
    }

    return 0;
}
