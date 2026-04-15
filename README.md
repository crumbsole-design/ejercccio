establecemos nombres de funciones y variables descriptivos para mejorar la legibilidad del código. Por ejemplo, `read_real_numbers_from_file` es un nombre claro que indica exactamente lo que hace la función.
usaremos verbos de accion para los nombres de funciones, como "read", "open", "convert", etc., para indicar claramente las operaciones que realizan.
opcionalmente añadiremos en el nombre referencias al input y output como "from_file" y "to_vector" para clarificar aun mas el proposito de la funcion.
los nombres de las variables serán descriptivos y seguirán el estilo camelCase o snake_case, dependiendo de la convención que se elija para el proyecto, para mantener la consistencia en el código.



usamos doxygen porque es free y opensource para documentar el código , aunque realmente la documentacion la produce la set de test que se encarga de probar el codigo paso por paso.


usamos la clase vector para almacenar los numeros reales por ser la forma mas sencilla y eficiente.
la clase string para la primera parte cuando se lee debe almacenarse en un contenedor temporal que acepte cualquier tipo de dato , luego se convierte a double y se almacena en el vector final.
para la conversion del string la clase ya nos da un metodo std::stod que es robusto y lanza excepciones si el formato no es correcto, lo que facilita el manejo de errores.

la lectura es primero comprobar que se puede abrir el archivo y luego un loop hasta que finaliza el fichero , leyendo cada linea e intentando el parseo a double, si el parseo falla se lanza una excepcion indicando el token problemático, si el parseo es exitoso se almacena el numero añadiendo al final en un vector de double donde se acumulan los resultados segun el orden de lectura.





para probar los resultados de los test primero creamos un comparador de double robusto. el operador == simple nos podria dar errores debido al redondeo y limitacion de precision.por eso usamos la tecnica del epsilon, en mi caso he usado un valor de 1e-9 para la comparacion, lo que significa que seran considerados iguales si la diferencia absoluta entre ellos es igual o menor a ese valor.
