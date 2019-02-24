#ifndef DATABASE_H
#define DATABASE_H

#include "Globals.h"
#include "Group.h"
#include <QHash>

class Item;
class ParserNode;
class ItemGroup;
class Database {
    public:
        using Items = QHash <int32_t, Item *>;
        using ItemGroups = QHash <int32_t, ItemGroup *>;
    public:
        /// constructor
        Database();

        /// called only once to load all data
        bool init();

        /// returns the item name for a given id
        const QString &getName(int32_t index) const;

        /// returns the description for a given id
        const QString &getDesc(int32_t index) const;

        // returns the prefix name for a given id
        const QString &getPrefix(int32_t index) const;

        /// returns the itemGroupName for a given id
        const QString &getItemGroupName(int32_t index) const;

        /// returns the itemGroupId for a given name
        int32_t getItemGroupIdFromName(const QString &name) const;

        /// returns the item for a given id
        const Item *getItem(int32_t index) const;

        /// returns the result of a random selection using ItemGroup.txt data
        const Group::Entry *selectItem(int32_t itemGroupId) const;

        /// returns the path to the game files
        const QString &getPathToGame() const;

        /// reloads itemGroups file if called
        void reloadItemGroups();

        /// returns the ItemGroup hash
        const ItemGroups &getItemGroups() const;
    private:
        /// helper method for parsing keyvalue iformation and update IdStringHash
        void genericAddToHash(ParserNode *node);

        /// used to parse the message.dat information
        void parseMessageDat(const QString &fileName);

        /// used to parse the group names file
        void parseItemGroupNames(const QString &name);

        /// used to parse InitItem.txt
        void parseItems(const QString &pathToServer);

        /// used to parse ItemGroup.txt
        void parseItemGroups(const QString &pathToServer);

        const QString m_defaultString;
        QString m_pathToGame;
        QString m_pathToServer;

        globals::IdStringHash m_names;
        globals::IdStringHash m_descriptions;
        globals::IdStringHash m_prefixes;
        globals::IdStringHash m_itemGroupNames;
        globals::StringIdHash m_itemGroupIds;
        Items m_items;
        ItemGroups m_itemGroups;

};

#endif // DATABASE_H
