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
