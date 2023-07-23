
/*
 * ListaJogos.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#include "ListaJogos.h"

using namespace std;


ListaJogos::ListaJogos(){}

ListaJogos::~ListaJogos(){
    soccer_games.clear();
    basketball_games.clear();
}

void ListaJogos::add_soccer_game(InfoJogoFutebol game) {
    soccer_games.push_back(game);
}

void ListaJogos::add_basketball_game(InfoJogoBasquetebol game) {
    basketball_games.push_back(game);
}

list<InfoJogoFutebol> ListaJogos::get_soccer_games() {
    return soccer_games;
}

list<InfoJogoBasquetebol> ListaJogos::get_basketball_games() {
    return basketball_games;
}

InfoJogoFutebol& ListaJogos::get_soccer_game(int id){

    auto it = std::next(soccer_games.begin(), id);
    return *it;

}

InfoJogoBasquetebol& ListaJogos::get_basketball_game(int id){

    auto it = std::next(basketball_games.begin(), id);
    return *it;

}