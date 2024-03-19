#include <Nextion.h>

#define nexSerial Serial2

NexProgressBar progressBar = NexProgressBar(0, 1, "j0"); // Nextion ekranındaki ilerleme çubuğu nesnesi
NexText suSeviyesiText = NexText(0, 2, "t0"); // Nextion ekranındaki metin alanı nesnesi
const int suSeviyesiPin = 34; // Su seviyesi sensörünün bağlı olduğu analog pin

void setup() {
  Serial.begin(115200);
  nexSerial.begin(115200);

  // Attach fonksiyonları kullanmaya gerek kalmadı
}

void loop() {
  int suSeviyesiOkuma = analogRead(suSeviyesiPin); // Su seviyesi sensöründen okunan değeri okuyun
  int suSeviyesi = map(suSeviyesiOkuma, 0, 4095, 0, 100); // 0 ile 100 arasında bir yüzde değerine dönüştürün
  
  // Nextion HMI ekranındaki ilerleme çubuğunu ve metin alanını güncelleme
  progressBar.setValue(suSeviyesi); // ProgressBar'ı belirli bir değere ayarlama
  
  // Metin alanına su seviyesini yazma
  char suSeviyesiStr[10]; // Metin alanına yazılacak su seviyesi metni için karakter dizisi
  snprintf(suSeviyesiStr, sizeof(suSeviyesiStr), "%d%%", suSeviyesi);
  suSeviyesiText.setText(suSeviyesiStr);
  
  Serial.print("Su Seviyesi: ");
  Serial.println(suSeviyesi);
  
  delay(1000); // Değerleri güncellemek için kısa bir bekleme süresi
}
