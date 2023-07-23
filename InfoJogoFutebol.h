/*
 * InfoJogoFutebol.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef INFOJOGOFUTEBOL_H_
#define INFOJOGOFUTEBOL_H_

#include "InfoJogo.h"

using namespace std;

class InfoJogoFutebol : public InfoJogo {

    public:
        //a ideia é a mesma do jogo de basket
        //*** CONTRUTORES E DESTRUTORES ***//
        InfoJogoFutebol();
        ~InfoJogoFutebol();
        ErrorHandling add_results(int resul1, int result2);
        ErrorHandling add_player(string name, string position, string team);
        ErrorHandling add_substitute_player(string name, string position, string team);
        ErrorHandling make_substitution(string substituted, string substitute, int time, string team);
        ErrorHandling file_register_substitution(string substituted, string substitute, int time, string team);
        ErrorHandling expel_player(string name, int time, string team);
        ErrorHandling add_scored_goal(string name, int time, string team);
        ErrorHandling load_game(string filename);
        
};

#endif /* INFOJOGOFUTEBOL_H_ */