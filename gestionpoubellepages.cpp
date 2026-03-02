#include "gestionpoubellepages.h"
#include <QSqlQuery>
#include "ui_gestionpoubellepages.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QDate>
#include <QDateTime>
#include <QPrinter>
#include <QPainter>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

// ============================================================
//  CONSTRUCTEUR
// ============================================================
GestionPoubellePage::GestionPoubellePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GestionPoubellePage)
{
    ui->setupUi(this);

    setStyleSheet(
        "QWidget#GestionPoubellePage { background-color: #F0F3F5; }"
        "QWidget#topButtonBar, QWidget#searchBar { background-color: transparent; }"
        "QPushButton#btnListPoubelles, QPushButton#btnAddPoubelle,"
        "QPushButton#btnStatistics, QPushButton#btnHistorique { min-height: 32px; }"
        "QPushButton#btnSearch, QPushButton#btnTri, QPushButton#btnExportPdf {"
        "  background-color:#8e944e; color:white; border:none; border-radius:8px;"
        "  padding:5px 12px; font-size:8pt; font-weight:bold; }"
        "QPushButton#btnSearch:hover, QPushButton#btnTri:hover, QPushButton#btnExportPdf:hover {"
        "  background-color:#6d7339; }"
        "QPushButton#btnConfirmAdd, QPushButton#btnConfirmUpdate {"
        "  background-color:#8e944e; color:white; border:none; border-radius:10px;"
        "  padding:6px 18px; font-size:8pt; font-weight:bold; }"
        "QPushButton#btnConfirmAdd:hover, QPushButton#btnConfirmUpdate:hover {"
        "  background-color:#6d7339; }"
        "QLineEdit, QComboBox, QSpinBox, QDateEdit {"
        "  border:2px solid #E0E0E0; border-radius:8px; padding:3px 6px;"
        "  background-color:white; color:#2C3E50; }"
        "QComboBox QAbstractItemView { background-color:white; color:#2C3E50;"
        "  selection-background-color:rgba(142,148,78,0.25); selection-color:#2C3E50; outline:none; }"
        "QTextEdit#inputNotes { border:2px solid #E0E0E0; border-radius:8px;"
        "  padding:6px; background-color:white; }"
        "QLabel { color:#2C3E50; font-size:8.5pt; font-weight:600; }"
        "QLabel#formTitle { color:#8e944e; font-size:11pt; font-weight:800; }"
        "QTableWidget { background-color:white; alternate-background-color:#F7F8FA;"
        "  border:2px solid #E0E0E0; border-radius:10px; gridline-color:#E0E0E0;"
        "  font-size:8pt; color:#2C3E50; }"
        "QTableWidget::item { padding:2px 4px; border-bottom:1px solid #F0F0F0; }"
        "QTableWidget::item:selected { background-color:rgba(142,148,78,0.22); color:#2C3E50; }"
        "QHeaderView::section { background-color:#8e944e; color:white; padding:4px;"
        "  border:none; font-weight:bold; font-size:8pt; }"
        "QWidget#formFieldsContainer { background-color:white; border:2px solid #8e944e;"
        "  border-radius:15px; }"
        "QWidget#statsLeftContainer, QWidget#statsRightContainer {"
        "  background-color:white; border:2px solid #E0E0E0; border-radius:15px; }"
        "QCheckBox { color:#2C3E50; font-size:8.5pt; font-weight:600; }"
        "QCheckBox::indicator { width:18px; height:18px; border:2px solid #E0E0E0;"
        "  border-radius:4px; background-color:white; }"
        "QCheckBox::indicator:checked { background-color:#8e944e; border-color:#8e944e; }"
    );

    QWidget *ffc = this->findChild<QWidget*>("formFieldsContainer");
    if (ffc) ffc->setMaximumWidth(900);



    if (ui->formGrid)    ui->formGrid->setVerticalSpacing(10);

    if (ui->searchBox)   { ui->searchBox->setClearButtonEnabled(true);
                           ui->searchBox->setPlaceholderText("Rechercher par type, ID, zone..."); }

    if (ui->inputTypeDechet)
        ui->inputTypeDechet->addItems({"Plastique","Verre","Papier","Organique","Métal","Mixte"});
    if (ui->inputEtat)
        ui->inputEtat->addItems({"Bon","Moyen","Mauvais"});
    if (ui->sortCombo)
        ui->sortCombo->addItems({"Type","État"});
    if (ui->inputTauxRemplissage) {
        ui->inputTauxRemplissage->setRange(0,100);
        ui->inputTauxRemplissage->setSuffix(" %");
    }
    if (ui->inputDateInstallation) {
        ui->inputDateInstallation->setDate(QDate::currentDate());
        ui->inputDateInstallation->setCalendarPopup(true);
    }
    if (ui->inputDateCollecte) {
        ui->inputDateCollecte->setDate(QDate::currentDate());
        ui->inputDateCollecte->setCalendarPopup(true);
    }

    setupPoubelleTable();
    setupCharts();

    connect(ui->btnListPoubelles, &QPushButton::clicked, this, &GestionPoubellePage::showListPage);
    connect(ui->btnAddPoubelle,   &QPushButton::clicked, this, &GestionPoubellePage::showFormPage);
    connect(ui->btnStatistics,    &QPushButton::clicked, this, &GestionPoubellePage::showStatsPage);
    connect(ui->btnHistorique,    &QPushButton::clicked, this, &GestionPoubellePage::showHistoriquePage);
    connect(ui->btnConfirmAdd,    &QPushButton::clicked, this, &GestionPoubellePage::ajouterPoubelle);
    connect(ui->btnConfirmUpdate, &QPushButton::clicked, this, &GestionPoubellePage::modifierPoubelle);
    connect(ui->btnSearch,        &QPushButton::clicked, this, &GestionPoubellePage::rechercherPoubelle);
    connect(ui->btnTri,           &QPushButton::clicked, this, &GestionPoubellePage::trierPoubelles);
    connect(ui->btnExportPdf,     &QPushButton::clicked, this, &GestionPoubellePage::exporterPDF);

    // Clic sur une ligne → pré-remplir formulaire pour modification
    connect(ui->poubelleTable, &QTableWidget::cellClicked, [this](int row, int) {
        if (row < 0 || row >= ui->poubelleTable->rowCount()) return;
        auto item = [&](int col) -> QString {
            return ui->poubelleTable->item(row,col)
                   ? ui->poubelleTable->item(row,col)->text() : "";
        };
        currentEditId = item(0).toInt();
        ui->inputTypeDechet->setCurrentText(item(1));
        ui->inputEtat->setCurrentText(item(3));
        ui->inputTauxRemplissage->setValue(item(4).toInt());
        ui->inputLocalisation->setText(item(6));  // Zone = localisation
        ui->inputDateInstallation->setDate(
            QDate::fromString(item(5), "dd/MM/yyyy"));
        ui->inputDateCollecte->setDate(QDate::currentDate());
        ui->checkEndommagee->setChecked(false);
        ui->inputNotes->clear();

        ui->formTitle->setText("Modifier la Poubelle #" + item(0));
        ui->btnConfirmAdd->setVisible(false);
        ui->btnConfirmUpdate->setVisible(true);
        showFormPage();
    });

    rafraichirTable();
    showListPage();
}

GestionPoubellePage::~GestionPoubellePage() { delete ui; }

// ============================================================
//  NAVIGATION
// ============================================================
void GestionPoubellePage::showListPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageList);
    ui->btnListPoubelles->setStyleSheet(
        "QPushButton{background-color:#8e944e;color:white;border:none;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#6d7339;}");
    QString inactif =
        "QPushButton{background-color:white;color:#8e944e;border:2px solid #E0E0E0;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#F5F5F5;border-color:#8e944e;}";
    ui->btnAddPoubelle->setStyleSheet(inactif);
    ui->btnStatistics->setStyleSheet(inactif);
    ui->btnHistorique->setStyleSheet(inactif);
    rafraichirTable();
}

void GestionPoubellePage::showFormPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageForm);
    QString actif =
        "QPushButton{background-color:#8e944e;color:white;border:none;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#6d7339;}";
    QString inactif =
        "QPushButton{background-color:white;color:#8e944e;border:2px solid #E0E0E0;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#F5F5F5;border-color:#8e944e;}";
    ui->btnListPoubelles->setStyleSheet(inactif);
    ui->btnAddPoubelle->setStyleSheet(actif);
    ui->btnStatistics->setStyleSheet(inactif);
    ui->btnHistorique->setStyleSheet(inactif);
}

void GestionPoubellePage::showStatsPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageStats);
    setupCharts();
    QString actif =
        "QPushButton{background-color:#8e944e;color:white;border:none;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#6d7339;}";
    QString inactif =
        "QPushButton{background-color:white;color:#8e944e;border:2px solid #E0E0E0;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#F5F5F5;border-color:#8e944e;}";
    ui->btnListPoubelles->setStyleSheet(inactif);
    ui->btnAddPoubelle->setStyleSheet(inactif);
    ui->btnStatistics->setStyleSheet(actif);
    ui->btnHistorique->setStyleSheet(inactif);
}

void GestionPoubellePage::showHistoriquePage()
{
    ui->pagesStack->setCurrentWidget(ui->pageHistorique);
    chargerHistorique();
    QString actif =
        "QPushButton{background-color:#8e944e;color:white;border:none;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#6d7339;}";
    QString inactif =
        "QPushButton{background-color:white;color:#8e944e;border:2px solid #E0E0E0;"
        "border-radius:8px;padding:6px 12px;font-size:8pt;font-weight:bold;}"
        "QPushButton:hover{background-color:#F5F5F5;border-color:#8e944e;}";
    ui->btnListPoubelles->setStyleSheet(inactif);
    ui->btnAddPoubelle->setStyleSheet(inactif);
    ui->btnStatistics->setStyleSheet(inactif);
    ui->btnHistorique->setStyleSheet(actif);
}

// ============================================================
//  CREATE
// ============================================================
void GestionPoubellePage::ajouterPoubelle()
{
    if (ui->inputLocalisation->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La localisation est obligatoire !");
        return;
    }

    // Générer ID auto via Oracle : MAX(ID_POUBELLE) + 1
    QSqlQuery qId;
    qId.exec("SELECT NVL(MAX(ID_POUBELLE), 0) + 1 FROM POUBELLE");
    int newId = 1;
    if (qId.next()) newId = qId.value(0).toInt();

    Poubelle p;
    p.setId(newId);
    p.setTypeDechet(ui->inputTypeDechet->currentText());
    p.setCapaciteMax(100);  // valeur par défaut (pas de champ dans UI)
    p.setEtat(ui->inputEtat->currentText());
    p.setTauxRemplissage(ui->inputTauxRemplissage->value());
    p.setDateInstallation(ui->inputDateInstallation->date());
    // Utiliser le premier ID_ZONE disponible dans la table ZONE
    QSqlQuery qZone;
    qZone.exec("SELECT MIN(ID_ZONE) FROM ZONE");
    int idZone = 1;
    if (qZone.next() && !qZone.value(0).isNull()) idZone = qZone.value(0).toInt();
    p.setIdZone(idZone);

    if (p.ajouter()) {
        sauvegarderHistorique("Ajout", p.getId(), p.getTypeDechet(),
                              ui->inputLocalisation->text());
        if (p.getTauxRemplissage() >= 80)
            QMessageBox::warning(this, "Alerte",
                QString("⚠ La poubelle #%1 est à %2% de remplissage !")
                    .arg(p.getId()).arg(p.getTauxRemplissage()));
        QMessageBox::information(this, "Succès", "Poubelle ajoutée avec succès !");
        viderFormulaire();
        rafraichirTable();
        showListPage();
    } else {
        QMessageBox::critical(this, "Erreur BD",
            "Échec de l'ajout !\nVérifiez la connexion Oracle et que l'ID n'existe pas déjà.");
    }
}

// ============================================================
//  UPDATE
// ============================================================
void GestionPoubellePage::modifierPoubelle()
{
    if (currentEditId <= 0) {
        QMessageBox::warning(this, "Erreur",
            "Aucune poubelle sélectionnée.\nCliquez d'abord sur une ligne dans la liste.");
        return;
    }

    Poubelle p;
    p.setId(currentEditId);
    p.setTypeDechet(ui->inputTypeDechet->currentText());
    p.setCapaciteMax(100);
    p.setEtat(ui->inputEtat->currentText());
    p.setTauxRemplissage(ui->inputTauxRemplissage->value());
    p.setDateInstallation(ui->inputDateInstallation->date());
    // Utiliser le premier ID_ZONE disponible
    QSqlQuery qZone2;
    qZone2.exec("SELECT MIN(ID_ZONE) FROM ZONE");
    int idZone2 = 1;
    if (qZone2.next() && !qZone2.value(0).isNull()) idZone2 = qZone2.value(0).toInt();
    p.setIdZone(idZone2);

    if (p.modifier()) {
        sauvegarderHistorique("Modification", p.getId(), p.getTypeDechet(),
                              ui->inputLocalisation->text());
        QMessageBox::information(this, "Succès", "Poubelle modifiée avec succès !");
        currentEditId = -1;
        viderFormulaire();
        rafraichirTable();
        showListPage();
    } else {
        QMessageBox::critical(this, "Erreur BD", "Échec de la modification !");
    }
}

// ============================================================
//  DELETE
// ============================================================
void GestionPoubellePage::supprimerPoubelle()
{
    int row = ui->poubelleTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune poubelle sélectionnée !");
        return;
    }
    int id = ui->poubelleTable->item(row,0)
             ? ui->poubelleTable->item(row,0)->text().toInt() : 0;
    if (id <= 0) return;

    auto reply = QMessageBox::question(this, "Confirmation",
        QString("Supprimer la poubelle #%1 ?").arg(id),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (Ptmp.supprimer(id)) {
            sauvegarderHistorique("Suppression", id, "", "");
            QMessageBox::information(this, "Succès", "Poubelle supprimée !");
            if (currentEditId == id) currentEditId = -1;
            rafraichirTable();
        } else {
            QMessageBox::critical(this, "Erreur BD", "Échec de la suppression !");
        }
    }
}

// ============================================================
//  RECHERCHE
// ============================================================
void GestionPoubellePage::rechercherPoubelle()
{
    QString mot = ui->searchBox->text().trimmed();
    QSqlQueryModel *model = mot.isEmpty() ? Ptmp.afficher() : Ptmp.rechercher(mot);
    remplirTableDepuisModel(model);
    delete model;
}

// ============================================================
//  TRI
// ============================================================
void GestionPoubellePage::trierPoubelles()
{
    QSqlQueryModel *model = (ui->sortCombo->currentText() == "État")
        ? Ptmp.trierParEtat() : Ptmp.trierParType();
    remplirTableDepuisModel(model);
    delete model;
}

// ============================================================
//  EXPORT PDF
// ============================================================
void GestionPoubellePage::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Exporter en PDF","","PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this,"Erreur","Impossible de créer le PDF");
        return;
    }
    painter.setFont(QFont("Arial",16,QFont::Bold));
    painter.drawText(100,100,"Rapport - Gestion des Poubelles");
    painter.setFont(QFont("Arial",10));
    painter.drawText(100,150,"Date : " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    painter.drawText(100,180,"Nombre de poubelles : " + QString::number(ui->poubelleTable->rowCount()));

    int y = 260;
    painter.setFont(QFont("Arial",9,QFont::Bold));
    painter.drawText(100,y,"ID");  painter.drawText(180,y,"Type");
    painter.drawText(340,y,"État"); painter.drawText(470,y,"Taux%");
    painter.drawText(590,y,"Zone");
    y += 30;
    painter.setFont(QFont("Arial",9));
    for (int r=0; r<ui->poubelleTable->rowCount(); ++r) {
        auto t=[&](int c){ return ui->poubelleTable->item(r,c)
                           ? ui->poubelleTable->item(r,c)->text() : ""; };
        painter.drawText(100,y,t(0)); painter.drawText(180,y,t(1));
        painter.drawText(340,y,t(3)); painter.drawText(470,y,t(4)+"%");
        painter.drawText(590,y,t(6).left(20));
        y+=25;
        if(y>2800){printer.newPage();y=100;}
    }
    painter.end();
    QMessageBox::information(this,"Succès","PDF exporté !");
}

// ============================================================
//  NOTIFICATION
// ============================================================
void GestionPoubellePage::afficherNotification()
{
    QSqlQueryModel *m = Ptmp.afficherPleinement();
    if (m->rowCount()>0)
        QMessageBox::warning(this,"Alerte",
            QString("%1 poubelle(s) à 80%+ de remplissage !").arg(m->rowCount()));
    delete m;
}

// ============================================================
//  HISTORIQUE
// ============================================================
void GestionPoubellePage::chargerHistorique()
{
    if (!ui->historiqueTable) return;
    ui->historiqueTable->setRowCount(0);
    for (int i=0; i<historique.size(); ++i) {
        ui->historiqueTable->insertRow(i);
        for (int j=0; j<4; ++j)
            ui->historiqueTable->setItem(i,j,new QTableWidgetItem(historique[i].value(j)));
    }
}

void GestionPoubellePage::sauvegarderHistorique(const QString &action, int id,
                                                  const QString &type, const QString &zone)
{
    historique.prepend({
        QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"),
        action,
        QString("Poubelle #%1 (%2)").arg(id).arg(type),
        zone
    });
}

// ============================================================
//  SETUP TABLE
// ============================================================
void GestionPoubellePage::setupPoubelleTable()
{
    // 8 colonnes : ID|Type|Cap|État|Taux|Date|Zone|Opérations
    ui->poubelleTable->setColumnCount(8);
    ui->poubelleTable->setHorizontalHeaderLabels({
        "ID","Type Déchet","Cap. Max","État","Taux (%)","Date Install.","Zone","Opérations"
    });
    ui->poubelleTable->horizontalHeader()->setStretchLastSection(false);
    ui->poubelleTable->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->poubelleTable->verticalHeader()->setVisible(false);
    ui->poubelleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->poubelleTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->poubelleTable->setAlternatingRowColors(true);
    ui->poubelleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->poubelleTable->setFocusPolicy(Qt::NoFocus);
    ui->poubelleTable->setColumnWidth(0,50);
    ui->poubelleTable->setColumnWidth(1,110);
    ui->poubelleTable->setColumnWidth(2,80);
    ui->poubelleTable->setColumnWidth(3,80);
    ui->poubelleTable->setColumnWidth(4,75);
    ui->poubelleTable->setColumnWidth(5,105);
    ui->poubelleTable->setColumnWidth(7,100);

    if (ui->historiqueTable) {
        ui->historiqueTable->setColumnCount(4);
        ui->historiqueTable->setHorizontalHeaderLabels({"Date/Heure","Action","Poubelle","Détails"});
        ui->historiqueTable->horizontalHeader()->setStretchLastSection(true);
        ui->historiqueTable->verticalHeader()->setVisible(false);
        ui->historiqueTable->setAlternatingRowColors(true);
        ui->historiqueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

// ============================================================
//  SETUP CHARTS
// ============================================================
void GestionPoubellePage::setupCharts()
{
    if (!ui->statsLeftContainer || !ui->statsRightContainer) return;

    auto clearW = [](QWidget *w){
        if (!w->layout()) { w->setLayout(new QVBoxLayout(w)); return; }
        QLayoutItem *it;
        while ((it = w->layout()->takeAt(0))!=nullptr) { delete it->widget(); delete it; }
    };
    clearW(ui->statsLeftContainer);
    clearW(ui->statsRightContainer);

    auto *left  = qobject_cast<QVBoxLayout*>(ui->statsLeftContainer->layout());
    auto *right = qobject_cast<QVBoxLayout*>(ui->statsRightContainer->layout());

    // ── Camembert par état ─────────────────────────────────
    QPieSeries *pie = new QPieSeries();
    QSqlQueryModel *se = Ptmp.statistiquesParEtat();
    QStringList cols = {"#2ECC71","#F39C12","#E74C3C","#3498DB"};
    for (int i=0; i<se->rowCount(); ++i) {
        QString lbl = se->data(se->index(i,0)).toString();
        int cnt = se->data(se->index(i,1)).toInt();
        auto *s = pie->append(lbl+" ("+QString::number(cnt)+")", cnt);
        s->setColor(QColor(cols.value(i%cols.size())));
        s->setLabelVisible(true);
    }
    delete se;

    QChart *pc = new QChart();
    pc->addSeries(pie);
    pc->setTitle("Répartition par État");
    pc->setAnimationOptions(QChart::SeriesAnimations);
    auto *pv = new QChartView(pc);
    pv->setRenderHint(QPainter::Antialiasing);
    pv->setMinimumHeight(150);
    left->addWidget(pv);

    // ── Barres par type ────────────────────────────────────
    auto *cs = new QBarSet("Nombre"); cs->setColor(QColor("#05668D"));
    auto *fs = new QBarSet("Taux Moyen (%)"); fs->setColor(QColor("#8e944e"));
    QStringList cats;
    QSqlQueryModel *st = Ptmp.statistiquesParType();
    for (int i=0; i<st->rowCount(); ++i) {
        cats << st->data(st->index(i,0)).toString();
        *cs << st->data(st->index(i,1)).toInt();
        *fs << st->data(st->index(i,2)).toDouble();
    }
    delete st;

    auto *bs = new QBarSeries(); bs->append(cs); bs->append(fs);
    QChart *bc = new QChart();
    bc->addSeries(bs);
    bc->setTitle("Statistiques par Type");
    bc->setAnimationOptions(QChart::SeriesAnimations);
    auto *ax = new QBarCategoryAxis(); ax->append(cats);
    bc->addAxis(ax, Qt::AlignBottom); bs->attachAxis(ax);
    auto *ay = new QValueAxis(); ay->setRange(0,100);
    bc->addAxis(ay, Qt::AlignLeft); bs->attachAxis(ay);
    bc->legend()->setAlignment(Qt::AlignTop);
    auto *bv = new QChartView(bc);
    bv->setRenderHint(QPainter::Antialiasing);
    bv->setMinimumHeight(150);
    right->addWidget(bv);
}

// ============================================================
//  RAFRAICHIR TABLE
// ============================================================
void GestionPoubellePage::rafraichirTable()
{
    QSqlQueryModel *model = Ptmp.afficher();
    remplirTableDepuisModel(model);
    delete model;
}

// ============================================================
//  REMPLIR TABLE depuis QSqlQueryModel
//  Colonnes modèle Oracle : 0=ID 1=Type 2=Cap 3=Etat 4=Taux 5=Date 6=Zone
//  Colonnes table widget  : 0=ID 1=Type 2=Cap 3=Etat 4=Taux 5=Date 6=Zone 7=Opérations
// ============================================================
void GestionPoubellePage::remplirTableDepuisModel(QSqlQueryModel *model)
{
    ui->poubelleTable->setRowCount(0);

    for (int row=0; row<model->rowCount(); ++row) {
        ui->poubelleTable->insertRow(row);
        ui->poubelleTable->setRowHeight(row,30);

        auto val = [&](int col){ return model->data(model->index(row,col)).toString(); };

        // 0 ID
        ui->poubelleTable->setItem(row,0,new QTableWidgetItem(val(0)));
        // 1 Type
        ui->poubelleTable->setItem(row,1,new QTableWidgetItem(val(1)));
        // 2 Capacité
        ui->poubelleTable->setItem(row,2,new QTableWidgetItem(val(2)));
        // 3 État (coloré)
        QString etat=val(3);
        QTableWidgetItem *ei=new QTableWidgetItem(etat);
        if(etat=="Bon")         ei->setBackground(QColor(46,204,113,50));
        else if(etat=="Moyen")  ei->setBackground(QColor(255,195,0,50));
        else                    ei->setBackground(QColor(231,76,60,50));
        ui->poubelleTable->setItem(row,3,ei);
        // 4 Taux (coloré)
        int taux=model->data(model->index(row,4)).toInt();
        QTableWidgetItem *ti=new QTableWidgetItem(QString::number(taux)+"%");
        if(taux>=80)       ti->setBackground(QColor(231,76,60,50));
        else if(taux>=50)  ti->setBackground(QColor(255,195,0,50));
        else               ti->setBackground(QColor(46,204,113,50));
        ui->poubelleTable->setItem(row,4,ti);
        // 5 Date
        ui->poubelleTable->setItem(row,5,new QTableWidgetItem(val(5)));
        // 6 Zone
        ui->poubelleTable->setItem(row,6,new QTableWidgetItem(val(6)));

        // 7 Boutons Modifier / Supprimer
        // Capturer toutes les données PAR VALEUR pour éviter crash après delete model
        int    id   = model->data(model->index(row,0)).toInt();
        QString type= model->data(model->index(row,1)).toString();
        QString etat2=val(3);
        int    taux2= model->data(model->index(row,4)).toInt();
        QString date2=val(5);

        QWidget *bw=new QWidget();
        bw->setStyleSheet("background:transparent;");
        QHBoxLayout *bl=new QHBoxLayout(bw);
        bl->setContentsMargins(4,2,4,2); bl->setAlignment(Qt::AlignCenter);

        QPushButton *btnUpd=new QPushButton();
        btnUpd->setIcon(QIcon(QPixmap(":/images/update.png").scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        btnUpd->setIconSize(QSize(28,28)); btnUpd->setFixedSize(34,34);
        btnUpd->setFlat(true);
        btnUpd->setStyleSheet("QPushButton{background:transparent;border:none;}");
        btnUpd->setCursor(Qt::PointingHandCursor);
        btnUpd->setToolTip("Modifier");

        QPushButton *btnDel=new QPushButton();
        btnDel->setIcon(QIcon(QPixmap(":/images/delete.png").scaled(28,28,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        btnDel->setIconSize(QSize(28,28)); btnDel->setFixedSize(34,34);
        btnDel->setFlat(true);
        btnDel->setStyleSheet("QPushButton{background:transparent;border:none;}");
        btnDel->setCursor(Qt::PointingHandCursor);
        btnDel->setToolTip("Supprimer");

        // Modifier : pré-remplir formulaire avec données capturées par valeur
        connect(btnUpd,&QPushButton::clicked,[this,id,type,etat2,taux2,date2](){
            currentEditId = id;
            ui->inputTypeDechet->setCurrentText(type);
            ui->inputEtat->setCurrentText(etat2);
            ui->inputTauxRemplissage->setValue(taux2);
            ui->inputLocalisation->clear();
            ui->inputDateInstallation->setDate(QDate::fromString(date2,"dd/MM/yyyy"));
            ui->inputDateCollecte->setDate(QDate::currentDate());
            ui->checkEndommagee->setChecked(false);
            ui->inputNotes->clear();
            ui->formTitle->setText("Modifier la Poubelle #"+QString::number(id));
            ui->btnConfirmAdd->setVisible(false);
            ui->btnConfirmUpdate->setVisible(true);
            showFormPage();
        });
        connect(btnDel,&QPushButton::clicked,[this,id](){
            auto rep=QMessageBox::question(this,"Confirmation",
                QString("Supprimer la poubelle #%1 ?").arg(id),
                QMessageBox::Yes|QMessageBox::No);
            if(rep==QMessageBox::Yes){
                if(Ptmp.supprimer(id)){
                    QMessageBox::information(this,"Succès","Poubelle supprimée !");
                    if(currentEditId==id) currentEditId=-1;
                    rafraichirTable();
                } else {
                    QMessageBox::critical(this,"Erreur","Échec de la suppression !");
                }
            }
        });
        bl->addWidget(btnUpd); bl->addWidget(btnDel);
        ui->poubelleTable->setCellWidget(row,7,bw);
    }
}

// ============================================================
//  VIDER FORMULAIRE
// ============================================================
void GestionPoubellePage::viderFormulaire()
{
    ui->inputTypeDechet->setCurrentIndex(0);
    ui->inputEtat->setCurrentIndex(0);
    ui->inputTauxRemplissage->setValue(0);
    ui->inputLocalisation->clear();
    ui->inputDateInstallation->setDate(QDate::currentDate());
    ui->inputDateCollecte->setDate(QDate::currentDate());
    ui->checkEndommagee->setChecked(false);
    ui->inputNotes->clear();
    currentEditId=-1;
    ui->formTitle->setText("Ajouter une Poubelle");
    ui->btnConfirmAdd->setVisible(true);
    ui->btnConfirmUpdate->setVisible(false);
}
