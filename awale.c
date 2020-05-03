#include <stdlib.h>
#include <stdio.h>

typedef int plateau[12];

int player = 0;
int lastcase;
int cs0 = 0, cs1 = 0;

int change_turn(int player)
{
	player = (player + 1)%2;
	return player;
}

void affichage(plateau tab)
{
	int i;

	for (i = 11; i >= 6; i--)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
	for (i = 0; i < 6; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void gameplay(plateau tab)
{
	int c;
	int hand;
	int i;

	do
	{
		printf("Choississez une case de 1 a 6 non vide (de gauche a droite)\n");
		scanf("%d", &c);
	
		while((c>6 || c<0))
		{
			printf("Le nombre choisin'est pas convenable.\n");
			printf("Choississez une case de 1 a 6 non vide (de gauche a droite)\n");
			scanf("%d", &c);
		}
		
		if (player == 1)
		{
			switch (c)
			{
			case 1:	c = 12;
				break;
			case 2:	c = 11;
			break;
			case 3: c = 10;
				break;
			case 4: c = 9;
				break;
			case 5: c = 8;
				break;
			case 6: c = 7;
				break;

			default:printf("le nombre choisi n'est pas convenable\n");
				break;
			}
	}
			
			
		
	}while(tab[c-1] == 0);
	
	
	
/*	while((c>6 || c<0) || tab[c-1] == 0)
	{
		if(c<0 || c > 6)
		{
			printf("le nombre choisi n'est pas convenable\n");
		}
		
		if(tab[c-1] == 0)
		{
			printf("il n y a rien a prendre dans cette case\n");
		}
		printf("Choississez une case de 1 a 6 non vide (de gauche a droite)\n");
		scanf("%d", &c);
	}
	
	if (player == 1)
	{
		switch (c)
		{
		case 1:	c = 12;
			break;
		case 2:	c = 11;
			break;
		case 3: c = 10;
			break;
		case 4: c = 9;
			break;
		case 5: c = 8;
			break;
		case 6: c = 7;
			break;

		default:printf("le nombre choisi n'est pas convenable\n");
			break;
		}
	}*/
	
	c=c-1;
	
	hand = tab[c];
	tab[c] = 0;
	for (i = c+1; i <= c+hand; i++)
	{
		tab[i%12] = tab[i%12] + 1;
		lastcase = i%12;
	}
		printf("               last case is : %d\n",(lastcase%12)+1);
	
}
// 2 6 1 4
//when a player scores, the case doesn t reset to 0 
//the mistake was in line 85 where lastecase received a number above 12
//solution add a modulo so that the number is always contained between 0 and 11


//2 6 1 4 3 3 4 2 5 5 
//at this stage the player 2 scores 4pts instead of 5

void  resultat(plateau tab, int lastcase)
{
	int lastc_seeds = tab[lastcase];
	
	if(lastc_seeds == 2 || lastc_seeds == 3)
	{
		do
		{
			if(player == 0)
			{
				cs0 = cs0 + lastc_seeds;
				tab[lastcase] = 0;
			}
			if (player == 1)
			{
				cs1 = cs1 + lastc_seeds;
				tab[lastcase] = 0;
			}
			lastcase = (lastcase - 1)%12;
			lastc_seeds = tab[lastcase];
		} while (lastcase == 2 || lastcase == 3);
	}
	printf("                     le score du joueur 1 est : %d\n", cs0);
	printf("                     le score du joueur 2 est : %d\n", cs1);

}

int endgame(plateau tab)
{
	if((tab[1] == tab[2] && tab[2] == tab[3] && tab[3]== tab[4] && tab[4] == tab[5] && tab[5] == tab[0] && tab[0]== 0) || (tab[11] == tab[10] && tab[10] == tab[9] && tab[9] == tab[8] && tab[8] == tab[7] && tab[7]== tab[6] && tab[6] == 0))
	{
		printf("Fin de la partie.\n");
		if(cs0<cs1)
		{
			printf("Joueur 2 gagne");
		}
		if(cs1<cs0)
		{
			printf("Joueur 1 gagne");
		}
		return 1;
	}
	return 0;
}

int main()
{
	int tab[12];
	int i;
	for(i=0;i<12;i++)
	{
		tab[i] = 4;
	}
	affichage(tab);
	printf("***Tour du joueur %d***\n",player+1);
	while(1)
	{
		gameplay(tab);
		resultat(tab,lastcase);
		player = change_turn(player);
		affichage(tab);
		if(endgame(tab) == 1)
		{
			break;
		}
		printf("***Tour du joueur %d***\n",player+1);

	}
	
}

