#include "maindialog.h"
#include "ui_maindialog.h"
#include "console.h"
#include <QLabel>
#include <QTimer>
#include <QScrollBar>
#include <QTextStream>

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
    initComponents();
    initProcess();
    //console->setLocalEchoEnabled(true);

    /** Timer de pruebas con ProgressBar **/
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, [=]() { int v = proBar->value(); proBar->setValue(v+1);} );
    /** END - BloqueTimer **/
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::initComponents()
{
    QWidget *wdg = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout();

    // Se crea la consola
    console = new Console();
    //console->setEnabled(false);
    vlay->addWidget(console);


    QHBoxLayout *hlay = new QHBoxLayout(wdg);
    labelStatus = new QLabel;
    status = new QLabel;
    labelStatus->setText("Estado actual: ");
    status->setText("DESCARGANDO ACTUALIZACIONES...");
    hlay->addWidget(labelStatus);
    hlay->addWidget(status);
    hlay->addStretch();
    vlay->addWidget(wdg);

    proBar = new QProgressBar();
    proBar->setMinimum(0);
    proBar->setMaximum(100);
    vlay->addWidget(proBar);

    this->setLayout(vlay);
}

void mainDialog::initProcess()
{
    batProce = new QProcess(this);
    batProce->setProcessChannelMode( QProcess::SeparateChannels );
    batProce->start(UPDATER, ARGUMENTS, QProcess::ReadWrite);
    batProce->waitForStarted(5000);

    connect(batProce, SIGNAL( readyReadStandardOutput() ), this, SLOT(readOutput()) );
    connect(batProce, SIGNAL( readyReadStandardError() ), this, SLOT(readError()) );

    batProce->write("cd C:/Users/diego.campos/Desktop/soft\n");
    batProce->waitForFinished(5000);
    batProce->write("update.bat\n");

    cleanConsole(console);

}

void mainDialog::readOutput()
{
    QString buff = QString::fromLatin1(batProce->readAllStandardOutput());
    console->putData(buff);
    console->putData("\n");
}

void mainDialog::readError()
{
    QPalette p = console->palette();
    p.setColor(QPalette::Text, Qt::red);
    console->setPalette(p);

    QString error = QString::fromLocal8Bit(batProce->readAllStandardError());
    console->putData(error);
    console->putData("\n");

    p.setColor(QPalette::Text, Qt::green);
    console->setPalette(p);
}

void mainDialog::cleanConsole(Console *console)
{
    console->clear();
    QScrollBar *bar = console->verticalScrollBar();
    bar->setValue(bar->maximum());

    QString arch = "";
    QFile file(":/data/logo_ascii.txt");

    if (!file.open(QIODevice::ReadOnly)){
        console->putData("../../logo_ascii.txt Not Found!");
        return;
    }else{
        QTextStream in(&file);
        arch = in.readAll();
        console->putData(arch);
    }

}
