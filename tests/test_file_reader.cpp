#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include "file_reader.h"
#include "test_helpers.h"

int main()
{
    // Test 1: archivo con varios números (decimales, negativos, signos, notación científica)
    {
        const std::string f = "tests/fixtures/tmp_test_numbers_mixed.txt";
        write_file(f, "1.5 2.0\n-3.14e2 4.5 +2 .5 2. 6.022e23 1E-3 -0.5 -0");
        try {
            auto v = read_real_numbers_from_file(f);
            std::vector<double> expected {1.5, 2.0, -314.0, 4.5, 2.0, 0.5, 2.0, 6.022e23, 0.001, -0.5, -0.0};
            if (!vectors_equal(v, expected)) {
                std::cerr << "Test1 failed: contenido leído no coincide\n";
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test1 failed with exception: " << e.what() << "\n";
            return 2;
        }
    }

    // Test 2: archivo inexistente -> runtime_error
    {
        const std::string missing = "this_file_should_not_exist_12345.txt";
        try {
            auto v = read_real_numbers_from_file(missing);
            (void)v;
            std::cerr << "Test2 failed: no se lanzó excepción para archivo inexistente\n";
            return 3;
        } catch (const std::runtime_error&) {
            // OK
        } catch (const std::exception& e) {
            std::cerr << "Test2 failed: excepción inesperada: " << e.what() << "\n";
            return 4;
        }
    }

    // Test 3: archivo vacío -> vector vacío
    {
        const std::string f = "tests/fixtures/tmp_empty.txt";
        write_file(f, "");
        try {
            auto v = read_real_numbers_from_file(f);
            if (!v.empty()) {
                std::cerr << "Test3 failed: archivo vacío devolvió elementos\n";
                return 5;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test3 failed with exception: " << e.what() << "\n";
            return 6;
        }
    }

    // Test 4: dato inválido (texto) -> invalid_argument con token en el mensaje
    {
        const std::string f = "tests/fixtures/tmp_invalid_text.txt";
        write_file(f, "1.5 abc 2.0");
        try {
            auto v = read_real_numbers_from_file(f);
            (void)v;
            std::cerr << "Test4 failed: no se lanzó std::invalid_argument para token inválido\n";
            return 7;
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            if (msg.find("abc") == std::string::npos) {
                std::cerr << "Test4 failed: mensaje de excepción no contiene el token problemático: '" << msg << "'\n";
                return 8;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test4 failed: excepción inesperada: " << e.what() << "\n";
            return 9;
        }
    }

    // Test 5: dato inválido (símbolos) -> invalid_argument
    {
        const std::string f = "tests/fixtures/tmp_invalid_symbols.txt";
        write_file(f, "$ % &");
        try {
            auto v = read_real_numbers_from_file(f);
            (void)v;
            std::cerr << "Test5 failed: no se lanzó std::invalid_argument para símbolos inválidos\n";
            return 10;
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            if (msg.find("$") == std::string::npos && msg.find("%") == std::string::npos) {
                std::cerr << "Test5 failed: mensaje de excepción no contiene el token problemático: '" << msg << "'\n";
                return 11;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test5 failed: excepción inesperada: " << e.what() << "\n";
            return 12;
        }
    }

    // Test 6: dato con coma como separador -> invalid_argument ("1,234")
    {
        const std::string f = "tests/fixtures/tmp_number_comma.txt";
        write_file(f, "1,234 5.6");
        try {
            auto v = read_real_numbers_from_file(f);
            (void)v;
            std::cerr << "Test6 failed: no se lanzó std::invalid_argument para token con coma\n";
            return 13;
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            if (msg.find("1,234") == std::string::npos) {
                std::cerr << "Test6 failed: mensaje de excepción no contiene '1,234' -> '" << msg << "'\n";
                return 14;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test6 failed: excepción inesperada: " << e.what() << "\n";
            return 15;
        }
    }

    // Test 7: número fuera de rango -> invalid_argument
    {
        const std::string f = "tests/fixtures/tmp_out_of_range.txt";
        write_file(f, "1e400");
        try {
            auto v = read_real_numbers_from_file(f);
            (void)v;
            std::cerr << "Test7 failed: no se lanzó std::invalid_argument para número fuera de rango\n";
            return 16;
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            if (msg.find("1e400") == std::string::npos) {
                std::cerr << "Test7 failed: mensaje de excepción no contiene '1e400' -> '" << msg << "'\n";
                return 17;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test7 failed: excepción inesperada: " << e.what() << "\n";
            return 18;
        }
    }

    // Test 8: token con letras al final -> invalid_argument
    {
        const std::string f = "tests/fixtures/tmp_trailing_letters.txt";
        write_file(f, "3.5abc");
        try {
            auto v = read_real_numbers_from_file(f);
            (void)v;
            std::cerr << "Test8 failed: no se lanzó std::invalid_argument para token '3.5abc'\n";
            return 19;
        } catch (const std::invalid_argument& e) {
            std::string msg = e.what();
            if (msg.find("3.5abc") == std::string::npos) {
                std::cerr << "Test8 failed: mensaje de excepción no contiene '3.5abc' -> '" << msg << "'\n";
                return 20;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test8 failed: excepción inesperada: " << e.what() << "\n";
            return 21;
        }
    }

    // Test 9: archivo con solo espacios/tabulaciones -> vector vacío
    {
        const std::string f = "tests/fixtures/tmp_whitespace.txt";
        write_file(f, "   \n\t  ");
        try {
            auto v = read_real_numbers_from_file(f);
            if (!v.empty()) {
                std::cerr << "Test9 failed: archivo con solo espacios devolvió elementos\n";
                return 22;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test9 failed with exception: " << e.what() << "\n";
            return 23;
        }
    }


    std::cout << "All tests passed\n";
    return 0;
}
