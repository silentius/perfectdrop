#include "UI.h"
#include "Drop.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>

UI::UI() : QWidget() {
    setWindowTitle("PerfectDrop by silentius");
    setFixedSize(400,600);
    setMouseTracking(true);
    init();
}

void UI::init() {
    QGridLayout    *gridLayout = new QGridLayout;
    m_holderWidget = new QWidget(this);
    m_resetButton  = new QPushButton("Reset",m_holderWidget);
    m_stopButton   = new QPushButton("Stop",m_holderWidget);
    m_startButton  = new QPushButton("Start",m_holderWidget);
    m_lineEdit     = new QLineEdit(m_holderWidget);
    m_lineEdit->setValidator(new QDoubleValidator(1, 10000, 1, this));
    m_lineEdit->setText("1000");
    m_lineEdit->setAlignment( Qt::AlignRight );

    m_desiredKills = new QLabel(this);
    m_desiredKills->setText("Desired Kills");

    m_holderWidget->setLayout(gridLayout);
    const int32_t xWdg = 197;
    m_holderWidget->setGeometry(5, 25, xWdg, 70);
    gridLayout->addWidget(m_resetButton, 0, 0);
    gridLayout->addWidget(m_stopButton, 0, 1);
    gridLayout->addWidget(m_startButton, 0, 2);
    gridLayout->addWidget(m_lineEdit,1, 1, 2, 2);
    gridLayout->addWidget(m_desiredKills, 1, 0, 2, 1);

    QGridLayout *gridLayout2 = new QGridLayout;
    m_holderWidget2 = new QWidget(this);
    QLabel *label1  = new QLabel("total kills", m_holderWidget2);
    QLabel *label2  = new QLabel("dropped items", m_holderWidget2);
    QLabel *label3  = new QLabel("simulator runtime", m_holderWidget2);
    QLabel *label4  = new QLabel("estimate", m_holderWidget2);

    m_killsLabel = new QLabel(m_holderWidget2);
    m_killsLabel->setAlignment (Qt::AlignCenter | Qt::AlignRight);
    m_killsLabel->setText("0");

    m_itemCountLabel = new QLabel(m_holderWidget2);
    m_itemCountLabel->setAlignment (Qt::AlignCenter | Qt::AlignRight);
    m_itemCountLabel->setText("0");

    m_timeLabel = new QLabel(m_holderWidget2);
    m_timeLabel->setAlignment (Qt::AlignCenter | Qt::AlignRight);
    m_timeLabel->setText("0");

    m_estimateLabel = new QLabel(m_holderWidget2);
    m_estimateLabel->setAlignment (Qt::AlignCenter | Qt::AlignRight);
    m_estimateLabel->setText("0");

    m_holderWidget2->setLayout(gridLayout2);
    m_holderWidget2->setGeometry(5, 98, xWdg, 120);
    m_holderWidget2->show();

    gridLayout2->addWidget(label1 ,0, 0);
    gridLayout2->addWidget(label2 ,1, 0);
    gridLayout2->addWidget(label3 ,2, 0);
    gridLayout2->addWidget(label4 ,3, 0);

    gridLayout2->addWidget(m_killsLabel     ,0, 1);
    gridLayout2->addWidget(m_itemCountLabel ,1, 1);
    gridLayout2->addWidget(m_timeLabel      ,2, 1);
    gridLayout2->addWidget(m_estimateLabel  ,3, 1);

    // list for name selection
    m_nameListWidget    = new QListWidget(this);
    m_nameListWidget->setGeometry(206, 25, 188, 536);
    m_nameListWidget->setSortingEnabled(true);
    m_reloadButton = new QPushButton("Reload Configs",this);
    m_reloadButton->setGeometry(206, 565, 188, 29);

    // finally apply CSS style
    setCSS();

    // connect the buttons
    connect(m_startButton,  SIGNAL(clicked()), SLOT(slotStartClicked()));
    connect(m_stopButton,   SIGNAL(clicked()), SLOT(slotStopClicked()));
    connect(m_reloadButton, SIGNAL(clicked()), SLOT(slotReloadClicked()));
    connect(m_resetButton,  SIGNAL(clicked()), SLOT(slotResetClicked()));
    connect(m_nameListWidget,  SIGNAL(itemSelectionChanged()), SLOT(slotNewGroupSelection()));
}

void UI::setItemGroupId(int32_t itemGroupId) {
    m_itemGroupId = itemGroupId;
}

void UI::setItemGroups(const QStringList &itemGroups) {
    int32_t currentRow(m_nameListWidget->currentRow());
    m_nameListWidget->clear();
    m_nameListWidget->addItems(itemGroups);
    if (currentRow < 0) {
        currentRow = 0;
    }
    m_nameListWidget->setCurrentRow(currentRow);
}

void UI::addGeons(int32_t geons) {
    m_geons += geons;
}

void UI::incrementKills() {
    m_killsLabel->setText(QString("%1").arg(++m_kills));
}

int32_t UI::getKillsTodo() const {
    return m_lineEdit->text().toInt();
}

bool UI::dropItem(Drop *drop) {
    if (m_dropPosition >= m_positionList.size()) {
        return false;
    }
    drop->move(m_positionList[m_dropPosition++]);
    drop->show();
    return true;
}

void UI::reset() {
    m_itemCountLabel->setText("0");
    m_timeLabel->setText("0");
    m_estimateLabel->setText("0");
    m_killsLabel->setText("0");
    m_dropPosition = 0;
    m_geons = 0;
    m_kills = 0;
    repaint();
}

void UI::paintEvent(QPaintEvent *) {
    QPainter pp;
    pp.begin(this);
    pp.fillRect(0, 0, width()-1, height()-1, QBrush(QColor("#CC9955")));
    pp.fillRect(1, 1, width()-3, height()-3, QBrush(QColor("#774422")));
    pp.fillRect(2, 22, width()-5, height()-25, QBrush(QColor("#0F0F0F")));

    const int32_t yStart = 230;

    pp.fillRect(3, yStart, (6*33)+1, (10*33)+1, QBrush(QColor("#774422")));

    // store all possible drop positions so be able to draw an item at the spot
    for (int32_t y = 0; y < 10; y++) {
        for (int32_t x = 0; x < 6; x++) {
            pp.fillRect(4+(x*33), 1+yStart+(y*33), 32, 32, QBrush(QColor("#0F0F0F")));
            if (m_firstFill) {
                m_positionList.append(QPoint(4+(x*33), 1+yStart+(y*33)));
            }
        }
    }
    m_firstFill = false;

    pp.setPen(QColor("#CC9955"));
    pp.setFont(QFont("Arial Unicode MS",8));
    pp.drawText (QRect(6, 6, width()-11, 16), Qt::AlignLeft,
                 QString("Drop-Simulation for ItemGroup: %1").arg(m_itemGroupId), nullptr);

    pp.setPen(Qt::white);
    pp.setRenderHints(QPainter::TextAntialiasing);
    pp.drawText (QRect(15, height()-29, 50, 16), Qt::AlignLeft ,"Money", nullptr);
    pp.drawText (QRect(165, height()-29, 50, 16), Qt::AlignLeft ,"Geon", nullptr);

    // format and write money
    QString value = QString("%1").arg(m_geons);
    for (int i = value.length()-3; i > 0; i-=3) {
        value = value.insert(i, ".");
    }

    pp.fillRect(55, height()-32, 100, 18, QBrush(QColor("#774422")));
    pp.fillRect(56, height()-31, 98, 16, QBrush(QColor("#0F0F0F")));
    pp.drawText (QRect(57, height()-29, 96, 17), Qt::AlignRight ,value, nullptr);
    pp.end();
}

void UI::setCSS() {
    setStyleSheet(
        "QWidget {"
        "    color: #CC9955;"
        "    border: 1px solid #CC9955;"
        "    background-color: #774422;}"
        "QPushButton:pressed {"
        "    background-color: #CC9955;}"
        "QPushButton:flat {border: none;}"
        "QPushButton:default {border-color: #CC9955;}"
        "QScrollBar:horizontal {"
        "    border: 1px solid #CC9955;"
        "    background: #0F0F0F;"
        "    height: 15px;"
        "    margin: 0px 40px 0 0px;}"
        "QScrollBar::handle:horizontal {"
        "    background: #CC9955;"
        "    min-width: 20px;}"
        "QScrollBar::add-line:horizontal {"
        "    background: #0F0F0F;"
        "    width: 16px;"
        "    subcontrol-position: right;"
        "    subcontrol-origin: margin;"
        "    border: 1px solid #CC9955;}"
        "QScrollBar::sub-line:horizontal {"
        "    background: #0F0F0F;"
        "    width: 16px;"
        "    subcontrol-position: top right;"
        "    subcontrol-origin: margin;"
        "    border: 1px solid #CC9955;"
        "    position: absolute;"
        "    right: 20px;}"
        "QScrollBar:left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
        "    width: 3px;"
        "    height: 3px;"
        "    background: #CC9955;}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
        "    background: none;}"
        "QLabel{background: #0F0F0F;}");

    m_lineEdit->setStyleSheet("QWidget {border: 2px solid #CC9955;}");
}


const QString UI::getSelectedItemGroup() const {
    return m_nameListWidget->currentItem()->text();
}

void UI::slotStartClicked() {
    emit startClicked();
}

void UI::slotStopClicked() {
    emit stopClicked();
}

void UI::slotReloadClicked() {
    emit reloadClicked();
}

void UI::slotResetClicked() {
    emit resetClicked();
}

void UI::slotNewGroupSelection() {
    emit resetClicked();
}
