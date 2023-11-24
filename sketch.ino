#include <Wire.h>
#include <DHT.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "46.17.108.113";
const int mqtt_port = 1883;
const int buttonPin = 2;
const int dhtPin = 4;

const char* mqtt_id = "fiware_166";

DHT dht(dhtPin, DHT22);
MPU6050 mpu(Wire);

WiFiClient espClient;
PubSubClient client(espClient);

const float limiteAceleracaoX = 0.0;
const float limiteAceleracaoY = 0.0;
const float limiteAceleracaoZ = 1.0;
const float limiteGiroscopioX = 90.0;
const float limiteGiroscopioY = 90.0;
const float limiteGiroscopioZ = 90.0;


unsigned long lastAlertTime = 0;  // Armazena o tempo do último alerta
const unsigned long alertInterval = 5000;  // Intervalo mínimo entre alertas (em milissegundos)

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado ao WiFi");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Conteúdo: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao servidor MQTT...");
    if (client.connect(mqtt_id)) {
      Serial.println("Conectado");
      client.subscribe("panico");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup_mpu() {
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
}

void lidarComAtaqueEpiletico() {
  unsigned long currentTime = millis();

  // Verifica se tempo suficiente passou desde o último alerta
  if (currentTime - lastAlertTime >= alertInterval) {
    Serial.println("Possível ataque epilético! Tomando medidas...");
    client.publish("lidarComAtaqueEpiletico", "Possível ataque epilético! Tomando medidas...");
    
    // Atualiza o tempo do último alerta
    lastAlertTime = currentTime;
  } else {
    Serial.println("Aguardando intervalo de alerta...");
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(buttonPin, INPUT_PULLUP);
  dht.begin();
  setup_mpu();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    Serial.println("Botão de pânico pressionado!");
    client.publish("panico", "Sinal de emergência acionado!");
    delay(1000);
  }

  float tempC = dht.readTemperature();
  float humidade = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.println(tempC);
  Serial.print("Umidade: ");
  Serial.println(humidade);

  if (tempC > 37.5 || humidade > 70) {
    char mensagem[100];
    snprintf(mensagem, sizeof(mensagem), "Alerta: Temperatura=%.2f°C, Umidade=%.2f%% fora dos limites!", tempC, humidade);
    client.publish("alerta", mensagem);
    Serial.println("Alerta de temperatura ou umidade!");
    delay(5000);
  }

  mpu.update();

  // Verifica se a aceleração ou giroscópio ultrapassaram o limite
  if (mpu.getAccX() > limiteAceleracaoX ||
      mpu.getAccY() > limiteAceleracaoY ||
      mpu.getAccZ() > limiteAceleracaoZ ||
      mpu.getGyroX() > limiteGiroscopioX ||
      mpu.getGyroY() > limiteGiroscopioY ||
      mpu.getGyroZ() > limiteGiroscopioZ) {
    Serial.println("Aceleração ou giroscópio acima do limite!");
    lidarComAtaqueEpiletico();
    delay(5000);
  }

  delay(500);
}
