#include "catch.hpp"

#include "NetworkResponse.h"
#include "SingleplayerNetwork.h"
#include "Packet.h"
#include <memory>

SCENARIO("SingleplayerNetwork::SendPacket"){


    SingleplayerNetwork network;
    Packet packet;

    Packet::PlayerInput input;

    input.Button1 = Packet::PlayerInput::ButtonAction::Pressed;

    packet.PlayerInputs.push_back(input);

    NetworkResponse response = network.SendPacket(packet);
    REQUIRE(response.Success == true);
}



SCENARIO("SingleplayerNetwork::RecievePacket"){

    SingleplayerNetwork network;
    Packet packet;

    Packet::PlayerInput input;

    input.Button1 = Packet::PlayerInput::ButtonAction::Pressed;

    packet.PlayerInputs.push_back(input);

    network.SendPacket(packet);

    std::shared_ptr<Packet> packetPtr = network.RecievePacket();

    REQUIRE(packetPtr != nullptr);
    Packet recievedPacket = *packetPtr.get();

    REQUIRE(recievedPacket.PlayerInputs.empty() == false);
    REQUIRE(recievedPacket.PlayerInputs[0].Button1 == Packet::PlayerInput::ButtonAction::Pressed);
}
