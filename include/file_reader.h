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

#endif // FILE_READER_H
