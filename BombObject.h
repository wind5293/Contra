#ifndef BOMB_OBJECT_H_
#define BOMB_OBJECT_H_

#include "commonFile.h"
#include "baseObject.h"

class BombObject : public baseObject
{
public:
    BombObject();
    ~BombObject();

    void set_is_placed(const bool& isPlaced) {is_placed_ = isPlaced;}
    bool get_is_placed() const {return is_placed_;}

    bool loadImageBomb(SDL_Renderer* renderer);
    //void explored();
private:
    bool is_placed_;
    //bool is_explored_;

    int explosion_time_;
};

#endif // BOMB_OBJECT_H_
