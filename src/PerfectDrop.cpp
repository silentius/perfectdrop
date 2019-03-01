#include "PerfectDrop.h"
#include "Database.h"
#include "Drop.h"
#include "Item.h"
#include <QDebug>
#include <QThread>

PerfectDrop::PerfectDrop(const QString &version)
    : m_ui(new UI(version)), m_db(new Database) {
}

PerfectDrop::~PerfectDrop() {
    for (auto drop : m_drops) {
        delete(drop);
    }
    delete m_ui;
    delete m_db;
}

bool PerfectDrop::init() {
    m_ui->show();
    connect(m_ui, SIGNAL(startClicked()), this, SLOT(slotStartClicked()));
    connect(m_ui, SIGNAL(stopClicked()), this, SLOT(slotStopClicked()));
    connect(m_ui, SIGNAL(reloadClicked()), this, SLOT(slotReloadClicked()));
    connect(m_ui, SIGNAL(resetClicked()), this, SLOT(slotResetClicked()));
    connect(&m_shotTimer, SIGNAL(timeout()), this, SLOT(slotTimerCallback()));
    m_shotTimer.setInterval(1);
    bool initOK = m_db->init();
    slotReloadClicked();
    return initOK;
}

void PerfectDrop::slotStartClicked() {
    if (!m_runningFlag) {
        QString itemGroupName(m_ui->getSelectedItemGroup());
        if (itemGroupName.contains("unnamed")) {
            QStringList kvpair(itemGroupName.split(" "));
            if (kvpair.size() == 2) {
                m_itemGroupId = kvpair.at(1).toInt();
            }
        } else {
            m_itemGroupId = m_db->getItemGroupIdFromName(m_ui->getSelectedItemGroup());
        }
        m_ui->setItemGroupId(m_itemGroupId);
        m_killsTodo = m_ui->getKillsTodo();
        m_killsDone = 0;
        m_runningFlag = true;
        m_shotTimer.start();
    }
}

void PerfectDrop::slotStopClicked() {
    m_runningFlag = false;
    m_shotTimer.stop();
}

void PerfectDrop::slotReloadClicked() {
    m_ui->setEnabled(false);
    slotResetClicked();
    m_db->reloadItemGroups();
    Database::ItemGroups::ConstIterator itr(m_db->getItemGroups().begin());
    const Database::ItemGroups::ConstIterator itrE(m_db->getItemGroups().end());

    QStringList groupNameList;
    for (; itr != itrE; ++itr) {
        const QString &groupName = m_db->getItemGroupName(itr.key());
        if (groupName.size()) {
            groupNameList.append(groupName);
        } else {
            groupNameList.append(QString("unnamed %1").arg(itr.key()));
        }
    }
    m_ui->setItemGroups(groupNameList);
    m_ui->setEnabled(true);
}

void PerfectDrop::slotResetClicked() {
    m_runningFlag = false;
    m_shotTimer.stop();
    for (auto drop : m_drops) {
        delete(drop);
    }

    m_drops.clear();
    m_ui->reset();
}

void PerfectDrop::slotTimerCallback() {
    processKill();
    if (m_runningFlag) {
        m_shotTimer.start(1);
    }
}

void PerfectDrop::processKill() {
    // let's do 10 kills per interval
    for (int32_t i = 0; i < 10 && m_runningFlag; ++i) {
        if (++m_killsDone >= m_killsTodo) {
            m_runningFlag = false;
            m_shotTimer.stop();
        }

        // first generate the drop
        const Group::Entry *droppedItem(m_db->selectItem(m_itemGroupId));
        if (droppedItem != nullptr && droppedItem->item != nullptr) {
            bool isMoney(droppedItem->item->getIndex() == 31);
            if (!isMoney) {
                m_ui->incrementNonNullDrops();
            }
            bool addItem(true);
            if (isMoney) {
                // is item money, if yes only increment money
                m_ui->addGeons(droppedItem->count);
                addItem = false;
            } else if (droppedItem->item->isStackable()) {
                // if stackable look if we got one already and just increment
                for (auto drop : m_drops) {
                    if (drop->getIndex() == droppedItem->item->getIndex()) {
                        drop->incQuantity(droppedItem->count);
                        addItem = false;
                        break;
                    }
                }
            }

            if (addItem) {
                Drop *drop = new Drop(m_ui, *droppedItem->item, *m_db);
                if (m_ui->dropItem(drop)) {
                    m_drops.append(drop);
                } else {
                    // let's assume inventory is full
                    m_runningFlag = false;
                    delete drop;
                }
            }
        } else {
            m_ui->incrementNullDrops();
        }

        m_ui->incrementKills();
    }
    m_ui->repaint();
}
