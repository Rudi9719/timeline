//
//  Card.cpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#include "Card.hpp"

Card::Card()
{
    this -> cardtype = -1;
    column = -1;
    y = -1;
    for (int i = 0; i > this -> paths.size();i++) {
       this -> paths.insert(-1); // give paths placer values
    }
    for (int i = 0; i > this -> comtaken.size();i++) {
        this -> comtaken.insert(false); // gives commodity bools placer values
    }
    for (int i = 0; i > this -> comtype.size();i++) {
        this -> comtype.insert(-1); // gives comtypes placer values
    }
}
int getCardType()
{
    return cardtype;
}
void setCardType(int _cardtype)
{
    this -> cardtype = _cardtype;
}
void setY(int _y) {
    y = _y;
}
vector<int> getPaths() {
    return paths;
}
void setPaths(vector<int> _v) {
    // Totally wipes current object's path tree
    this.paths.erase(this.paths.begin(),this.paths.end());
    // Replaces it with the values of the passed vector
    for( int i = 0;i<this.paths.size(); i++) {
        this.paths.insert(_v[i]); // the magic line...
    }
}
int getColumn() {
    return this.column;
}
vector<int> getComType() {
    return comtype;
}
vector<bool> getComTaken() {
    return comtaken;
}
