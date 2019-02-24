#include "Variant.h"
#include <limits>

Variant::Variant(const QString &var) : m_variable(var) {
}

Variant::Variant(const Variant &var) {
    this->m_variable = var.m_variable;
}

bool Variant::isNull() const {
    return m_variable.size() == 0;
}

int32_t Variant::toInt32() const {
    return static_cast <int32_t>(m_variable.toInt());
}

const QString &Variant::toString() const {
    return m_variable;
}
