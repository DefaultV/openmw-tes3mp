#include "../Packets/Worldstate/PacketRecordDynamic.hpp"
#include "../Packets/Worldstate/PacketWorldTime.hpp"

#include "WorldstatePacketController.hpp"

mwmp::WorldstatePacketController::WorldstatePacketController(RakNet::RakPeerInterface *peer)
{
    AddPacket<PacketRecordDynamic>(&packets, peer);
    AddPacket<PacketWorldTime>(&packets, peer);
}
