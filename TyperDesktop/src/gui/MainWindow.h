#pragma once

#include <QMainWindow>

#include "EnterMenu.h"
#include "../common/TypeResult.h"

namespace typer
{
    namespace gui
    {
        class MainWindow : public QMainWindow
        {
            Q_OBJECT

        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

            /// @todo move to somewhere
            struct TypeSettings
            {
                QString wordType;
                int timeS;
            };

        private slots:
            void showEnterWidget();
            void showTyperWidget(const QString & wordType, int timeS);
            void showSettingsWidget();
            void showResultWidget(const common::TypeResults & typeResults);

            void updateWordTypes();

        private:
            void restoreWindowSettings();
            void storeWindowSettings();
            QPoint getDefaultWindowPos();

        private:
            QStringList m_wordTypes;
            TypeSettings m_prevTypeSettings;
        };
    }
}
