#include "CryptoSumSymple.h"


String senha = "alterePorOutraSenha";
void setup() {
  // serial com 1200 devido a instabilidade previa
  Serial.begin(1200);
  delay(3000);
}

void loop() {
  if (true) {
    while (!Serial.available());
    String msg = Serial.readStringUntil('\n');
    msg = encryptoSimple(msg, senha, ":");
    Serial.println(msg);

/* para decriptografar algo descomente abaixo */
//    while (!Serial.available());
//    msg = Serial.readStringUntil('\n');
//    Serial.print("[HTTP] begin...\n");
    Serial.println(decryptoSimple(msg,senha,":"));
    //    continue;
  }
  // put your main code here, to run repeatedly:

}
