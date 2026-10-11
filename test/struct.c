#include <stdio.h>
#include <string.h>

typedef struct
{
    char nom[30];
    float prix;
    int quantite;
} Produit;


void afficher(Produit *p)
{
    printf("%s : %.1f € x %d\n", p->nom, p->prix, p->quantite);
}

int total(Produit *p)
{
    int total;
    total = p->prix * p->quantite;
}

int main()
{
    Produit stock[3] = {
        {"Stylo", 1.5, 10},
        {"Cahier", 3.0, 5},
        {"Sac", 25.0, 2}
    };

    int i = 0;
    float total = 0;
    while(i < 3)
    {
        afficher(&stock[i]);
        total += stock[i].prix * stock[i].quantite;
        i++;
    }
    printf("Valeur totale du stock : %.1f €\n", total);
}

