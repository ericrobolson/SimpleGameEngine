#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H
#include "NetworkResponse.h"
#include "Packet.h"
#include <memory>

class AbstractNetwork
{
    public:

        // What if we made the network poll for packets in a background thread, which then adds the packet to a queue. Every other system waits for the queued packet before it processes.
        // Try to add some sort of buffer, in that the queued packets is always for 2 gamesteps ahead?
        // Need a way to figure out a lockstep mechanism that works in a peer 2 peer setup
        // And also allows up to 12 simultaneous connections
        // Each network has 1 primary host, and a secondary host. Each time a node misses a packet and has to rerequest, they send a vote to switch to the next host. After
        // a certain period of time or votes, it switches hosts to the secondary and finds a new secondary.

        AbstractNetwork();
        virtual ~AbstractNetwork();

        virtual std::shared_ptr<NetworkResponse> SendPacket(Packet packet) = 0;
        virtual std::shared_ptr<Packet> RecievePacket() = 0;

        // Since we are making a deterministic synced game, we'll need to keep track of 'turns' or gamesteps that happened if a client is
        //out of sync so they can request that turn and then load up to the current gamestep
        virtual std::shared_ptr<Packet> RequestPacketFromGamestep(int gameStep) = 0;
};

#endif // ABSTRACTNETWORK_H
