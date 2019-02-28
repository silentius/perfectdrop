#ifndef ITEM_H
#define ITEM_H

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

        /// returns the name id
        int32_t getNameId() const;

        /// returns the full path to the image file
        const QString &getFileName() const;

        /// if true, item is stackable
        bool isStackable() const;
    private:
        /// helper method to parse ParserNode
        void parse(ParserNode *node);
        int32_t m_index = 0;
        QString m_fileName;
        int32_t m_nameId;
        bool m_stackable = false;
};

#endif // ITEM_H
