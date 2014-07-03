#include "miningpage.h"
#include "ui_miningpage.h"

#include "bitcoingui.h"
#include "guiutil.h"
#include "main.h"
#include "init.h"
#include "walletdb.h"

#include <QSettings>
#include <QThread>

MiningPage::MiningPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MiningPage)
{
    ui->setupUi(this);

    //cpuName = ProcNameRead();

    // Setup Mining Tab
    coreCount = QThread::idealThreadCount();

    //Setup all the sliders and LCDs
    QSettings settings;

    if (settings.contains("nMiningIntensity"))
        sliderValue = settings.value("nMiningIntensity", GetArg("-genproclimit", 1)).toInt();
    else
        sliderValue = 1;

    if (settings.contains("bMiningEnabled"))
    {
        if (settings.value("bMiningEnabled") == true)
        {
            ui->miningChecked->setEnabled(true);
            ui->miningCrossed->setEnabled(false);
        }
        else
        {
            ui->miningChecked->setEnabled(false);
            ui->miningCrossed->setEnabled(true);
        }
    }

    miningCores.setNum(sliderValue);
    ui->allocatedCoresSlider->setMaximum(coreCount);
    ui->coreCountLCD->display(coreCount);
    ui->allocatedCoresLCD->display(sliderValue);
    ui->allocatedCoresSlider->setValue(sliderValue);
    ui->maxCoresLabel->setText(QString::number(coreCount));

    //Toggle mining
    connect(ui->mineButton,SIGNAL(clicked()),this,SLOT(startMining()));
    connect(ui->mineStopButton,SIGNAL(clicked()),this,SLOT(stopMining()));
    connect(ui->allocatedCoresSlider,SIGNAL(valueChanged(int)),this,SLOT(setAllocatedCores()));
}

/*
QString MiningPage::ProcNameRead()
{
QString cpuName;
char Buffer[_MAX_PATH];
DWORD BufSize = _MAX_PATH;
DWORD dwMHz = _MAX_PATH;
HKEY hKey;

// open the key where the proc speed is hidden:
long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                        "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                        0,
                        KEY_READ,
                        &hKey);

    if(lError != ERROR_SUCCESS)
      {// if the key is not found, tell the user why:
           FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                         NULL,
                         lError,
                         0,
                         Buffer,
                         _MAX_PATH,
                         0);
               AfxMessageBox(Buffer);
           return "N/A";
       }

        // query the key:
        RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE) &dwMHz, &BufSize);

    // convert the DWORD to a CString:
    cpuName.Format("%i", dwMHz);

return cpuName;
}
*/

void MiningPage::startMining()
{
    SetArg("-genproclimit", miningCores.toStdString());
    SoftSetArg("-genproclimit", miningCores.toStdString());
    SoftSetBoolArg("-gen", true);
    QSettings settings;

    settings.setValue("bMiningEnabled","true");

       if (settings.contains("bMiningEnabled"))
           SetBoolArg("-gen", settings.value("bMiningEnabled").toBool());
       if (settings.contains("nMiningIntensity"))
           SetArg("-genproclimit", settings.value("nMiningIntensity").toString().toStdString());

       // stop
        GenerateBitcoins(false, NULL);

       // start
        GenerateBitcoins(GetBoolArg("-gen", false), pwalletMain);

        ui->miningChecked->setEnabled(true);
        ui->miningCrossed->setEnabled(false);

}

void MiningPage::stopMining()
{
    QSettings settings;

    settings.setValue("bMiningEnabled","false");

    // These are shared with core Bitcoin; we want
    // command-line options to override the GUI settings:
    if (settings.contains("fUseUPnP"))
        SoftSetBoolArg("-upnp", settings.value("fUseUPnP").toBool());
    if (settings.contains("addrProxy") && settings.value("fUseProxy").toBool())
        SoftSetArg("-proxy", settings.value("addrProxy").toString().toStdString());
    if (settings.contains("nSocksVersion") && settings.value("fUseProxy").toBool())
        SoftSetArg("-socks", settings.value("nSocksVersion").toString().toStdString());

    if (settings.contains("bMiningEnabled"))
        SetBoolArg("-gen", settings.value("bMiningEnabled").toBool());
    if (settings.contains("nMiningIntensity"))
        SetArg("-genproclimit", settings.value("nMiningIntensity").toString().toStdString());

    // stop
     GenerateBitcoins(false, NULL);

    // start
     GenerateBitcoins(GetBoolArg("-gen", false), pwalletMain);

     ui->miningChecked->setEnabled(false);
     ui->miningCrossed->setEnabled(true);

}


void MiningPage::setAllocatedCores()
{
    QSettings settings;

    sliderValue = ui->allocatedCoresSlider->value();
    miningCores.setNum(sliderValue);
    ui->allocatedCoresLCD->display(sliderValue);

    SetArg("-genproclimit", miningCores.toStdString());
    SoftSetArg("-genproclimit", miningCores.toStdString());

    settings.setValue("nMiningIntensity",miningCores);

    // stop
    GenerateBitcoins(false, NULL);
    // start
    GenerateBitcoins(true, pwalletMain);
}


MiningPage::~MiningPage()
{
    delete ui;
}

void MiningPage::done(int retval)
{
    if(returnValue.isEmpty())
    {
        // If no address entry selected, return rejected
        retval = Rejected;
    }

    QDialog::done(retval);
}
