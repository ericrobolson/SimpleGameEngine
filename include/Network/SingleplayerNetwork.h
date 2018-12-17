#ifndef SINGLEPLAYERNETWORK_H
#define SINGLEPLAYERNETWORK_H

#include "AbstractNetwork.h"
#include "NetworkResponse.h"
#include "Packet.h"
#include <memory>

class SingleplayerNetwork : public AbstractNetwork
{
    public:
        SingleplayerNetwork();
        virtual ~SingleplayerNetwork();

        NetworkResponse SendPacket(Packet packet);
        std::shared_ptr<Packet> RecievePacket();
        std::shared_ptr<Packet> RequestPacketFromGamestep(int gameStep);

    protected:

    private:
        // add a list/vector to keep track of all gamesteps; need to think of how long/big this will get with how long a game lasts; e.g. with 15minutes x  30 gamesteps a second = massive!
        // Don't need to keep that big of a list though in single player, if at all
        Packet _packet;
};

#endif // SINGLEPLAYERNETWORK_H
