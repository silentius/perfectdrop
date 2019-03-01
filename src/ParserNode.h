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

#ifndef PARSERNODE_H
#define PARSERNODE_H

#include <QString>
#include <list>
#include <cstdint>
#include <memory>

class Variant;
class ParserNode {
        friend class Parser;
    public:
        using VariantList = std::list <Variant>;
        using NodeList = std::list <ParserNode*>;
        /// returns true if a sub node exists
        bool hasNext() const;

        /// returns the next sub node
        ParserNode *getNext();

        /// returns a list of all variables in the current node
        VariantList &getList();

        /// removes and returns the next Variant
        Variant pop();

        /// returns true if variable list is empty
        bool empty() const;
    private:
        /// called by Parser to add a node
        void addNode(ParserNode *next);

        /// called by Parser to a a variable
        void add(const QString &var);

        VariantList m_list;
        NodeList m_nodes;
};

#endif // PARSERNODE_H
