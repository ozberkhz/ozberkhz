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
#include <fstream>

#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---// 
// 
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---// 
//
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    //---Creating Enemy and Pokemon Name Arrays---//
    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    
    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon:"<< endl;
    cout << "1- Bulbasaur" << endl;
    cout << "2- Charmender" << endl;
    cout << "3- Squirtle" << endl;
    cout << "Choice: " << endl;
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readEnemyNames(const char* argv){
    //---Code Here---//

    // Reading the file
    
    ifstream enemyfile;
    enemyfile.open(argv);

    int number_of_enemies;
    enemyfile >> number_of_enemies; // Reading the number of names in the file that is given at the start of the file
    string* enemies_list = new string[number_of_enemies]; // Creating a dynamic array with the size of the number of enemy names in the enemyNames.txt file
    
    for (int i = 0; i < number_of_enemies; i++){
        enemyfile >> enemies_list[i]; // Saving the enemy names into the dynamic array
    }

    return enemies_list; // returning the dynamic array
    //---------------//   
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readPokemonNames(const char* argv){
    //---Code Here---//

    // Reading the file
    
    ifstream pokemonfile;
    pokemonfile.open(argv);

    int number_of_pokemons;
    pokemonfile >> number_of_pokemons; // Reading the number of names in the file that is given at the start of the file
    string* pokemons_list = new string[number_of_pokemons]; // Creating a dynamic array with the size of the number of pokemon names in the pokemonNames.txt file
    
    for (int i = 0; i < number_of_pokemons; i++){
        pokemonfile >> pokemons_list[i]; // Saving the pokemon names into the dynamic array
    }

    return pokemons_list; // returning the dynamic array
    //---------------//
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice){
    //---Code Here---//

    // Creating the player object depending on the chosen starting pokemon

    if (pokemonChoice == 1){
       pokemon bulbasaur = pokemon("Bulbasaur", PLAYER_POKEMON_ATTACK);
       player new_player = player(playerName, bulbasaur);
       return new_player;
    } else if (pokemonChoice == 2){
       pokemon charmender = pokemon("Charmender", PLAYER_POKEMON_ATTACK);
       player new_player = player(playerName, charmender);
       return new_player;
    } else if (pokemonChoice == 3){
       pokemon squirtle = pokemon("Squirtle", PLAYER_POKEMON_ATTACK);
       player new_player = player(playerName, squirtle);
       return new_player;
    } else {
       player default_player = player(); // If an invalid input is given then the default constructor is called
       return default_player;
   }
    //---------------//
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){
    //---Code Here---//
    pokemon enemy_pokemon = pokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK); // Creating the enemy pokemon object
    enemy fighting_enemy = enemy(enemyNames[NAME_COUNTER], enemy_pokemon); // Creating the enemy object
    newPlayer->playerPokedex.updatePokedex(enemy_pokemon); // Updating the pokedex 

    POK_COUNTER++; // Moving onto the next pokemon name
    NAME_COUNTER++; // Moving onto the next enemy name
    if (POK_COUNTER == 6){
        POK_COUNTER = 0; // If number of pokemon names run out, go back to the first name
    }
    if (NAME_COUNTER == 5){
        NAME_COUNTER = 0; // If number of enemy names run out, go back to the first name
    }                         

    int choice;

    cout << "You encounter with " << fighting_enemy.getName() << " and his/hers pokemon " << fighting_enemy.getPokemon().getPokemonName() << endl;
    cout << fighting_enemy.getPokemon().getPokemonName() << " Health: " << fighting_enemy.getPokemon().getHpValue() << " Attack: " << fighting_enemy.getPokemon().getAttackValue() << endl;
    
    cout << "1- Fight" << endl;
    cout << "2- Runaway" << endl;
    cout << "Choice: ";
    cin >> choice;
    cout << "\n";

    if (choice == 1){
        int new_choice;
        int number_of_brawls = 0;
        while (true){
            number_of_brawls += 1;
            cout << "Your Pokemons Health: " << newPlayer->getPokemon().getHpValue() - (number_of_brawls * fighting_enemy.getPokemon().getAttackValue()) << endl; // Since we can't change the private values of the pokemon objects - like hpValue - I multiplied the amount of brawls (number of times you choose to attack and not run away) with the attack values
            cout << fighting_enemy.getName() << " Pokemons Health: " << fighting_enemy.getPokemon().getHpValue() - (number_of_brawls * newPlayer->getPokemon().getAttackValue()) << endl; // of the pokemons using a loop and subtracted them from their enemies and used that value as the current hp the pokemons had during the fight

            if (fighting_enemy.getPokemon().getHpValue() - (number_of_brawls * newPlayer->getPokemon().getAttackValue()) <= 0){ // If the enemies current hp is zero or less, then the fight ends
                cout << "You Won!" << endl;
                newPlayer->battleWon(); // Call battleWon() if the battle is won
                return;
            }

            cout << "1- Fight" << endl;
            cout << "2- Runaway" << endl;
            cout << "Choice: ";
            cin >> new_choice;
            cout << "\n";
            if (new_choice == 1){
                continue; // Go back to the start of the loop to continue fighting. Mind that the number of brawls will increase by one at the start of the loop
            }
            else if (new_choice == 2){
                cout << "You chose to run away" << endl;
                return;
            }
        }


    }
    else if (choice == 2){
        cout << "You chose to run away" << endl;
        return;
    }


    //---------------//
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player* newPlayer, string* pokemonNames){
    //---Code Here---//
    int choice;

    pokemon pokemon_to_catch = pokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);
    newPlayer->playerPokedex.updatePokedex(pokemon_to_catch); // updating the pokedex 
    POK_COUNTER++; // Moving onto the next pokemon name

    if (POK_COUNTER == 6){
        POK_COUNTER = 0; // If number of pokemon names run out, go back to the first name
    }

    cout << "You encounter with " << pokemon_to_catch.getPokemonName() << " Health: " << pokemon_to_catch.getHpValue() << " Attack: " << pokemon_to_catch.getAttackValue() << endl;
    cout << "1- Catch" << endl;
    cout << "2- Runaway" << endl;
    cout << "Choice: ";
    cin >> choice; 
    cout << "\n";

    if (choice == 1){
        cout << "You catch " << pokemon_to_catch.getPokemonName() << endl;
        newPlayer->catchPokemon(); // catchPokemon() method called to catch the pokemon
        return;
    }
    else if(choice == 2){
        cout << "You chose to run away" << endl;
        return;
    }
    else{
        return;
    }

    //---------------//
};
//--------------------------------------------//
