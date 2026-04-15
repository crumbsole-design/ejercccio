Agregar manejo de error para el caso en que el archivo contenga datos no convertibles a número real. La función debe lanzar una excepción estándar (`std::invalid_argument`) si encuentra un token inválido.

**Criterios de aceptación:**
- Si algún dato no es convertible a double, se lanza `std::invalid_argument`.
- El mensaje de la excepción indica el token problemático.
- El comportamiento está cubierto por pruebas unitarias.