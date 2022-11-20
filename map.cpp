#include "Map.h"

using namespace std;

Map::Map(){
    resetMap();
}

/*
 * Algorithm: Resets positions of player, NPCs, and rooms and clears map_data_
 * Set Player position coordinates to 0
 * Set npc_count_ to false
 * Set room_count_ to 0
 * loop i from 0 to max_npcs_
 *      Set row and col of location to -1
 * loop i from 0 to max_rooms
 *      Set row and col of room location to -1
 * loop i from 0 to num_rows_
 *      loop j from 0 to num_cols_
 *          Set (i,j) location on map_data_ to '-'
 * Parameters: none
 * Return: nothing (void)
 */
void Map::resetMap(){
    // resets player position, count values, and initializes values in position arrays to -1
    player_position_[0] = 0;
    player_position_[1] = 0;

    // set dungeon exit
    dungeon_exit_[0] = num_rows_ - 1;
    dungeon_exit_[1] = num_cols_ / 2;

    for (int i = 0; i < max_npcs_; i++)
    {
        npc_positions_[i][0] = -1;
        npc_positions_[i][1] = -1;
    }
    npc_count_ = 0;

    for (int i = 0; i < max_rooms_; i++)
    {
        room_positions_[i][0] = -1;
        room_positions_[i][1] = -1;
    }
    room_count_ = 0;

    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            map_data_[i][j] = UNEXPLORED;
        }
    }
    map_data_[dungeon_exit_[0]][dungeon_exit_[1]] = EXIT;
}

int Map::getPlayerRow(){
    return player_position_[0];
}// return player's column position
int Map::getPlayerCol(){
    return player_position_[1];
}// return current room count
int Map::getDungeonExitRow(){
    return dungeon_exit_[0];
}// return dungeon exit col
int Map::getDungeonExitCol(){
    return dungeon_exit_[1];
}// set player position, if in range
int Map::getRoomCount(){
    return room_count_;
}// return dungeon exit row

