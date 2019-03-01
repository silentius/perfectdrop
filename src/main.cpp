#include "PerfectDrop.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    // init random generator
    qsrand(static_cast<uint32_t>(QTime(0,0,0).secsTo(QTime::currentTime())));

    // set build version parameters
    const QString version("0.1.0");
    const QString versionStr = QString("%1 %2").arg(version)
            .arg(QString::fromLocal8Bit(__DATE__));
    PerfectDrop w(versionStr);
    w.init();

    return a.exec();
}
