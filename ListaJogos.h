/*
 * ListaJogos.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef LISTAJOGOS_H_
#define LISTAJOGOS_H_

#include "InfoJogoFutebol.h"
#include "InfoJogoBasquetebol.h"

#include <list>

using namespace std;

class ListaJogos {

private:

    //*** VARIAVEIS DA CLASSE ***//
    //para permitir varios jogos no sistema criamos uma classe para guardar a lista de jogos 
    //que basicamente é uma lista de objetos de futebol ou basket
    list<InfoJogoFutebol> soccer_games;
    list<InfoJogoBasquetebol> basketball_games;

public:
    //*** CONTRUTORES E DESTRUTORES ***//
    ListaJogos();
    virtual ~ListaJogos();

    //*** SETTERS ***//
    void add_soccer_game(InfoJogoFutebol game);
    void add_basketball_game(InfoJogoBasquetebol game);
    //*** GETTERS ***//
    list<InfoJogoFutebol> get_soccer_games();
    list<InfoJogoBasquetebol> get_basketball_games();
    //*** GETTERS ESPECIFICOS POR ID ***//
    InfoJogoFutebol& get_soccer_game(int id);
    InfoJogoBasquetebol& get_basketball_game(int id);
};

#endif /* LISTAJOGOS_H_ */