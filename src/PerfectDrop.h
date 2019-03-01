#ifndef PERFECTDROP_H
#define PERFECTDROP_H

#include "UI.h"
#include <QObject>
#include <QTimer>
#include <cstdint>
#include <QList>
class Drop;
class Database;
class PerfectDrop : public QObject {
    Q_OBJECT
        using DropList = QList <Drop *>;
    public:
        /// constructor
        PerfectDrop(const QString &version);

        /// destructor
        virtual ~PerfectDrop();

        /// used to initialize PerfectDrop
        bool init();
    public slots:
        /// slot to start a run
        void slotStartClicked();

        /// slot to pause a run
        void slotStopClicked();

        /// slot to reload ItemGroup.txt
        void slotReloadClicked();

        /// slot to reset
        void slotResetClicked();

        /// slot to perform actual selection logic
        void slotTimerCallback();
    private:
        /// used to select items and update screen
        void processKill();
        UI *m_ui;
        Database *m_db;
        QTimer m_shotTimer;
        bool m_runningFlag = false;
        int32_t m_killsTodo = 0;
        int32_t m_killsDone = 0;
        int32_t m_itemGroupId = 0;
        //QTimer m_actionTimer;
        DropList m_drops;
};

#endif // PERFECTDROP_H
