#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_stop_button_clicked();
    void changeTime();
    void on_round_button_clicked();

private:
    Ui::MainWindow *ui;
    bool m_uistate = false;
    QTimer* m_timer = new QTimer(this);
    QTime* m_time = new QTime();
    QTime m_starttime;
    QVector<QTime> m_roundtimes;
    QTime m_output;
};
#endif // MAINWINDOW_H
