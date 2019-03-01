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

#include "ParserNode.h"
#include "Variant.h"

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
