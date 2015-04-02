IPAddress ip(192,168,0,105);
uint16_t port = 8080;

TCPClient client;

void setup(void)
{
  Serial.begin(115200);

  delay(1000);
}

void draw(char c) {
  Serial.print(c);
  static int col = 0;
  col = (col+1) % 80;
  if (!col) {
    Serial.println();
  }
}

void loop(void)
{
  Serial.print(F("Connecting to "));
  Serial.println(ip);

  if (client.connect(ip, port)) {
    Serial.println(F("Connected."));
    /* Echo incoming data */
    while (client.connected()) {
      char buf[128];
      int qty = 0;
      while (client.available()) {
        buf[qty] = client.read();
        draw(buf[qty]);
        qty++;
      }
      for (int i=0; i<qty; ++i) {
        client.write(buf[i]);
        draw('.');
      }
    }
    client.stop();
  } else {
    Serial.println(F("Connection failed"));
    client.stop();
  }

  // Delay before next connection attempt
  delay(5000);
}
