#### [SPEC_JSON]
{
  "slice_id": "calcular_distribucion",
  "task_id": "4",
  "signature": {
    "function_name": "calculate_distribution_by_intervals",
    "parameters": [
      {"name": "normalized", "type": "const std::vector<double>&", "source": "include/file_reader.h"}
    ],
    "return_type": "std::vector<double>"
  }
}

#### [DATOS DE INTERCAMBIO]
- Entrada: const std::vector<double>& normalized
- Salida: std::vector<double> (proporciones por intervalo)

#### [DEFINITION OF DONE]
- [x] Compila sin warnings. (verificado con `g++ -std=c++17 -Wall -Wextra -Wpedantic`)
- [x] Todos los tests pasan. (ejecutado `./tests/test_distribution.exe`)
- [x] Tipos y estilo globales correctos.

**Verification**: Compilación y ejecución locales sin warnings; no se modificó la lógica en `src/file_reader.cpp`.