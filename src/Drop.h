#ifndef DROP_H
#define DROP_H

#include <QWidget>
#include <cstdint>

class Item;
class Drop : public QWidget {
    public:
        /// constructor
        Drop(QWidget *parent,
             const Item *item, const QString &location);

        /// returns the item index
        int32_t getIndex() const;

        /// used to increment the quantity value
        void incQuantity(int32_t quantity);
    protected:
        /// used to pain the QPixmap
        void paintEvent(QPaintEvent *);
    private:
        const Item *m_item;
        QString m_location;
        int32_t m_quantity = 0;
};

#endif // DROP_H
