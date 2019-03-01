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

#ifndef ITEM_H
#define ITEM_H

#include <QEvent>
#include <QWidget>

class ParserNode;
class Item : public QWidget {
    public:
        /// constructor
        Item(QWidget *parent);

        /// used to initialize the item
        void init(ParserNode *node);

        /// returns the item index
        int32_t getIndex() const;

        /// returns the name id
        int32_t getNameId() const;

        /// returns the full path to the image file
        const QString &getFileName() const;

        /// if true, item is stackable
        bool isStackable() const;

        /// returns the chance of the first prefix
        int32_t getFirstPrefixChance() const;

        /// returns the first prefix value
        int32_t getFirstPrefix() const;

        /// returns the chance of the second prefix
        int32_t getSecondPrefixChance() const;

        /// returns the second prefix value
        int32_t getSecondPrefix() const;

        /// returns true if the item has prefixes
        bool hasPrefix() const;
    private:
        /// helper method to parse ParserNode
        void parse(ParserNode *node);

        /// parse sub category speciality
        void parseSpeciality(ParserNode *node);
        int32_t m_index = 0;
        QString m_fileName;
        int32_t m_nameId = 0;
        int32_t m_firstPrefixChance = 0;
        int32_t m_firstPrefix = 0;
        int32_t m_secondPrefChance = 0;
        int32_t m_secondPrefix = 0;
        bool m_stackable = false;
};

#endif // ITEM_H
