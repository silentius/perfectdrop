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

#include "ItemGroup.h"
#include "ParserNode.h"
#include "Database.h"
#include "Variant.h"
#include <QDebug>

ItemGroup::EntryMap ItemGroup::m_groups;
ItemGroup::ItemGroup() {
}

ItemGroup::~ItemGroup() {
}

void ItemGroup::init(ParserNode *node, const Database &db) {
    const QString type(node->pop().toString());
    if (type == "group") {
        while(node->hasNext()) {
            parseGroup(node, db);
        }
    } else if (type == "itemgroup") {
        while(node->hasNext()) {
            parseItemGroup(node->getNext(), db);
        }
    } else {
        return;
    }
}

void ItemGroup::deleteGroups() {
    for (auto group : m_groups) {
        delete(group);
    }
    m_groups.clear();
}

void ItemGroup::parseGroup(ParserNode *node, const Database &db) {
    Group *nextGroup = new Group;
    nextGroup->init(node, db);
    m_groups.insert(nextGroup->getGroupId(), nextGroup);
}

void ItemGroup::parseItemGroup(ParserNode *node, const Database &db) {
    const QString type(node->pop().toString());
    if (type == "index") {
        m_itemGroupId = node->pop().toInt32();
    } else if (type == "group") {
        while(node->hasNext()) {
            parseItemGroupEntry(node->getNext(), db);
        }
    }
}

void ItemGroup::parseItemGroupEntry(ParserNode *node, const Database &db) {
    const int32_t chance = node->pop().toInt32();
    const int32_t index = node->pop().toInt32();
    Group *group(m_groups[index]);
    if (group == nullptr) {
        db.logError(QString("group: %1 does not exist in itemgroup: %2")
                    .arg(index).arg(m_itemGroupId));
    }
    add(chance, group);
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
            if (itr.value() != nullptr) {
                return itr.value()->getItem();
            }
            break;
        }
    }
    return nullptr;
}

int32_t ItemGroup::getItemGroupId() const {
    return m_itemGroupId;
}
