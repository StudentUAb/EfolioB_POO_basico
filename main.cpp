/*
 * main.cpp
 *
 *      Author: Rúdi Gualter
 *
 * 
 */

//O programa tem como base apenas os requesitos levantados no enunciado, 
//não explorando nada mais além do que é pedido

#include <iostream>
#include "UserInterface.h"

using namespace std;

int main()
{   
    cout << "#################################################################" << endl;
    cout << "#########  Bem Vindo ao Sistema de Informacao de Jogos ##########" << endl;
    cout << "#################################################################" << endl;
    
    UserInterface show;
    
    show.run();

    return 0;
}
