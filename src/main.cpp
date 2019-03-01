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
