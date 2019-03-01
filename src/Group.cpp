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

#include "Group.h"
#include "ParserNode.h"
#include "Database.h"
#include "Variant.h"
#include "Item.h"
#include <QDebug>

Group::Group() {
}

Group::~Group() {
    for (auto entry : m_entries) {
        delete(entry);
    }
}

void Group::init(ParserNode *node, const Database &db) {
    while(node->hasNext()) {
        parse(node->getNext(), db);
    }
}

void Group::parse(ParserNode *node, const Database &db) {
    const QString type(node->pop().toString());
    if (type == "index") {
        m_groupId = node->pop().toInt32();
    } else if (type == "money") {
        while(node->hasNext()) {
            parseMoney(node->getNext(), db);
        }
    } else if (type == "item") {
        while(node->hasNext()) {
            parseItem(node->getNext(), db);
        }
    }
}

void Group::parseMoney(ParserNode *node, const Database &db) {
    add(node->pop().toInt32(), db.getItem(31), 0, node->pop().toInt32());
}

void Group::parseItem(ParserNode *node, const Database &db) {
    const int32_t chance = node->pop().toInt32();
    const int32_t index = node->pop().toInt32();
    const int32_t prefix = node->pop().toInt32();
    int32_t count = node->pop().toInt32();

    if (count < 1) {
        count = 1;
    }
    const Item *item(db.getItem(index));
    if (!item) {
        db.logError(QString("item index: %1 does not exist in group: %2")
                    .arg(index).arg(m_groupId));

    }
    add(chance, item, prefix, count);
}

int32_t Group::getGroupId() const {
    return m_groupId;
}

void Group::add(int32_t chance, const Item *item,
                int32_t prefix, int32_t count) {
    m_entries.insert(chance, new Group::Entry(item , prefix, count));
}

const Group::Entry *Group::getItem() const {
    const int32_t rndVal(1+(qrand()%1000));
    EntryMap::const_iterator itr(m_entries.begin());
    const EntryMap::const_iterator itrE(m_entries.end());
    for (; itr != itrE; ++itr) {
        if (rndVal <= itr.key()) {
            return itr.value();
        }
    }
    return nullptr;
}
