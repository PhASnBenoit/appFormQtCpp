/********************************************************************************
** Form generated from reading UI file 'cgui.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CGUI_H
#define UI_CGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CGui
{
public:
    QWidget *centralWidget;
    QGroupBox *gbCapteurs;
    QWidget *layoutWidget;
    QVBoxLayout *vlI2c;
    QLineEdit *leTempI2c;
    QLineEdit *leHumI2c;
    QWidget *layoutWidget1;
    QVBoxLayout *vlValSeuils;
    QLineEdit *leSeuilTempI2c;
    QLineEdit *leSeuilHumI2c;
    QWidget *layoutWidget2;
    QVBoxLayout *vlSeuils;
    QLabel *label_24;
    QLabel *label_25;
    QWidget *verticalLayoutWidget_8;
    QVBoxLayout *vlLI2c;
    QLabel *label;
    QLabel *label_2;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *vlI2cL;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *verticalLayoutWidget_12;
    QVBoxLayout *vlI2cL_2;
    QLabel *label_32;
    QLabel *label_33;
    QPushButton *pbStartStop;
    QGroupBox *gbLed;
    QPushButton *pbOnOffLed;
    QLabel *laNoir;
    QLabel *laRouge;
    QTextEdit *teTexte;
    QGroupBox *gbCapteurSpi;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlSpi;
    QLineEdit *leTempSpi;
    QLineEdit *leSeuilTempSpi;
    QLabel *label_28;
    QLabel *label_29;
    QWidget *verticalLayoutWidget_10;
    QVBoxLayout *vlLSpi;
    QLabel *label_26;
    QLabel *label_27;
    QWidget *verticalLayoutWidget_11;
    QVBoxLayout *vlSpiL;
    QLabel *label_30;
    QLabel *label_31;
    QGroupBox *gbBouton;
    QLabel *lEtatBouton;
    QGroupBox *gbLcd;
    QPushButton *pbLcd;
    QGroupBox *gbEcranRs;
    QPushButton *pbEnvoyer;
    QTextEdit *teRecevoir;
    QLineEdit *leEnvoyer;
    QPushButton *pbEffacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGroupBox *gbIntervalle;
    QWidget *layoutWidget3;
    QVBoxLayout *vlInter;
    QLineEdit *leInterCapt;
    QLineEdit *leInterBdd;
    QLineEdit *leInterServ;
    QLineEdit *leInterPeriph;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *vlLInter;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *vlInterL;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *gbVS;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *vlLVS;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *vlParamsVS;
    QComboBox *cbPorts;
    QComboBox *cbVitesse;
    QComboBox *cbParite;
    QComboBox *cbBits;
    QComboBox *cbStop;
    QGroupBox *gbServeur;
    QWidget *layoutWidget4;
    QVBoxLayout *vlServer;
    QLineEdit *leAdrServ;
    QLineEdit *lePortServ;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *vlLServeur;
    QLabel *label_13;
    QLabel *label_14;
    QGroupBox *gbSgbd;
    QWidget *layoutWidget5;
    QVBoxLayout *vlSgbd;
    QLineEdit *leAdrSgbd;
    QLineEdit *leNomBdd;
    QLineEdit *leUserSgbd;
    QLineEdit *lePassSgbd;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *vlLSgbd;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;

    void setupUi(QMainWindow *CGui)
    {
        if (CGui->objectName().isEmpty())
            CGui->setObjectName("CGui");
        CGui->resize(1040, 840);
        CGui->setMinimumSize(QSize(1040, 840));
        centralWidget = new QWidget(CGui);
        centralWidget->setObjectName("centralWidget");
        gbCapteurs = new QGroupBox(centralWidget);
        gbCapteurs->setObjectName("gbCapteurs");
        gbCapteurs->setGeometry(QRect(10, 30, 361, 181));
        layoutWidget = new QWidget(gbCapteurs);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(150, 30, 161, 68));
        vlI2c = new QVBoxLayout(layoutWidget);
        vlI2c->setSpacing(6);
        vlI2c->setContentsMargins(11, 11, 11, 11);
        vlI2c->setObjectName("vlI2c");
        vlI2c->setContentsMargins(0, 0, 0, 0);
        leTempI2c = new QLineEdit(layoutWidget);
        leTempI2c->setObjectName("leTempI2c");
        leTempI2c->setReadOnly(true);

        vlI2c->addWidget(leTempI2c);

        leHumI2c = new QLineEdit(layoutWidget);
        leHumI2c->setObjectName("leHumI2c");
        leHumI2c->setReadOnly(true);

        vlI2c->addWidget(leHumI2c);

        layoutWidget1 = new QWidget(gbCapteurs);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(150, 100, 161, 68));
        vlValSeuils = new QVBoxLayout(layoutWidget1);
        vlValSeuils->setSpacing(6);
        vlValSeuils->setContentsMargins(11, 11, 11, 11);
        vlValSeuils->setObjectName("vlValSeuils");
        vlValSeuils->setContentsMargins(0, 0, 0, 0);
        leSeuilTempI2c = new QLineEdit(layoutWidget1);
        leSeuilTempI2c->setObjectName("leSeuilTempI2c");

        vlValSeuils->addWidget(leSeuilTempI2c);

        leSeuilHumI2c = new QLineEdit(layoutWidget1);
        leSeuilHumI2c->setObjectName("leSeuilHumI2c");

        vlValSeuils->addWidget(leSeuilHumI2c);

        layoutWidget2 = new QWidget(gbCapteurs);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 100, 131, 71));
        vlSeuils = new QVBoxLayout(layoutWidget2);
        vlSeuils->setSpacing(6);
        vlSeuils->setContentsMargins(11, 11, 11, 11);
        vlSeuils->setObjectName("vlSeuils");
        vlSeuils->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(layoutWidget2);
        label_24->setObjectName("label_24");
        label_24->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlSeuils->addWidget(label_24);

        label_25 = new QLabel(layoutWidget2);
        label_25->setObjectName("label_25");
        label_25->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlSeuils->addWidget(label_25);

        verticalLayoutWidget_8 = new QWidget(gbCapteurs);
        verticalLayoutWidget_8->setObjectName("verticalLayoutWidget_8");
        verticalLayoutWidget_8->setGeometry(QRect(10, 30, 131, 71));
        vlLI2c = new QVBoxLayout(verticalLayoutWidget_8);
        vlLI2c->setSpacing(6);
        vlLI2c->setContentsMargins(11, 11, 11, 11);
        vlLI2c->setObjectName("vlLI2c");
        vlLI2c->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_8);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLI2c->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_8);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLI2c->addWidget(label_2);

        verticalLayoutWidget_9 = new QWidget(gbCapteurs);
        verticalLayoutWidget_9->setObjectName("verticalLayoutWidget_9");
        verticalLayoutWidget_9->setGeometry(QRect(320, 30, 31, 61));
        vlI2cL = new QVBoxLayout(verticalLayoutWidget_9);
        vlI2cL->setSpacing(6);
        vlI2cL->setContentsMargins(11, 11, 11, 11);
        vlI2cL->setObjectName("vlI2cL");
        vlI2cL->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(verticalLayoutWidget_9);
        label_11->setObjectName("label_11");

        vlI2cL->addWidget(label_11);

        label_12 = new QLabel(verticalLayoutWidget_9);
        label_12->setObjectName("label_12");

        vlI2cL->addWidget(label_12);

        verticalLayoutWidget_12 = new QWidget(gbCapteurs);
        verticalLayoutWidget_12->setObjectName("verticalLayoutWidget_12");
        verticalLayoutWidget_12->setGeometry(QRect(320, 100, 31, 61));
        vlI2cL_2 = new QVBoxLayout(verticalLayoutWidget_12);
        vlI2cL_2->setSpacing(6);
        vlI2cL_2->setContentsMargins(11, 11, 11, 11);
        vlI2cL_2->setObjectName("vlI2cL_2");
        vlI2cL_2->setContentsMargins(0, 0, 0, 0);
        label_32 = new QLabel(verticalLayoutWidget_12);
        label_32->setObjectName("label_32");

        vlI2cL_2->addWidget(label_32);

        label_33 = new QLabel(verticalLayoutWidget_12);
        label_33->setObjectName("label_33");

        vlI2cL_2->addWidget(label_33);

        pbStartStop = new QPushButton(centralWidget);
        pbStartStop->setObjectName("pbStartStop");
        pbStartStop->setGeometry(QRect(380, 60, 301, 51));
        gbLed = new QGroupBox(centralWidget);
        gbLed->setObjectName("gbLed");
        gbLed->setGeometry(QRect(380, 220, 301, 111));
        pbOnOffLed = new QPushButton(gbLed);
        pbOnOffLed->setObjectName("pbOnOffLed");
        pbOnOffLed->setGeometry(QRect(10, 40, 131, 48));
        laNoir = new QLabel(gbLed);
        laNoir->setObjectName("laNoir");
        laNoir->setGeometry(QRect(230, 40, 51, 51));
        laNoir->setPixmap(QPixmap(QString::fromUtf8("noir.gif")));
        laNoir->setScaledContents(true);
        laRouge = new QLabel(gbLed);
        laRouge->setObjectName("laRouge");
        laRouge->setGeometry(QRect(230, 40, 51, 51));
        laRouge->setPixmap(QPixmap(QString::fromUtf8("rouge.png")));
        laRouge->setScaledContents(true);
        laRouge->raise();
        laNoir->raise();
        pbOnOffLed->raise();
        teTexte = new QTextEdit(centralWidget);
        teTexte->setObjectName("teTexte");
        teTexte->setGeometry(QRect(10, 520, 671, 231));
        teTexte->setReadOnly(true);
        gbCapteurSpi = new QGroupBox(centralWidget);
        gbCapteurSpi->setObjectName("gbCapteurSpi");
        gbCapteurSpi->setGeometry(QRect(10, 220, 361, 111));
        verticalLayoutWidget = new QWidget(gbCapteurSpi);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(150, 30, 161, 68));
        vlSpi = new QVBoxLayout(verticalLayoutWidget);
        vlSpi->setSpacing(6);
        vlSpi->setContentsMargins(11, 11, 11, 11);
        vlSpi->setObjectName("vlSpi");
        vlSpi->setContentsMargins(0, 0, 0, 0);
        leTempSpi = new QLineEdit(verticalLayoutWidget);
        leTempSpi->setObjectName("leTempSpi");
        leTempSpi->setReadOnly(true);

        vlSpi->addWidget(leTempSpi);

        leSeuilTempSpi = new QLineEdit(verticalLayoutWidget);
        leSeuilTempSpi->setObjectName("leSeuilTempSpi");

        vlSpi->addWidget(leSeuilTempSpi);

        label_28 = new QLabel(gbCapteurSpi);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(540, 60, 51, 39));
        label_29 = new QLabel(gbCapteurSpi);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(540, 110, 51, 39));
        verticalLayoutWidget_10 = new QWidget(gbCapteurSpi);
        verticalLayoutWidget_10->setObjectName("verticalLayoutWidget_10");
        verticalLayoutWidget_10->setGeometry(QRect(10, 30, 131, 71));
        vlLSpi = new QVBoxLayout(verticalLayoutWidget_10);
        vlLSpi->setSpacing(6);
        vlLSpi->setContentsMargins(11, 11, 11, 11);
        vlLSpi->setObjectName("vlLSpi");
        vlLSpi->setContentsMargins(0, 0, 0, 0);
        label_26 = new QLabel(verticalLayoutWidget_10);
        label_26->setObjectName("label_26");
        label_26->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSpi->addWidget(label_26);

        label_27 = new QLabel(verticalLayoutWidget_10);
        label_27->setObjectName("label_27");
        label_27->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSpi->addWidget(label_27);

        verticalLayoutWidget_11 = new QWidget(gbCapteurSpi);
        verticalLayoutWidget_11->setObjectName("verticalLayoutWidget_11");
        verticalLayoutWidget_11->setGeometry(QRect(320, 30, 31, 71));
        vlSpiL = new QVBoxLayout(verticalLayoutWidget_11);
        vlSpiL->setSpacing(6);
        vlSpiL->setContentsMargins(11, 11, 11, 11);
        vlSpiL->setObjectName("vlSpiL");
        vlSpiL->setContentsMargins(0, 0, 0, 0);
        label_30 = new QLabel(verticalLayoutWidget_11);
        label_30->setObjectName("label_30");

        vlSpiL->addWidget(label_30);

        label_31 = new QLabel(verticalLayoutWidget_11);
        label_31->setObjectName("label_31");

        vlSpiL->addWidget(label_31);

        gbBouton = new QGroupBox(centralWidget);
        gbBouton->setObjectName("gbBouton");
        gbBouton->setGeometry(QRect(380, 120, 301, 91));
        lEtatBouton = new QLabel(gbBouton);
        lEtatBouton->setObjectName("lEtatBouton");
        lEtatBouton->setGeometry(QRect(20, 40, 261, 31));
        lEtatBouton->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gbLcd = new QGroupBox(centralWidget);
        gbLcd->setObjectName("gbLcd");
        gbLcd->setGeometry(QRect(10, 340, 151, 121));
        pbLcd = new QPushButton(gbLcd);
        pbLcd->setObjectName("pbLcd");
        pbLcd->setGeometry(QRect(20, 30, 91, 29));
        gbEcranRs = new QGroupBox(centralWidget);
        gbEcranRs->setObjectName("gbEcranRs");
        gbEcranRs->setGeometry(QRect(180, 340, 501, 151));
        pbEnvoyer = new QPushButton(gbEcranRs);
        pbEnvoyer->setObjectName("pbEnvoyer");
        pbEnvoyer->setGeometry(QRect(10, 60, 91, 29));
        teRecevoir = new QTextEdit(gbEcranRs);
        teRecevoir->setObjectName("teRecevoir");
        teRecevoir->setGeometry(QRect(190, 30, 301, 111));
        leEnvoyer = new QLineEdit(gbEcranRs);
        leEnvoyer->setObjectName("leEnvoyer");
        leEnvoyer->setGeometry(QRect(10, 30, 171, 29));
        pbEffacer = new QPushButton(centralWidget);
        pbEffacer->setObjectName("pbEffacer");
        pbEffacer->setGeometry(QRect(10, 480, 91, 29));
        CGui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CGui);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1040, 27));
        CGui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CGui);
        mainToolBar->setObjectName("mainToolBar");
        CGui->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CGui);
        statusBar->setObjectName("statusBar");
        CGui->setStatusBar(statusBar);
        dockWidget = new QDockWidget(CGui);
        dockWidget->setObjectName("dockWidget");
        dockWidget->setMinimumSize(QSize(340, 720));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        gbIntervalle = new QGroupBox(dockWidgetContents);
        gbIntervalle->setObjectName("gbIntervalle");
        gbIntervalle->setGeometry(QRect(10, 0, 301, 191));
        layoutWidget3 = new QWidget(gbIntervalle);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(190, 30, 71, 140));
        vlInter = new QVBoxLayout(layoutWidget3);
        vlInter->setSpacing(6);
        vlInter->setContentsMargins(11, 11, 11, 11);
        vlInter->setObjectName("vlInter");
        vlInter->setContentsMargins(0, 0, 0, 0);
        leInterCapt = new QLineEdit(layoutWidget3);
        leInterCapt->setObjectName("leInterCapt");

        vlInter->addWidget(leInterCapt);

        leInterBdd = new QLineEdit(layoutWidget3);
        leInterBdd->setObjectName("leInterBdd");

        vlInter->addWidget(leInterBdd);

        leInterServ = new QLineEdit(layoutWidget3);
        leInterServ->setObjectName("leInterServ");

        vlInter->addWidget(leInterServ);

        leInterPeriph = new QLineEdit(layoutWidget3);
        leInterPeriph->setObjectName("leInterPeriph");

        vlInter->addWidget(leInterPeriph);

        verticalLayoutWidget_5 = new QWidget(gbIntervalle);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(10, 30, 171, 141));
        vlLInter = new QVBoxLayout(verticalLayoutWidget_5);
        vlLInter->setSpacing(6);
        vlLInter->setContentsMargins(11, 11, 11, 11);
        vlLInter->setObjectName("vlLInter");
        vlLInter->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_5);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLInter->addWidget(label_3);

        label_4 = new QLabel(verticalLayoutWidget_5);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLInter->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget_5);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLInter->addWidget(label_5);

        label_6 = new QLabel(verticalLayoutWidget_5);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLInter->addWidget(label_6);

        verticalLayoutWidget_6 = new QWidget(gbIntervalle);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(270, 30, 21, 141));
        vlInterL = new QVBoxLayout(verticalLayoutWidget_6);
        vlInterL->setSpacing(6);
        vlInterL->setContentsMargins(11, 11, 11, 11);
        vlInterL->setObjectName("vlInterL");
        vlInterL->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(verticalLayoutWidget_6);
        label_7->setObjectName("label_7");

        vlInterL->addWidget(label_7);

        label_8 = new QLabel(verticalLayoutWidget_6);
        label_8->setObjectName("label_8");

        vlInterL->addWidget(label_8);

        label_9 = new QLabel(verticalLayoutWidget_6);
        label_9->setObjectName("label_9");

        vlInterL->addWidget(label_9);

        label_10 = new QLabel(verticalLayoutWidget_6);
        label_10->setObjectName("label_10");

        vlInterL->addWidget(label_10);

        gbVS = new QGroupBox(dockWidgetContents);
        gbVS->setObjectName("gbVS");
        gbVS->setGeometry(QRect(10, 200, 301, 221));
        verticalLayoutWidget_2 = new QWidget(gbVS);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(0, 30, 151, 181));
        vlLVS = new QVBoxLayout(verticalLayoutWidget_2);
        vlLVS->setSpacing(6);
        vlLVS->setContentsMargins(11, 11, 11, 11);
        vlLVS->setObjectName("vlLVS");
        vlLVS->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(verticalLayoutWidget_2);
        label_19->setObjectName("label_19");
        label_19->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLVS->addWidget(label_19);

        label_20 = new QLabel(verticalLayoutWidget_2);
        label_20->setObjectName("label_20");
        label_20->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLVS->addWidget(label_20);

        label_21 = new QLabel(verticalLayoutWidget_2);
        label_21->setObjectName("label_21");
        label_21->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLVS->addWidget(label_21);

        label_22 = new QLabel(verticalLayoutWidget_2);
        label_22->setObjectName("label_22");
        label_22->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLVS->addWidget(label_22);

        label_23 = new QLabel(verticalLayoutWidget_2);
        label_23->setObjectName("label_23");
        label_23->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLVS->addWidget(label_23);

        verticalLayoutWidget_3 = new QWidget(gbVS);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(160, 30, 121, 181));
        vlParamsVS = new QVBoxLayout(verticalLayoutWidget_3);
        vlParamsVS->setSpacing(6);
        vlParamsVS->setContentsMargins(11, 11, 11, 11);
        vlParamsVS->setObjectName("vlParamsVS");
        vlParamsVS->setContentsMargins(0, 0, 0, 0);
        cbPorts = new QComboBox(verticalLayoutWidget_3);
        cbPorts->setObjectName("cbPorts");
        cbPorts->setEditable(true);

        vlParamsVS->addWidget(cbPorts);

        cbVitesse = new QComboBox(verticalLayoutWidget_3);
        cbVitesse->addItem(QString());
        cbVitesse->addItem(QString());
        cbVitesse->addItem(QString());
        cbVitesse->addItem(QString());
        cbVitesse->addItem(QString());
        cbVitesse->setObjectName("cbVitesse");
        cbVitesse->setEditable(true);

        vlParamsVS->addWidget(cbVitesse);

        cbParite = new QComboBox(verticalLayoutWidget_3);
        cbParite->addItem(QString());
        cbParite->addItem(QString());
        cbParite->addItem(QString());
        cbParite->setObjectName("cbParite");
        cbParite->setEditable(true);

        vlParamsVS->addWidget(cbParite);

        cbBits = new QComboBox(verticalLayoutWidget_3);
        cbBits->addItem(QString());
        cbBits->addItem(QString());
        cbBits->setObjectName("cbBits");
        cbBits->setEditable(true);

        vlParamsVS->addWidget(cbBits);

        cbStop = new QComboBox(verticalLayoutWidget_3);
        cbStop->addItem(QString());
        cbStop->addItem(QString());
        cbStop->addItem(QString());
        cbStop->setObjectName("cbStop");
        cbStop->setEditable(true);

        vlParamsVS->addWidget(cbStop);

        gbServeur = new QGroupBox(dockWidgetContents);
        gbServeur->setObjectName("gbServeur");
        gbServeur->setGeometry(QRect(10, 430, 301, 111));
        layoutWidget4 = new QWidget(gbServeur);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(140, 30, 151, 68));
        vlServer = new QVBoxLayout(layoutWidget4);
        vlServer->setSpacing(6);
        vlServer->setContentsMargins(11, 11, 11, 11);
        vlServer->setObjectName("vlServer");
        vlServer->setContentsMargins(0, 0, 0, 0);
        leAdrServ = new QLineEdit(layoutWidget4);
        leAdrServ->setObjectName("leAdrServ");

        vlServer->addWidget(leAdrServ);

        lePortServ = new QLineEdit(layoutWidget4);
        lePortServ->setObjectName("lePortServ");

        vlServer->addWidget(lePortServ);

        verticalLayoutWidget_4 = new QWidget(gbServeur);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(10, 30, 121, 52));
        vlLServeur = new QVBoxLayout(verticalLayoutWidget_4);
        vlLServeur->setSpacing(6);
        vlLServeur->setContentsMargins(11, 11, 11, 11);
        vlLServeur->setObjectName("vlLServeur");
        vlLServeur->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(verticalLayoutWidget_4);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLServeur->addWidget(label_13);

        label_14 = new QLabel(verticalLayoutWidget_4);
        label_14->setObjectName("label_14");
        label_14->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLServeur->addWidget(label_14);

        gbSgbd = new QGroupBox(dockWidgetContents);
        gbSgbd->setObjectName("gbSgbd");
        gbSgbd->setGeometry(QRect(10, 550, 301, 181));
        layoutWidget5 = new QWidget(gbSgbd);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(150, 30, 141, 140));
        vlSgbd = new QVBoxLayout(layoutWidget5);
        vlSgbd->setSpacing(6);
        vlSgbd->setContentsMargins(11, 11, 11, 11);
        vlSgbd->setObjectName("vlSgbd");
        vlSgbd->setContentsMargins(0, 0, 0, 0);
        leAdrSgbd = new QLineEdit(layoutWidget5);
        leAdrSgbd->setObjectName("leAdrSgbd");

        vlSgbd->addWidget(leAdrSgbd);

        leNomBdd = new QLineEdit(layoutWidget5);
        leNomBdd->setObjectName("leNomBdd");

        vlSgbd->addWidget(leNomBdd);

        leUserSgbd = new QLineEdit(layoutWidget5);
        leUserSgbd->setObjectName("leUserSgbd");

        vlSgbd->addWidget(leUserSgbd);

        lePassSgbd = new QLineEdit(layoutWidget5);
        lePassSgbd->setObjectName("lePassSgbd");
        lePassSgbd->setEchoMode(QLineEdit::EchoMode::Password);

        vlSgbd->addWidget(lePassSgbd);

        verticalLayoutWidget_7 = new QWidget(gbSgbd);
        verticalLayoutWidget_7->setObjectName("verticalLayoutWidget_7");
        verticalLayoutWidget_7->setGeometry(QRect(10, 30, 131, 141));
        vlLSgbd = new QVBoxLayout(verticalLayoutWidget_7);
        vlLSgbd->setSpacing(6);
        vlLSgbd->setContentsMargins(11, 11, 11, 11);
        vlLSgbd->setObjectName("vlLSgbd");
        vlLSgbd->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(verticalLayoutWidget_7);
        label_15->setObjectName("label_15");
        label_15->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSgbd->addWidget(label_15);

        label_16 = new QLabel(verticalLayoutWidget_7);
        label_16->setObjectName("label_16");
        label_16->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSgbd->addWidget(label_16);

        label_17 = new QLabel(verticalLayoutWidget_7);
        label_17->setObjectName("label_17");
        label_17->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSgbd->addWidget(label_17);

        label_18 = new QLabel(verticalLayoutWidget_7);
        label_18->setObjectName("label_18");
        label_18->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        vlLSgbd->addWidget(label_18);

        dockWidget->setWidget(dockWidgetContents);
        CGui->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, dockWidget);

        retranslateUi(CGui);
        QObject::connect(pbEffacer, &QPushButton::clicked, teTexte, qOverload<>(&QTextEdit::clear));

        QMetaObject::connectSlotsByName(CGui);
    } // setupUi

    void retranslateUi(QMainWindow *CGui)
    {
        CGui->setWindowTitle(QCoreApplication::translate("CGui", "Formation Qt C++ (PhA-2024 v2.0)", nullptr));
        gbCapteurs->setTitle(QCoreApplication::translate("CGui", "Capteurs I2C", nullptr));
        leSeuilTempI2c->setText(QCoreApplication::translate("CGui", "37", nullptr));
        leSeuilHumI2c->setText(QCoreApplication::translate("CGui", "20", nullptr));
        label_24->setText(QCoreApplication::translate("CGui", "Seuil de temp :", nullptr));
        label_25->setText(QCoreApplication::translate("CGui", "Seuil d'humidit\303\251 :", nullptr));
        label->setText(QCoreApplication::translate("CGui", "Temp\303\251rature : ", nullptr));
        label_2->setText(QCoreApplication::translate("CGui", "Humidit\303\251 :", nullptr));
        label_11->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        label_12->setText(QCoreApplication::translate("CGui", "%", nullptr));
        label_32->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        label_33->setText(QCoreApplication::translate("CGui", "%", nullptr));
        pbStartStop->setText(QCoreApplication::translate("CGui", "Start acquisitions", nullptr));
        gbLed->setTitle(QCoreApplication::translate("CGui", "Commander la LED", nullptr));
        pbOnOffLed->setText(QCoreApplication::translate("CGui", "Allumer", nullptr));
        laNoir->setText(QString());
        laRouge->setText(QString());
        gbCapteurSpi->setTitle(QCoreApplication::translate("CGui", "Capteur SPI", nullptr));
        leSeuilTempSpi->setText(QCoreApplication::translate("CGui", "36", nullptr));
        label_28->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        label_29->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        label_26->setText(QCoreApplication::translate("CGui", "Temp\303\251rature :", nullptr));
        label_27->setText(QCoreApplication::translate("CGui", "Seuil de temp :", nullptr));
        label_30->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        label_31->setText(QCoreApplication::translate("CGui", "\302\260C", nullptr));
        gbBouton->setTitle(QCoreApplication::translate("CGui", "Etat du bouton poussoir", nullptr));
        lEtatBouton->setText(QCoreApplication::translate("CGui", "Ind\303\251termin\303\251 !", nullptr));
        gbLcd->setTitle(QCoreApplication::translate("CGui", "Commandes \303\251cran", nullptr));
        pbLcd->setText(QCoreApplication::translate("CGui", "Afficher", nullptr));
        gbEcranRs->setTitle(QCoreApplication::translate("CGui", "Ecran RS232C", nullptr));
        pbEnvoyer->setText(QCoreApplication::translate("CGui", "Envoyer", nullptr));
        pbEffacer->setText(QCoreApplication::translate("CGui", "Effacer", nullptr));
        dockWidget->setWindowTitle(QCoreApplication::translate("CGui", "Initialisation", nullptr));
        gbIntervalle->setTitle(QCoreApplication::translate("CGui", "Intervalles", nullptr));
        leInterCapt->setInputMask(QCoreApplication::translate("CGui", "99", nullptr));
        leInterCapt->setText(QCoreApplication::translate("CGui", "2", nullptr));
        leInterBdd->setInputMask(QCoreApplication::translate("CGui", "99", nullptr));
        leInterBdd->setText(QCoreApplication::translate("CGui", "30", nullptr));
        leInterServ->setInputMask(QCoreApplication::translate("CGui", "99", nullptr));
        leInterServ->setText(QCoreApplication::translate("CGui", "10", nullptr));
        leInterPeriph->setInputMask(QCoreApplication::translate("CGui", "99", nullptr));
        leInterPeriph->setText(QCoreApplication::translate("CGui", "10", nullptr));
        label_3->setText(QCoreApplication::translate("CGui", "Capteurs :", nullptr));
        label_4->setText(QCoreApplication::translate("CGui", "Base de donn\303\251es :", nullptr));
        label_5->setText(QCoreApplication::translate("CGui", "Serveur (r\303\251seau) :", nullptr));
        label_6->setText(QCoreApplication::translate("CGui", "P\303\251riph\303\251rique RS232C :", nullptr));
        label_7->setText(QCoreApplication::translate("CGui", "s", nullptr));
        label_8->setText(QCoreApplication::translate("CGui", "s", nullptr));
        label_9->setText(QCoreApplication::translate("CGui", "s", nullptr));
        label_10->setText(QCoreApplication::translate("CGui", "s", nullptr));
        gbVS->setTitle(QCoreApplication::translate("CGui", "Param\303\250tres liaison s\303\251rie", nullptr));
        label_19->setText(QCoreApplication::translate("CGui", "Choix de la liaison :", nullptr));
        label_20->setText(QCoreApplication::translate("CGui", "Vitesse :", nullptr));
        label_21->setText(QCoreApplication::translate("CGui", "Parit\303\251 :", nullptr));
        label_22->setText(QCoreApplication::translate("CGui", "Nbre de bits/car :", nullptr));
        label_23->setText(QCoreApplication::translate("CGui", "Nbre de bit de stop :", nullptr));
        cbVitesse->setItemText(0, QCoreApplication::translate("CGui", "9600", nullptr));
        cbVitesse->setItemText(1, QCoreApplication::translate("CGui", "19200", nullptr));
        cbVitesse->setItemText(2, QCoreApplication::translate("CGui", "4800", nullptr));
        cbVitesse->setItemText(3, QCoreApplication::translate("CGui", "2400", nullptr));
        cbVitesse->setItemText(4, QCoreApplication::translate("CGui", "1200", nullptr));

        cbParite->setItemText(0, QCoreApplication::translate("CGui", "Sans parit\303\251", nullptr));
        cbParite->setItemText(1, QCoreApplication::translate("CGui", "Paire", nullptr));
        cbParite->setItemText(2, QCoreApplication::translate("CGui", "Impaire", nullptr));

        cbBits->setItemText(0, QCoreApplication::translate("CGui", "8", nullptr));
        cbBits->setItemText(1, QCoreApplication::translate("CGui", "7", nullptr));

        cbStop->setItemText(0, QCoreApplication::translate("CGui", "1", nullptr));
        cbStop->setItemText(1, QCoreApplication::translate("CGui", "2", nullptr));
        cbStop->setItemText(2, QString());

        gbServeur->setTitle(QCoreApplication::translate("CGui", "Param\303\250tres serveur", nullptr));
        leAdrServ->setInputMask(QCoreApplication::translate("CGui", "999.999.999.999", nullptr));
        leAdrServ->setText(QCoreApplication::translate("CGui", "192.168.2.151", nullptr));
        lePortServ->setText(QCoreApplication::translate("CGui", "5555", nullptr));
        label_13->setText(QCoreApplication::translate("CGui", "Adresse IP :", nullptr));
        label_14->setText(QCoreApplication::translate("CGui", "Port :", nullptr));
        gbSgbd->setTitle(QCoreApplication::translate("CGui", "Param\303\250tres SGBD", nullptr));
        leAdrSgbd->setInputMask(QCoreApplication::translate("CGui", "999.999.999.999", nullptr));
        leAdrSgbd->setText(QCoreApplication::translate("CGui", "192.168.1.31", nullptr));
        leNomBdd->setText(QCoreApplication::translate("CGui", "bddFormation", nullptr));
        leUserSgbd->setText(QCoreApplication::translate("CGui", "bddFormation", nullptr));
        lePassSgbd->setText(QCoreApplication::translate("CGui", "bddFormation", nullptr));
        label_15->setText(QCoreApplication::translate("CGui", "Adresse IP :", nullptr));
        label_16->setText(QCoreApplication::translate("CGui", "Nom de la base :", nullptr));
        label_17->setText(QCoreApplication::translate("CGui", "Nom utilisateur :", nullptr));
        label_18->setText(QCoreApplication::translate("CGui", "Mot de passe :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CGui: public Ui_CGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGUI_H
