#include "Item.h"
#include "ParserNode.h"
#include "Variant.h"
#include <QPainter>
#include <QDebug>

Item::Item(QWidget *parent) : QWidget(parent) {
    setFixedSize(32,32);
}

void Item::init(ParserNode *node) {
    if (node->pop().toString() != "item") {
        return;
    }
    while(node->hasNext()) {
        parse(node->getNext());
    }
}

void Item::parse(ParserNode *node) {
    const QString name(node->pop().toString());
    if (name == "Index") {
        m_index = node->pop().toInt32();
    } else if (name == "Image") {
        m_fileName = node->pop().toString();
    } else if (name == "name") {
        m_nameId = node->pop().toInt32();
    } else if (name == "plural") {
        m_stackable = node->pop().toInt32() == 1;
    } else if (name == "specialty") {
        while(node->hasNext()) {
            parseSpeciality(node->getNext());
        }
    }
}

void Item::parseSpeciality(ParserNode *node) {
    const QString name(node->pop().toString());
    if (name == "Changeprefix") {
        node->pop(); // skip kind because we really don't care
        m_firstPrefixChance = node->pop().toInt32();
        m_firstPrefix = node->pop().toInt32();
        m_secondPrefChance = node->pop().toInt32();
        m_secondPrefix = node->pop().toInt32();
    }
}

int32_t Item::getIndex() const {
    return m_index;
}

int32_t Item::getNameId() const {
    return m_nameId;
}

const QString &Item::getFileName() const {
    return m_fileName;
}

bool Item::isStackable() const {
    return m_stackable;
}

int32_t Item::getFirstPrefixChance() const {
    return m_firstPrefixChance;
}

int32_t Item::getFirstPrefix() const {
    return m_firstPrefix;
}

int32_t Item::getSecondPrefixChance() const {
    return m_secondPrefChance;
}

int32_t Item::getSecondPrefix() const {
    return m_secondPrefix;
}

bool Item::hasPrefix() const {
    return getFirstPrefix() && getSecondPrefix();
}
