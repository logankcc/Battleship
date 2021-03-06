/**
 * Grid class implementation
 *
 * Authors: Jacob and Reid
 */

#include "../../include/entity/grid.h"

using entity::Coordinate;
using entity::Grid;
using entity::shipsNames;
using entity::SquareType;
using std::get;


Grid::Grid(const map<shipsNames, tuple<Coordinate, bool>> &shipOrientations) : size(10) {
    // Initialize the grid itself
    squares = new SquareType *[size];
    for (int i = 0; i < size; i++) {
        squares[i] = new SquareType[size];
        for (int k = 0; k < size; k++) {
            squares[i][k] = WATER;
        }
    }

    // Create the ship objects
    for (auto const &ship : shipOrientations) {
        const int x = get<0>(ship.second).getX();// Topmost/leftmost square x and y
        const int y = get<0>(ship.second).getY();
        const bool horizontal = get<1>(ship.second);
        get<0>(ships[ship.first]) = new Coordinate[shipSizes[ship.first]];// Array of coordinates this ship occupies

        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            // Initializes the i^th square (from the top left)
            if (horizontal) {
                get<0>(ships[ship.first])[i] = Coordinate(x + i, y);
                squares[y][x + i] = SHIP;
            } else {
                get<0>(ships[ship.first])[i] = Coordinate(x, y + i);
                squares[y + i][x] = SHIP;
            }
        }
        get<1>(ships[ship.first]) = 0;// Initialize hit count to 0

        // Also store the ship's orientation
        this->shipPositions[ship.first] = ship.second;
    }
}

SquareType Grid::attack(Coordinate coord) {
    // Determine the type of the square
    SquareType *status = &squares[coord.getY()][coord.getX()];
    switch (*status) {
        case WATER:
            *status = HIT_WATER;
            return WATER;
        case SHIP:
            *status = HIT_SHIP;
            break;
        default:
            // For a square that has already been hit (HIT_SHIP or HIT_WATER)
            // do nothing (the attack doesn't go through)
            return *status;
    }

    // If this is a ship, find the ship in this square and hit it
    for (auto const &ship : this->ships) {
        // Loop through the squares in this ship
        Coordinate *coords = get<0>(ship.second);
        for (int i = 0; i < shipSizes[ship.first]; ++i) {
            if (coords[i] == coord) {       // Found it!
                get<1>(ships[ship.first])++;// Update hit count
                return SHIP;
            }
        }
    }
    throw std::invalid_argument("Ship was not found- this game is in an impossible state!");
}

map<shipsNames, bool> Grid::getShipStatus() {
    map<shipsNames, bool> shipStatuses;
    for (auto const &ship : this->ships) {
        // If this ship has as many hits as it has squares, it has been sunk
        shipStatuses[ship.first] = get<1>(ship.second) == shipSizes[ship.first];
    }
    return shipStatuses;
}

map<shipsNames, tuple<Coordinate, bool>> entity::Grid::getShips() {
    return shipPositions;
}

entity::Grid::Grid() : size(0) {}


// Big three
Grid::~Grid() = default;

Grid::Grid(Grid &grid) = default;

Grid &Grid::operator=(Grid *rhs) {
    if (this == rhs) return *this;
    this->ships = rhs->ships;
    this->squares = rhs->squares;
    return *this;
}
