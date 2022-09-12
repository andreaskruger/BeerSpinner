#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAdress[] = {0x94,0xB9,0x7E,0xE6,0x79,0x9C};//Change to target MAC adress
int error, succ;

typedef struct struct_message{
  int sendID;
}struct_message;
 
struct_message msg_to_send;
struct_message msg_incoming;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success: " : "Delivery Fail: ");
    status == ESP_NOW_SEND_SUCCESS ? succ++ :error++;
    Serial.println(error);
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&msg_incoming, incomingData, sizeof(msg_incoming));
}

void WIFI_init(){
    WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  esp_now_register_send_cb(OnDataSent);
 
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAdress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
 
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
    WiFi.mode(WIFI_MODE_STA);
    Serial.println(WiFi.macAddress());
}

