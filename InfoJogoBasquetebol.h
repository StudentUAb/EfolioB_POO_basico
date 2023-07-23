/*
 * InfoJogoBasquetebol.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef INFOJOGOBASQUETEBOL_H_
#define INFOJOGOBASQUETEBOL_H_

#include "InfoJogo.h"

using namespace std;

class InfoJogoBasquetebol : public InfoJogo {
    private:
        //temos apenas um unico métod privado e nenhuma variavel como estamos
        //a herdar o infojogo todas as informações já estão disponieis lá
        //aqui temos um metodo só para trabalhar o tempo como string
        //devolve a soma do tempo em campo com o tempo já existente na lista.
        string add_time(string time1, string time2);

    public:
        //*** CONTRUTORES E DESTRUTORES ***//
        InfoJogoBasquetebol();
        virtual ~InfoJogoBasquetebol();

        //Os métodospublicos representam os métods para cada particularidade do jogo, 
        //como tal estes métodos fazem verificações específicas
        ErrorHandling add_results(int resul1, int result2); //adiciona o resultado que não pode ser empate
        ErrorHandling add_player(string name, string position, string team);    //adiciona jogador vai verificar a posição
        ErrorHandling add_substitute_player(string name, string position, string team); //adiciona jogador substituto vai verificar a posição
        ErrorHandling make_substitution(string substituted, string substitute, string time, string team);   //faz uma substituição va incrementar o tempo jogado
        ErrorHandling file_register_substitution(string name, string time, string team);    //este método é exclusivo para o trabalho com ficheiro dado que o ficheiro vem já com o tempo somado
        ErrorHandling add_scored_goal(string name, int points, string team);    //adicona pontos incementando o total do jogador
        ErrorHandling add_scored_goal_file(string name, int points, string team);   //para trabalho com fichero também nãi realiza uma validação
        ErrorHandling load_game(string filename);   //finalmente carregar um jogo de ficheiro
};

#endif /* INFOJOGOBASQUETEBOL_H_ */