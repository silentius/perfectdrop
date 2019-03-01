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

#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include "Group.h"
#include <QMap>

class ParserNode;
class Database;
class ItemGroup {
        using EntryMap = QMap <int32_t, Group*>;
    public:
        /// constructor
        ItemGroup();

        /// destructor
        ~ItemGroup();

        /// used to init ItemGroup
        void init(ParserNode *node, const Database &db);

        /// returns the result of a random selection (item drop)
        const Group::Entry *getItem() const;

        /// returns m_itemGroupId
        int32_t getItemGroupId() const;

        /// this method should be called before loading itemgroups
        static void deleteGroups();
    private:
        /// helper method used to fill m_groups
        void add(int32_t chance, Group *group);

        /// helper method used to parse ParserNode
        void parseGroup(ParserNode *node, const Database &db);

        /// helper method used to parse ParserNode
        void parseItemGroup(ParserNode *node, const Database &db);

        /// helper method used to parse ParserNode
        void parseItemGroupEntry(ParserNode *node, const Database &db);

        int32_t m_itemGroupId = 0;
        EntryMap m_entries;
        static EntryMap m_groups;

};

#endif // ITEMGROUP_H
