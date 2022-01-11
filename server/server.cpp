#include <stdio.h>
#include <enet/enet.h>

int main(int argc, char ** argv)
{
  ENetAddress addr;
  ENetHost *server;

  addr.host = ENET_HOST_ANY;
  addr.port = 11113;

  if (enet_initialize() != 0) {
    fprintf(stderr, "cannot init enet\n");
    return -1;
  }
  atexit(enet_deinitialize);

  server = enet_host_create(&addr, 1024, 2, 0, 0);
  if (server == NULL) {
    fprintf(stderr, "an error occurred while trying to create a enet server host\n");
    return -1;
  }

  ENetEvent event;

  while (1) {
    enet_host_service(server, &event, 0);
    switch (event.type) {
    case ENET_EVENT_TYPE_NONE:
      continue;
      break;
    case ENET_EVENT_TYPE_CONNECT:
      printf("a new client connected from: %x:%u \n", event.peer->address.host, event.peer->address.port);
      event.peer->data = (void*)"Client information";
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      printf("a packet of length %d constaining %s was received from %s on channel %u\n",
	     event.packet->dataLength,
	     event.packet->data,
	     event.peer->data,
	     event.channelID
	     );
      enet_packet_destroy(event.packet);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      printf("%s disconnected.\n", static_cast<char*>(event.peer->data)); 
      event.peer->data = NULL;
      break;
    default:
      break;
    }
  }
  enet_host_destroy(server);
}
  
