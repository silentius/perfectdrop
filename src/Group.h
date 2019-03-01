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

#ifndef GROUP_H
#define GROUP_H

#include <cstdint>
#include <QMap>

class Item;
class ParserNode;
class Database;
class Group {
    public:
        /// Entry definition for m_entries
        class Entry {
            public:
                Entry(const Item *_item,
                      int32_t _prefix, int32_t _count)
                            : item(_item), prefix(_prefix),
                              count(_count) {
                }
                const Item *item;
                const int32_t prefix;
                const int32_t count;
        };
        /// constructor
        Group();

        /// destructor
        ~Group();

        /// called to initialize this class
        void init(ParserNode *node, const Database &db);

        /// returns the result of a random selection (item drop)
        const Group::Entry *getItem() const;

        /// return the groupId
        int32_t getGroupId() const;
    private:
        /// helper method used to add entries to m_entries
        void add(int32_t chance, const Item *item,
                 int32_t prefix = 0, int32_t count = 1);

        /// helper method used to parse ParserNode data;
        void parse(ParserNode *node, const Database &db);

        /// helper method used to parse the money section
        void parseMoney(ParserNode *node, const Database &db);

        /// helper method used to parse the item section
        void parseItem(ParserNode *node, const Database &db);

        int32_t m_groupId = 0;
        using EntryMap = QMap <int32_t, Group::Entry*>;
        EntryMap m_entries;
};

#endif // GROUP_H
