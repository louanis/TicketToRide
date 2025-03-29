#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"
//#define VERSION_1


#ifdef VERSION_1


void manual_loop(t_game_info * game_info){
    
	MoveData * move = (MoveData*)malloc(sizeof(MoveData));
	MoveData * move2 = (MoveData*)malloc(sizeof(MoveData));

    MoveResult move_result;
    move_result.state = 0x1;
    ResultCode result_code;
	int replay=1;


	int ScanAction = 0;
	int ScanAction2 = 0;	

	while(move_result.state == 0x1){
		printBoard();
		//roadToPlace = algo_one_road( YOU->TabOfObjetive[0], generalInfo);

		//int test = chooseColor(YOU->TabOfObjetive[0], generalInfo, YOU);

		if (game_info->playerTurn==0)
		{
			printf("Decrire action\n" );

			printf("1 pour claimRoute; 2 pour drawBlindCard; 3 pour drawCard; 4 pour chooseObjectives\n" );
			scanf("%d",&ScanAction);
			
			if (ScanAction==1)		//claim road
			{
				move->action=1;
				printf("Nom ville depart:\n");		//choose your move
				scanf("%d",(int*)&move->claimRoute.from);
				printf("Nom ville arrive:\n");
				scanf("%d",(int*)&move->claimRoute.to);
				printf("couleur:\n");
				scanf("%d",(int*)&move->claimRoute.color);
				printf("Nonbre multicolor:\n");
				scanf("%d",(int*)&move->claimRoute.nbLocomotives);

				result_code = playTheMove(move);
				filClaimRoad(generalInfo,move,YOU);
			}

			if (ScanAction==3)		//draw card
			{
				move->action=3;
				printf("couleur de la carte voulu:\n");		//choose your color
				scanf("%d",&move->drawCard.card);
				result_code = playTheMove(move);
				filCard(move,YOU,generalInfo);

				if (move->drawCard.card!=9)		//cant replay if multicolor
				{
					printf("Decrire action\n" );
					printf("1 pour drawCard; 2 pour drawBlindCard\n" );
					scanf("%d",&ScanAction2);

					if(ScanAction2==1)
					{
						printf("couleur de la carte voulu:\n");		//choose your color
						scanf("%d",&move->drawCard.card);
						result_code = playTheMove(move);
						filCard(move,YOU,generalInfo);				//fil your cards with what you draw
					}
					else
					{
						move->action=2;								//draw blind 
						result_code = playTheMove(move);
						filBlindCard(generalInfo,move,YOU);						//fil your cards with what you drawblinb
					}
				}
			}

			if (ScanAction==2)		//draw blind card
			{
				move->action=2;
				result_code = playTheMove(move);		//next what did u do?
				filBlindCard(generalInfo,move,YOU);						// fil your cards with what you drawblind

				printf("Decrire action\n" );
				printf("1 pour drawCard; 2 pour drawBlindCard\n" );
				scanf("%d",&ScanAction2);
				if(ScanAction2==1)
				{
					move->action=3;
					printf("couleur de la carte voulu:\n");		//choose your color
					scanf("%d",&move->drawCard.card);
					result_code = playTheMove(move);
					filCard(move,YOU,generalInfo);				//fil your cards with what you draw
				}
				else
				{
					result_code = playTheMove(move);		//draw blind 
					filBlindCard(generalInfo,move,YOU);						//fil your cards with what you drawblinb
				}
			}

			if (ScanAction==4)		//take ojective
			{
				move->action=4;
				result_code = playTheMove(move);

				for (int i = 0; i < 3; ++i)
				{
					printf("objectif:%d ville:%d a ville:%d valeur:%d \n",i,move->chooseObjectives[i].from,
																			move->chooseObjectives[i].to,
																			move->chooseObjectives[i].score);
				}

				move2->action=5;		//chose objective
				printf("choisir 1 valider 0 jeter pour chaque objectifs\n");
				scanf("%d",(int*)&move2->chooseObjectives[0]);
				scanf("%d",(int*)&move2->chooseObjectives[1]);
				scanf("%d",(int*)&move2->chooseObjectives[2]);

				result_code = playTheMove(move2);
				printf("Vous avez pris %d objectifs\n",move2->chooseObjectives.nbObjectives );

				filOjective(generalInfo,move,move2,YOU);	//fil you with the objeective

			}
			if (ScanAction==5)
			{
				break;
			}

			game_info->playerTurn=1;	
		}

		else {
			if (game_info->playerTurn==1)
			{
				printf("tour ENNEMIE\n");
				// t_return_code getMove(t_move* move, int* replay);
				result_code = getMove(move,&replay);
				lookMove(move);
				if (move->action==1)
				{
					filClaimRoad(generalInfo,move,ENNEMIE);
				}
				if (move->action==2)
				{
					filBlindCard(generalInfo,move,ENNEMIE);
				}
				if (move->action==3)
				{
					filCard(move,ENNEMIE,generalInfo);	
				}
				if (move->action==4)
				{
					replay=1;	//take objectiv
				}

		
				if(replay)
					result_code = getMove(move2,&replay);

				game_info->playerTurn=0;
				lookMove(move2);
				if (move2->action==1)
				{
					filClaimRoad(generalInfo,move2,ENNEMIE);
				}
				if (move2->action==2)
				{
					filBlindCard(generalInfo,move2,ENNEMIE);
				}
				if (move2->action==3)
				{
					filCard(move2,ENNEMIE,generalInfo);	
				}
				if (move2->action==5)
				{
					filOjective(generalInfo,move,move2,ENNEMIE);;
				}
			}
		}
	}
	free(move);
	free(move2);

    printf("%d",(int)result_code);
    return;

}

int play_move_authorize(MoveData * move,t_game_info * game_info){

    switch((int)move->action){
        case 1:
            int maxcit = MAX((int)move->claimRoute.from,(int)move->claimRoute.to);
            int mincit = MIN((int)move->claimRoute.from,(int)move->claimRoute.to);
            if(game_info->board->M[maxcit][mincit].length ==-1 || ((int)move->claimRoute.color!=game_info->board->M[maxcit][mincit].col1 && (int)move->claimRoute.color!= game_info->board->M[maxcit][mincit].col2)){
                return 0;
            } else{
                return 1;
            } 
        break;

        case 2:
            return 1;
        break;

        case 3:
            if(is_in(move->drawCard,(int*)game_info->visibleCards.card,5)){
                return 1;
            } else{
                return 0;
            }  
        break;

        case 4:
            
        break;

        default:
        break;
     
    } 

    return 0;
} 
#else

void JouerSolo(int continuer,MoveResult mresult ,BoardState EtatPlateau)
{
    int OnJoue;
    MoveData moveData;
    getBoardState(&EtatPlateau);
    AfficherEtatPlateau(&EtatPlateau);
    printf("Jouons à un jeu: \n 0: l'adversaire joue \n 1: piocher des objectives \n 2: piochez wagons\n 3: choisi wagons\n 4: claim route\n 5: ff\n");
    scanf("%d",&OnJoue);
    switch (OnJoue)
    {
    case 0: //on laisse l'adversaire jouer
        getMove(&moveData, &mresult);
        AfficherAction(&moveData);
        free(mresult.opponentMessage);
        free(mresult.message);
        if ( ((moveData.action%2) || (moveData.drawCard!=9 )) && (moveData.action != 1) )
        {
            getMove(&moveData, &mresult);
            AfficherAction(&moveData);
            free(mresult.opponentMessage);
            free(mresult.message);
        }
        //faire if quand le joueur adversaire doit rejouer
        break;

    case 1: // on pioche des objectives
        moveData.action = 4;
        sendMove(&moveData, &mresult);
        printf("move :%d\n",mresult.state);
        AfficherObjectif(&mresult);
        free(mresult.opponentMessage);
        free(mresult.message);
        printf("lesquels prendre? \n");
        int val;
        for (int i=0;i<3;i++)
        {
            scanf("%d",&val);
            moveData.chooseObjectives[i]=val;
        }
        moveData.action = 5;
        sendMove(&moveData, &mresult);
        printf("move :%d\n",mresult.state);
        free(mresult.opponentMessage);
        free(mresult.message);
        break;

    case 2: // on pioche un carte de la pioche wagon face caché
        moveData.action = 2;
        sendMove(&moveData, &mresult);
        printf("move :%d\n",mresult.state);
        printf("carte pioché :%d\n",mresult.card);
        free(mresult.opponentMessage);
        free(mresult.message);
        printf("vous pouvez rejouer 2 ou 3");
        break;
    
    case 3: // on choisit un wagon face visible attention si on prend un locomotive on doit passer notre tour
        int carte;
        moveData.action = 3; 
        printf("choisir carte\n");
        scanf("%d",&carte);
        moveData.drawCard = carte;
        sendMove(&moveData, &mresult);
        printf("move :%d\n",mresult.state);
        free(mresult.opponentMessage);
        free(mresult.message);
        if (moveData.drawCard == 9) {printf("vous pouvez rejouer 2 ou 3");}
        break;

    case 4: // claim une route
        printf("On prend une route \n");
        moveData.action = 1;
        printf("ville1 puis ville2 puis couleur puis nbrlocomotive \n");
        int value;
        scanf("%d",&value);
        moveData.claimRoute.from = value;
        scanf("%d",&value);
        moveData.claimRoute.to = value;
        scanf("%d",&value);
        moveData.claimRoute.color = value;
        scanf("%d",&value);
        moveData.claimRoute.nbLocomotives = value;
        sendMove(&moveData, &mresult);
        printf("move :%d\n",mresult.state);
        free(mresult.opponentMessage);
        free(mresult.message);
        break;


    case 5: // on abandonne le jeu
        printf("fin du fun \n");
        continuer = 0;
        quitGame();
        break;
    
    }
}


#endif

