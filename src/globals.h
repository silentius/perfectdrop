#ifndef GLOBALS_H
#define GLOBALS_H
#include <QString>
#include <QHash>
#include <cstdint>

namespace globals {
    using IdStringHash = QHash <int32_t, QString>;
    using StringIdHash = QHash <QString, int32_t>;
} /// ns globals
#endif // GLOBALS_H
