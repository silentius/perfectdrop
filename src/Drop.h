#ifndef DROP_H
#define DROP_H

#include <QWidget>
#include <QTimer>
#include <cstdint>

class Item;
class Database;
class Drop : public QWidget {
        Q_OBJECT
    public:
        /// constructor
        Drop(QWidget *parent,
             const Item &item, const Database &m_db);

        /// returns the item index
        int32_t getIndex() const;

        /// used to increment the quantity value
        void incQuantity(int32_t quantity);
    protected:
        /// used to pain the QPixmap
        void paintEvent(QPaintEvent *);

        void mouseMoveEvent(QMouseEvent *);
    public slots:
        void overlayTimerSlot();
    private:
        QString getPrefix();
        const Database &m_db;
        const Item &m_item;
        QTimer m_overlayTimer;
        int32_t m_quantity = 1;
};

#endif // DROP_H
