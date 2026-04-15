#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>

inline bool double_equal(double x, double y, double eps = 1e-9)
{
    if (std::isnan(x) && std::isnan(y)) return true;
    if (std::isinf(x) || std::isinf(y)) return x == y;
    double diff = std::fabs(x - y);
    if (diff <= eps) return true;
    double maxabs = std::max(1.0, std::max(std::fabs(x), std::fabs(y)));
    return diff <= eps * maxabs;
}

inline bool vectors_equal(const std::vector<double>& a, const std::vector<double>& b, double eps = 1e-9)
{
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (!double_equal(a[i], b[i], eps)) return false;
    }
    return true;
}

inline void write_file(const std::string& path, const std::string& content)
{
    std::ofstream ofs(path);
    ofs << content;
}

#endif // TEST_HELPERS_H
