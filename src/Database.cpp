#include "Database.h"
#include "Parser.h"
#include "ParserNode.h"
#include "Variant.h"
#include "Item.h"
#include "ItemGroup.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

Database::Database() : m_defaultString("") {
}

bool Database::init() {
    //QFile myConfig("PerfectDrop.cfg");
    QFile myConfig("A:\\KalOnlineDevelopment\\Perfect Drop\\PerfectDrop.cfg");
    if (!myConfig.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr,"File not found error",
                             QString("Unable to open %1!").arg(myConfig.fileName()));
        return false;
    }
    QString pathToMsgDat;
    QString pathToItemGroupNames;
    while (!myConfig.atEnd()) {
        QString line = myConfig.readLine();
        QStringList list = line.split("=");
        if (list.count() < 2) {
            continue;
        }
        if (list.at(0) == "PathToGame") {
            m_pathToGame = list.at(1).trimmed();
        } else if (list.at(0) == "PathToServer") {
            m_pathToServer = list.at(1).trimmed();
        } else if (list.at(0) == "MessageDat") {
            pathToMsgDat = list.at(1).trimmed();
        } else if (list.at(0) == "ItemGroupNames") {
            pathToItemGroupNames  = list.at(1).trimmed();
        }
    }
    if (m_pathToGame.isEmpty() || m_pathToServer.isEmpty()
            || pathToMsgDat.isEmpty() || pathToItemGroupNames.isEmpty()) {
        QMessageBox::warning(nullptr,"Config not valid",
                             "At least one parameter is missing!");
        return false;
    }
    parseMessageDat(pathToMsgDat);
    parseItemGroupNames(pathToItemGroupNames);
    parseItems(m_pathToServer);
    return true;
}

void Database::reloadItemGroups() {
    for (auto itemGroup : m_itemGroups) {
        delete(itemGroup);
    }
    m_itemGroups.clear();
    parseItemGroups(m_pathToServer);
}

const Database::ItemGroups &Database::getItemGroups() const {
    return m_itemGroups;
}

void Database::genericAddToHash(ParserNode *node) {
    const QString nodeName(node->pop().toString());
    const int32_t key(node->pop().toInt32());
    const QString value(node->pop().toString());
    if (nodeName == "itemname" || nodeName == "itemdesc" || nodeName == "prefixname") {
        if (nodeName == "itemname") {
            m_names[key] = value;
        } else if (nodeName == "itemdesc") {
            m_descriptions[key] = value;
        } else if (nodeName == "prefixname") {
            m_prefixes[key] = value;
        }
    }
}

void Database::parseMessageDat(const QString &fileName) {
    Parser parser;
    parser.parse("dontcare", fileName.toStdString());
    ParserNode *node = parser.getRoot("dontcare");
    if (node == nullptr) {
        return;
    }
    while (node->hasNext()) {
        genericAddToHash(node->getNext());
    }
}

void Database::parseItemGroupNames(const QString &name) {
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr,"File not found error",
                             QString("Unable to open %1!").arg(name));
        exit(1);
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line(in.readLine());
        if (line.length() == 0 || line.at(0) == '#') {
            continue;
        }
        QStringList values(line.split('=', QString::SkipEmptyParts));
        if (values.count() != 2) {
            continue;
        }
        m_itemGroupNames[values.at(0).toInt()] = values.at(1);
        m_itemGroupIds[values.at(1)] = values.at(0).toInt();
    }
}

int32_t Database::getItemGroupIdFromName(const QString &name) const {
    return m_itemGroupIds[name];
}

void Database::parseItems(const QString &pathToServer) {
    Parser parser;
    parser.parse("dontcare",
                 QString("%1/Config/InitItem.txt").arg(pathToServer).toStdString());
    ParserNode *node = parser.getRoot("dontcare");
    if (node == nullptr) {
        return;
    }
    while (node->hasNext()) {
        Item *item = new Item(nullptr);
        item->init(node->getNext());
        m_items[item->getIndex()] = item;
    }
}

void Database::parseItemGroups(const QString &pathToServer) {
    Parser parser;
    parser.parse("dontcare",
                 QString("%1/Config/ItemGroup.txt").arg(pathToServer).toStdString());
    ParserNode *node = parser.getRoot("dontcare");
            ItemGroup *itemGroup = new ItemGroup;
    while (node->hasNext()) {
        itemGroup->init(node->getNext(), *this);
        if (itemGroup->getItemGroupId() != 0) {
            m_itemGroups.insert(itemGroup->getItemGroupId(), itemGroup);
            itemGroup = new ItemGroup;
        }
    }
    if (itemGroup->getItemGroupId() != 0) {
        m_itemGroups.insert(itemGroup->getItemGroupId(), itemGroup);
    } else {
        delete(itemGroup);
    }
}

const QString &Database::getName(int32_t index) const {
    globals::IdStringHash::const_iterator itr(m_names.find(index));
    if (itr != m_names.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getDesc(int32_t index) const {
    globals::IdStringHash::const_iterator itr(m_descriptions.find(index));
    if (itr != m_descriptions.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getPrefix(int32_t index) const {
    globals::IdStringHash::const_iterator itr(m_prefixes.find(index));
    if (itr != m_prefixes.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getItemGroupName(int32_t index) const {
    globals::IdStringHash::const_iterator itr(m_itemGroupNames.find(index));
    if (itr != m_itemGroupNames.end()) {
        return *itr;
    }
    return m_defaultString;
}

const Item *Database::getItem(int32_t index) const {
    return m_items[index];
}

const Group::Entry *Database::selectItem(int32_t itemGroupId) const {
    const ItemGroup *itemGroup = m_itemGroups[itemGroupId];
    if (itemGroup != nullptr) {
        return itemGroup->getItem();
    }
    return nullptr;
}

const QString &Database::getPathToGame() const {
    return m_pathToGame;
}
