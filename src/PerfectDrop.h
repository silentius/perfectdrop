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
