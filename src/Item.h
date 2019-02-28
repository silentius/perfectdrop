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

        /// returns the chance of the first prefix
        int32_t getFirstPrefixChance() const;

        /// returns the first prefix value
        int32_t getFirstPrefix() const;

        /// returns the chance of the second prefix
        int32_t getSecondPrefixChance() const;

        /// returns the second prefix value
        int32_t getSecondPrefix() const;

        /// returns true if the item has prefixes
        bool hasPrefix() const;
    private:
        /// helper method to parse ParserNode
        void parse(ParserNode *node);

        /// parse sub category speciality
        void parseSpeciality(ParserNode *node);
        int32_t m_index = 0;
        QString m_fileName;
        int32_t m_nameId = 0;
        int32_t m_firstPrefixChance = 0;
        int32_t m_firstPrefix = 0;
        int32_t m_secondPrefChance = 0;
        int32_t m_secondPrefix = 0;
        bool m_stackable = false;
};

#endif // ITEM_H
