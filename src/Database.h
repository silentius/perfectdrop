#ifndef DATABASE_H
#define DATABASE_H

#include "Group.h"
#include <QHash>

class Item;
class ParserNode;
class ItemGroup;
class Database {
    public:
        using Items = QHash <int32_t, Item *>;
        using ItemGroups = QHash <int32_t, ItemGroup *>;
        using IdStringHash = QHash <int32_t, QString>;
        using StringIdHash = QHash <QString, int32_t>;
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

        void logError(const QString &error) const;
    private:
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
        QString m_pathToServerConfig;

        IdStringHash m_names;
        IdStringHash m_descriptions;
        IdStringHash m_prefixes;
        IdStringHash m_itemGroupNames;
        StringIdHash m_itemGroupIds;
        Items m_items;
        ItemGroups m_itemGroups;

};

#endif // DATABASE_H
