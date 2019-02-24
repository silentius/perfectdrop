#include "PerfectDrop.h"
#include "UI.h"

#include <QApplication>
#include <QTime>
#include <QDebug>
#include "Group.h"
#include "Database.h"
#include "Item.h"

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    // init random generator
    qsrand(static_cast<uint32_t>(QTime(0,0,0).secsTo(QTime::currentTime())));
/*
    Database *m_db =new Database;
    m_db->init();

    for (int32_t i = 0; i < 10; ++i) {
        const Group::Entry *entry = m_db->selectItem(102133);

        if (entry != nullptr) {
            if (entry->item != nullptr) {
                qDebug() << entry->item->getIndex() << entry->prefix << entry->count;
            } else {
                qDebug() << "PREFIX: "<< entry->prefix;
            }
        } else {
            qDebug() << "NULL";
        }
    }*/

    PerfectDrop w;
    w.init();

    return a.exec();
}
