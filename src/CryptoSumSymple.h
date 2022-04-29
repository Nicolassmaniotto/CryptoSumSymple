/*
 * encryptSumSymple.h
 * Nicolas Smaniotto
 * 08-04-2022
 * 
 * biblioteca para geração de textos 
 * cryptografado com base em soma
 * ex: abc+abc =a+a:b+b:c+c
 */
#ifndef _CRYPTO_SUM
#define _CRYPTO_SUM

#include <Arduino.h>

inline String split(String msg, String separador, String * result) {
  //  função com o proposito de funcionar semelhante ao split do javascript
  int comprimento =  (msg.length() + 1);
  // String result[comprimento];
  int cont = 0;
  for (int i = 0; i < comprimento; i++) {
    if ((String)msg[i] == (String)separador) {
      // Serial.println(result[cont]);
      cont++;
      continue;
    }
    if (result[cont] == "") {
      result[cont] =  msg[i];
    } else {
      result[cont] += msg[i];
    }
  }
  return *result;
}
inline int splitToInt(String msg, String separador, int *varBuffer) {
  //  funcção com o proposito de funcionar semelhante ao split do javascript
  int comprimento =  (msg.length() + 1);
  int cont = 0;
  String calc;
  for (int i = 0; i < comprimento; i++) {
    if ((String)msg[i] == (String)separador || i == (comprimento - 1)) {

      varBuffer[cont] = calc.toInt();
      calc = "";
      cont++;
      continue;
    }
    if (calc == "") {
      calc = (String) msg[i];
    } else {
      calc += (String)  msg[i];
    }
  }

  return *varBuffer;
}

inline String encryptoSimple(String msg, String key, String separador ) {
  //  converte string em byte array e depois em hex
  int comprimento =  (msg.length() + 1);
  char parteTexto[comprimento]; //buffer pros bytes
  msg.toCharArray(parteTexto, comprimento);
  //  converte string em byte array e depois em hex
  int keyTamanho = (key.length() + 1);
  char parteKey[keyTamanho]; //buffer pros bytes
  key.toCharArray(parteKey, keyTamanho);

  String result = (String) comprimento;


  //  Serial.println(comprimento);
  int contKey = 0;

  for (int i = 0; i < comprimento; i++) {
    //    Serial.println(i);
    //      Serial.println(parteKey[0]);
    if ((int)parteTexto[i] == 0)  {
      break;
    }

    result.concat((String)(separador));
    result.concat((int)parteTexto[i] - (int)parteKey[contKey]);


    contKey++;
    if (contKey >= keyTamanho - 1) {
      contKey = 0;
    }
  }
  return result;


}

inline String decryptoSimple(String msg, String key , String separador ) {
  //  int tamanho = msg.length() + 1;
  //  converte string em byte array

  int parteTexto[(msg.length() + 1) / 2];
  splitToInt(msg, separador, parteTexto);
  //   for(int i =1;i<10;i++){
  //    Serial.println(parteTexto[i]);
  //   }
  int comprimento = (msg.length() / 2);
  //   Serial.println("Comprimento::::");
  //   Serial.println((sizeof(parteTexto)/2) +1);
  //  char parteTexto[] = {returnCharArray(msg)};
  //  converte string em byte array e depois em hex
  int keyTamanho = (key.length() + 1);
  char parteKey[keyTamanho]; //buffer pros bytes
  key.toCharArray(parteKey, keyTamanho);
  //  char parteKey[]   = {returnCharArray(key)};
  String result;
  //  Serial.println(comprimento);
  int contKey = 0;

  for (int i = 1; i < parteTexto[0]; i++) {
    //    Serial.println(i);
    if (sizeof(parteTexto[i]) == 0) {
      //      Serial.println("Break ::"+parteTexto[i]);
      break;
    }
    if (sizeof(parteKey[contKey]) == 0) {

      contKey = 0;
    }
    //    result.concat((String)(separador));
    int calc = (int)parteTexto[i] + (int)parteKey[contKey];
    result.concat((char) calc);
    //    Serial.println(parteTexto[i]);
    //    Serial.println((char)calc);
    //    Serial.println(keyTamanho);
    contKey++;
    //    Serial.println(contKey);
    if (contKey >= keyTamanho - 1) {
      contKey = 0;
    }
  }
  return result;

  //fim decripto
}


#endif