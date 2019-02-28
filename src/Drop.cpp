#include "Drop.h"
#include "Item.h"
#include "Database.h"

#include <QPainter>
#include <QToolTip>
#include <QDebug>

Drop::Drop(QWidget *parent, const Item *item, const Database &db)
    : QWidget(parent), m_db(db), m_item(item) {
    setFixedSize(32,32);
    hide();
    setMouseTracking(true);
    connect(&m_overlayTimer, SIGNAL(timeout()), SLOT(overlayTimerSlot()));
}

int32_t Drop::getIndex() const {
    return m_item->getIndex();
}

void Drop::incQuantity(int32_t quantity) {
    m_quantity += quantity;
}

void Drop::paintEvent(QPaintEvent *) {
    QPainter pp(this);

    QPixmap pixm(QString("%1data/HyperText/%2.bmp")
            .arg(m_db.getPathToGame())
            .arg(m_item->getFileName()));
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
    m_overlayTimer.start(500);
}

void Drop::overlayTimerSlot() {
    m_overlayTimer.stop();
    if (underMouse()) {
        QString name = m_db.getName(m_item->getNameId());
        if (name.size() == 0) {
            name = QString("%1").arg(m_item->getNameId());
        }

        QString tooltip = QString("Index: %1 (%2)")
                .arg(m_item->getIndex()).arg(name);
        QToolTip::showText(QCursor::pos(), tooltip);
    }
}
