#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->round_button->setDisabled(true);
    ui->round_output->addItem("Rundenzeit-Liste: \n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_stop_button_clicked()
{
    //Ui Adaption
    if(m_uistate == false)
    {
        //Start gedrückt
        ui->round_output->clear();
        ui->round_output->addItem("Rundenzeit-Liste: \n");
        m_roundtimes.clear();
        ui->start_stop_button->setText("Stop");

        m_timer->start();
        m_timer->setInterval(10);
        m_starttime = m_time->currentTime();
        connect(m_timer, SIGNAL(timeout()), this, SLOT(changeTime()));
    }
    else
    {
        //Stop gedrückt
        m_timer->stop();

        //Auswertung schnellster Runde
        if(m_roundtimes.size() > 0)
        {
            QTime reference;
            reference.setHMS(0,0,0,0);
            QTime fastest;
            fastest.setHMS(0,0,0,0);

            int ms = reference.msecsTo(m_roundtimes[0]);
            int cnt = 1;
            int lowest = 0;
            for(QTime i : m_roundtimes)
            {
                if(reference.msecsTo(i) <= ms)
                {
                    ms = reference.msecsTo(i);
                    lowest = cnt;
                }
                cnt++;
            }

            fastest = fastest.addMSecs(ms);

            ui->round_output->addItem("schnellste: R" + QString::number(lowest) + ' ' + fastest.toString("mm:ss:z"));
        }

        ui->time_output->setText("00:00:00");
        ui->start_stop_button->setText("Start");
    }

    ui->round_button->setDisabled(m_uistate);
    m_uistate = !m_uistate;
}

void MainWindow::changeTime()
{
    m_output.setHMS(0,0,0,0);
    int msecdif = m_starttime.msecsTo(m_time->currentTime());
    m_output = m_output.addMSecs(msecdif);

    ui->time_output->setText(m_output.toString("mm:ss:z"));
}

void MainWindow::on_round_button_clicked()
{
    m_starttime = m_time->currentTime();
    m_roundtimes.append(m_output);
    ui->round_output->addItem("R" + QString::number(m_roundtimes.size())+ ' ' + ui->time_output->text());
}

