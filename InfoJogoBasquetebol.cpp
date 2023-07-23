/*
 * InfoJogoBasquetebol.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#include "InfoJogoBasquetebol.h"
#include <iostream>

using namespace std;

InfoJogoBasquetebol::InfoJogoBasquetebol() : InfoJogo(5,7) {}

InfoJogoBasquetebol::~InfoJogoBasquetebol(){}

//este método pega no tempo já existente e o novo tempo jogado e soma-os
//lembre que eles estão em formato string guardados na nossa lista e introduzidos pelo utilizador
string InfoJogoBasquetebol::add_time(string time1, string time2) {
    char sep1 = time1.find(':') != string::npos ? ':' : (time1.find('.') != string::npos ? '.' : ' ');
    char sep2 = time2.find(':') != string::npos ? ':' : (time2.find('.') != string::npos ? '.' : ' ');
    if(sep1 == ' ' && sep2 == ' '){
        return "ERROR";
    }
    int min1 = -1, sec1 = -1, min2 = -1, sec2 = -1;
    try {
        min1 = stoi(time1.substr(0, time1.find(sep1)));
        sec1 = stoi(time1.substr(time1.find(sep1) + 1));
        min2 = stoi(time2.substr(0, time2.find(sep2)));
        sec2 = stoi(time2.substr(time2.find(sep2) + 1));
    } catch (invalid_argument) {
        return "ERROR";
    }
    if (min1 < 0 || min1 > 59 || sec1 < 0 || sec1 > 59 || min2 < 0 || min2 > 59 || sec2 < 0 || sec2 > 59) {
        return "ERROR";
    }

    int total_sec = sec1 + sec2 + (min1 + min2) * 60;
    int total_min = total_sec / 60;
    total_sec %= 60;
    return to_string(total_min) + ":" + to_string(total_sec);
}

//repare que a adição dos resultados vaz a validação de empate e reultado maior que 0
ErrorHandling InfoJogoBasquetebol::add_results(int result1, int result2){
    
    if (result1 < 0 || result2 < 0) {
        return ErrorHandling::INVALID_RESULT_MINOR;
    }

    if (result1 == result2) {
        return ErrorHandling::IVALID_RESULT_TIE;
    }

    set_result1(result1);
    set_result2(result2);

    return ErrorHandling::OK;

}

//aidionar uum jogador faz uma serie de verificações, desde ao jogador já existir, se a posção é uma posição valida e a que equipa
ErrorHandling InfoJogoBasquetebol::add_player(string name, string position, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

    if (!iequals(position, "base") && !iequals(position, "extremo") && !iequals(position,"poste")) {
        return ErrorHandling::INVALID_POSITION;
    }
    if (team == get_name1()) {
        if (has_player1(name)) {
            return ErrorHandling::PLAYER_ALREADY_EXISTS;
        }
        if (get_players1().size() >= get_max_players1()) {
            return ErrorHandling::MAX_PLAYERS_REACHED;
        }
        add_player1(name, position);
    } else {
        if (has_player2(name)) {
            return ErrorHandling::PLAYER_ALREADY_EXISTS;
        }
        if (get_players2().size() >= get_max_players2()) {
            return ErrorHandling::MAX_PLAYERS_REACHED;
        }
        add_player2(name, position);
    }
    return ErrorHandling::OK;
}


ErrorHandling InfoJogoBasquetebol::add_substitute_player(string name, string position, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }
    if (!iequals(position, "base") && !iequals(position, "extremo") && !iequals(position,"poste")) {
        return ErrorHandling::INVALID_POSITION;
    }
    if (team == get_name1()) {
        if (has_substitute_player1(name)) {
            return ErrorHandling::PLAYER_ALREADY_EXISTS;
        }
        if (get_substitute_players1().size() >= get_max_substitute_players()) {
            return ErrorHandling::MAX_SUBSTITUTE_PLAYERS_REACHED;
        }
        add_substitute_player1(name, position);
    } else {
        if (has_substitute_player2(name)) {
            return ErrorHandling::PLAYER_ALREADY_EXISTS;
        }
        if (get_substitute_players2().size() >= get_max_substitute_players()) {
            return ErrorHandling::MAX_SUBSTITUTE_PLAYERS_REACHED;
        }
        add_substitute_player2(name, position);
    }
    return ErrorHandling::OK;
}

//a realização de substituição no basket tem a particularidade de ir registando o tempo total de jogo
//então existe ma série de verificações, se o jogador está em campo, se o jogador já tinha sido substituido e se sim somar o novo tempo jogado ao tempo já existente
//trocar o jogador da lista de suplente para o campo e vice versa
ErrorHandling InfoJogoBasquetebol::make_substitution(string substituted, string substitute, string time, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }
    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

        if (!has_player1(substituted)) {
            return ErrorHandling::SUBSTITUTED_PLAYER_NOT_FOUND;
        }
        if (!has_substitute_player1(substitute)) {
            return ErrorHandling::SUBSTITUTE_PLAYER_NOT_FOUND;
        }
        string position_substituted = "";
        string position_substitute = "";
        for (auto player : get_players1()) {
            if (player.first == substituted) {
                position_substituted = player.second;
            }
        }
        for (auto player : get_substitute_players1()) {
            if (player.first == substitute) {
                position_substitute = player.second;
            }
        }
        
        string current_time_played;
        if(has_substitution1(substituted)){

            list<tuple<string, string, int>> substitutions = get_substitutions1();
            for (auto& substitution : substitutions) {
                if (get<0>(substitution) == substituted) {
                    current_time_played = get<1>(substitution);
                }
            }

            string new_time_played = add_time(current_time_played, time);
            if(new_time_played == "ERROR"){
                return ErrorHandling::NO_VALID_TIME;
            }
            remove_substitution1(substituted);
            add_substitution1(substituted, new_time_played, 0);

        }else{
            add_substitution1(substituted, time, 0);
        }

        remove_player1(substituted);
        remove_substitute_player1(substitute);
        add_player1(substitute, position_substitute);
        add_substitute_player1(substituted, position_substituted);
        
    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

        if (!has_player2(substituted)) {
            return ErrorHandling::SUBSTITUTED_PLAYER_NOT_FOUND;
        }
        if (!has_substitute_player2(substitute)) {
            return ErrorHandling::SUBSTITUTE_PLAYER_NOT_FOUND;
        }
        string position_substituted = "";
        string position_substitute = "";
        for (auto player : get_players2()) {
            if (player.first == substituted) {
                position_substituted = player.second;
            }
        }
        for (auto player : get_substitute_players2()) {
            if (player.first == substitute) {
                position_substitute = player.second;
            }
        }
        

        string current_time_played;
        if(has_substitution2(substituted)){

            list<tuple<string, string, int>> substitutions = get_substitutions2();
            for (auto& substitution : substitutions) {
                if (get<0>(substitution) == substituted) {
                    current_time_played = get<1>(substitution);
                }
            }

            string new_time_played = add_time(current_time_played, time);
            if(new_time_played == "ERROR"){
                return ErrorHandling::NO_VALID_TIME;
            }
            remove_substitution2(substituted);
            add_substitution2(substituted, new_time_played, 0);

        }else{
            add_substitution2(substituted, time, 0);
        }

        remove_player2(substituted);
        remove_substitute_player2(substitute);
        add_player2(substitute, position_substitute);
        add_substitute_player2(substituted, position_substituted);

    }
    return ErrorHandling::OK;
}

//este métod apenas regista a substituição
ErrorHandling InfoJogoBasquetebol::file_register_substitution(string name, string time, string team){
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }
    if (team == get_name1()) {

        if ( !has_player1(name) && !has_substitute_player1(name)) {
            return ErrorHandling::SUBSTITUTED_PLAYER_NOT_FOUND;
        }

        add_substitution1(name, time, 0);
        
        
    } else {

        if ( !has_player2(name) && !has_substitute_player2(name)) {
            return ErrorHandling::SUBSTITUTED_PLAYER_NOT_FOUND;
        }

        add_substitution2(name, time, 0);

    }
    return ErrorHandling::OK;
}

//este método regista os pontos, também faz uma série de verificações, se o jogador está em campo, se já tem registo, pois no basket os pontos são somados na lista
//ainda verifica se os pontos recebidos são 1,2 ou 3
//repare que na leitura de registos em ficheiro (ficha de jogo) a verificação de 1,2,3 não é valida pois o ficheiro já é uma base consolidada, 
//daí termos métodos específicos para os ficheuiros
ErrorHandling InfoJogoBasquetebol::add_scored_goal(string name, int points, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

    if(points != 1 || points != 2 || points != 3){
        return ErrorHandling::BASKETPOINTS_NOT_GOOD;
    }

    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }
        if (!has_player1(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = points;
        int player_points = 0;
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        for (auto& scored_regiter1 : scored_regiters1) {

            if(name != "#"){
                total_score += get<1>(scored_regiter1);
            }
            
            if(get<0>(scored_regiter1) == name){
                player_points = get<1>(scored_regiter1);
            }
        }

        for (auto& scored_regiter2 : scored_regiters2) {

            if(name == "#"){
                total_score += get<1>(scored_regiter2);
            }
        }

        if(total_score > get_result1()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{

            if(player_points > 0){
                int new_poits = player_points+points;

                remove_scored_goal1(name);
                add_scored_goal1(name, new_poits);

            }else{

                add_scored_goal1(name, points);
            }

        }
       
        
    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

       if (!has_player2(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = points;
        int player_points = 0;
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        for (auto& scored_regiter2 : scored_regiters2) {
            if(name != "#"){
                total_score += get<1>(scored_regiter2);
            }
            if(get<0>(scored_regiter2) == name){
                player_points = get<1>(scored_regiter2);
            }
        }

        for (auto& scored_regiter1 : scored_regiters1) {

            if(name == "#"){
                total_score += get<1>(scored_regiter1);
            }
        }

        if(total_score > get_result2()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{

            if(player_points > 0){
                int new_poits = player_points+points;

                remove_scored_goal2(name);
                add_scored_goal2(name, new_poits);

            }else{

                add_scored_goal2(name, points);
            }

        }

    }
    return ErrorHandling::OK;
}

//aqui é o método especifico de ficheiro
ErrorHandling InfoJogoBasquetebol::add_scored_goal_file(string name, int points, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }
        if (!has_player1(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = points;
        int player_points = 0;
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        for (auto& scored_regiter1 : scored_regiters1) {

            if(name != "#"){
                total_score += get<1>(scored_regiter1);
            }
            
            if(get<0>(scored_regiter1) == name){
                player_points = get<1>(scored_regiter1);
            }
        }

        for (auto& scored_regiter2 : scored_regiters2) {

            if(name == "#"){
                total_score += get<1>(scored_regiter2);
            }
        }

        if(total_score > get_result1()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{

            if(player_points > 0){
                int new_poits = player_points+points;

                remove_scored_goal1(name);
                add_scored_goal1(name, new_poits);

            }else{

                add_scored_goal1(name, points);
            }

        }
       
        
    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

       if (!has_player2(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = points;
        int player_points = 0;
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        for (auto& scored_regiter2 : scored_regiters2) {
            if(name != "#"){
                total_score += get<1>(scored_regiter2);
            }
            if(get<0>(scored_regiter2) == name){
                player_points = get<1>(scored_regiter2);
            }
        }

        for (auto& scored_regiter1 : scored_regiters1) {

            if(name == "#"){
                total_score += get<1>(scored_regiter1);
            }
        }

        if(total_score > get_result2()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{

            if(player_points > 0){
                int new_poits = player_points+points;

                remove_scored_goal2(name);
                add_scored_goal2(name, new_poits);

            }else{

                add_scored_goal2(name, points);
            }

        }

    }
    return ErrorHandling::OK;
}

//este métod carrega um jogo de basket
//repare que ele usa os métods específicos da class para validar os dados introduzidos
ErrorHandling InfoJogoBasquetebol::load_game(string filename) {
    ifstream ifs(filename);
    string line;
    string element1;
    string element2;
    string element3;
    string team1;
    string team2;
    int team1_goals=0;
    int team2_goals=0;

    while (getline(ifs, line)) {
        if (line == "name1:") {
            getline(ifs, team1);
        } else if (line == "name2:") {
            getline(ifs, team2);
            ErrorHandling set_element = add_teams(team1, team2);
            if(set_element != ErrorHandling::OK){return set_element;}
        } else if (line == "result1:") {
            getline(ifs, element1);
        } else if (line == "result2:") {
            getline(ifs, element2);
            ErrorHandling set_element = add_results(stoi(element1), stoi(element2));
            if(set_element != ErrorHandling::OK){return set_element;}
        } else if (line == "max_players1:") {
            getline(ifs, element1);
            ErrorHandling set_element = set_max_players1(stoi(element1));
            if(set_element != ErrorHandling::OK){return set_element;}
        } else if (line == "max_players2:") {
            getline(ifs, element1);
            ErrorHandling set_element = set_max_players2(stoi(element1));
            if(set_element != ErrorHandling::OK){return set_element;}
        } else if (line == "max_substitute_players:") {
            getline(ifs, element1);
            ErrorHandling set_element = set_max_substitute_players(stoi(element1));
            if(set_element != ErrorHandling::OK){return set_element;}
        } else if (line == "players1_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "players1_name:") {
                    getline(ifs, element1);
                } else if (line == "players1_position:") {
                    getline(ifs, element2);
                    ErrorHandling set_element = add_player(element1, element2, team1);
                    if(set_element != ErrorHandling::OK){return set_element;}
                } 
            }
        } else if (line == "players2_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "players2_name:") {
                    getline(ifs, element1);
                } else if (line == "players2_position:") {
                    getline(ifs, element2);
                    ErrorHandling set_element = add_player(element1, element2, team2);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "substitute_players1_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "substitute_players1_name:") {
                    getline(ifs, element1);
                } else if (line == "substitute_players1_position:") {
                    getline(ifs, element2);
                    ErrorHandling set_element = add_substitute_player(element1, element2, team1);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "substitute_players2_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "substitute_players2_name:") {
                    getline(ifs, element1);
                } else if (line == "substitute_players2_position:") {
                    getline(ifs, element2);
                    ErrorHandling set_element = add_substitute_player(element1, element2, team2);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "scored_goals1_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "scored_goals1_name:") {
                    getline(ifs, element1);
                } else if (line == "scored_goals1_score:") {
                    getline(ifs, element2);
                    if(element1 == "#"){
                        team2_goals = team2_goals + stoi(element2);
                    }else{
                        team1_goals = team1_goals + stoi(element2);
                    }
                    ErrorHandling set_element = add_scored_goal_file(element1, stoi(element2), team1);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "scored_goals2_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*2; ++i) {
                getline(ifs, line);
                if (line == "scored_goals2_name:") {
                    getline(ifs, element1);
                } else if (line == "scored_goals2_score:") {
                    getline(ifs, element2);
                    if(element1 == "#"){
                        team1_goals = team1_goals + stoi(element2);
                    }else{
                        team2_goals = team2_goals + stoi(element2);
                    }
                    ErrorHandling set_element = add_scored_goal_file(element1, stoi(element2), team2);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "substitutions1_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*3; ++i) {
                getline(ifs, line);
                if (line == "substitutions1_in:") {
                    getline(ifs, element1);
                } else if (line == "substitutions1_out:") {
                    getline(ifs, element2);
                } else if (line == "substitutions1_time:") {
                    getline(ifs, element3);
                    ErrorHandling set_element = file_register_substitution(element1, element2, team1);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        } else if (line == "substitutions2_size:") {
            string size;
            getline(ifs, size);
            int s = stoi(size);
            for (int i = 0; i < s*3; ++i) {
                getline(ifs, line);
                if (line == "substitutions2_in:") {
                    getline(ifs, element1);
                } else if (line == "substitutions2_out:") {
                    std::getline(ifs, element2);
                } else if (line == "substitutions2_time:") {
                    std::getline(ifs, element3);
                    ErrorHandling set_element = file_register_substitution(element1, element2, team2);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        }
    }

    ifs.close();

    if(team1_goals != get_result1() || team2_goals != get_result2()){
        return ErrorHandling::RESULT_DIFFERENT_GOALS;
    }

    return ErrorHandling::OK;
}