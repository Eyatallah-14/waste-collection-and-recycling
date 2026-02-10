#!/bin/bash

# Script de correction des erreurs de compilation
# emp_vehic_zones_poubelle

echo "🔧 Correction des erreurs de compilation..."

# 1. Vérifier si le mainwindow.ui existe
if [ -f "mainwindow.ui" ]; then
    echo "✓ Fichier mainwindow.ui trouvé"
    
    # Supprimer les lignes problématiques avec setVerticalHeaderVisible
    # Cette fonction n'existe pas en Qt6, on doit utiliser verticalHeader()->setVisible()
    if grep -q "setVerticalHeaderVisible" mainwindow.ui; then
        echo "⚠️  Correction de setVerticalHeaderVisible dans mainwindow.ui..."
        # Commenter ou supprimer la ligne problématique
        sed -i '/<bool>setVerticalHeaderVisible<\/bool>/d' mainwindow.ui
        sed -i '/setVerticalHeaderVisible/d' mainwindow.ui
        echo "✓ Correction appliquée"
    else
        echo "✓ Pas de setVerticalHeaderVisible trouvé"
    fi
fi

# 2. Vérifier CMakeLists.txt
if grep -q "PrintSupport" CMakeLists.txt; then
    echo "✓ PrintSupport déjà dans CMakeLists.txt"
else
    echo "⚠️  Ajout de PrintSupport manquant!"
    echo "   Veuillez ajouter PrintSupport dans CMakeLists.txt"
fi

echo ""
echo "🎉 Corrections terminées!"
echo ""
echo "Pour compiler maintenant:"
echo "  mkdir -p build && cd build"
echo "  cmake .."
echo "  cmake --build ."
