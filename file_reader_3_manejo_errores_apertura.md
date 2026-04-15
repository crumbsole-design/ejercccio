Agregar manejo de error para el caso en que el archivo no pueda abrirse. La función debe lanzar una excepción estándar (`std::runtime_error`) con un mensaje descriptivo si la apertura falla.

**Criterios de aceptación:**
- Si el archivo no existe o no puede abrirse, se lanza `std::runtime_error`.
- El mensaje de la excepción indica el problema de apertura.
- El comportamiento está cubierto por pruebas unitarias.
