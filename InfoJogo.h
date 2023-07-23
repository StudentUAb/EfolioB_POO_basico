/*
 * InfoJogo.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef INFOJOGO_H_
#define INFOJOGO_H_

#include <string>
#include <list>
#include <utility>
#include <tuple>
#include <fstream>
#include <sstream>

#include "ErrorHandling.h"

using namespace std;

class InfoJogo {
  
    private:
        //*** VARIAVEIS DA CLASSE ***//
        //vamos nos manter fieis ao enununciado e apenas aplicar o que e estritamente necessario
        int max_players1;   //maximo de jogadores em campo da equipa 1
        int max_players2;   //maximo de jogadores em campo da equipa 2
        int max_substitute_players; //maximo de jogadores substitutos que é igual para ambas as equipas
        string name1;   //nome da equipa 1
        string name2;   //nome da equipa 2
        int result1;    //resultado da equipa 1
        int result2;    //resultado da equipa 2

        //Repare agora que ao invés de estar a criar mais classes vamos seguir o que enunciado nos diz:
        //cada equipa tem jogadores titulares tanto no basket como no futebol então:
        //Poderiamos criar uma calsse Jogador com dois atributos nome e posição, e definir uma lista list<Jogador>, mas vamos simplificar e criamos um pair.
        //primeira string nome , segunda posição, repare que é igual em ambos os desportos o que muda são os nomes das posições
        list<pair<string, string>> players1;    //jogadores titurales equipa 1
        list<pair<string, string>> players2;    //jogadores titurales equipa 2
        //a lista de suplentes segue a mesma filosofia
        list<pair<string, string>> substitute_players1;
        list<pair<string, string>> substitute_players2;
        //Os golos ou pontos também tem uma estrutura identica a diferença é que no futebol é registado nome, tempo do golo e no basket é o nome e pontos totais do jogador
        //repare que continua a ser string, int.
        list<pair<string, int>> scored_goals1;
        list<pair<string, int>> scored_goals2;
        //Depois temos as substituições repare que elas existem nos dois tipos de jogos a unica diferença é a forma de registo
        //no futebol é da forma sai, entra, minuto em caso de expulsão tem o sai , #, minuto, no basket é contabilizado apenas o tempo de jogo do jogador ou seja nome, tempo
        //repare que cnsegue aproveitar a mesma lista para ambos os desportes pois se olhar temos string, string , int, 
        //no caso do basket só precisamos de string e algo para o tempo na forma 00:00 para isso podemos em usar a segunda string e ter um métod que faça a conversão da string em tempo.
        list<tuple<string, string, int>> substitutions1;
        list<tuple<string, string, int>> substitutions2;
    public:

        //*** CONTRUTORES E DESTRUTORES ***//
        //repare que no nosso destrutor geral estamos a passar o numero máximo de jogadores da modalidade
        InfoJogo(int max_players, int max_substitute_players);
        virtual ~InfoJogo();

        //*** SETTERS ***//
        //vamos fazer os nossos setters para todas as nossas variáveis incluido as nossas listas.
        //Repare desde já que muntos são do tipo ErrorHandling que é a nossa class enumerda de informação de erros
        //isto vai permitir saber que tipo de erro xiste sempre que usamos o método
        ErrorHandling set_max_players1(int max_match);
        ErrorHandling set_max_players2(int max_match);
        ErrorHandling set_max_substitute_players(int max_substitute);
        void set_result1(int result1);
        void set_result2(int result2);
        void set_name1(string name);
        void set_name2(string name);
        ErrorHandling add_teams(string team1, string team2);
        void add_player1(string name, string position);
        void add_player2(string name, string position);
        void add_substitute_player1(string name, string position);
        void add_substitute_player2(string name, string position);
        void add_scored_goal1(string name, int time);
        void add_scored_goal2(string name, int time);
        void add_substitution1(string substituted, string substitute, int time);
        void add_substitution2(string substituted, string substitute, int time);
        
        //*** GETTERS ***//
        //vamos definir todos os getters
        int get_max_players1();
        int get_max_players2();
        int get_max_substitute_players();
        int get_result1();
        int get_result2();
        string get_name1();
        string get_name2();
        list<pair<string, string>> get_players1();
        list<pair<string, string>> get_players2();
        list<pair<string, string>> get_substitute_players1();
        list<pair<string, string>> get_substitute_players2();
        list<pair<string, int>> get_scored_goals1();
        list<pair<string, int>> get_scored_goals2();
        list<tuple<string, string, int>> get_substitutions1();
        list<tuple<string, string, int>> get_substitutions2();

        //*** EXISTÊNCIAS ***//
        //já prevendo que podeeremos ter que verificar a existência em algum eleento de uma lista podemos já defiir métds para tal.
        bool has_player1(string name);
        bool has_player2(string name);
        bool has_substitute_player1(string name);
        bool has_substitute_player2(string name);
        bool has_scored_goal1(string name);
        bool has_scored_goal2(string name);
        bool has_substitution1(string name);
        bool has_substitution2(string name);

        //*** REMOÇÕES ***//
        //já prevendo que podeeremos ter que remover algu elemento de uma lista podemos já defiir métds para tal.
        void remove_player1(string name);
        void remove_player2(string name);
        void remove_substitute_player1(string name);
        void remove_substitute_player2(string name);
        void remove_scored_goal1(string name);
        void remove_scored_goal2(string name);
        void remove_substitution1(string name);
        void remove_substitution2(string name);

        //*** UTILITÁRIOS ***//
        //um pequeno utilizatrio para comparar strings
        bool iequals(const string& a, const string& b);
        //um um metodopara salvar jogos, como a composição é idêntica para salvar o método é igual
        //repare que jpa o método de carregamento não existe pelas particularidades de cada jogo.
        void save_game();
};

#endif /* INFOJOGO_H_ */