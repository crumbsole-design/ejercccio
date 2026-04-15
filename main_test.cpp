#include "file_reader.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    // El fichero por defecto contiene una lista mixta de números válidos.
    const std::string default_input = "test_features/tmp_test_numbers_mixed.txt";
    const std::string filename = (argc > 1) ? std::string(argv[1]) : default_input;

    try {
        // 1) Lectura
        const auto values = read_real_numbers_from_file(filename);

        // 2) Normalización
        const auto normalized = normalize_to_unit_range(values);

        // 3) Cálculo de distribución
        const auto distribution = calculate_distribution_by_intervals(normalized);

        // 4) Formateo
        const auto formatted = format_distribution_as_string(distribution);

        // 5) Impresión (presentación separada de la lógica de dominio)
        print_distribution_to_console(formatted);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
