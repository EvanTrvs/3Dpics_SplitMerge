# Développement et Optimisation en C++ de l'Algorithme 3D de Segmentation d'Image "Split and Merge" avec image NIfTI

## Projet de programmation
### Introduction
Ce projet vise à mettre en œuvre et optimiser l'algorithme de segmentation d'image "Split and Merge" pour des images médicales en trois dimensions (3D). Il s'inscrit dans le cadre d'un projet de Programmation et de Génie Logiciel.

### Segmentation d’image
La segmentation d'image est un processus essentiel qui consiste à regrouper des pixels en fonction de certains critères, formant ainsi des régions distinctes. Cette automatisation permet une analyse plus précise des images médicales, facilitant la détection de tumeurs et d'anomalies.

### Split and Merge
L'algorithme "Split and Merge" est un procédé de traitement d'image utilisé pour segmenter une image en régions dites homogènes. L'idée principale est de diviser successivement l'image en quadrants en fonction d'un critère d'homogénéité et d’un seuil de finesse, puis de fusionner les régions similaires pour créer le résultat segmenté.

### Image numérique 3D NIfTI
Le format d’image traité est le NIfTI (Neuroimaging Informatics Technology Initiative). Employé pour stocker des données d'imagerie médicale, il offre un support aux images multidimensionnelles. Il se présente sous la forme d'extensions telles que .nii ou .nii.gz, et des applications accessibles, telles qu'ITK-SNAP, permettent la lecture de ce format.

![illustration Traitement](https://cdn.discordapp.com/attachments/812733378520547378/1196545901016125591/image.png?ex=65b80535&is=65a59035&hm=d9f1736bf77f8d8a3cdf7b4ba41f857157f140789590e2a19cb4e3d0c7e3e7ae&)

## Utilisation
### Installation
- Téléchargement de l’exécutable fourni
- Compilation du code source c++

### Exécution
- **Exécution mode console, avec insertion de paramètres**
  ```bash
  ./NiiSplitMerge.exe [critère homogénéité] [seuil de segmentation] [chemin image source] [chemin image segmentation]
  ```
### Paramètres
| Paramètre                    | Description                                       | Champs possibles
|---|---------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|
| Critère d’homogénéité | Définit la similarité souhaitée entre les valeurs d'une région pour qu’elle soit considéré homogène                  | Flottant dans l'intervalle [0, 1]
| Seuil de segmentation| Définit la taille minimale que peut prendre une région, limite la segmentation a une certaine profondeur | Entier naturel dans l'intervalle [1, 10 000]
| Chemin image source | Chemin vers l'image NIfTI source à segmenter | Chemin de fichier existant avec extension .nii
| Chemin image segmentation | Chemin où les images résultantes seront enregistrées | Chemin de fichier avec extension .nii
| Fichier de configuration (optionnel) | Fichier de configuration avancée | Chemin de fichier existant avec extension .txt

### Paramètres avancés

Image préenregistrée : à la place du 3ème argument avec la syntaxe "mireN", où N est un entier naturel non signé non nul. Utilise NIfTI source préenregistré de dimension 32x25xN dans le processus de segmentation d'image 3D.

Fichier de Configuration : Pour accéder à des fonctionnalités avancées, un fichier de configuration optionnel peut être utilisé. Le fichier doit avoir l'extension .txt et respecter la syntaxe suivante
| Clé                    | Description                                       | Valeurs
|---|---------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|
| prepro | Plage de prétraitement | min,max (deux entiers naturels séparés par une virgule)
| split | Choix de stratégie de division | N (0, 1, 2 - voir guide des stratégies)
| neighbourg | Choix de stratégie de voisinage | N (0, 1, 2 - voir guide des stratégies)
| merge | Choix de stratégie de fusion | N (0, 1, 2 - voir guide des stratégies)
| preproimg | Production de l'image de prétraitement | true ou false
| splitimg | Production de l'image de segmentation Split | true ou false
| mergeimg | Production de l'image de segmentation Split and Merge | true ou false
| details | Activation/désactivation de l'affichage console détaillé | true ou false

Le fichier est parsé en suivant le format "Clé"="Valeur" ligne par ligne. Les lignes débutant par //, #, ou ; sont considérées comme des commentaires et seront ignorées.

## Exemples d'utilisations

### Segmentation Standard
**Objectif :** Obtenir une image segmentée avec un critère d'homogénéité de 5% et une taille minimale de segmentation de 2 voxels.
```bash
./NiiSplitMerge.exe 0.05 2 source.nii sortie.nii
```
### Utilisation de l'Image Préenregistrée "Mire"
**Objectif :** Utiliser l'image préenregistrée NIfTI "Mire" avec une dimension de 50.
```bash
./NiiSplitMerge.exe 0.15 3 mire50 image/mire50_0-5_3.nii
```
### Segmentation avec Paramètres Avancés
**Objectif :**  Obtenir l'image résultante de chaque procédé avec des stratégies spécifiques et un prétraitement des valeurs entre 0 et 10.
```bash
./NiiSplitMerge.exe 0.05 2 mire4 sortie.nii config.txt
```
config.txt :
```bash
// Ce fichier de configuration est un exemple
prepro=0,10
split=1
neighbourg=2
merge=2

# Commentaire d'exemple
preproimg=true
splitimg=true
mergeimg=true
details=true
```

![illustration Traitement](https://cdn.discordapp.com/attachments/812733378520547378/1196544476227837972/illustrationTraitement.png?ex=65b803e1&is=65a58ee1&hm=327048c39cef9439db2eea99bfb0ddc525b5a977daa3ab966db7f126b56c7276&)

![illustration cerveau caille seg](https://media.discordapp.net/attachments/1087514695268847656/1203812297139556446/bellecailleseg.png?ex=65d27491&is=65bfff91&hm=2bd2e4e6b7b7261599ca77562816cf1a0cfa6d3133be8013f6b7874592bcc531&=&format=webp&quality=lossless)

### Dépendances
Ce projet, développé en C++14 (/std:c++14) et compilé avec GNU G++. Le code source fait appel à des librairies standard via ainsi qu'à des librairies externes, notamment :
- BGL (Boost Graph Library) : Facilite la manipulation des graphes.
- Boost Multidimensional Array Library : Permet la manipulation efficace de tableaux multidimensionnels.
  
[Release boost_1_83_0](https://boostorg.jfrog.io/artifactory/main/release/1.84.0/source/)

### Guide des stratégies
| Fonction | Indice | Titre | Description
|---|---------------------------------------------------|----------------------------------------------------------|---------------------------------------------------------------|
| Split | 0 | Classic | Séparation du multi-array en analysant tout d’abord l’homogénéité du fragment puis si ce dernier n’est pas homogène, les dimensions divisibles.
| Split | 1 | Classic avec Threads | Séparation du multi-array en analysant tout d’abord l’homogénéité du fragment puis si ce dernier n’est pas homogène, les dimensions divisibles. Le travail de la première division est séparé en threads distincts.
| Split | 2 | Classic avec conditions inversé | Séparation du multi-array en analysant tout d’abord les dimensions divisibles puis test l’homogénéité du fragment.
| Voisinage | 0 | Stockage de potentiel voxel voisin dans une liste | Analyse des voxels des fragments, en recherchant si un voxel voisin a été précédemment étudié. Le stockage est une liste utilisant la dichotomie.
| Voisinage | 1 | Stockage de potentiel voxel voisin dans une liste de listes | Analyse des voxels des fragments, en recherchant si un voxel voisin a été précédemment étudié. Le stockage est une liste de listes utilisant la dichotomie.
| Voisinage | 2 | Ecriture de la matrice afin détecter les voisins | Analyse des voxels des fragments, en écrivant dans la matrice le numéro du fragment et en étudiant les voxels présents autours.
| Merge | 0 | Lien des fragments des paires de voisins fusionnable | Analyse des paires de voisins fusionnables afin de les regrouper dans une même connexité (dans un graphe).
| Merge | 1 | Lien des fragments des paires de voisins fusionnable avec Threads | Analyse des paires de voisins fusionnables afin de les regrouper dans une même connexité (dans un graphe). Les threads sont exploités afin de limiter certains temps de calcul.
| Merge | 2 | Lien des fragments des paires de voisins fusionnable sans choix | Analyse des paires de voisins fusionnables afin de les regrouper dans une même connexité (dans un graphe). Cette version ne prend que la première paire homogène de la liste à chaque itération. Nous ne respectons donc pas le déterminisme.

## Auteurs
[EvanTrvs](https://github.com/EvanTrvs) et Thibaud, 2023
