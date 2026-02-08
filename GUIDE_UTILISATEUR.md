# Guide d'Utilisation - Système de Gestion des Poubelles

## 🚀 Démarrage Rapide

### Lancement de l'Application
1. Double-cliquez sur `GestionPoubelle.exe` (Windows) ou `./GestionPoubelle` (Linux/Mac)
2. L'application s'ouvre sur la page "Liste des Poubelles"

## 📖 Guide des Fonctionnalités

### 1. Liste des Poubelles

**Navigation**: Cliquez sur "Liste des Poubelles" dans le menu supérieur

**Que voir?**
- Tableau avec toutes les poubelles enregistrées
- Codes couleur:
  - 🟢 Vert = Bon état / Remplissage < 50%
  - 🟡 Jaune = État moyen / Remplissage 50-89%
  - 🔴 Rouge = Mauvais état / Remplissage ≥ 90% / Endommagée

**Actions disponibles**:
- **Rechercher**: Tapez un mot-clé et cliquez "Rechercher"
- **Trier**: Utilisez "Tri État" ou "Tri Type"
- **Modifier**: Cliquez sur l'icône ✏️ (crayon) dans la colonne Opérations
- **Supprimer**: Cliquez sur l'icône 🗑️ (poubelle) dans la colonne Opérations
- **Exporter**: Cliquez "PDF" ou "CSV" pour exporter les données

### 2. Ajouter une Poubelle

**Navigation**: Cliquez sur "Ajouter Poubelle"

**Étapes**:
1. Remplissez les champs obligatoires:
   - Type de Déchet (menu déroulant)
   - État (Bon/Moyen/Mauvais)
   - Taux de Remplissage (0-100%)
   - **Localisation** ⚠️ OBLIGATOIRE
   
2. Champs optionnels:
   - Date d'Installation
   - Dernière Collecte
   - Cochez "Poubelle Endommagée" si nécessaire
   - Ajoutez des notes
   - Ajoutez une photo (optionnel)

3. Cliquez "Ajouter"

**Notifications**:
- ⚠️ Si la poubelle est endommagée → Alerte affichée
- 🔔 Si le remplissage ≥ 90% → Notification de collecte urgente

### 3. Modifier une Poubelle

**Méthode 1**: 
1. Dans la liste, cliquez sur l'icône ✏️ de la poubelle
2. Modifiez les informations
3. Cliquez "Modifier"

**Méthode 2**:
1. Cliquez "Ajouter Poubelle"
2. Le bouton devient "Modifier" après sélection

### 4. Supprimer une Poubelle

1. Dans la liste, cliquez sur l'icône 🗑️
2. Confirmez la suppression
3. La poubelle est supprimée et l'historique mis à jour

### 5. Statistiques

**Navigation**: Cliquez sur "Statistiques"

**Graphiques disponibles**:

**Graphique de gauche (Camembert)**:
- Distribution des poubelles par type de déchet
- Pourcentages affichés
- Les sections > 20% sont éclatées pour visibilité

**Graphique de droite (Barres)**:
- Nombre de poubelles par type (barres bleues)
- Taux moyen de remplissage par type (barres vertes)
- Comparaison facile entre types

**Utilité**:
- Identifier les types de déchets les plus/moins utilisés
- Voir quels types se remplissent le plus vite
- Planifier les collectes

### 6. Historique

**Navigation**: Cliquez sur "Historique"

**Informations affichées**:
- Date et heure de chaque action
- Type d'action (Ajout, Modification, Suppression)
- Poubelle concernée
- Détails de l'action

**Utilité**:
- Traçabilité complète
- Audit des modifications
- Suivi des opérations

### 7. Recherche et Filtres

**Recherche simple**:
1. Tapez dans la barre de recherche
2. Recherche dans: ID, Type, Localisation, État
3. Cliquez "Rechercher"
4. Pour tout réafficher, videz la barre et recherchez

**Tri par État**:
- Organise: Bon → Moyen → Mauvais

**Tri par Type**:
- Organise alphabétiquement par type de déchet

**Filtre combiné**:
- Utilisez le menu déroulant pour sélectionner un critère
- Puis cliquez sur le bouton de tri correspondant

### 8. Export de Données

#### Export PDF
**Usage**: Rapport complet pour impression ou archive

**Contenu**:
- En-tête avec date du rapport
- Statistiques globales:
  - Nombre total de poubelles
  - Taux moyen de remplissage
  - Nombre de poubelles endommagées
- Tableau complet de toutes les poubelles

**Étapes**:
1. Cliquez "PDF"
2. Choisissez l'emplacement de sauvegarde
3. Nommez le fichier
4. Cliquez "Enregistrer"

#### Export CSV
**Usage**: Analyse dans Excel, LibreOffice, ou autres outils

**Format**: Valeurs séparées par virgules

**Colonnes exportées**:
- ID, Type Déchet, État, Taux Remplissage, Localisation
- Date Installation, Dernière Collecte, Endommagée, Notes

**Étapes**:
1. Cliquez "CSV"
2. Choisissez l'emplacement
3. Ouvrez avec votre logiciel de tableur préféré

## 💡 Astuces et Bonnes Pratiques

### Organisation
- ✅ Mettez à jour la "Dernière Collecte" après chaque passage
- ✅ Vérifiez régulièrement les poubelles avec taux > 80%
- ✅ Traitez immédiatement les poubelles endommagées
- ✅ Ajoutez des notes détaillées pour le suivi

### Utilisation Efficace
- 🔍 Utilisez la recherche pour trouver rapidement une poubelle
- 📊 Consultez les statistiques hebdomadairement
- 📄 Exportez un PDF mensuel pour les rapports
- 📝 Vérifiez l'historique en cas de doute

### Codes Couleur à Retenir
- **Vert** = Tout va bien
- **Jaune** = À surveiller
- **Rouge** = Action urgente requise

## 🆘 Problèmes Courants

### "Impossible d'ajouter la poubelle"
➡️ Vérifiez que la localisation est remplie (champ obligatoire)

### "Les graphiques ne s'affichent pas"
➡️ Assurez-vous d'avoir au moins une poubelle ajoutée

### "L'export PDF ne fonctionne pas"
➡️ Vérifiez que vous avez les droits d'écriture dans le dossier

### "Je ne vois pas mes modifications"
➡️ Retournez à la page Liste pour voir les changements

## 📞 Support

Pour toute question ou problème:
- Consultez d'abord ce guide
- Vérifiez le README.md pour les détails techniques
- Contactez le support technique

## ⌨️ Raccourcis Clavier

- **Ctrl+Q** : Quitter l'application
- **F1** : Aide (menu À propos)

---

**Dernière mise à jour**: Février 2026  
**Version de l'application**: 1.0.0
