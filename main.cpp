#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QPushButton>
#include <mainwindow.h>
#include <autentification.h>
#include <QLibraryInfo>
#include <editdossier.h>


int main(int argc, char *argv[])

{

    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    app.installTranslator(&translator);
    Autentification *m=new Autentification();
    m->show();

    return app.exec();

}
