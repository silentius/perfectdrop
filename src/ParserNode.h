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
