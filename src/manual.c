#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"
#define VERSION_1


#ifdef VERSION_1


void manual_loop(t_game_info * game_info){

	MoveData oppMove;
	MoveData myMove;
	MoveResult moveResult;

	int buffer[20]; // storing all input in the same array in an organized way to prevent pletorade of variables

	int replay = 0; // 0 if first move played since last turn switch, 1 if second move in a row 
    int legal = 1; // 1 if the move i am going to play is legal, else 0

	while(1){ 
		if(game_info->playerTurn == 1){
			printf("Move ? : ");
			scanf("%d",&buffer[0]);
			printf("\n");

			switch(buffer[0]){
				/*Still need to fill in the cases*/
				case 1:
                    if(replay == 0) {
                        
                    }

				break;

				case 2:
                    myMove.action = 2;
				break;

				case 3:
				break;

				case 4:
				break;

				default: //5
				break;
			} 
            if(legal == 1) {
			    sendMove(&myMove,&moveResult);

            }


		}else if(game_info->playerTurn == 2){
			getMove(&oppMove,&moveResult);
			free(moveResult.message);
			free(moveResult.opponentMessage);

			if((int)oppMove.action == 2 || (int)oppMove.action == 4 ){ //%2 == 0

				switch(replay){
					case 0:
						game_info->playerTurn = 2;
						replay = 1;
					break;

					case 1:
						game_info->playerTurn = 1;
						replay = 0;
					break;

					default:
					break;
				} 

			} else if ((int)oppMove.action == 3){ // if in another if to prevent wrongful acess of 
				if( (int)oppMove.drawCard == 9){
					game_info->playerTurn = 2;

				} else{
					game_info->playerTurn = 1;

				} 
			}  else{
				game_info->playerTurn = 1;
			} 
		} 
	} 
    
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

