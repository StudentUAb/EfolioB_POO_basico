/*
 * ErrorHandling.h
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

#ifndef ERRORHANDLING_H_
#define ERRORHANDLING_H_

using namespace std;

//Uma classe de enumercao para usar para definicao de erros do programa durante as verificacoes de variaveis nos metodos das classes e no programa em geral

enum class ErrorHandling {
    OK,
    TEAM_NOT_FOUND,
    INVALID_POSITION,
    PLAYER_ALREADY_EXISTS,
    MAX_PLAYERS_REACHED,
    MAX_SUBSTITUTE_PLAYERS_REACHED,
    SUBSTITUTED_PLAYER_NOT_FOUND,
    SUBSTITUTE_PLAYER_NOT_FOUND,
    INVALID_TEAM_NAME,
    INVALID_RESULT_MINOR,
    IVALID_RESULT_TIE,
    MATCHING_TEAM_NAMES,
    SUBSTITUTE_WAS_ALREADY_IN_GAME,
    EXPELLED_PLAYER_NOT_FOUND,
    PLAYER_NOT_FOUND_IN_MATCH,
    BASKETPOINTS_NOT_GOOD,
    MORE_POINTS_THEN_RESULT,
    NOT_PLAYERS_ON_MATCH,
    FILE_ELEMENTS_ERROR,
    RESULT_DIFFERENT_GOALS,
    INVALID_PLAYER_NUMBERS,
    NO_VALID_TIME,
    EXPULSION_NOT_MACH
};

#endif /* ERRORHANDLING_H_ */