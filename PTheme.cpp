#include "PTheme.h"

#include <QFile>
#include <QTextStream>

QString PTheme::themeFile = "";
QString PTheme::themeContent = "";
QString PTheme::colorsFile = "";
QMap<QString, QString> PTheme::colorsContent;
QStringList PTheme::pluginContents;

void PTheme::addPlugin(const QString& pluginContent)
{
    PTheme::pluginContents.append(pluginContent);
}

QString PTheme::load(const QString& themeFile, const QString& colorsFile)
{
    PTheme::themeFile = themeFile;
    PTheme::colorsFile = colorsFile;

    // Get theme content from themeFile
    QFile fTheme(themeFile);
    fTheme.open(QFile::ReadOnly);
    QTextStream inTheme(&fTheme);
    QString theme = inTheme.readAll();
    fTheme.close();

    theme += "\n";
    auto pluginContents = PTheme::pluginContents;
    for (const auto& pluginContent: pluginContents) {
        theme += pluginContent;
        theme += "\n";
    }

    // Get colors content from colorsFile
    QFile fColors(colorsFile);
    fColors.open(QFile::ReadOnly);
    QTextStream inColors(&fColors);
    QString colors = inColors.readAll();
    fColors.close();

    // Transform colors content to list
    QMap<QString, QString> vColors;
    QStringList lines = colors.split("\n");
    for (const auto& line: lines) {
        if (line.startsWith("//") || line.startsWith("#")) continue;
        auto items = line.split("=");
        if (items.length() == 2) {
            vColors.insert(items[0].trimmed(), items[1].trimmed());
        }
    }

    // Update theme with colors
    QMapIterator<QString, QString> it(vColors);
    while (it.hasNext()) {
        it.next();
        theme.replace(it.key(), it.value());
    }

    PTheme::themeContent = theme;
    PTheme::colorsContent = vColors;

    return theme;
}

QString PTheme::getColor(const QString& name)
{
    return PTheme::colorsContent.value(name);
}

void PTheme::install(QApplication* app, const QString& themeFile, const QString& colorsFile)
{
    app->setStyleSheet(PTheme::load(themeFile, colorsFile));
}
