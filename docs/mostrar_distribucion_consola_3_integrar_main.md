#### [SPEC_JSON]
```json
{
  "slice_id": "mostrar_distribucion_consola",
  "task_id": "3",
  "signature": {
    "function_name": "main",
    "parameters": [],
    "return_type": "int"
  },
  "contracts": {
    "dependencies": [
      {"object": "print_distribution_to_console", "method": "", "returns": "void", "is_mockable": false},
      {"object": "calculate_distribution_by_intervals", "method": "", "returns": "std::vector<double>", "is_mockable": false},
      {"object": "normalize_to_unit_range", "method": "", "returns": "std::vector<double>", "is_mockable": false},
      {"object": "read_real_numbers_from_file", "method": "", "returns": "std::vector<double>", "is_mockable": false}
    ]
  },
  "tdd_requirements": {
    "test_file": "main_test.cpp",
    "expected_behavior": "Lee archivo, normaliza, calcula distribución, imprime string formateado en consola."
  }
}
```

#### [DATOS DE INTERCAMBIO]
- Entrada: archivo de números reales (string)
- Salida: impresión en consola del string de distribución

#### [PROMPT PARA EL PROGRAMADOR]
> **Rol**: Programador Especialista.
> **Tarea**: Integrar flujo completo en main_test.cpp (o main_console.cpp).
> **Archivos a modificar/crear**: main_test.cpp
> **Instrucciones**:
> - Leer archivo de números reales.
> - Normalizar valores.
> - Calcular distribución por intervalos.
> - Imprimir string formateado usando `print_distribution_to_console`.
> - No mezclar lógica de negocio y presentación.
> **Restricciones**: No modificar funciones puras ni lógica de formateo/cálculo.

#### [DEFINITION OF DONE]
- [ ] El main ejecuta el flujo y muestra el string esperado en consola.
- [ ] No hay efectos colaterales ni lógica duplicada.
 - [x] El main ejecuta el flujo y muestra el string esperado en consola.
 - [x] No hay efectos colaterales ni lógica duplicada.