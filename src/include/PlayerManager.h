#ifndef PlayerManager_h
#define PlayerManager_h



class PlayerManager {

public:

    void movement(int directionFrontBack, int directionRightLeft);

    void flyAndRun(bool run, bool fly);

    PlayerManager(Player player);


private:
    Player m_player;
};

#endif // PlayerManager_h
