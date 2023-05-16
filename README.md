# Simulateur de frappe

Ce programme permet de simuler la frappe de touches à l'aide de la bibliothèque X11. Il est utile pour automatiser des actions qui nécessitent une interaction avec le clavier.

## Prérequis

Avant de compiler et exécuter le programme, assurez-vous d'avoir installé les bibliothèques suivantes :

- libx11-dev
- libxtst-dev

Pour les installer, vous pouvez utiliser la commande suivante :

```bash
apt install libx11-dev libxtst-dev
```

## Compilation

Pour compiler le programme, exécutez la commande suivante :

```bash
gcc -o simulateur simulateur.c -lX11 -lXtst
```

## Utilisation

Pour exécuter le programme, utilisez la commande suivante :

```bash
./simulateur
```

Le programme simule les actions suivantes :

1. Appui de la touche Super (la touche Windows)
2. Frappe du texte "Mouspad"
3. Appui de la touche Return
4. Frappe du texte "Hello World !!"

Assurez-vous d'avoir une fenêtre active qui peut recevoir les frappes de clavier lors de l'exécution du programme.

## Notes

- Ce programme utilise la bibliothèque X11 pour interagir avec le System.
- Il a été testé sur un environnement Xubuntu 22.04.2 Desktop.
- Assurez-vous d'avoir les droits d'accès nécessaires pour interagir le System.
