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
#include <QDir>

Database::Database() : m_defaultString("") {
    QFile::remove("error.log");
}

bool Database::init() {
    QFile myConfig(QString("%1\\PerfectDrop.cfg").arg(QDir::currentPath()));
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
        } else if (list.at(0) == "PathToServerConfig") {
            m_pathToServerConfig = list.at(1).trimmed();
        } else if (list.at(0) == "MessageDat") {
            pathToMsgDat = list.at(1).trimmed();
        } else if (list.at(0) == "ItemGroupNames") {
            pathToItemGroupNames  = list.at(1).trimmed();
        }
    }

    if (m_pathToGame.size() > 0 && !m_pathToGame.endsWith("\\")) {
        m_pathToGame.append("/");
    }
    if (m_pathToServerConfig.size() > 0 && !m_pathToServerConfig.endsWith("\\")) {
        m_pathToServerConfig.append("/");
    }

    parseMessageDat(pathToMsgDat);
    parseItemGroupNames(pathToItemGroupNames);
    parseItems(m_pathToServerConfig);
    return true;
}

void Database::logError(const QString &error) const {
    QFile errorFile("error.log");
    if (errorFile.open(QIODevice::Append | QIODevice::Text | QIODevice::WriteOnly)) {
        QTextStream outputStream(&errorFile);
        outputStream << error << "\n";
        errorFile.close();
    }
    qDebug() << error;
}

void Database::reloadItemGroups() {
    for (auto itemGroup : m_itemGroups) {
        delete(itemGroup);
    }
    m_itemGroups.clear();
    // cleanup the static groups map
    ItemGroup::deleteGroups();
    parseItemGroups(m_pathToServerConfig);
}

const Database::ItemGroups &Database::getItemGroups() const {
    return m_itemGroups;
}

void Database::parseMessageDat(const QString &fileName) {
    // not using node parser because it won't work with this design
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr,"File not found error",QString("Unable to open %1!").arg(fileName));
        exit(1);
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().replace("\t", " ");
        if (line.startsWith(";")) {
           continue;
        }
        QString type_and_index;
        QString val;
        bool inBrackets = false, inVal = false;
        for (auto sign : line) {
            if (sign == '(') {
               inBrackets = true;
            } else if (sign == ')') {
               inBrackets = false;
            } else if (inBrackets) {
                if (sign == '"' && inVal) {
                    inVal = false;
                } else if (sign == '"') {
                    inVal = true;
                } else if (inVal) {
                    val.append(sign);
                } else {
                    type_and_index.append(sign);
                }
            }
        }
        QStringList strList = type_and_index.split(" ");
        strList.removeAll({}); // who wants empty strings :-)
        if (strList.size() < 2) {
            continue;
        }
        const int32_t index = strList[1].toInt();

        if (strList[0] == "itemname" || strList[0] == "itemdesc"
                || strList[0] == "prefixname") {
            if (strList[0] == "itemname") {
                m_names[index] = val;
            } else if (strList[0] == "itemdesc") {
                m_descriptions[index] = val;
            } else if (strList[0] == "prefixname") {
                m_prefixes[index] = val;
            }
        }
    }
    file.close();
}

void Database::parseItemGroupNames(const QString &name) {
    if (name.size() == 0) {
        return; // this is optional so no need to terminate if file is not there
    }
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
                 QString("%1InitItem.txt").arg(pathToServer).toStdString());
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
                 QString("%1ItemGroup.txt").arg(pathToServer).toStdString());
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
    IdStringHash::const_iterator itr(m_names.find(index));
    if (itr != m_names.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getDesc(int32_t index) const {
    IdStringHash::const_iterator itr(m_descriptions.find(index));
    if (itr != m_descriptions.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getPrefix(int32_t index) const {
    IdStringHash::const_iterator itr(m_prefixes.find(index));
    if (itr != m_prefixes.end()) {
        return *itr;
    }
    return m_defaultString;
}

const QString &Database::getItemGroupName(int32_t index) const {
    IdStringHash::const_iterator itr(m_itemGroupNames.find(index));
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
