//Lachlan Kotarski and Diego Olin 

#ifndef MAP_H
#define MAP_H

#include <iostream>

using namespace std;

class Map
{
private:
    const char UNEXPLORED = '-'; // marker for unexplored spaces
    const char EXPLORED = ' ';   // marker for explored spaces
    const char MARKET = 'M';       // marker for room locations
    const char ROOM = 'R';
    const char CULTIST = 'C';
    const char BANDIT_CAMP = 'B';
    const char KING_WOOK = 'W';
    const char SCHOOL = 'S';
    const char FINAL_BATTLE = 'F';
    
    const char NPC = 'N';        // marker for NPC locations
    const char PARTY = 'X';      // marker for party position
    const char EXIT = 'E';       // marker for dungeon exit

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 30; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 8;
    static const int max_markets_ = 5; // max number of rooms
    static const int max_schools_ = 4;
    static const int max_bandit_camp_ = 4;
    static const int max_cultist_ = 2;
    static const int max_king_wook_ = 1;
    static const int max_final_battle_ = 1;


    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];
    int school_positions_[max_schools_][2]; // sores row,col positions of schools
    int bandit_camp_positions_[max_bandit_camp_][2]; // sores row,col positions of bandit camps
    //!
    int cultist_positions_[max_cultist_][2]; // should we make them discoverable? if so the 2nd array will have 3 as its max. 
    
    int king_wook_positions[max_king_wook_][2];
    int final_battle_positions[max_final_battle_][2];
    int market_positions_[max_markets_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_=0;  // stores number of misfortunes currently on map
    int room_count_=0;
    int market_count_=0; // stores number of sites currently on map
    int school_count_=0;
    int bandit_camp_count_=0;
    int cultist_count_=0;
    int king_wook_count_=0;
    int final_battle_count_=0;
public:
    Map();

    void resetMap();

    // getters
    int getPlayerRow(); //important
    int getPlayerCol(); // important
    int getDungeonExitRow(); // we could use for final battle
    int getDungeonExitCol(); // we could use for final battle
    int getRoomCount(); // meh... prolly remove.
    int getNPCCount(); // meh... 
    int getNumRows(); // useful
    int getNumCols(); // useful
    bool isOnMap(int row, int col); // useful
    bool isNPCLocation(int row, int col);
    bool isRoomLocation(int row, int col);
    bool isMarketLocation(int row, int col);
    bool isSchoolLocation(int row, int col);
    bool isBanditCampLocation(int row, int col);
    bool isCultistLocation(int row, int col);
    bool isKingWookLocation(int row, int col);
    bool isFinalBattleLocation(int row, int col);

    bool isExplored(int row, int col);
    bool isFreeSpace(int row, int col);
    bool isDungeonExit(int row, int col);

    // setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col); //we could use for final battle at the beginning of displaying map

    // other
    void displayMap();
    bool move(char);
    bool addNPC(int row, int col); // might need for randomization of spawning enemies
    bool addRoom(int row, int col);
    bool addSchool(int row, int col);
    bool addBanditCamp(int row, int col);
    bool addCultist(int row, int col);
    bool addKingWook(int row, int col);
    bool addFinalBattle(int row, int col);
    bool addMarket(int row, int col); // use for start of game and adding markets & schools
    bool removeNPC(int row, int col); // use for sta
    bool removeBanditCamp(int row, int col); // not use really because our markets & schools won't disappear
    bool removeCultistCamp(int row, int col); // not use really because our markets & schools won't disappear
    void exploreSpace(int row, int col); // use while navigating
};

#endif