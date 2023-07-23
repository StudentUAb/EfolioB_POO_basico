/*
 * InfoJogo.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#include "InfoJogo.h"

using namespace std;

//repare que no nosso construtor definimos o maximo de jogadores do desporto
InfoJogo::InfoJogo(int max_match, int max_substitute){
    max_players1 = max_match;
    max_players2 = max_match;
    max_substitute_players = max_substitute;
}

//no nosso destrutor como estamos a trabalhar com listas temos que as limpar
InfoJogo::~InfoJogo(){
    players1.clear();
    players2.clear();
    substitute_players1.clear();
    substitute_players2.clear();
    scored_goals1.clear();
    scored_goals2.clear();
    substitutions1.clear();
    substitutions2.clear();
}

//repare que ao longo dos métodos a calass eumerada é untilizada para devolver o status d erro ou sucesso, 
//dessa forma temos a certeza que o métod resultou.
//repare ainda que isso não acontece em todos os métodos do InfoJogo pois estes não são acessados diretamente pelo ytilizador mas sim vão ser usados como herança.
ErrorHandling InfoJogo::set_max_players1(int max_match){
    if(max_match < 0){return ErrorHandling::INVALID_PLAYER_NUMBERS;}
    max_players1 = max_match;
    return ErrorHandling::OK;
}

ErrorHandling InfoJogo::set_max_players2(int max_match){
    if(max_match < 0){return ErrorHandling::INVALID_PLAYER_NUMBERS;}
    max_players2 = max_match;
    return ErrorHandling::OK;
}

int InfoJogo::get_max_players1(){
    return max_players1;
}

int InfoJogo::get_max_players2(){
    return max_players2;
}

ErrorHandling InfoJogo::set_max_substitute_players(int max_substitute){
    if(max_substitute < 0){return ErrorHandling::INVALID_PLAYER_NUMBERS;}
    max_substitute_players = max_substitute;
    return ErrorHandling::OK;
}

int InfoJogo::get_max_substitute_players(){
    return max_substitute_players;
}

void InfoJogo::set_name1(string name){
    name1 = name;
}

string InfoJogo::get_name1(){
    return name1;
}

void InfoJogo::set_name2(string name) {
    name2 = name;
}

string InfoJogo::get_name2(){
    return name2;
}

//Repare que neste método existe verificação se as equipes são iguais ou não e apenas depois usa o setter para as definir
ErrorHandling InfoJogo::add_teams(string team1, string team2){
    if(team1 == "" || team2 == ""){
        return ErrorHandling::INVALID_TEAM_NAME;
    }

    if(team1 == team2){
        return ErrorHandling::MATCHING_TEAM_NAMES;
    }

    set_name1(team1);
    set_name2(team2);

    return ErrorHandling::OK;
}

void InfoJogo::set_result1(int result){
    result1 = result;
}

int InfoJogo::get_result1(){
    return result1;
}

void InfoJogo::set_result2(int result) {
    result2 = result;
}

int InfoJogo::get_result2(){
    return result2;
}

void InfoJogo::add_player1(string name, string position) {
    players1.push_back({name, position});
}

void InfoJogo::add_player2(string name, string position) {
    players2.push_back({name, position});
}

void InfoJogo::add_substitute_player1(string name, string position) {
    substitute_players1.push_back({name, position});
}

void InfoJogo::add_substitute_player2(string name, string position) {
    substitute_players2.push_back({name, position});
}

void InfoJogo::add_scored_goal1(string name, int time) {
    scored_goals1.push_back({name, time});
}

void InfoJogo::add_scored_goal2(string name, int time) {
    scored_goals2.push_back({name, time});
}

void InfoJogo::add_substitution1(string substituted, string substitute, int time) {
    substitutions1.push_back({substituted, substitute, time});
}

void InfoJogo::add_substitution2(string substituted, string substitute, int time) {
    substitutions2.push_back({substituted, substitute, time});
}

list<pair<string, string>> InfoJogo::get_players1() {
    return players1;
}

list<pair<string, string>> InfoJogo::get_players2() {
    return players2;
}

list<pair<string, string>> InfoJogo::get_substitute_players1() {
    return substitute_players1;
}

list<pair<string, string>> InfoJogo::get_substitute_players2() {
    return substitute_players2;
}

list<pair<string, int>> InfoJogo::get_scored_goals1() {
    return scored_goals1;
}

list<pair<string, int>> InfoJogo::get_scored_goals2() {
    return scored_goals2;
}

list<tuple<string, string, int>> InfoJogo::get_substitutions1() {
    return substitutions1;
}

list<tuple<string, string, int>> InfoJogo::get_substitutions2() {
    return substitutions2;
}

bool InfoJogo::has_player1(string name) {
    for (auto p : players1) {
        if (p.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_player2(string name) {
    for (auto p : players2) {
        if (p.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_substitute_player1(string name) {
    for (auto p : substitute_players1) {
        if (p.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_substitute_player2(string name) {
    for (auto p : substitute_players2) {
        if (p.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_scored_goal1(string name) {
    for (auto g : scored_goals1) {
        if (g.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_scored_goal2(string name) {
    for (auto g : scored_goals2) {
        if (g.first == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_substitution1(string name) {
    for (auto s : substitutions1) {
        if (get<0>(s) == name) {
            return true;
        }
    }
    return false;
}

bool InfoJogo::has_substitution2(string name) {
    for (auto s : substitutions2) {
        if (get<0>(s) == name) {
            return true;
        }
    }
    return false;
}

void InfoJogo::remove_player1(string name) {
    players1.remove_if([&](pair<string, string> p){
        return p.first == name;
    });
}

void InfoJogo::remove_player2(string name) {
    players2.remove_if([&](pair<string, string> p){
        return p.first == name;
    });
}

void InfoJogo::remove_substitute_player1(string name) {
    substitute_players1.remove_if([&](pair<string, string> p){
        return p.first == name;
    });
}

void InfoJogo::remove_substitute_player2(string name) {
    substitute_players2.remove_if([&](pair<string, string> p){
        return p.first == name;
    });
}

void InfoJogo::remove_scored_goal1(string name) {
    scored_goals1.remove_if([&](pair<string, int> g){
        return g.first == name;
    });
}

void InfoJogo::remove_scored_goal2(string name) {
    scored_goals2.remove_if([&](pair<string, int> g){
        return g.first == name;
    });
}

void InfoJogo::remove_substitution1(string name) {
    substitutions1.remove_if([&](tuple<string, string, int> s){
        return get<0>(s) == name || get<1>(s) == name;
    });
}

void InfoJogo::remove_substitution2(string name) {
    substitutions2.remove_if([&](tuple<string, string, int> s){
        return get<0>(s) == name || get<1>(s) == name;
    });
}

bool InfoJogo::iequals(const string& a, const string& b){
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}


//para savalr as informações de jogo criamos uma ficha de jogo em txt, 
//essa ficha basicamente usa cabeçalhos para identificar as variaveis.
void InfoJogo::save_game() {
    string filename = get_name1() + " vs " +get_name2() + ".txt";
    ofstream ofs(filename);
    ostringstream oStream;

    oStream << "name1:" << '\n';
    oStream << name1 << '\n';
    oStream << "name2:" << '\n';
    oStream << name2 << '\n';
    oStream << "result1:" << '\n';
    oStream << result1 << '\n';
    oStream << "result2:" << '\n';
    oStream << result2 << '\n';
    oStream << "max_players1:" << '\n';
    oStream << max_players1 << '\n';
    oStream << "max_players2:" << '\n';
    oStream << max_players2 << '\n';
    oStream << "max_substitute_players:" << '\n';
    oStream << max_substitute_players << '\n';
    oStream << "players1_size:" << '\n';
    oStream << players1.size() << '\n';
    for (const auto& pair : players1) {
        oStream << "players1_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "players1_position:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "players2_size:" << '\n';
    oStream << players2.size() << '\n';
    for (const auto& pair : players2) {
        oStream << "players2_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "players2_position:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "substitute_players1_size:" << '\n';
    oStream << substitute_players1.size() << '\n';
    for (const auto& pair : substitute_players1) {
        oStream << "substitute_players1_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "substitute_players1_position:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "substitute_players2_size:" << '\n';
    oStream << substitute_players2.size() << '\n';
    for (const auto& pair : substitute_players2) {
        oStream << "substitute_players2_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "substitute_players2_position:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "scored_goals1_size:" << '\n';
    oStream << scored_goals1.size() << '\n';
    for (const auto& pair : scored_goals1) {
        oStream << "scored_goals1_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "scored_goals1_score:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "scored_goals2_size:" << '\n';
    oStream << scored_goals2.size() << '\n';
    for (const auto& pair : scored_goals2) {
        oStream << "scored_goals2_name:" << '\n';
        oStream << pair.first << '\n';
        oStream << "scored_goals2_score:" << '\n';
        oStream << pair.second << '\n';
    }
    oStream << "substitutions1_size:" << '\n';
    oStream << substitutions1.size() << '\n';
    for (const auto& tuple : substitutions1) {
        oStream << "substitutions1_in:" << '\n';
        oStream << std::get<0>(tuple) << '\n';
        oStream << "substitutions1_out:" << '\n';
        oStream << std::get<1>(tuple) << '\n';
        oStream << "substitutions1_time:" << '\n';
        oStream << std::get<2>(tuple) << '\n';
    }
    oStream << "substitutions2_size:" << '\n';
    oStream << substitutions2.size() << '\n';
    for (const auto& tuple : substitutions2) {
        oStream << "substitutions2_in:" << '\n';
        oStream << std::get<0>(tuple) << '\n';
        oStream << "substitutions2_out:" << '\n';
        oStream << std::get<1>(tuple) << '\n';
        oStream << "substitutions2_time:" << '\n';
        oStream << std::get<2>(tuple) << '\n';
    }

    ofs << oStream.str();
    ofs.close();
}