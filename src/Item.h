#ifndef ITEM_H
#define ITEM_H

#include "Globals.h"
#include <QEvent>
#include <QWidget>

class ParserNode;
class Item : public QWidget {
    public:
        /// constructor
        Item(QWidget *parent);

        /// used to initialize the item
        void init(ParserNode *node);

        /// returns the item index
        int32_t getIndex() const;

        /// returns the full path to the image file
        const QString &getFileName() const;

        /// if true, item is stackable
        bool isStackable() const;
    private:
        /// helper method to parse ParserNode
        void parse(ParserNode *node);
        int32_t m_index = 0;
        QString m_fileName;
        QString name;
        QString desc;
        int32_t m_sell = 0;
        int32_t m_buy = 0;
        bool m_stackable = false;
};

#endif // ITEM_H
