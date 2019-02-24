#include "ParserNode.h"
#include "Variant.h"
#include <iostream>

bool ParserNode::hasNext() const {
    return !m_nodes.empty();
}

ParserNode *ParserNode::getNext() {
    if (!hasNext()) {
        return nullptr;
    }
    ParserNode *node = m_nodes.front();
    m_nodes.pop_front();
    return node;
}

ParserNode::VariantList &ParserNode::getList() {
    return m_list;
}

void ParserNode::addNode(ParserNode *next) {
    m_nodes.push_back(next);
}

void ParserNode::add(const QString &var) {
    m_list.push_back(var);
}

Variant ParserNode::pop() {
    if (empty()) {
        return Variant("0");
    }
    Variant tmpVar = m_list.front();
    m_list.pop_front();
    return tmpVar;
}

bool ParserNode::empty() const {
    return m_list.empty();
}
