/*
 * UserInterface.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <iostream>
#include <string>
#include <limits>
#include <iomanip> 
#include "ListaJogos.h"
#include "InfoJogoFutebol.h"
#include "InfoJogoBasquetebol.h"

using namespace std;

class UserInterface {

private:

    //esta classe não necessita de grande explicação cada método é uma representação de 
    //output e inout para o usário que se integra com as classes do nosso sistema
    void clear_cin();
    string error_messages(ErrorHandling type_error);
   
    void create_new_game(ListaJogos& game_list);

    void create_soccer_game(ListaJogos& game_list);

    void register_new_match_player(InfoJogoFutebol& game);
    void register_new_sub_player(InfoJogoFutebol& game);
    void register_soccer_game_sub(InfoJogoFutebol& game);
    void register_soccer_game_exp(InfoJogoFutebol& game);
    void register_soccer_goals(InfoJogoFutebol& game);

    void create_basketball_game(ListaJogos& game_list);
    void register_new_match_b_player(InfoJogoBasquetebol& game);
    void register_new_sub_b_player(InfoJogoBasquetebol& game);
    void register_basket_game_sub(InfoJogoBasquetebol& game);
    void register_basket_points(InfoJogoBasquetebol& game);

    void show_list_of_games(ListaJogos& game_list);
    void show_soccer_games(ListaJogos& game_list);
    void show_basketball_games(ListaJogos& game_list);

    void show_game_details(ListaJogos& game_list);
    void show_details_soccer_game(ListaJogos& game_list);
    void show_details_basketball_game(ListaJogos& game_list);
    
    void update_game_info(ListaJogos& game_list);
    void update_soccer_game(ListaJogos& game_list);
    void update_basketball_game(ListaJogos& game_list);

    void load_game_info_from_file(ListaJogos& game_list);
    void load_file_basket(ListaJogos& game_list);
    void load_file_soccer(ListaJogos& game_list);

    void save_game_info(ListaJogos& game_list);
    void save_soccer_info(ListaJogos& game_list);
    void save_basket_info(ListaJogos& game_list);

   
public:
    //*** CONTRUTORES E DESTRUTORES ***//
    UserInterface();
    virtual ~UserInterface();
    void run();
};

#endif /* USERINTERFACE_H_ */