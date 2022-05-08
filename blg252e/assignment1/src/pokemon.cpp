//--- 2021-2022 Summer Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Özberk Hazantekin
//---Student Number: 150200100
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

//-------------You Can Add Your Functions Down Below-------------//

// pokemon functions

// Constructors

pokemon::pokemon(){
    name = "Default Pokemon";
    hpValue = 100;
    atkValue = 20;
}

pokemon::pokemon(string name, int atkValue){
    this->name = name;
    hpValue = 100;
    this->atkValue = atkValue;
}

pokemon::pokemon(const pokemon& copied_pokemon){
    name = copied_pokemon.name;
    hpValue = copied_pokemon.hpValue;
    atkValue = copied_pokemon.atkValue;
}

// Getters

string pokemon::getPokemonName(){
    return name;
}

int pokemon::getHpValue(){
    return hpValue;
}

int pokemon::getAttackValue(){
    return atkValue;
}

// pokedex functions

// Constructor that initializes value as 0, with value representing the amount of pokemons in the pokedex

pokedex::pokedex(){
    value = 0;
}

// Methods to update and print the pokedex

void pokedex::updatePokedex(pokemon new_pokemon){
    // Checking if there are any duplicates in the pokedexArray
    for (int i = 0; i < value; i++){
        if (pokedexArray[i].getPokemonName() == new_pokemon.getPokemonName()){
            return;
        }
    }
    pokedexArray[value] = new_pokemon;
    value++;
    return; 
}

void pokedex::printPokedex(){
    for(int i = 0; i < value; i++){
        cout << pokedexArray[i].getPokemonName() << endl;
    }
    return;
}

// player functions

// Constructors

player::player(){
    name = "Player 1";
    pokemonNumber = 0;
    pokeballNumber = 10;
    badgeNumber = 0;
    playerPokemon = pokemon();
    playerPokedex = pokedex();
}

player::player(string name, pokemon pokemon_object){
    this->name = name;
    pokemonNumber = 0;
    pokeballNumber = 10;
    badgeNumber = 0;
    playerPokemon = pokemon_object;
    playerPokedex = pokedex();
}

// Getters 

int player::showPokemonNumber(){
    return pokemonNumber;
}

int player::showPokeballNumber(){
    return pokeballNumber;
}

int player::showBadgeNumber(){
    return badgeNumber;
}

pokemon player::getPokemon(){
    return playerPokemon;
}

// Player methods for battles and catching

void player::battleWon(){
    badgeNumber += 1;
    pokeballNumber += 3;
}

void player::catchPokemon(){
    pokemonNumber += 1;
    pokeballNumber -= 1;
}

// enemy functions

// Constructors

enemy::enemy(){
    name = "Goblin";
    enemyPokemon = pokemon();
}

enemy::enemy(string name, pokemon pokemon_object){
    this->name = name;
    enemyPokemon = pokemon_object;
}

// Getters

string enemy::getName(){
    return name;
}

pokemon enemy::getPokemon(){
    return enemyPokemon;
}