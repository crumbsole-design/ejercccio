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

#endif // FILE_READER_H
