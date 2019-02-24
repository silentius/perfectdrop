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
    } else if (name == "sell") {
        m_sell = node->pop().toInt32();
    } else if (name == "buy") {
        m_buy = node->pop().toInt32();
    } else if (name == "plural") {
        m_stackable = node->pop().toInt32() == 1;
    }
}

int32_t Item::getIndex() const {
    return m_index;
}

const QString &Item::getFileName() const {
    return m_fileName;
}

bool Item::isStackable() const {
    return m_stackable;
}
