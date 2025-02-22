#pragma once

#include <QWidget>
#include <QComboBox>

namespace typer
{
    namespace gui
    {
        class EnterMenu : public QWidget
        {
            Q_OBJECT
        public:
            EnterMenu( const QStringList & wordTypes,
                       QWidget * parent = nullptr);

            void setCurentSettings(const QString & wordType, int time);

        signals:
            void start(const QString & wordType, int sTime);
            void settings();

        protected:
            void keyReleaseEvent(QKeyEvent *event) override;
            void resizeEvent(QResizeEvent *event) override;
            void showEvent(QShowEvent *event) override;

        protected slots:
            void emitStart();

        private:
            void buildForm(const QStringList & wordTypes);
            void updateComboBoxesPos();
            QString timeToStr(int time);
            int strToTime(const QString & timeStr);

        private:
            QComboBox * m_wordTypeComboBox;
            QComboBox * m_timeComboBox;
        };
    }
}

