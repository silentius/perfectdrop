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

#ifndef UI_H
#define UI_H

#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>
#include <QListWidget>
#include <cstdint>

class Drop;
class UI : public QWidget {
    Q_OBJECT
    public:
        using PositionList = QList <QPoint>;
        /// constructor
        UI(const QString &version);

        /// called to initialize the ui
        void init();

        /// used to set m_itemGroupId
        void setItemGroupId(int32_t itemGroupId);

        /// used to set item group names
        void setItemGroups(const QStringList &itemGroups);

        /// used to update dropped geons
        void addGeons(int32_t geons);

        /// used to increment the kill counter
        void incrementKills();

        /// returns the number of kills provided by the user
        int32_t getKillsTodo() const;

        /// used to add a new drop to the widget, returns true if successful
        bool dropItem(Drop *drop);

        /// used to reset the widget
        void reset();

        /// returns the name of the current group name selected
        const QString getSelectedItemGroup() const;

        /// used to increment the null drop counter (no item on kill)
        void incrementNullDrops();

        /// used to increment the counter for actual drops
        void incrementNonNullDrops();
    protected:
        /// helper method used update the ui
        void paintEvent(QPaintEvent *);
        //void mouseMoveEvent(QMouseEvent *event);
    private:
        /// used to apply css style to all widgets
        void setCSS();

        bool m_firstFill = true;
        int32_t m_dropPosition = 0;
        int32_t m_itemGroupId = 0;
        int32_t m_geons = 0;
        int32_t m_kills = 0;
        int32_t m_nullDrops = 0;
        int32_t m_itemsDropped = 0;
        QPushButton *m_startButton;
        QPushButton *m_stopButton;
        QPushButton *m_reloadButton;
        QLineEdit   *m_lineEdit;
        QLabel      *m_desiredKills;
        QLabel      *m_killsLabel;
        QLabel      *m_itemCountLabel;
        QLabel      *m_nullsLabel;
        QLabel      *m_estimateLabel;
        QListWidget *m_nameListWidget;
        QPushButton *m_resetButton;
        QWidget     *m_holderWidget;
        QWidget     *m_holderWidget2;
        PositionList m_positionList;
    protected slots:
        /// called by button start and emits startClicked
        void slotStartClicked();

        /// called by button stop and emits stopClicked
        void slotStopClicked();

        /// called by button reload and emits reloadClicked
        void slotReloadClicked();

        /// called by button reset and emits resetClicked
        void slotResetClicked();

        /// called by m_nameListWidget and emits resetClicked
        void slotNewGroupSelection();
    signals:
        /// custom signal
        void startClicked();

        /// custom signal
        void stopClicked();

        /// custom signal
        void reloadClicked();

        /// custom signal
        void resetClicked();

};
#endif // UI_H
