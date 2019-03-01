/// This file is part of PerfectDrop.
///
/// PerfectDrop is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License.
///
/// PerfectDrop is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with PerfectDrop.  If not, see <https://www.gnu.org/licenses/>.

#include "Variant.h"

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
