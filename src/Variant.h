#ifndef VARIANT_H
#define VARIANT_H

#include <QString>
#include <cstdint>

class Variant {
    public:
        /// contructor
        Variant(const QString &var);

        /// copy contructor
        Variant(const Variant &var);

        /// returns true if the Variant is not set
        bool isNull() const;

        /// returns Variant as int
        int32_t toInt32() const;

        /// returns Variant as string
        const QString &toString() const;
    private:
        QString m_variable;
};

#endif // VARIANT_H
