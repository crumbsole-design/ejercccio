#### [SPEC_JSON]
```json
{
  "slice_id": "mostrar_distribucion_consola",
  "task_id": "2",
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
> **Tarea**: Implementar la función de impresión en src/file_reader.cpp.
> **Archivos a modificar/crear**: src/file_reader.cpp
> **Instrucciones**:
> - Implementar la función `print_distribution_to_console` según la firma y documentación.
> - Debe llamar a `format_distribution_as_string` y mostrar el resultado en consola con `std::cout`.
> - No modificar lógica de formateo ni cálculo.
> **Restricciones**: Solo implementación, no modificar otros archivos.

#### [DEFINITION OF DONE]
- [ ] La función imprime correctamente el string formateado.
- [ ] Cumple estilo y formato del proyecto.
- [ ] No hay efectos colaterales ni salida adicional.