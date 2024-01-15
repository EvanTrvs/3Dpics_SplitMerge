# Développement et Optimisation en C++ de l'Algorithme 3D de Segmentation d'Image "Split and Merge" avec image NIfTI

### Auteurs
Evan TORTEVOIS et Thibaud SCRIBE

## Projet de programmation
### Introduction
Ce projet vise à mettre en œuvre et optimiser l'algorithme de segmentation d'image "Split and Merge" pour des images médicales en trois dimensions (3D). Il s'inscrit dans le cadre du projet de Programmation et de Génie Logiciel de 4ème année du cursus d'ingénierie informatique à l'École Polytech Tours.

### Segmentation d’image
La segmentation d'image est un processus essentiel qui consiste à regrouper des pixels en fonction de certains critères, formant ainsi des régions distinctes. Cette automatisation permet une analyse plus précise des images médicales, facilitant la détection de tumeurs et d'anomalies.

### Split and Merge
L'algorithme "Split and Merge" est un procédé de traitement d'image utilisé pour segmenter une image en régions dites homogènes. L'idée principale est de diviser successivement l'image en quadrants en fonction d'un critère d'homogénéité et d’un seuil de finesse, puis de fusionner les régions similaires pour créer le résultat segmenté.

### Image numérique 3D NIfTI
Le format d’image traité est le NIfTI (Neuroimaging Informatics Technology Initiative). Employé pour stocker des données d'imagerie médicale, il offre un support aux images multidimensionnelles. Il se présente sous la forme d'extensions telles que .nii ou .nii.gz, et des applications accessibles, telles qu'ITK-SNAP, permettent la lecture de ce format.

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
| Paramètre                    | Description                                       | Champ possibles
|---|---------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|
| Critère d’homogénéité | Définit la similarité souhaitée entre les valeurs d'une région pour qu’elle soit considéré homogène                  | Flottant dans l'intervalle [0, 1]
| Seuil de segmentation| Définit la taille minimale que peut prendre une région, limite la segmentation a une certaine profondeur | Entier naturel dans l'intervalle [1, 10 000]
| Chemin image source | Chemin vers l'image NIfTI source à segmenter | Chemin de fichier existant avec extension .nii
| Chemin image segmentation | Chemin où les images résultantes seront enregistrées | Chemin de fichier avec extension .nii
| Fichier de configuration (optionnel) | Fichier de configuration avancée | Chemin de fichier existant avec extension .txt
