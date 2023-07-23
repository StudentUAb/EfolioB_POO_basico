/*
 * UserInterface.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#include "UserInterface.h"

using namespace std;

UserInterface::UserInterface(){}
UserInterface::~UserInterface(){}

//para facilitar para limpar o buffer de entrada quando recolhemos um cin normal para não gerar entradas indezejadas
void UserInterface::clear_cin(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Tranformação das mensagens de erro em texto para o utilziador
string UserInterface::error_messages(ErrorHandling type_error){

    switch (type_error) {
            case ErrorHandling::OK:
                return "Sucesso!";
            case ErrorHandling::TEAM_NOT_FOUND:
                return "Equipa nao encontrada!";
            case ErrorHandling::INVALID_POSITION:
                return "A posicao escolhida e invalida!";
            case ErrorHandling::PLAYER_ALREADY_EXISTS:
                return "O jogador ja existe!";
            case ErrorHandling::MAX_PLAYERS_REACHED:
                return "Atingiu o numero maximo de jogadores em campo!";
            case ErrorHandling::MAX_SUBSTITUTE_PLAYERS_REACHED:
                return "Atingiu o numero maximo de jogadores nos substitutos!";
            case ErrorHandling::SUBSTITUTED_PLAYER_NOT_FOUND:
                return "Jogador a substituir nao encontrado em campo!";
            case ErrorHandling::SUBSTITUTE_PLAYER_NOT_FOUND:
                return "Jogador a substituto nao encontrado nos suplentes!";
            case ErrorHandling::INVALID_TEAM_NAME:
                return "Nome de equipa invalido!";
            case ErrorHandling::INVALID_RESULT_MINOR:
                return "Resultado invalido, é menor que zero!";
            case ErrorHandling::IVALID_RESULT_TIE:
                return "Resultado invalido, colocou empate e nao e valido para este tipo de jogo!";
            case ErrorHandling::MATCHING_TEAM_NAMES:
                return "Os nomes das equipas estao iguais!";
            case ErrorHandling::SUBSTITUTE_WAS_ALREADY_IN_GAME:
                return "O suplente selecionado ja esteve em jogo!";
            case ErrorHandling::EXPELLED_PLAYER_NOT_FOUND:
                return "Jogardor a expulsar nao encontrado!";
            case ErrorHandling::PLAYER_NOT_FOUND_IN_MATCH:
                return "O Jogador nao esta em jogo!";
            case ErrorHandling::BASKETPOINTS_NOT_GOOD:
                return "Os pontos estão incorretos apenas sao aceites 1 , 2 ou 3 pontos!";
            case ErrorHandling::MORE_POINTS_THEN_RESULT:
                return "A sua insercao esta a gerar mais pontos que o resultado do jogo, altere o resultado primeiro!";
            case ErrorHandling::NOT_PLAYERS_ON_MATCH:
                return "Precisa de Jogadores em campo!";
            case ErrorHandling::FILE_ELEMENTS_ERROR:
                return "O seu ficheiro esta com elementos invalidos!";
            case ErrorHandling::RESULT_DIFFERENT_GOALS:
                return "Os golos/pontos da lista nao corresponde ao resultado do jogo!";
            case ErrorHandling::INVALID_PLAYER_NUMBERS:
                return "O numero de jogadores esta incorreto!";
            case ErrorHandling::NO_VALID_TIME:
                return "O tempo esta invalido!";
            case ErrorHandling::EXPULSION_NOT_MACH:
                return "O numero de jogadores em campo nao corresponde com as expulsoes efetuadas!";
            default:
                return "Erro Desconhecido!";
        }
}

//funão principal que roda o menu geral
void UserInterface::run() {

    ListaJogos game_list;

    while (true) {
        
        cout << endl << "############ MENU PRINCIPAL ##############" << endl;
        cout << endl << "1. Registar um novo jogo" << endl;
        cout << "2. Mostrar jogos" << endl;
        cout << "3. Mostrar Detalhes de jogo" << endl;
        cout << "4. Registar Novas Informacoes a um jogo existente" << endl;
        cout << "5. Carregar ficha de jogo" << endl;
        cout << "6. Salvar ficha de jogo" << endl;
        cout << "7. Sair" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                create_new_game(game_list);
                break;
            case 2:
                show_list_of_games(game_list);
                break;
            case 3:
                show_game_details(game_list);
                break;
            case 4:
                update_game_info(game_list);
                break;
            case 5:
                load_game_info_from_file(game_list);
                break;
            case 6:
                save_game_info(game_list);
                break;
            case 7:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }
}

void UserInterface::create_new_game(ListaJogos& game_list) {
    while (true) {
        cout << endl << "############ CRIAR JOGO ##############" << endl;
        cout << endl << "1. Criar Jogo de Futebol" << endl;
        cout << "2. Criar Jogo de Basquetebol" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                create_soccer_game(game_list);
                break;
            case 2:
                create_basketball_game(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }
}

void UserInterface::create_soccer_game(ListaJogos& game_list){

    string line1, line2;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;
    InfoJogoFutebol new_game;
    clear_cin();
    do{
		cout << endl << "Insira o nome da Equipa 1: ";
        getline(cin, line1);
        cout << endl << "Insira o nome da Equipa 2: ";
        getline(cin, line2);
        

        result = new_game.add_teams(line1, line2);

        if(result != ErrorHandling::OK){
            cout << endl << "Erro: " << error_messages(result);
            
        }

	}while(result != ErrorHandling::OK);

    cout << endl << "Equipas Adicionadas!";

    do{
        
		cout << endl << "Insira o resultado da Equipa " << new_game.get_name1() <<": ";
        getline(cin, number1);
        cout << endl << "Insira o resultado da Equipa " << new_game.get_name2() <<": ";
        getline(cin, number2);

        try{ 
            number11 = stoi(number1);
            number22 = stoi(number2);
            result = new_game.add_results(number11, number22);
        }catch(invalid_argument){
             cout << endl << "Erro: Não Inseriu numeros validos no resultado";
             result = ErrorHandling::FILE_ELEMENTS_ERROR;
             continue;
        }
       
        if(result != ErrorHandling::OK){
            cout << endl << "Erro: " << error_messages(result);
        }

	}while(result != ErrorHandling::OK);

    cout << endl << "Resultados Adicionados!";

     while (true) {
        cout << endl << "############ ADICIONAR DETALHES ##############" << endl;
        cout << endl << "1. Adicionat jogador em Campo" << endl;
        cout << "2. Adicionar Jogador Suplente" << endl;
        cout << "3. Registar Substituicao" << endl;
        cout << "4. Registar Expulsao" << endl;
        cout << "5. Registar Golo" << endl;
        cout << "6. Acabar Registo" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                register_new_match_player(new_game);
                break;
            case 2:
                register_new_sub_player(new_game);
                break;
            case 3:
                register_soccer_game_sub(new_game);
                break;
            case 4:
                register_soccer_game_exp(new_game);
                break;
            case 5:
                register_soccer_goals(new_game);
                break;
            case 6:
                game_list.add_soccer_game(new_game);
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }

}

void UserInterface::register_new_match_player(InfoJogoFutebol &game){
    clear_cin();
    string line1, line2, line3;
    int number1, number2;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja adicionar jogador (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador: ";
    getline(cin, line1);
    cout << endl << "Insira a posicao do jogador: ";
    getline(cin, line2);

    result = game.add_player(line1,line2, line3);

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Jogador Adicionado!";

}

void UserInterface::register_new_sub_player(InfoJogoFutebol &game){
    clear_cin();
    string line1, line2, line3;
    int number1, number2;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja adicionar jogador substituto (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador: ";
    getline(cin, line1);
    cout << endl << "Insira a posicao do jogador: ";
    getline(cin, line2);

    result = game.add_substitute_player(line1,line2, line3);

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Jogador Substituto Adicionado!";

}

void UserInterface::register_soccer_game_sub(InfoJogoFutebol &game){
    clear_cin();
    string line1, line2, line3;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja realizar a substitucao (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador a substituir: ";
    getline(cin, line1);
    cout << endl << "Insira o nome do jogador substituto: ";
    getline(cin, line2);
    cout << endl << "Insira a que minuto a substituicao ocorreu: ";
    getline(cin, number1);

    
    try{ 
        number11 = stoi(number1);
        result = game.make_substitution(line1,line2,number11,line3);
    }catch(invalid_argument){
        cout << endl << "Erro: Não Inseriu  minutos validos";
        return;
    }

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Substituicao Realizada!";

}

void UserInterface::register_soccer_game_exp(InfoJogoFutebol &game){
    clear_cin();
    string line1, line2, line3;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja realizar a expulsao (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador a expulsar: ";
    getline(cin, line1);
    cout << endl << "Insira a que minuto a expulsao ocorreu: ";
    getline(cin, number1);

    try{ 
        number11 = stoi(number1);
        result = game.expel_player(line1,number11,line3);
    }catch(invalid_argument){
        cout << endl << "Erro: Não Inseriu  minutos validos";
        return;
    }

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Expulsao Realizada!";

}

void UserInterface::register_soccer_goals(InfoJogoFutebol &game){
    clear_cin();
    string line1, line2, line3;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja realizar o registo (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador que marcou (Se autogolo insira # em vez do nome): ";
    getline(cin, line1);
    cout << endl << "Insira a que minuto que o golo ocorreu: ";
    getline(cin, number1);

    try{ 
        number11 = stoi(number1);
        result = game.add_scored_goal(line1,number11, line3);
    }catch(invalid_argument){
        cout << endl << "Erro: Não Inseriu  minutos validos";
        return;
    }

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Registado!";

}

void UserInterface::create_basketball_game(ListaJogos& game_list){

    string line1, line2;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;
    InfoJogoBasquetebol new_game;
    clear_cin();
    do{
		cout << endl << "Insira o nome da Equipa 1: ";
        getline(cin, line1);
        cout << endl << "Insira o nome da Equipa 2: ";
        getline(cin, line2);

        result = new_game.add_teams(line1, line2);

        if(result != ErrorHandling::OK){
            cout << endl << "Erro: " << error_messages(result);
        }

	}while(result != ErrorHandling::OK);

    cout << endl << "Equipas Adicionadas!";

    do{
		cout << endl << "Insira o resultado da Equipa " << new_game.get_name1() <<": ";
		getline(cin, number1);
        cout << endl << "Insira o resultado da Equipa " << new_game.get_name2() <<": ";
		getline(cin, number2);

        try{ 
            number11 = stoi(number1);
            number22 = stoi(number2);
            result = new_game.add_results(number11, number22);
        }catch(invalid_argument){
             cout << endl << "Erro: Não Inseriu numeros validos no resultado";
             result = ErrorHandling::FILE_ELEMENTS_ERROR;
             continue;
        }

        if(result != ErrorHandling::OK){
            cout << endl << "Erro: " << error_messages(result);
        }

	}while(result != ErrorHandling::OK);

    cout << endl << "Resultados Adicionados!";

     while (true) {
        cout << endl << "############ ADICIONAR DETALHES ##############" << endl;
        cout << endl << "1. Adicionat jogador em Campo" << endl;
        cout << "2. Adicionar Jogador Suplente" << endl;
        cout << "3. Registar Substituicao" << endl;
        cout << "4. Registar Pontos" << endl;
        cout << "5. Acabar Registo" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                register_new_match_b_player(new_game);
                break;
            case 2:
                register_new_sub_b_player(new_game);;
                break;
            case 3:
                register_basket_game_sub(new_game);
                break;
            case 4:
                register_basket_points(new_game);
                break;
            case 5:
                game_list.add_basketball_game(new_game);
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;

                break;
        }
    }
}

void UserInterface::register_new_match_b_player(InfoJogoBasquetebol &game){
    clear_cin();
    string line1, line2, line3;
    int number1, number2;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja adicionar jogador (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador: ";
    getline(cin, line1);
    cout << endl << "Insira a posicao do jogador: ";
    getline(cin, line2);

    result = game.add_player(line1,line2, line3);

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Jogador Adicionado!";

}

void UserInterface::register_new_sub_b_player(InfoJogoBasquetebol &game){
    clear_cin();
    string line1, line2, line3;
    int number1, number2;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja adicionar jogador substituto (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador: ";
    getline(cin, line1);
    cout << endl << "Insira a posicao do jogador: ";
    getline(cin, line2);

    result = game.add_substitute_player(line1,line2, line3);

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Jogador Substituto Adicionado!";

}

void UserInterface::register_basket_game_sub(InfoJogoBasquetebol &game){
    clear_cin();
    string line1, line2, line3, line4;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja realizar a substitucao (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador a substituir: ";
    getline(cin, line1);
    cout << endl << "Insira o nome do jogador substituto: ";
    getline(cin, line2);
    cout << endl << "Insira o tempo que o jogador jogou da forma (mm:ss): ";
    getline(cin, line4);

    result = game.make_substitution(line1,line2,line4,line3);

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }

    cout << endl << "Substituicao Realizada!";

}

void UserInterface::register_basket_points(InfoJogoBasquetebol &game){
    clear_cin();
    string line1, line2, line3;
    string number1, number2;
    int number11, number22;
    ErrorHandling result;

    cout << endl << "Insira o nome da Equipa que deseja realizar o registo (" << game.get_name1() << " ou " << game.get_name2() <<"): ";
    getline(cin, line3);
    cout << endl << "Insira o nome do jogador que marcou (Se auto-cesto insira # em vez do nome): ";
    getline(cin, line1);
    cout << endl << "Insira quantos pontos(1,2,3): ";
    getline(cin, number1);

    try{ 
        number11 = stoi(number1);
        result = game.add_scored_goal(line1,number11, line3);
    }catch(invalid_argument){
        cout << endl << "Erro: Não Inseriu  pontos validos";
        return;
    }

    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
        return;
    }


    cout << endl << "Registado!";

}

void UserInterface::show_list_of_games(ListaJogos& game_list){

     while (true) {
        cout << endl << "############ MOSTRAR JOGOS ##############" << endl;
        cout << endl << "1. Mostrar Jogos Futebol" << endl;
        cout << "2. Mostrar Jogos de Basquetebol" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                show_soccer_games(game_list);
                break;
            case 2:
                show_basketball_games(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }
}

void UserInterface::show_soccer_games(ListaJogos& game_list){

    int id = 0;
    list<InfoJogoFutebol> soccer_games = game_list.get_soccer_games();
    if(soccer_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
         return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoFutebol game : soccer_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

}

void UserInterface::show_basketball_games(ListaJogos& game_list){

    int id = 0;
    list<InfoJogoBasquetebol> basketball_games = game_list.get_basketball_games();
    if(basketball_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
         return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoBasquetebol game : basketball_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

}

void UserInterface::show_game_details(ListaJogos& game_list){
    
    while (true) {
        cout << endl << "############ MOSTRAR DETALHES DE JOGOS ##############" << endl;
        cout << endl << "1. Detalhes de Jogo de Futebol" << endl;
        cout << "2. Detalhes de Jogo de Basquetebol" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                show_details_soccer_game(game_list);
                break;
            case 2:
                show_details_basketball_game(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }
}

void UserInterface::show_details_soccer_game(ListaJogos& game_list){

    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoFutebol> soccer_games = game_list.get_soccer_games();
    if(soccer_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
        return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoFutebol game : soccer_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

    do{
		cout << endl << "Escolha o jogo a Apresentar: ";
		getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }

        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu uk numero";
        }

        

	}while(number11 < 0 || number11 > id-1);

    InfoJogoFutebol& game = game_list.get_soccer_game(number11);

    cout  << endl << "Equipa 1: " << game.get_name1() << endl;
    cout  << "Equipa 2: " << game.get_name2() << endl;
    cout  << "Resultado: " << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;

   list<pair<string, string>> team1_players = game.get_players1();
   list<pair<string, string>> team2_players = game.get_players2();

   list<pair<string, string>> team1_sub_players =  game.get_substitute_players1();
   list<pair<string, string>> team2_sub_players =  game.get_substitute_players2();

   list<pair<string, int>> team1_scored_goals = game.get_scored_goals1();
   list<pair<string, int>> team2_scored_goals = game.get_scored_goals2();
   list<tuple<string, string, int>> team1_substitutions = game.get_substitutions1();
   list<tuple<string, string, int>> team2_substitutions = game.get_substitutions2();

    cout  << endl << game.get_name1() << " - Jogadores em Campo" << endl;
    cout << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team1_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team1_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Jogadores em Campo" << endl;
    cout  << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team2_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team2_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() << " - Jogadores Suplentes" << endl;
    cout << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team1_sub_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team1_sub_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Jogadores Suplentes" << endl;
    cout  << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team2_sub_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team2_sub_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() <<  " - Registo Golos" << endl;
    cout << setw(20) << left << "Jogador" << setw(20) << left << "Tempo" << endl;
    if(team1_scored_goals.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto p : team1_scored_goals) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Registo Golos" << endl;
    cout  << setw(20) << left << "Jogador" << setw(20) << left << "Tempo" << endl;
    if(team2_scored_goals.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto p : team2_scored_goals) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() << " - Registo de Substituicoes" << endl;
    cout << setw(20) << left << "Sustituido" << setw(20) << left << "Substituto" << setw(20) << left << "Tempo" << endl;
    if(team1_substitutions.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto s : team1_substitutions) {
            cout << setw(20) << left << get<0>(s) << setw(20) << left << get<1>(s) << setw(20) << left <<  get<2>(s) << endl;

        }

    }

    cout  << endl << game.get_name2() << " - Registo de Substituicoes" << endl;
    cout << setw(20) << left << "Sustituido" << setw(20) << left << "Substituto" << setw(20) << left << "Tempo" << endl;
    if(team2_substitutions.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto s : team2_substitutions) {
            cout << setw(20) << left << get<0>(s) << setw(20) << left << get<1>(s) << setw(20) << left <<  get<2>(s) << endl;

        }

    }


}

void UserInterface::show_details_basketball_game(ListaJogos& game_list){

    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoBasquetebol> basketball_games = game_list.get_basketball_games();
    if(basketball_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
         return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoBasquetebol game : basketball_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

     do{
		cout << endl << "Escolha o jogo a Apresentar: ";
		getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }
            
        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu uk numero";
        }

	}while(number11 < 0 || number11 > id-1);

    InfoJogoBasquetebol& game = game_list.get_basketball_game(number11);

    cout  << endl << "Equipa 1: " << game.get_name1() << endl;
    cout  << "Equipa 2: " << game.get_name2() << endl;
    cout  << "Resultado: " << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;

    list<pair<string, string>> team1_players = game.get_players1();
    list<pair<string, string>> team2_players = game.get_players2();

    list<pair<string, string>> team1_sub_players =  game.get_substitute_players1();
    list<pair<string, string>> team2_sub_players =  game.get_substitute_players2();

    list<pair<string, int>> team1_scored_goals = game.get_scored_goals1();
    list<pair<string, int>> team2_scored_goals = game.get_scored_goals2();
    list<tuple<string, string, int>> team1_substitutions = game.get_substitutions1();
    list<tuple<string, string, int>> team2_substitutions = game.get_substitutions2();

    cout  << endl << game.get_name1() << " - Jogadores em Campo" << endl;
    cout << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team1_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team1_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Jogadores em Campo" << endl;
    cout  << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team2_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team2_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() << " - Jogadores Suplentes" << endl;
    cout << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team1_sub_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team1_sub_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Jogadores Suplentes" << endl;
    cout  << setw(20) << left << "Nome" << setw(20) << left << "Posicao" << endl;
    if(team2_sub_players.empty()){ cout  << endl << "Sem Jogadores na Lista." << endl;}else{

        for (auto p : team2_sub_players) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() << " - Registo Pontos" << endl;
    cout << setw(20) << left << "Jogador" << setw(20) << left << "Pontos" << endl;
    if(team1_scored_goals.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto p : team1_scored_goals) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name2() << " - Registo Pontos" << endl;
    cout  << setw(20) << left << "Jogador" << setw(20) << left << "Pontos" << endl;
    if(team2_scored_goals.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto p : team2_scored_goals) {
            cout << setw(20) << left << p.first << setw(20) << left << p.second << endl;
        }

    }

    cout  << endl << game.get_name1() << " - Registo de Substituicoes" << endl;
    cout << setw(20) << left << "Jogador" << setw(20) << left << "Tempo Jogado" << endl;
    if(team1_substitutions.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto s : team1_substitutions) {
            cout << setw(20) << left << get<0>(s) << setw(20) << left << get<1>(s) << endl;

        }

    }

    cout  << endl << game.get_name2() << " - Registo de Substituicoes" << endl;
    cout << setw(20) << left << "Jogador" << setw(20) << left << "Tempo Jogado" << endl;
    if(team2_substitutions.empty()){ cout  << endl << "Sem Registos Lista." << endl;}else{

        for (auto s : team2_substitutions) {
            cout << setw(20) << left << get<0>(s) << setw(20) << left << get<1>(s) << setw(20) << endl;

        }

    }

}

void UserInterface::update_game_info(ListaJogos& game_list){

    while (true) {
        cout << endl << "############ ATUALIZAR JOGOS ##############" << endl;
        cout << endl << "1. Atualizar Jogo de Futebol" << endl;
        cout << "2. Atualizar Jogo de Basquete" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                update_soccer_game(game_list);
                break;
            case 2:
                update_basketball_game(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }

}

void UserInterface::update_soccer_game(ListaJogos& game_list){

    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoFutebol> soccer_games = game_list.get_soccer_games();
    if(soccer_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
        return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoFutebol game : soccer_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

    do{
		cout << endl << "Escolha o jogo a Atualizar: ";
		getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }
            
        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu uk numero";
        }

	}while(number11 < 0 || number11 > id-1);

    InfoJogoFutebol& change_game = game_list.get_soccer_game(number11);

    while (true) {
        cout << endl << "############ DETALHES A ATUALIZAR ##############" << endl;
        cout << endl << "1. Adicionat jogador em Campo" << endl;
        cout << "2. Adicionar Jogador Suplente" << endl;
        cout << "3. Registar Substituicao" << endl;
        cout << "4. Registar Expulsao" << endl;
        cout << "5. Registar Golo" << endl;
        cout << "6. Acabar Atualizacao" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                register_new_match_player(change_game);
                break;
            case 2:
                register_new_sub_player(change_game);
                break;
            case 3:
                register_soccer_game_sub(change_game);
                break;
            case 4:
                register_soccer_game_exp(change_game);
                break;
            case 5:
                register_soccer_goals(change_game);
                break;
            case 6:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }


}

void UserInterface::update_basketball_game(ListaJogos& game_list){

    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoBasquetebol> basketball_games = game_list.get_basketball_games();
    if(basketball_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
         return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoBasquetebol game : basketball_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

     do{
		cout << endl << "Escolha o jogo a Atualizar: ";
		getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }
            
        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu uk numero";
        }

	}while(number11 < 0 || number11 > id-1);

    InfoJogoBasquetebol& change_game = game_list.get_basketball_game(number11);

    while (true) {
        cout << endl << "############ DETALHES A ATUALIZAR ##############" << endl;
        cout << endl << "1. Adicionar jogador em Campo" << endl;
        cout << "2. Adicionar Jogador Suplente" << endl;
        cout << "3. Registar Substituicao" << endl;
        cout << "4. Registar Pontos" << endl;
        cout << "5. Acabar Atualizacao" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                register_new_match_b_player(change_game);
                break;
            case 2:
                register_new_sub_b_player(change_game);
                break;
            case 3:
                register_basket_game_sub(change_game);
                break;
            case 4:
                register_basket_points(change_game);
                break;
            case 5:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }


}

void UserInterface::load_game_info_from_file(ListaJogos& game_list){
     
     while (true) {
        cout << endl << "############ CARREGAR FICHA DE JOGO ##############" << endl;
        cout << endl << "1. Adicionar Jogo de Futebol" << endl;
        cout << "2. Adicionar Jogo de Basquetebol" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                load_file_soccer(game_list);
                break;
            case 2:
                load_file_basket(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }

}

void UserInterface::load_file_soccer(ListaJogos& game_list){

     ErrorHandling result;
     string filename;
    clear_cin();
    cout << endl << "Informe o nome do arquivo da ficha de jogo: ";
    getline(cin, filename);
    InfoJogoFutebol new_game;
    result = new_game.load_game(filename);
    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
    }else{
        game_list.add_soccer_game(new_game);
        cout << endl << "Carregado com sucesso!" << endl;
    }
}

void UserInterface::load_file_basket(ListaJogos& game_list){

     ErrorHandling result;
     string filename;
    clear_cin();
    cout << endl << "Informe o nome do arquivo da ficha de jogo: ";
    getline(cin, filename);
    InfoJogoBasquetebol new_game;
    result = new_game.load_game(filename);
    if(result != ErrorHandling::OK){
        cout << endl << "Erro: " << error_messages(result);
    }else{
        game_list.add_basketball_game(new_game);
        cout << endl << "Carregado com sucesso!" << endl;
    }
}

void UserInterface::save_game_info(ListaJogos& game_list){
     while (true) {
        cout << endl << "############ SALVAR FICHA DE JOGO ##############" << endl;
        cout << endl << "1. Salvar Jogo de Futebol" << endl;
        cout << "2. Salvar Jogo de Basquete" << endl;
        cout << "3. Voltar para o menu anterior" << endl << endl;
        cout << "Por Favor selecione uma opcao: ";

        int selection;
        cin >> selection;

        switch (selection) {
            case 1:
                save_soccer_info(game_list);
                break;
            case 2:
                save_basket_info(game_list);
                break;
            case 3:
                return;
            default:
                cout << "Selecao Invalida. Tente de Novo." << endl << endl;
                break;
        }
    }
}

void UserInterface::save_soccer_info(ListaJogos& game_list){
    
    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoFutebol> soccer_games = game_list.get_soccer_games();
    if(soccer_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
        return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoFutebol game : soccer_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

    do{
		cout << endl << "Escolha o jogo a Salvar: ";
        getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }
            
        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu um numero";
        }

	}while(number11 < 0 || number11 > id-1);

    InfoJogoFutebol& change_game = game_list.get_soccer_game(number11);
    change_game.save_game();
    cout << endl << "Jogo Salvo";
}

void UserInterface::save_basket_info(ListaJogos& game_list){

    int id = 0;
    string number1;
    int number11 = -1;
    list<InfoJogoBasquetebol> basketball_games = game_list.get_basketball_games();
    if(basketball_games.empty()){
        cout  << endl << "Sem jogos na Lista." << endl;
         return;
    }
    cout << endl << setw(5) << left << "ID" << setw(20) << left << "Equipa 1" << setw(20) << left << "Equipa 2" << setw(10) << left << "Resultado" << endl;
    for (InfoJogoBasquetebol game : basketball_games) {
        cout << setw(5) << left << id << setw(20) << left << game.get_name1() << setw(20) << left << game.get_name2() << setw(10) << left << to_string(game.get_result1()) + ":" + to_string(game.get_result2()) << endl;
        id ++;
    }

     do{
		cout << endl << "Escolha o jogo a Atualizar: ";
        getline(cin, number1);

        try{ 
            number11 = stoi(number1);

            if(number11 < 0 || number11 > id-1){
            cout << endl << "Erro: Id de jogo nao e valido";
            }
            
        }catch(invalid_argument){
            number11= -1;
            cout << endl << "Erro: Não Inseriu um numero";
        }

	}while(number11 < 0 || number11 > id-1);

    InfoJogoBasquetebol& change_game = game_list.get_basketball_game(number11);
    change_game.save_game();
    cout << endl << "Jogo Salvo";
}