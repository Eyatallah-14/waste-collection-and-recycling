#include "gestionpoubellepages.h"
#include "ui_gestionpoubellepages.h"

#include <QHeaderView>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDate>
#include <QDateTime>
#include <QPrinter>
#include <QPainter>
#include <QInputDialog>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

GestionPoubellePage::GestionPoubellePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GestionPoubellePage)
    , nextId(1)
{
    ui->setupUi(this);

    // Style global du widget
    setStyleSheet(
        "QWidget#GestionPoubellePage { background-color: #F0F3F5; }"
        "QWidget#topButtonBar, QWidget#searchBar { background-color: transparent; }"
        "QPushButton#btnListPoubelles, QPushButton#btnAddPoubelle, QPushButton#btnStatistics, QPushButton#btnHistorique { min-height: 45px; }"
        "QPushButton#btnSearch, QPushButton#btnTriEtat, QPushButton#btnTriType, QPushButton#btnExportPdf, QPushButton#btnExportCsv { background-color: #8e944e; color: white; border: none; border-radius: 8px; padding: 10px 20px; font-size: 10pt; font-weight: bold; }"
        "QPushButton#btnSearch:hover, QPushButton#btnTriEtat:hover, QPushButton#btnTriType:hover, QPushButton#btnExportPdf:hover, QPushButton#btnExportCsv:hover { background-color: #6d7339; }"
        "QPushButton#btnConfirmAdd, QPushButton#btnConfirmUpdate { background-color: #8e944e; color: white; border: none; border-radius: 10px; padding: 12px 30px; font-size: 11pt; font-weight: bold; }"
        "QPushButton#btnConfirmAdd:hover, QPushButton#btnConfirmUpdate:hover { background-color: #6d7339; }"
        "QPushButton#btnUploadImage { background-color: #05668D; color: white; border: none; border-radius: 10px; padding: 12px 16px; font-size: 10pt; font-weight: bold; }"
        "QPushButton#btnUploadImage:hover { background-color: #044a5e; }"
        "QLineEdit, QComboBox, QSpinBox, QDateEdit { border: 2px solid #E0E0E0; border-radius: 8px; padding: 8px 12px; background-color: white; color: #2C3E50; }"
        "QLineEdit::placeholder { color: #7B8794; }"
        "QComboBox QAbstractItemView { background-color: white; color: #2C3E50; selection-background-color: rgba(142, 148, 78, 0.25); selection-color: #2C3E50; outline: none; }"
        "QTextEdit#inputNotes { border: 2px solid #E0E0E0; border-radius: 8px; padding: 10px; background-color: white; }"
        "QLabel { color: #2C3E50; font-size: 9.5pt; font-weight: 600; }"
        "QLabel#formTitle { color: #8e944e; font-size: 18pt; font-weight: 800; }"
        "QWidget#pageForm QLabel { margin-top: 6px; margin-bottom: 4px; }"
        "QTableWidget { background-color: white; alternate-background-color: #F7F8FA; border: 2px solid #E0E0E0; border-radius: 10px; gridline-color: #E0E0E0; font-size: 10pt; color: #2C3E50; }"
        "QTableWidget::viewport { background-color: white; }"
        "QTableWidget::item { padding: 10px; border-bottom: 1px solid #F0F0F0; }"
        "QTableWidget::item:selected { background-color: rgba(142, 148, 78, 0.22); color: #2C3E50; }"
        "QHeaderView::section { background-color: #8e944e; color: white; padding: 12px; border: none; font-weight: bold; font-size: 10pt; }"
        "QWidget#formFieldsContainer { background-color: white; border: 2px solid #8e944e; border-radius: 15px; }"
        "QWidget#statsLeftContainer, QWidget#statsRightContainer { background-color: white; border: 2px solid #E0E0E0; border-radius: 15px; }"
        "QCheckBox { color: #2C3E50; font-size: 9.5pt; font-weight: 600; }"
        "QCheckBox::indicator { width: 18px; height: 18px; border: 2px solid #E0E0E0; border-radius: 4px; background-color: white; }"
        "QCheckBox::indicator:checked { background-color: #8e944e; border-color: #8e944e; }"
        );

    // Configuration du conteneur du formulaire
    QWidget *formFieldsContainer = this->findChild<QWidget*>("formFieldsContainer");
    if (formFieldsContainer) {
        formFieldsContainer->setMaximumWidth(900);
    }
    if (ui->formLayout) {
        ui->formLayout->setAlignment(Qt::AlignHCenter);
        ui->formLayout->setSpacing(18);
        ui->formLayout->setContentsMargins(0, 10, 0, 0);
    }

    if (ui->formGrid) {
        ui->formGrid->setVerticalSpacing(18);
    }

    // Configuration de la barre de recherche
    if (ui->searchBox) {
        ui->searchBox->setClearButtonEnabled(true);
        ui->searchBox->setPlaceholderText("Rechercher par type, ID, localisation...");
        ui->searchBox->setToolTip("Rechercher des poubelles par type, ID ou localisation");
    }

    // Configuration des boutons
    if (ui->btnExportPdf) {
        ui->btnExportPdf->setToolTip("Exporter la liste des poubelles en PDF");
    }
    if (ui->btnExportCsv) {
        ui->btnExportCsv->setToolTip("Exporter la liste des poubelles en CSV");
    }
    if (ui->btnTriEtat) {
        ui->btnTriEtat->setToolTip("Trier par état");
    }
    if (ui->btnTriType) {
        ui->btnTriType->setToolTip("Trier par type de déchet");
    }
    if (ui->btnUploadImage) {
        ui->btnUploadImage->setToolTip("Ajouter une photo de la poubelle");
        ui->btnUploadImage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->btnUploadImage->setFixedHeight(44);
    }
    if (ui->inputNotes) {
        ui->inputNotes->setToolTip("Ajouter des notes supplémentaires");
        ui->inputNotes->setMinimumHeight(120);
    }

    // Remplir les combobox
    if (ui->inputTypeDechet) {
        ui->inputTypeDechet->addItems({"Plastique", "Verre", "Papier", "Organique", "Métal", "Mixte"});
    }
    if (ui->inputEtat) {
        ui->inputEtat->addItems({"Bon", "Moyen", "Mauvais"});
    }
    if (ui->sortCombo) {
        ui->sortCombo->addItems({"Type", "État", "Taux remplissage", "Localisation"});
    }

    // Configuration du SpinBox pour le taux de remplissage
    if (ui->inputTauxRemplissage) {
        ui->inputTauxRemplissage->setRange(0, 100);
        ui->inputTauxRemplissage->setSuffix(" %");
    }

    // Configuration des dates
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

    // Connexion des signaux et slots
    connect(ui->btnListPoubelles, &QPushButton::clicked, this, &GestionPoubellePage::showListPage);
    connect(ui->btnAddPoubelle, &QPushButton::clicked, this, &GestionPoubellePage::showFormPage);
    connect(ui->btnStatistics, &QPushButton::clicked, this, &GestionPoubellePage::showStatsPage);
    connect(ui->btnHistorique, &QPushButton::clicked, this, &GestionPoubellePage::showHistoriquePage);
    
    connect(ui->btnConfirmAdd, &QPushButton::clicked, this, &GestionPoubellePage::ajouterPoubelle);
    connect(ui->btnConfirmUpdate, &QPushButton::clicked, this, &GestionPoubellePage::modifierPoubelle);
    connect(ui->btnSearch, &QPushButton::clicked, this, &GestionPoubellePage::rechercherPoubelle);
    connect(ui->btnTriEtat, &QPushButton::clicked, this, &GestionPoubellePage::trierParEtat);
    connect(ui->btnTriType, &QPushButton::clicked, this, &GestionPoubellePage::trierParType);
    connect(ui->btnExportPdf, &QPushButton::clicked, this, &GestionPoubellePage::exporterPDF);
    connect(ui->btnExportCsv, &QPushButton::clicked, this, &GestionPoubellePage::exporterCSV);
    connect(ui->btnUploadImage, &QPushButton::clicked, this, &GestionPoubellePage::uploadImage);

    // Ajouter quelques données de démonstration
    Poubelle p1 = {1, "Plastique", "Bon", 45, "Zone A - Rue 12", "2024-01-15", "2026-02-05", false, "Nouvelle installation"};
    Poubelle p2 = {2, "Verre", "Moyen", 78, "Zone B - Avenue 5", "2023-06-20", "2026-02-01", false, "Nécessite nettoyage"};
    Poubelle p3 = {3, "Papier", "Mauvais", 95, "Zone C - Boulevard 8", "2022-11-10", "2026-01-28", true, "Couvercle endommagé"};
    Poubelle p4 = {4, "Organique", "Bon", 30, "Zone A - Place Centrale", "2024-03-01", "2026-02-06", false, "RAS"};
    Poubelle p5 = {5, "Métal", "Bon", 60, "Zone D - Parc Municipal", "2023-09-15", "2026-02-03", false, "Bon état général"};
    
    poubelles[1] = p1;
    poubelles[2] = p2;
    poubelles[3] = p3;
    poubelles[4] = p4;
    poubelles[5] = p5;
    nextId = 6;

    rafraichirTable();
    showListPage();
}

GestionPoubellePage::~GestionPoubellePage()
{
    delete ui;
}

void GestionPoubellePage::showListPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageList);

    ui->btnListPoubelles->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );

    ui->btnAddPoubelle->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnHistorique->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    rafraichirTable();
}

void GestionPoubellePage::showFormPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageForm);
    viderFormulaire();
    ui->formTitle->setText("Ajouter une Poubelle");
    ui->btnConfirmAdd->setVisible(true);
    ui->btnConfirmUpdate->setVisible(false);

    ui->btnListPoubelles->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnAddPoubelle->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnHistorique->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );
}

void GestionPoubellePage::showStatsPage()
{
    ui->pagesStack->setCurrentWidget(ui->pageStats);

    ui->btnListPoubelles->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnAddPoubelle->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );

    ui->btnHistorique->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );
}

void GestionPoubellePage::showHistoriquePage()
{
    ui->pagesStack->setCurrentWidget(ui->pageHistorique);
    chargerHistorique();

    ui->btnListPoubelles->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnAddPoubelle->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnStatistics->setStyleSheet(
        "QPushButton { background-color: white; color: #8e944e; border: 2px solid #E0E0E0; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #F5F5F5; border-color: #8e944e; }"
        );

    ui->btnHistorique->setStyleSheet(
        "QPushButton { background-color: #8e944e; color: white; border: none; "
        "border-radius: 8px; padding: 12px 20px; font-size: 11pt; font-weight: bold; }"
        "QPushButton:hover { background-color: #6d7339; }"
        );
}

void GestionPoubellePage::ajouterPoubelle()
{
    Poubelle p;
    p.id = nextId++;
    p.type_dechet = ui->inputTypeDechet->currentText();
    p.etat = ui->inputEtat->currentText();
    p.taux_remplissage = ui->inputTauxRemplissage->value();
    p.localisation = ui->inputLocalisation->text();
    p.date_installation = ui->inputDateInstallation->date().toString("yyyy-MM-dd");
    p.derniere_collecte = ui->inputDateCollecte->date().toString("yyyy-MM-dd");
    p.endommagee = ui->checkEndommagee->isChecked();
    p.notes = ui->inputNotes->toPlainText();

    if (p.localisation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La localisation est obligatoire !");
        return;
    }

    poubelles[p.id] = p;
    sauvegarderHistorique("Ajout", p);
    verifierEtatPoubelle(p);

    QMessageBox::information(this, "Succès", "Poubelle ajoutée avec succès !");
    showListPage();
}

void GestionPoubellePage::modifierPoubelle()
{
    int currentRow = ui->poubelleTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune poubelle sélectionnée !");
        return;
    }

    int id = ui->poubelleTable->item(currentRow, 0)->text().toInt();
    
    if (poubelles.contains(id)) {
        Poubelle &p = poubelles[id];
        p.type_dechet = ui->inputTypeDechet->currentText();
        p.etat = ui->inputEtat->currentText();
        p.taux_remplissage = ui->inputTauxRemplissage->value();
        p.localisation = ui->inputLocalisation->text();
        p.date_installation = ui->inputDateInstallation->date().toString("yyyy-MM-dd");
        p.derniere_collecte = ui->inputDateCollecte->date().toString("yyyy-MM-dd");
        p.endommagee = ui->checkEndommagee->isChecked();
        p.notes = ui->inputNotes->toPlainText();

        sauvegarderHistorique("Modification", p);
        verifierEtatPoubelle(p);

        QMessageBox::information(this, "Succès", "Poubelle modifiée avec succès !");
        showListPage();
    }
}

void GestionPoubellePage::supprimerPoubelle()
{
    int currentRow = ui->poubelleTable->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune poubelle sélectionnée !");
        return;
    }

    int id = ui->poubelleTable->item(currentRow, 0)->text().toInt();
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", 
                                   "Voulez-vous vraiment supprimer cette poubelle ?",
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (poubelles.contains(id)) {
            Poubelle p = poubelles[id];
            sauvegarderHistorique("Suppression", p);
            poubelles.remove(id);
            rafraichirTable();
            QMessageBox::information(this, "Succès", "Poubelle supprimée avec succès !");
        }
    }
}

void GestionPoubellePage::rechercherPoubelle()
{
    QString recherche = ui->searchBox->text().toLower();
    
    if (recherche.isEmpty()) {
        rafraichirTable();
        return;
    }

    ui->poubelleTable->setRowCount(0);
    int row = 0;

    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        const Poubelle &p = it.value();
        
        if (QString::number(p.id).contains(recherche) ||
            p.type_dechet.toLower().contains(recherche) ||
            p.localisation.toLower().contains(recherche) ||
            p.etat.toLower().contains(recherche)) {
            
            ajouterLigneTable(p, row++);
        }
    }
}

void GestionPoubellePage::trierParEtat()
{
    // Créer une liste triée
    QList<Poubelle> liste;
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        liste.append(it.value());
    }

    std::sort(liste.begin(), liste.end(), [](const Poubelle &a, const Poubelle &b) {
        return a.etat < b.etat;
    });

    ui->poubelleTable->setRowCount(0);
    for (int i = 0; i < liste.size(); ++i) {
        ajouterLigneTable(liste[i], i);
    }
}

void GestionPoubellePage::trierParType()
{
    QList<Poubelle> liste;
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        liste.append(it.value());
    }

    std::sort(liste.begin(), liste.end(), [](const Poubelle &a, const Poubelle &b) {
        return a.type_dechet < b.type_dechet;
    });

    ui->poubelleTable->setRowCount(0);
    for (int i = 0; i < liste.size(); ++i) {
        ajouterLigneTable(liste[i], i);
    }
}

void GestionPoubellePage::exporterPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier PDF");
        return;
    }

    // En-tête
    QFont titleFont("Arial", 16, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(100, 100, "Rapport de Gestion des Poubelles");

    QFont normalFont("Arial", 10);
    painter.setFont(normalFont);
    painter.drawText(100, 150, "Date: " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"));
    painter.drawText(100, 180, "Nombre total de poubelles: " + QString::number(poubelles.size()));

    // Calculer les statistiques
    int totalRemplissage = 0;
    int nbEndommagees = 0;
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        totalRemplissage += it.value().taux_remplissage;
        if (it.value().endommagee) nbEndommagees++;
    }
    int moyenneRemplissage = poubelles.isEmpty() ? 0 : totalRemplissage / poubelles.size();

    painter.drawText(100, 210, "Taux moyen de remplissage: " + QString::number(moyenneRemplissage) + "%");
    painter.drawText(100, 240, "Poubelles endommagées: " + QString::number(nbEndommagees));

    // Table des données
    int y = 300;
    QFont headerFont("Arial", 9, QFont::Bold);
    painter.setFont(headerFont);
    painter.drawText(100, y, "ID");
    painter.drawText(200, y, "Type");
    painter.drawText(350, y, "État");
    painter.drawText(500, y, "Remplissage");
    painter.drawText(650, y, "Localisation");

    painter.setFont(normalFont);
    y += 30;

    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        const Poubelle &p = it.value();
        
        painter.drawText(100, y, QString::number(p.id));
        painter.drawText(200, y, p.type_dechet);
        painter.drawText(350, y, p.etat);
        painter.drawText(500, y, QString::number(p.taux_remplissage) + "%");
        painter.drawText(650, y, p.localisation.left(30));

        y += 25;
        
        if (y > 2800) {
            printer.newPage();
            y = 100;
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "PDF exporté avec succès !");
}

void GestionPoubellePage::exporterCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en CSV", "", "CSV Files (*.csv)");
    
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier CSV");
        return;
    }

    QTextStream out(&file);
    
    // En-tête
    out << "ID,Type Déchet,État,Taux Remplissage (%),Localisation,Date Installation,Dernière Collecte,Endommagée,Notes\n";

    // Données
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        const Poubelle &p = it.value();
        QString escapedNotes = p.notes;
        escapedNotes.replace("\"", "\"\"");
        
        out << p.id << ","
            << p.type_dechet << ","
            << p.etat << ","
            << p.taux_remplissage << ","
            << p.localisation << ","
            << p.date_installation << ","
            << p.derniere_collecte << ","
            << (p.endommagee ? "Oui" : "Non") << ","
            << "\"" << escapedNotes << "\"\n";
    }

    file.close();
    QMessageBox::information(this, "Succès", "CSV exporté avec succès !");
}

void GestionPoubellePage::afficherNotification()
{
    // Cette fonction sera appelée pour afficher les notifications
}

void GestionPoubellePage::chargerHistorique()
{
    // Charger l'historique depuis un fichier ou une base de données
    if (ui->historiqueTable) {
        ui->historiqueTable->setRowCount(0);
        // Ajouter des exemples d'historique
        ui->historiqueTable->insertRow(0);
        ui->historiqueTable->setItem(0, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm")));
        ui->historiqueTable->setItem(0, 1, new QTableWidgetItem("Ajout"));
        ui->historiqueTable->setItem(0, 2, new QTableWidgetItem("Poubelle #5"));
        ui->historiqueTable->setItem(0, 3, new QTableWidgetItem("Nouvelle poubelle ajoutée"));
    }
}

void GestionPoubellePage::uploadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Sélectionner une image", "",
                                                     "Images (*.png *.jpg *.jpeg *.bmp)");
    
    if (!fileName.isEmpty()) {
        QMessageBox::information(this, "Image", "Image chargée: " + fileName);
        // Ici, vous pourriez afficher l'image dans un QLabel
    }
}

void GestionPoubellePage::setupPoubelleTable()
{
    ui->poubelleTable->setColumnCount(9);
    ui->poubelleTable->setHorizontalHeaderLabels({
        "ID", "Type Déchet", "État", "Remplissage", "Localisation",
        "Installation", "Collecte", "Endommagée", "Opérations"
    });

    ui->poubelleTable->horizontalHeader()->setStretchLastSection(false);
    ui->poubelleTable->verticalHeader()->setVisible(false);
    ui->poubelleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->poubelleTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->poubelleTable->setAlternatingRowColors(true);
    ui->poubelleTable->setShowGrid(true);
    ui->poubelleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->poubelleTable->setFocusPolicy(Qt::NoFocus);

    ui->poubelleTable->setColumnWidth(0, 60);    // ID
    ui->poubelleTable->setColumnWidth(1, 120);   // Type
    ui->poubelleTable->setColumnWidth(2, 80);    // État
    ui->poubelleTable->setColumnWidth(3, 100);   // Remplissage
    ui->poubelleTable->setColumnWidth(4, 180);   // Localisation
    ui->poubelleTable->setColumnWidth(5, 110);   // Installation
    ui->poubelleTable->setColumnWidth(6, 110);   // Collecte
    ui->poubelleTable->setColumnWidth(7, 100);   // Endommagée
    ui->poubelleTable->setColumnWidth(8, 150);   // Opérations

    // Configuration de la table d'historique
    if (ui->historiqueTable) {
        ui->historiqueTable->setColumnCount(4);
        ui->historiqueTable->setHorizontalHeaderLabels({
            "Date/Heure", "Action", "Poubelle", "Détails"
        });
        ui->historiqueTable->horizontalHeader()->setStretchLastSection(true);
        ui->historiqueTable->verticalHeader()->setVisible(false);
        ui->historiqueTable->setAlternatingRowColors(true);
        ui->historiqueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void GestionPoubellePage::setupCharts()
{
    if (!ui->statsLeftContainer || !ui->statsRightContainer) {
        return;
    }

    // Graphique en camembert - Distribution par type de déchet
    QVBoxLayout *leftLayout = new QVBoxLayout(ui->statsLeftContainer);
    leftLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *pieTitle = new QLabel("Distribution des Poubelles par Type de Déchet");
    pieTitle->setStyleSheet("font-size: 13pt; font-weight: bold; color: #2C3E50; background-color: transparent;");
    pieTitle->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(pieTitle);

    QPieSeries *pieSeries = new QPieSeries();
    
    // Compter les types
    QMap<QString, int> compteurTypes;
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        compteurTypes[it.value().type_dechet]++;
    }

    for (auto it = compteurTypes.begin(); it != compteurTypes.end(); ++it) {
        pieSeries->append(it.key(), it.value());
    }

    QList<QColor> colors = {
        QColor("#8e944e"), QColor("#6d7339"), QColor("#05668D"), 
        QColor("#02C39A"), QColor("#F77F00"), QColor("#06AED5")
    };

    for (int i = 0; i < pieSeries->slices().count(); i++) {
        QPieSlice *slice = pieSeries->slices().at(i);
        slice->setColor(colors[i % colors.size()]);
        slice->setLabelVisible(true);
        slice->setLabel(slice->label() + QString(" (%1%)").arg(100 * slice->percentage(), 0, 'f', 1));
        if (slice->percentage() > 0.20) {
            slice->setExploded(true);
            slice->setExplodeDistanceFactor(0.1);
        }
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->legend()->setAlignment(Qt::AlignBottom);
    pieChart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    pieChartView->setMinimumHeight(400);

    leftLayout->addWidget(pieChartView);

    // Graphique à barres - Nombre et taux moyen de remplissage
    QVBoxLayout *rightLayout = new QVBoxLayout(ui->statsRightContainer);
    rightLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *barTitle = new QLabel("Statistiques par Type de Déchet");
    barTitle->setStyleSheet("font-size: 13pt; font-weight: bold; color: #2C3E50; background-color: transparent;");
    barTitle->setAlignment(Qt::AlignCenter);
    rightLayout->addWidget(barTitle);

    QBarSet *countSet = new QBarSet("Nombre");
    QBarSet *fillSet = new QBarSet("Taux moyen (%)");

    QMap<QString, int> compteur;
    QMap<QString, int> totalRemplissage;
    
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        compteur[it.value().type_dechet]++;
        totalRemplissage[it.value().type_dechet] += it.value().taux_remplissage;
    }

    QStringList categories;
    for (auto it = compteur.begin(); it != compteur.end(); ++it) {
        categories << it.key();
        *countSet << it.value();
        int moyenne = totalRemplissage[it.key()] / it.value();
        *fillSet << moyenne;
    }

    countSet->setColor(QColor("#05668D"));
    fillSet->setColor(QColor("#8e944e"));

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(countSet);
    barSeries->append(fillSet);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    barChart->legend()->setAlignment(Qt::AlignTop);

    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->setMinimumHeight(400);

    rightLayout->addWidget(barChartView);
}

void GestionPoubellePage::rafraichirTable()
{
    ui->poubelleTable->setRowCount(0);
    
    int row = 0;
    for (auto it = poubelles.begin(); it != poubelles.end(); ++it) {
        ajouterLigneTable(it.value(), row++);
    }

    // Mettre à jour les graphiques
    setupCharts();
}

void GestionPoubellePage::ajouterLigneTable(const Poubelle &p, int row)
{
    ui->poubelleTable->insertRow(row);
    ui->poubelleTable->setRowHeight(row, 60);
    
    ui->poubelleTable->setItem(row, 0, new QTableWidgetItem(QString::number(p.id)));
    ui->poubelleTable->setItem(row, 1, new QTableWidgetItem(p.type_dechet));
    
    QTableWidgetItem *etatItem = new QTableWidgetItem(p.etat);
    if (p.etat == "Bon") {
        etatItem->setBackground(QColor(46, 204, 113, 50));
    } else if (p.etat == "Moyen") {
        etatItem->setBackground(QColor(255, 195, 0, 50));
    } else {
        etatItem->setBackground(QColor(231, 76, 60, 50));
    }
    ui->poubelleTable->setItem(row, 2, etatItem);
    
    QTableWidgetItem *remplissageItem = new QTableWidgetItem(QString::number(p.taux_remplissage) + "%");
    if (p.taux_remplissage >= 80) {
        remplissageItem->setBackground(QColor(231, 76, 60, 50));
    } else if (p.taux_remplissage >= 50) {
        remplissageItem->setBackground(QColor(255, 195, 0, 50));
    } else {
        remplissageItem->setBackground(QColor(46, 204, 113, 50));
    }
    ui->poubelleTable->setItem(row, 3, remplissageItem);
    
    ui->poubelleTable->setItem(row, 4, new QTableWidgetItem(p.localisation));
    ui->poubelleTable->setItem(row, 5, new QTableWidgetItem(p.date_installation));
    ui->poubelleTable->setItem(row, 6, new QTableWidgetItem(p.derniere_collecte));
    
    QTableWidgetItem *endommageItem = new QTableWidgetItem(p.endommagee ? "Oui" : "Non");
    if (p.endommagee) {
        endommageItem->setBackground(QColor(231, 76, 60, 50));
        endommageItem->setForeground(QColor(231, 76, 60));
    }
    ui->poubelleTable->setItem(row, 7, endommageItem);

    // Boutons d'opération
    QWidget *buttonWidget = new QWidget();
    buttonWidget->setStyleSheet("background-color: transparent;");
    QHBoxLayout *btnLayout = new QHBoxLayout(buttonWidget);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(10);
    btnLayout->setAlignment(Qt::AlignCenter);

    QSize buttonSize(35, 35);

    QPushButton *btnUpdate = new QPushButton();
    QPixmap updatePixmap(":/images/update.png");
    updatePixmap = updatePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnUpdate->setIcon(QIcon(updatePixmap));
    btnUpdate->setIconSize(buttonSize);
    btnUpdate->setFixedSize(buttonSize);
    btnUpdate->setFlat(true);
    btnUpdate->setStyleSheet("QPushButton { background: transparent; border: none; }");
    btnUpdate->setCursor(Qt::PointingHandCursor);
    btnUpdate->setToolTip("Modifier");

    QPushButton *btnDelete = new QPushButton();
    QPixmap deletePixmap(":/images/delete.png");
    deletePixmap = deletePixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btnDelete->setIcon(QIcon(deletePixmap));
    btnDelete->setIconSize(buttonSize);
    btnDelete->setFixedSize(buttonSize);
    btnDelete->setFlat(true);
    btnDelete->setStyleSheet("QPushButton { background: transparent; border: none; }");
    btnDelete->setCursor(Qt::PointingHandCursor);
    btnDelete->setToolTip("Supprimer");

    connect(btnUpdate, &QPushButton::clicked, [this, p]() {
        remplirFormulaire(p);
        showFormPage();
        ui->formTitle->setText("Modifier la Poubelle");
        ui->btnConfirmAdd->setVisible(false);
        ui->btnConfirmUpdate->setVisible(true);
    });

    connect(btnDelete, &QPushButton::clicked, this, &GestionPoubellePage::supprimerPoubelle);

    btnLayout->addWidget(btnUpdate);
    btnLayout->addWidget(btnDelete);

    ui->poubelleTable->setCellWidget(row, 8, buttonWidget);
}

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
}

void GestionPoubellePage::remplirFormulaire(const Poubelle &p)
{
    ui->inputTypeDechet->setCurrentText(p.type_dechet);
    ui->inputEtat->setCurrentText(p.etat);
    ui->inputTauxRemplissage->setValue(p.taux_remplissage);
    ui->inputLocalisation->setText(p.localisation);
    ui->inputDateInstallation->setDate(QDate::fromString(p.date_installation, "yyyy-MM-dd"));
    ui->inputDateCollecte->setDate(QDate::fromString(p.derniere_collecte, "yyyy-MM-dd"));
    ui->checkEndommagee->setChecked(p.endommagee);
    ui->inputNotes->setPlainText(p.notes);
}

void GestionPoubellePage::verifierEtatPoubelle(const Poubelle &p)
{
    // Vérifier si la poubelle nécessite une attention
    if (p.endommagee) {
        QMessageBox::warning(this, "Attention", 
            QString("ALERTE : La poubelle #%1 est endommagée !\nLocalisation : %2")
            .arg(p.id).arg(p.localisation));
    }
    
    if (p.taux_remplissage >= 90) {
        QMessageBox::information(this, "Notification", 
            QString("La poubelle #%1 est presque pleine (%2%)\nCollecte recommandée rapidement.")
            .arg(p.id).arg(p.taux_remplissage));
    }
}

void GestionPoubellePage::sauvegarderHistorique(const QString &action, const Poubelle &p)
{
    // Sauvegarder l'action dans l'historique
    // Dans une vraie application, ceci serait sauvegardé dans une base de données
    QString log = QString("%1 - %2 - Poubelle #%3 (%4) - %5")
        .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm"))
        .arg(action)
        .arg(p.id)
        .arg(p.type_dechet)
        .arg(p.localisation);
    
    qDebug() << "HISTORIQUE:" << log;
}
