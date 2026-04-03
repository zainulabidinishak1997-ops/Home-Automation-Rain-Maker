#include <Arduino.h>          /// ZAINUL ABIDIN BIN ISHAK
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

// =========================
// CONFIG
// =========================
#define GPIO_1 12//LAMPU 1
#define GPIO_2 13//LAMPU 2
#define GPIO_3 14//LAMPU 3
#define GPIO_4 15//KIPAS 4

#define RESET_BUTTON_GPIO 0
#define ACTIVE_HIGH false   // 🔥 ACTIVE LOW

const char *SERVICE_NAME = "ESP32_4CH";
const char *POP = "12345678";

const char *NODE_NAME = "BILIK ZAINUL";
const char *DEVICE1_NAME = "LAMPU 1";
const char *DEVICE2_NAME = "LAMPU 2";
const char *DEVICE3_NAME = "LAMPU 3";
const char *DEVICE4_NAME = "KIPAS 4";

// =========================
// STATE
// =========================
bool state1 = false;
bool state2 = false;
bool state3 = false;
bool state4 = false;

static Switch *sw1;
static Switch *sw2;
static Switch *sw3;
static Switch *sw4;

// =========================
// APPLY GPIO
// =========================
void setGPIO(int pin, bool state) {
  // ACTIVE LOW
  digitalWrite(pin, state ? LOW : HIGH);

  Serial.printf("GPIO %d -> %s\n", pin, state ? "ON" : "OFF");
}

// =========================
// CALLBACK
// =========================
void write_callback(Device *device, Param *param, const param_val_t val,
                    void *priv_data, write_ctx_t *ctx) {

  const char *device_name = device->getDeviceName();
  bool newState = val.val.b;

  Serial.printf("Device: %s -> %s\n", device_name, newState ? "ON" : "OFF");

  if (strcmp(device_name, DEVICE1_NAME) == 0) {
    state1 = newState;
    setGPIO(GPIO_1, state1);
  }
  else if (strcmp(device_name, DEVICE2_NAME) == 0) {
    state2 = newState;
    setGPIO(GPIO_2, state2);
  }
  else if (strcmp(device_name, DEVICE3_NAME) == 0) {
    state3 = newState;
    setGPIO(GPIO_3, state3);
  }
  else if (strcmp(device_name, DEVICE4_NAME) == 0) {
    state4 = newState;
    setGPIO(GPIO_4, state4);
  }

  param->updateAndReport(val);
}

// =========================
// PROVISION EVENT
// =========================
void sysProvEvent(arduino_event_t *sys_event) {
  switch (sys_event->event_id) {

    case ARDUINO_EVENT_PROV_START:
      Serial.printf("\nProvisioning: %s\n", SERVICE_NAME);
      WiFiProv.printQR(SERVICE_NAME, POP, "ble");
      break;

    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("WiFi connected");
      break;

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      break;

    default:
      break;
  }
}

// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(GPIO_1, OUTPUT);
  pinMode(GPIO_2, OUTPUT);
  pinMode(GPIO_3, OUTPUT);
  pinMode(GPIO_4, OUTPUT);

  // 🔥 default OFF (relay tak hidup masa boot)
  digitalWrite(GPIO_1, HIGH);
  digitalWrite(GPIO_2, HIGH);
  digitalWrite(GPIO_3, HIGH);
  digitalWrite(GPIO_4, HIGH);

  pinMode(RESET_BUTTON_GPIO, INPUT_PULLUP);

  Node my_node = RMaker.initNode(NODE_NAME);

  sw1 = new Switch(DEVICE1_NAME, NULL, state1);
  sw2 = new Switch(DEVICE2_NAME, NULL, state2);
  sw3 = new Switch(DEVICE3_NAME, NULL, state3);
  sw4 = new Switch(DEVICE4_NAME, NULL, state4);

  sw1->addCb(write_callback);
  sw2->addCb(write_callback);
  sw3->addCb(write_callback);
  sw4->addCb(write_callback);

  my_node.addDevice(*sw1);
  my_node.addDevice(*sw2);
  my_node.addDevice(*sw3);
  my_node.addDevice(*sw4);

  RMaker.enableOTA(OTA_USING_TOPICS);
  RMaker.start();

  WiFi.onEvent(sysProvEvent);

WiFiProv.beginProvision(NETWORK_PROV_SCHEME_BLE,
                        NETWORK_PROV_SCHEME_HANDLER_FREE_BTDM,
                        NETWORK_PROV_SECURITY_1,
                        POP,
                        SERVICE_NAME);

  Serial.println("System ready (4CH ACTIVE LOW)");
}

// =========================
// LOOP
// =========================
void loop() {

  if (digitalRead(RESET_BUTTON_GPIO) == LOW) {
    delay(100);
    int t = millis();

    while (digitalRead(RESET_BUTTON_GPIO) == LOW) {
      delay(50);
    }

    int duration = millis() - t;

    if (duration > 10000) {
      Serial.println("Factory Reset");
      RMakerFactoryReset(2);
    } 
    else if (duration > 3000) {
      Serial.println("WiFi Reset");
      RMakerWiFiReset(2);
    }
  }

  delay(100);
}