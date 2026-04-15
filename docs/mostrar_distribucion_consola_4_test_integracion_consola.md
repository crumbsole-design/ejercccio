#### [SPEC_JSON]
```json
{
  "slice_id": "mostrar_distribucion_consola",
  "task_id": "4",
  "signature": {
    "function_name": "test_print_distribution_to_console",
    "parameters": [],
    "return_type": "int"
  },
  "contracts": {
    "dependencies": [
      {"object": "print_distribution_to_console", "method": "", "returns": "void", "is_mockable": false},
      {"object": "format_distribution_as_string", "method": "", "returns": "std::string", "is_mockable": false}
    ]
  },
  "tdd_requirements": {
    "test_file": "tests/test_distribution.cpp",
    "expected_behavior": "Captura la salida estándar, ejecuta print_distribution_to_console y compara con el string esperado."
  }
}
```

#### [DATOS DE INTERCAMBIO]
- Entrada: vector de distribución de prueba
- Salida: comparación de salida estándar con string esperado

#### [PROMPT PARA EL PROGRAMADOR]
> **Rol**: Programador Especialista.
> **Tarea**: Escribir test de integración para impresión en consola en tests/test_distribution.cpp.
> **Archivos a modificar/crear**: tests/test_distribution.cpp
> **Instrucciones**:
> - Capturar la salida estándar (stdout) durante la llamada a print_distribution_to_console.
> - Comparar la salida capturada con el string devuelto por format_distribution_as_string.
> - Validar para casos típicos y extremos (vector vacío, todos ceros, valores grandes).
> **Restricciones**: No modificar funciones puras ni lógica de formateo/cálculo.

#### [DEFINITION OF DONE]
- [ ] El test valida que la impresión en consola es idéntica al string esperado.
- [ ] Se cubren casos típicos y extremos.
- [ ] No hay efectos colaterales ni salida adicional.