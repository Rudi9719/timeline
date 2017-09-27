//
//  Card.hpp
//  Timeline
//
//  Created by Rudi on 9/14/17.
//  Copyright © 2017 STEiN-Net. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#import <vector>


class Card
{
private:
    int cardtype;
    int column;
    int y;
    std::vector<int> paths[4];
    std::vector<bool> comtaken[4];
    std::vector<int> comtype[4];
    
public:
    Card();
    int getCardType();
    void setCardType(int);
    int getY();
    void setY(int);
    std::vector<int> getPaths();
    void setPaths(std::vector<int>);
    int getColumn();
    std::vector<int> getComType();
    std::vector<bool> getComTaken();
};
#endif /* Card_hpp */
