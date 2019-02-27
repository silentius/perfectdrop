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
        void parseItemGroup(ParserNode *node);

        /// helper method used to parse ParserNode
        void parseItemGroupEntry(ParserNode *node);

        int32_t m_itemGroupId = 0;
        EntryMap m_entries;
        static EntryMap m_groups;

};

#endif // ITEMGROUP_H
