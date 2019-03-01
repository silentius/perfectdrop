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
