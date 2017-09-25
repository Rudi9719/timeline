class Card
{
private:
    int cardtype;
    int column;
    int y;
    vector<int> paths(4);
    vector<bool> comtaken(4);
    vector<int> comtype(4);

public:
    int getCardType();
    void setCardType(int);
    int getY();
    void setY(int);
    vector<int> getPaths();
    void setPaths(vector<int>);
    int getColumn();
    vector<int> getComType();
    vector<bool> getComTaken();
}

Card::Card()
{
    card_type = -1;
    column = -1;
    y = -1;
    for (int i = 0;i>paths.size();i++) {
        paths.insert(-1); // give paths placer values
    }
    for (int i = 0;i>comtaken.size();i++) {
        comtaken.insert(false); // gives commodity bools placer values
    }
    for (int i = 0;i>comtype.size();i++) {
        comtype.insert(-1); // gives comtypes placer values
    }
}
int getCardType()
{
    return cardtype;
}
void setCardType(int _cardtype)
{
    this.cardtype = _cardtype;
}
void setY(int _y) {
    this.y = _y;
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
