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

#include "Drop.h"
#include "Item.h"
#include "Database.h"

#include <QPainter>
#include <QToolTip>
#include <QDebug>

Drop::Drop(QWidget *parent, const Item &item, const Database &db)
    : QWidget(parent), m_db(db), m_item(item) {
    setFixedSize(32,32);
    hide();
    setMouseTracking(true);
    connect(&m_overlayTimer, SIGNAL(timeout()), SLOT(overlayTimerSlot()));
}

int32_t Drop::getIndex() const {
    return m_item.getIndex();
}

void Drop::incQuantity(int32_t quantity) {
    m_quantity += quantity;
}

void Drop::paintEvent(QPaintEvent *) {
    QPainter pp(this);

    QPixmap pixm(QString("%1data/HyperText/%2.bmp")
            .arg(m_db.getPathToGame())
            .arg(m_item.getFileName()));
    if (pixm.isNull()) {
        pixm = QString(":/noItemPic.png");
    }
    pp.drawPixmap (0,0, pixm);

    if (m_quantity > 1) {
        pp.setFont(QFont("Arial Unicode MS",6));
        pp.setPen(QColor("#FFFFFF"));
        pp.drawText(0,20,30,30,Qt::AlignRight,QString::number(m_quantity));
    }
    pp.end();
}

void Drop::mouseMoveEvent(QMouseEvent *) {
    m_overlayTimer.start(200);
}

void Drop::overlayTimerSlot() {
    m_overlayTimer.stop();
    if (underMouse()) {
        QString name = m_db.getName(m_item.getNameId());
        if (name.size() == 0) {
            name = QString("%1").arg(m_item.getNameId());
        }
        QString tooltip = QString("Index: %1 (%2)")
                .arg(m_item.getIndex()).arg(name);
        if (m_item.hasPrefix()) {
            tooltip.append(getPrefix());
        }
        QToolTip::showText(QCursor::pos(), tooltip);
    }
}

QString Drop::getPrefix() {
    QString prefix1 = m_db.getPrefix(m_item.getFirstPrefix());
    if (!prefix1.size()) {
        prefix1 = QString("%1").arg(m_item.getFirstPrefix());
    }
    QString prefix2 = m_db.getPrefix(m_item.getSecondPrefix());
    if (!prefix2.size()) {
        prefix2 = QString("%1").arg(m_item.getSecondPrefix());
    }
    return QString("\n%1% %2 %3% %4")
            .arg(m_item.getFirstPrefixChance()).arg(prefix1)
            .arg(m_item.getSecondPrefixChance()).arg(prefix2);
}
