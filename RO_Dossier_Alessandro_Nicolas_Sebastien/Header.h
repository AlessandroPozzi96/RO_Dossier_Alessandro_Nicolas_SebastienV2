#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define RACINNE
#define SMIN 11
#define SMAX 42
#define TEMPSSIMULE 960
#define CAPACITE_FILE_EXPRESS 8
#define NBSTATION_EXPRESS 2
#define NBCLIENTSNORMALE 1000
#define LAMBDA 2.2
#define COUT_CLIENT_EXPRESS 37.5
#define COUT_CLIENT_NORMALE 25.5
#define COUT_CLIENT_PRIORITAIRE	42.5
#define COUT_EXPRESS 30
#define COUT_NORMALE 35
#define COUT_INOCCUPATION 18
#define EXPRESS_VERS_NORMALE 5

//Structures et �num�rations

enum type { VIDE = 0, PRIORITAIRE, NORMALE, EXPRESS };
typedef enum type Type;

typedef struct clientNormale ClientNormale;
struct clientNormale
{
	int DS;
	Type type;
};

//Prototypes de fonctions

void initialisations(int s, int *fileNormale, int *fileExpress, int *nbMinInoccupation, int *nbPrioritaires, int *minStationExpress, int *minStationNormale, int *t, int *minCumulExpress, int *minCumNormale, int *minCumPrioritaire, int *minStationExpressPr�c�dent, int *tabStationExpress, ClientNormale *tabStationNormale);
int g�n�rerNbArriv�(void);
void placementEnFile(int nbArriv�es, int *fileExpress, int *fileNormale, int *tabFileExpress, int *tabFileNormale, int *nbrExpressDansStationNormaleEtFileNormale, int nbPrioritaires, int *nbrNormaleDansSyst�me, int *cout);
int g�n�rerDS(void);
void d�calageDroite(int *tabFile, int file, int iPos);
void d�calageGauche(int *tabFile, int file);
void trtStationNormale(int s, ClientNormale *tabStationNormale, int *fileNormale, int *minStationNormale, int *nbPrioritaires, int *tabFileNormale, int *nbMinInoccupation, int *nbrPrioritairesDansSyst�me, int *nbrNormaleDansSyst�me, int *nbrExpressDansStationNormaleEtFileNormale);
void quiSort(ClientNormale *tabStationNormale, int iStation, int *nbrPrioritairesDansSyst�me, int *nbrNormaleDansSyst�me, int *nbrExpressDansStationNormaleEtFileNormale);
void trtStationExpress(int *tabStationExpress, int *fileExpress, int *minStationExpress, int *tabFileExpress, int *nbMinInoccupation);
void trtPrioritaires(int *fileNormale, int s, int *tabFileNormale, ClientNormale *tabStationNormale, int *nbPrioritaires, int *nbrPrioritairesDansSyst�me, int *nbrNormaleDansSyst�me);
void cout(int s, int *cout, int minCumNormale, int minCumulExpress, int minCumPrioritaires, int minStationExpress, int minStationNormale, int nbMinInoccupation, int *tabCout);




// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme
