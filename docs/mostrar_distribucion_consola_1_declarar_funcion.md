#### [SPEC_JSON]
```json
{
  "slice_id": "mostrar_distribucion_consola",
  "task_id": "1",
  "signature": {
    "function_name": "print_distribution_to_console",
    "parameters": [
      {"name": "distribution", "type": "const std::vector<double>&", "source": "include/file_reader.h"}
    ],
    "return_type": "void"
  },
  "contracts": {
    "dependencies": [
      {"object": "format_distribution_as_string", "method": "", "returns": "std::string", "is_mockable": false}
    ]
  },
  "tdd_requirements": {
    "test_file": "tests/test_distribution.cpp",
    "expected_behavior": "Imprime en consola el string formateado de la distribución. No modifica la lógica de formateo ni cálculo."
  }
}
```

#### [DATOS DE INTERCAMBIO]
- Entrada: const std::vector<double>& distribution
- Salida: impresión en consola (std::cout)

#### [PROMPT PARA EL PROGRAMADOR]
> **Rol**: Programador Especialista.
> **Tarea**: Declarar la función de impresión en include/file_reader.h.
> **Archivos a modificar/crear**: include/file_reader.h
> **Instrucciones**:
> - Declarar la función `print_distribution_to_console` con la firma exacta y documentación Doxygen.
> - La función debe imprimir en consola el string devuelto por `format_distribution_as_string`.
> - No modificar lógica de formateo ni cálculo.
> **Restricciones**: Solo declaración y documentación.

#### [DEFINITION OF DONE]
- [ ] El header declara la función y la documenta.
- [ ] Cumple estilo y formato del proyecto.
