#ifndef PTHEME_H
#define PTHEME_H

#include <QMap>
#include <QString>
#include <QApplication>

namespace PTheme
{
    extern QString themeFile;
    extern QString themeContent;

    extern QString colorsFile;
    extern QMap<QString, QString> colorsContent;

    extern QStringList pluginContents;

    extern QString getColor(const QString& name);

    extern void addPlugin(const QString& pluginContent);

    extern QString load(const QString& themeFile, const QString& colorsFile);
    extern void install(QApplication* app, const QString& themeFile, const QString& colorsFile);
};

#endif // PTHEME_H
