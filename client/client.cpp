#include <stdio.h>
#include <cstring>
#include <enet/enet.h>

int
main(int argc, char ** argv)
{
  ENetHost *client;
  if (enet_initialize() != 0) {
    fprintf(stderr, "cannot init enet\n");
    return -1;
  }
  atexit(enet_deinitialize);

  client = enet_host_create(NULL, 1, 2, 0, 0);
  if (client == NULL) {
    fprintf(stderr, "an error occurred while trying to create an enet client host\n");
    return -1;
  }

  ENetAddress addr;
  ENetEvent event;
  ENetPeer *peer;

  enet_address_set_host(&addr, "127.0.0.1");
  addr.port = 11113;

  peer = enet_host_connect(client, &addr, 2, 0);

  if (peer == NULL) {
    fprintf(stderr, "no available peers for initiating and enet connection.\n");
    return -1;
  }

  if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    printf("connection to localhost:11113 succeeded.");
  } else {
    enet_peer_reset(peer);
    fprintf(stderr, "connection to localhost:11113 failed.");
    return -1;
  }

  ENetPacket *packet = enet_packet_create("jjyyds", strlen("jjyyds") + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer, 0, packet);
  enet_host_flush(client);

  enet_host_destroy(client);
}
