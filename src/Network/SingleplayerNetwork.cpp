#include "SingleplayerNetwork.h"

#include "AbstractNetwork.h"
#include "NetworkResponse.h"
#include "Packet.h"
#include <memory>

SingleplayerNetwork::SingleplayerNetwork()
{
    //ctor
}

SingleplayerNetwork::~SingleplayerNetwork()
{
    //dtor
}

NetworkResponse SingleplayerNetwork::SendPacket(Packet packet){
    _packet = packet;

    NetworkResponse response;
    response.Success = true;

    return response;
}

std::shared_ptr<Packet> SingleplayerNetwork::RecievePacket(){
    return std::shared_ptr<Packet>(&_packet);
}

std::shared_ptr<Packet> SingleplayerNetwork::RequestPacketFromGamestep(int gameStep){
    return std::shared_ptr<Packet>(&_packet);
}
