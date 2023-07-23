/*
 * InfoJogoFutebol.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#include "InfoJogoFutebol.h"

using namespace std;

//veja o documento InfoJogoBasquetebol as permissas são parecidas, apenas as validações mudam.
InfoJogoFutebol::InfoJogoFutebol() : InfoJogo(11,7) {}

InfoJogoFutebol::~InfoJogoFutebol(){}

ErrorHandling InfoJogoFutebol::add_results(int result1, int result2){
    if (result1 < 0 || result2 < 0) {
        return ErrorHandling::INVALID_RESULT_MINOR;
    }

    set_result1(result1);
    set_result2(result2);

     return ErrorHandling::OK;
}

ErrorHandling InfoJogoFutebol::add_player(string name, string position, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

    if (!iequals(position, "guarda-redes") && !iequals(position, "defesa") && !iequals(position,"medio") && !iequals(position,"avancado")) {
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

ErrorHandling InfoJogoFutebol::add_substitute_player(string name, string position, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }
    if (!iequals(position, "guarda-redes") && !iequals(position, "defesa") && !iequals(position,"medio") && !iequals(position,"avancado")) {
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

ErrorHandling InfoJogoFutebol::make_substitution(string substituted, string substitute, int time, string team) {
    
   
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
        
        if(has_substitution1(substitute)){

            return ErrorHandling::SUBSTITUTE_WAS_ALREADY_IN_GAME;

        }else{

             remove_player1(substituted);
             remove_substitute_player1(substitute);
             add_player1(substitute, position_substitute);
             add_substitute_player1(substituted, position_substituted);
             add_substitution1(substituted, substitute, time);
        }
        
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

        if(has_substitution2(substitute)){

            return ErrorHandling::SUBSTITUTE_WAS_ALREADY_IN_GAME;

        }else{

             remove_player2(substituted);
             remove_substitute_player2(substitute);
             add_player2(substitute, position_substitute);
             add_substitute_player2(substituted, position_substituted);
             add_substitution2(substituted, substitute, time);
        }

    }
    return ErrorHandling::OK;
}

ErrorHandling InfoJogoFutebol::expel_player(string name, int time, string team){
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

        if (!has_player1(name)) {
            return ErrorHandling::EXPELLED_PLAYER_NOT_FOUND;
        }

        remove_player1(name);
        add_substitution1(name, "#", time);
        int players_match = get_max_players1();
        players_match -= 1;
        set_max_players1(players_match);
 
    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

         if (!has_player2(name)) {
            return ErrorHandling::EXPELLED_PLAYER_NOT_FOUND;
        }

        remove_player2(name);
        add_substitution2(name, "#", time);
        int players_match = get_max_players2();
        players_match -= 1;
        set_max_players2(players_match);
    }
    return ErrorHandling::OK;
}

ErrorHandling InfoJogoFutebol::file_register_substitution(string substituted, string substitute, int time, string team) {
    
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }
    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }
             add_substitution1(substituted, substitute, time);

    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }
        
        add_substitution2(substituted, substitute, time);


    }
    return ErrorHandling::OK;
}

ErrorHandling InfoJogoFutebol::add_scored_goal(string name, int time, string team) {
    if (team != get_name1() && team != get_name2()) {
        return ErrorHandling::TEAM_NOT_FOUND;
    }

     if (time < 0) {
        return ErrorHandling::NO_VALID_TIME;
    }


    if (team == get_name1()) {

        if (get_players1().size() < get_max_players1()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

        if (!has_player1(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = 1;
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        for (auto& scored_regiter1 : scored_regiters1) {

            if(name != "#"){
                total_score += 1;
            }
        }

        for (auto& scored_regiter2 : scored_regiters2) {

            if(name == "#"){
                total_score += 1;
            }
        }

        if(total_score > get_result1()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{
                add_scored_goal1(name, time);
        }
       
        
    } else {

        if (get_players2().size() < get_max_players2()) {
            return ErrorHandling::NOT_PLAYERS_ON_MATCH;
        }

       if (!has_player2(name)) {
            return ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH;
        }

        int total_score = 1;
        list<pair<string, int>> scored_regiters2 = get_scored_goals2();
        list<pair<string, int>> scored_regiters1 = get_scored_goals1();
        for (auto& scored_regiter2 : scored_regiters2) {
            if(name != "#"){
                total_score += 1;
            }
        }

        for (auto& scored_regiter1 : scored_regiters1) {

            if(name == "#"){
                total_score += 1;
            }
        }

        if(total_score > get_result2()){

            return ErrorHandling::MORE_POINTS_THEN_RESULT;

        }else{
                add_scored_goal2(name, time);

        }

    }
    return ErrorHandling::OK;
}

ErrorHandling InfoJogoFutebol::load_game(string filename) {
    ifstream ifs(filename);
    string line;
    string element1;
    string element2;
    string element3;
    string team1;
    string team2;
    int team1_goals=0;
    int team2_goals=0;
    int team1_expell = 11;
    int team2_expell = 11;

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
                        team2_goals = team2_goals + 1;
                    }else{
                        team1_goals = team1_goals + 1;
                    }
                    ErrorHandling set_element = add_scored_goal(element1, stoi(element2), team1);
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
                        team1_goals = team1_goals + 1;
                    }else{
                        team2_goals = team2_goals + 1;
                    }
                    ErrorHandling set_element = add_scored_goal(element1, stoi(element2), team2);
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
                    if(element2=="#"){team1_expell -=1;}
                    ErrorHandling set_element = file_register_substitution(element1, element2, stoi(element3), team1);
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
                    getline(ifs, element2);
                } else if (line == "substitutions2_time:") {
                    getline(ifs, element3);
                    if(element2=="#"){team2_expell -=1;}
                    ErrorHandling set_element = file_register_substitution(element1, element2, stoi(element3), team2);
                    if(set_element != ErrorHandling::OK){return set_element;}
                }
            }
        }
    }

    ifs.close();

    if(team1_goals != get_result1() || team2_goals != get_result2()){
        return ErrorHandling::RESULT_DIFFERENT_GOALS;
    }

    if(team1_expell != get_max_players1() || team2_expell != get_max_players2()){
        return ErrorHandling::EXPULSION_NOT_MACH;
    }

    return ErrorHandling::OK;
}