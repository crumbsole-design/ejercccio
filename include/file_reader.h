#ifndef FILE_READER_H
#define FILE_READER_H

#include <vector>
#include <string>

/**
 * @file file_reader.h
 * @brief Declaración de utilidades para lectura de números reales desde archivos.
 */

/**
 * @brief Lee números reales desde un fichero de texto.
 *
 * Lee todas las representaciones de números reales presentes en el fichero
 * indicado por @p filename y devuelve un vector con los valores en el mismo
 * orden en que aparecen en el fichero.
 *
 * @param filename Ruta al fichero de entrada.
 * @return std::vector<double> Vector con los números reales leídos.
 */
std::vector<double> read_real_numbers_from_file(const std::string& filename);

/**
 * @brief Normaliza los valores de un vector al rango [0,1].
 *
 * Algoritmo:
 * - Calcula el mínimo (@p min) y el máximo (@p max) de todos los elementos en @p y.
 * - Para cada elemento \f$ x \f$ en @p y computa: \f$ (x - min) / (max - min) \f$.
 * - Si \f$ max == min \f$ (es decir, todos los valores son idénticos), se devuelve
 *   un vector del mismo tamaño con todos los elementos igual a `0.0` para evitar
 *   la división por cero. Esta elección representa la ausencia de variación entre
 *   los elementos y garantiza un resultado determinista.
 *
 * Comportamiento adicional:
 * - El orden de los elementos se conserva.
 * - No se modifica el vector de entrada.
 *
 * @param y Vector de entrada con valores reales.
 * @return std::vector<double> Nuevo vector con los valores normalizados en [0,1].
 *
 * @example
 * std::vector<double> datos = {2.0, 3.0, 5.0};
 * auto normalizados = normalize_to_unit_range(datos); // {0.0, 0.333333, 1.0}
 */
std::vector<double> normalize_to_unit_range(const std::vector<double>& y);

/**
 * @brief Calcula la distribución de proporciones por intervalos a partir de valores normalizados.
 *
 * Dado un vector @p normalized con valores en el rango [0,1], esta función calcula
 * la proporción de elementos que caen en cada intervalo de una partición uniforme
 * del rango [0,1]. La función no modifica el vector de entrada.
 *
 * Notas de precondición:
 * - Se asume que todos los valores en @p normalized están dentro de [0,1].
 * - Si @p normalized está vacío, la función devuelve un vector vacío.
 *
 * Comportamiento esperado (contrato):
 * - La partición exacta de intervalos y el número de intervalos se definen en la
 *   implementación; esta declaración solo especifica la interfaz y el contrato.
 * - La suma de las proporciones en el vector devuelto deberá ser igual a 1.0
 *   cuando @p normalized no esté vacío (comportamiento garantizado por la
 *   implementación).
 *
 * @param normalized Vector con valores normalizados en [0,1].
 * @return std::vector<double> Vector con las proporciones por intervalo.
 */
std::vector<double> calculate_distribution_by_intervals(const std::vector<double>& normalized);

/**
 * @brief Formatea una distribución de proporciones como una cadena de texto.
 *
 * Genera una representación textual de la distribución dada en @p distribution.
 * Cada intervalo se imprime en una línea separada con el índice del intervalo
 * alineado y el valor formateado con cuatro decimales.
 *
 * Formato de salida (ejemplo):
 * - Para una distribución {0.25, 0.75} el resultado sería:
 *   "0: 0.2500\n1: 0.7500\n"
 *
 * Detalles de formato:
 * - Una línea por intervalo.
 * - El índice del intervalo aparece al inicio de la línea.
 * - El valor de la proporción se muestra con exactamente 4 decimales.
 * - La función NO imprime en consola; devuelve la cadena resultante.
 *
 * @param distribution Vector con las proporciones por intervalo. Se asume
 *        que los valores representan proporciones (la suma puede aproximarse a 1.0).
 * @return std::string Cadena con la representación formateada, con un salto de
 *         línea al final de cada intervalo.
 *
 * @example
 * std::vector<double> d = {0.25, 0.75};
 * auto out = format_distribution_as_string(d);
 * // out == "0: 0.2500\n1: 0.7500\n"
 */
std::string format_distribution_as_string(const std::vector<double>& distribution);

/**
 * @brief Muestra en consola la representación de una distribución.
 *
 * Recibe una cadena ya formateada que representa la distribución de
 * proporciones y la imprime en la salida estándar (`std::cout`). La
 * función no modifica la cadena de entrada y se limita a escribirla
 * seguida de un salto de línea.
 *
 * @note La función solo declara la interfaz; la implementación
 *       se encuentra en el fichero fuente correspondiente.
 *
 * @param distribution_str Cadena con la representación formateada de la distribución.
 */
void print_distribution_to_console(const std::string& distribution_str);

#endif // FILE_READER_H

