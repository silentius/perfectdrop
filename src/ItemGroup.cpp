#include "ItemGroup.h"
#include "ParserNode.h"
#include "Database.h"
#include "Variant.h"
#include <QDebug>

ItemGroup::EntryMap ItemGroup::m_groups;
ItemGroup::ItemGroup() {
}

ItemGroup::~ItemGroup() {
    // pretty much aware that this is ugly but
    // it solves soo many issues :-)
    /*if (!ItemGroup::m_groups.empty()) {
        for (auto entry : ItemGroup::m_groups) {
            delete(entry);
        }
        ItemGroup::m_groups.clear();
    }*/
}

void ItemGroup::init(ParserNode *node, const Database &db) {
    const QString type(node->pop().toString());
    if (type == "group") {
        while(node->hasNext()) {
            parseGroup(node, db);
        }
    } else if (type == "itemgroup") {
        while(node->hasNext()) {
            parseItemGroup(node->getNext());
        }
    } else {
        return;
    }
}

void ItemGroup::parseGroup(ParserNode *node, const Database &db) {
    Group *nextGroup = new Group;
    nextGroup->init(node, db);
    m_groups.insert(nextGroup->getGroupId(), nextGroup);
}

void ItemGroup::parseItemGroup(ParserNode *node) {
    const QString type(node->pop().toString());
    if (type == "index") {
        m_itemGroupId = node->pop().toInt32();
    } else if (type == "group") {
        while(node->hasNext()) {
            parseItemGroupEntry(node->getNext());
        }
    }
}

void ItemGroup::parseItemGroupEntry(ParserNode *node) {
    const int32_t chance = node->pop().toInt32();
    const int32_t index = node->pop().toInt32();
    add(chance, m_groups[index]);
}

void ItemGroup::add(int32_t chance, Group *group) {
    m_entries.insert(chance, group);
}

const Group::Entry *ItemGroup::getItem() const {
    const int32_t rndVal(1+(qrand()%1000));
    EntryMap::const_iterator itr(m_entries.begin());
    const EntryMap::const_iterator itrE(m_entries.end());
    for (; itr != itrE; ++itr) {
        if (rndVal <= itr.key()) {
            return itr.value()->getItem();
        }
    }
    return nullptr;
}

int32_t ItemGroup::getItemGroupId() const {
    return m_itemGroupId;
}
