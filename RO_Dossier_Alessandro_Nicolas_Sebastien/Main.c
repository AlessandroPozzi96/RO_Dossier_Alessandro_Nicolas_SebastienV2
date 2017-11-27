#include "Header.h"
#include "stdafx.h"

void main(void)
{


	system("pause");
}

void initialisations(int s, int *fileNormale, int *fileExpress, int *nbMinInoccupation, int *nbPrioritaires, int *minStationExpress, int *minStationNormale, int *t, int *minCumulExpress, int *minCumNormale, int *minCumPrioritaire, int *minStationExpressPrécédent, int *tabStationExpress, ClientNormale *tabStationNormale)
{
	//Initialisations des stations

	int i = 0;
	while (i < NBSTATION_EXPRESS)
	{
		tabStationExpress[i] = 0;
	}

	i = 0;
	while (i < s)
	{
		tabStationNormale[i].DS = 0;
		tabStationNormale[i].type = VIDE;
	}

	//Initialisations des variables
	*fileNormale = *fileExpress = *nbMinInoccupation = *nbPrioritaires = *minStationExpress = *minStationNormale = *minCumulExpress = *minCumNormale = *minCumPrioritaire = *minStationExpressPrécédent = 0;
	*t = 1;
}

void placementEnFile(int nbArrivées, int *fileExpress, int *fileNormale, int *tabFileExpress, int *tabFileNormale, int *nbrExpressDansStationNormaleEtFileNormale, int nbPrioritaires, int *nbrNormaleDansSystème, int *cout)
{
	int i = 0;
	int DS = 0;
	int iPos;

	while (i < nbArrivées)
	{
		DS = générerDS();

		if (DS <= 3)
		{
			if (*fileExpress < 8)
			{
				tabFileExpress[*fileExpress] = DS;
				*fileExpress++;
			}
			else
			{
				*nbrExpressDansStationNormaleEtFileNormale++;
				iPos = nbPrioritaires;

				while (iPos < *fileNormale && tabFileNormale[iPos] <= 3)
				{
					iPos++;
				}

				décalageDroite(tabFileNormale, *fileNormale, iPos);
				tabFileNormale[iPos] = DS;
				*fileNormale++;
				*cout += 5;
			}
		}
		else
		{
			tabFileNormale[iPos] = DS;
			*fileNormale++;
			*nbrNormaleDansSystème++;
		}
		i++;
	}
}

void décalageDroite(int *tabFile, int file, int iPos)
{
	int i = file;
	while (i > iPos)
	{
		tabFile[i] = tabFile[i - 1];
		i--;
	}
}	

void décalageGauche(int *tabFile, int file)
{
	int i = 0;
	while (i < file)
	{
		tabFile[i] = tabFile[i + 1];
		i++;
	}
}

void trtStationNormale(int s, ClientNormale *tabStationNormale, int *fileNormale, int *minStationNormale, int *nbPrioritaires, int *tabFileNormale, int *nbMinInoccupation, int *nbrPrioritairesDansSystème, int *nbrNormaleDansSystème, int *nbrExpressDansStationNormaleEtFileNormale)
{
	int iStation = 0;

	while (iStation < s)
	{
		if (tabStationNormale[iStation].DS == 0) // Si la station normale est vide 
		{
			quiSort(tabStationNormale, iStation, nbrPrioritairesDansSystème, nbrNormaleDansSystème, nbrExpressDansStationNormaleEtFileNormale);
			//Un client est à 0 minutes

			tabStationNormale[iStation].type = VIDE;

			if (*fileNormale > 0)
			{
				*minStationNormale++;

				if (nbPrioritaires > 0)
				{
					tabStationNormale[iStation].DS = tabFileNormale[0] - 1;
					tabStationNormale[iStation].type = PRIORITAIRE;
					*nbPrioritaires--;
				}
				else
				{
					if (tabFileNormale[0] <= 3)
					{
						tabStationNormale[iStation].type = EXPRESS;
					}
					else
					{
						tabStationNormale[iStation].type == NORMALE;
					}

					tabStationNormale[iStation].DS = tabFileNormale[0] - 1;
				}

				décalageGauche(tabFileNormale, *fileNormale);
				*fileNormale--;
			}
			else
			{
				*nbMinInoccupation++;
			}
		}
		else
		{
			tabStationNormale[iStation].DS--;
			*minStationNormale++;
		}
		iStation++;
	}
}

void quiSort(ClientNormale *tabStationNormale, int iStation, int *nbrPrioritairesDansSystème, int *nbrNormaleDansSystème, int *nbrExpressDansStationNormaleEtFileNormale)
{
	switch (tabStationNormale[iStation].type)
	{
	case PRIORITAIRE: *nbrPrioritairesDansSystème--;
		break;
	case NORMALE: *nbrNormaleDansSystème--;
		break;
	case EXPRESS: *nbrExpressDansStationNormaleEtFileNormale--;
		break;
	}
}

void trtStationExpress(int *tabStationExpress, int *fileExpress, int *minStationExpress, int *tabFileExpress, int *nbMinInoccupation)
{
	int iStation = 0;

	while (iStation < NBSTATION_EXPRESS)
	{
		if (tabStationExpress[iStation] == 0)
		{
			if (*fileExpress > 0) //Si il y a qqun en file express
			{
				*minStationExpress++;
				tabStationExpress[iStation] = tabFileExpress[0] - 1;

				//On décale le tableau a gauche
				décalageGauche(tabFileExpress, *fileExpress);

				*fileExpress--;
			}
			else
			{
				*nbMinInoccupation--;
			}
		}
		else
		{
			*minStationExpress++;
			tabStationExpress[iStation]--;
		}
		iStation++;
	}
}

void trtPrioritaires(int *fileNormale, int s, int *tabFileNormale, ClientNormale *tabStationNormale, int *nbPrioritaires, int *nbrPrioritairesDansSystème, int *nbrNormaleDansSystème)
{
	if (*fileNormale > 0)
	{
		int iStation = 0;
		int prio = 0;

		while (iStation < s && tabFileNormale[0] < 3)
		{
			if (tabStationNormale[iStation].DS >= 5 && tabStationNormale[iStation].type != PRIORITAIRE)
			{
				*nbPrioritaires++;
				*nbrPrioritairesDansSystème++;
				*nbrNormaleDansSystème--;
				prio = tabStationNormale[iStation].DS;
				tabStationNormale[iStation].DS = tabFileNormale[0];
				tabStationNormale[iStation].type = EXPRESS;
				tabFileNormale[0] = prio;
			}

			iStation++;
		}
	}
}

void cout(int s, int *cout, int minCumNormale, int minCumulExpress, int minCumPrioritaires, int minStationExpress, int minStationNormale, int nbMinInoccupation, int *tabCout)
{
	*cout = minCumNormale * ((double)COUT_CLIENT_NORMALE / 60) + minCumulExpress * ((double)COUT_CLIENT_EXPRESS / 60) + minCumPrioritaires * ((double)COUT_CLIENT_PRIORITAIRE / 60) + minStationExpress * ((double)COUT_EXPRESS / 60) + minStationNormale * ((double)COUT_NORMALE / 60) + nbMinInoccupation * ((double)COUT_INOCCUPATION / 60);
	tabCout[s - SMIN] = *cout;
}