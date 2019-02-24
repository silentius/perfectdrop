#include "Drop.h"
#include "Item.h"

#include <QPainter>

Drop::Drop(QWidget *parent, const Item *item, const QString &location)
    : QWidget(parent), m_item(item), m_location(location)  {
    setFixedSize(32,32);
    hide();
}

int32_t Drop::getIndex() const {
    return m_item->getIndex();
}

void Drop::incQuantity(int32_t quantity) {
    m_quantity += quantity;
}

void Drop::paintEvent(QPaintEvent *) {
    QPainter pp(this);

    QPixmap pixm(QString("%1/data/HyperText/%2.bmp")
            .arg(m_location)
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
