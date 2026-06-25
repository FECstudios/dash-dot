// NOTE: AI WAS USED FOR DOCUMENTATİON, WRITING COMMENTS, AND HELPING WITH THE CODE WRITING PROCESS

/*
Pin Mapping:
- BTN_MEGAPHONE : GPIO 8
- BTN_GYRO      : GPIO 9
- BTN_POTATO    : GPIO 10
- BTN_SPECTRUM  : GPIO 20

- LED_PIN       : GPIO 1
- I2S BCLK      : GPIO 2
- I2S WS        : GPIO 4
- I2S DOUT      : GPIO 5
- I2S DIN       : GPIO 3

===========================================================
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <driver/i2s.h>
#include <math.h>

// ---------------- BUTTONS ----------------
#define BTN_MEGAPHONE 8
#define BTN_GYRO      9
#define BTN_POTATO    10
#define BTN_SPECTRUM  20

// ---------------- LED CONFIG ----------------
#define LED_PIN 1
#define NUM_LEDS 7

// ---------------- I2S PINS ----------------
#define I2S_BCLK 2
#define I2S_WS   4
#define I2S_DOUT 5
#define I2S_DIN  3

#define BUFFER_SIZE 64

Adafruit_MPU6050 mpu;
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int16_t audio_buffer[BUFFER_SIZE];

bool mpuOK = false;
int activeMode = 0;

// ---------------- HOT POTATO GAME STATE ----------------
unsigned long potatoExplodeTime = 0;
int potatoCurrentLed = 0;
bool potatoInitialized = false;

// ---------------- DEBOUNCE CONTROL ----------------
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

// ---------------- I2S SETUP ----------------
void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 32,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

// ---------------- AUDIO TONE GENERATOR ----------------
void playAdvancedTone(int startFreq, int endFreq, int durationMs, float maxVolume = 32767.0) {
  int totalSamples = (16000 * durationMs) / 1000;
  if (totalSamples <= 0) totalSamples = 1;

  int16_t *buf = (int16_t*)malloc(32 * sizeof(int16_t));
  if (!buf) return;

  int sampleIdx = 0;
  size_t written;
  float phase = 0;

  while (sampleIdx < totalSamples) {
    int chunk = (totalSamples - sampleIdx > 32) ? 32 : (totalSamples - sampleIdx);

    for (int i = 0; i < chunk; i++) {
      int currentIdx = sampleIdx + i;
      float progress = (float)currentIdx / totalSamples;

      float currentFreq = startFreq + (endFreq - startFreq) * progress;
      float decay = exp(-progress * 2.0);
      float currentVol = maxVolume * decay;

      buf[i] = (int16_t)(sin(phase) * currentVol);

      phase += (2.0 * M_PI * currentFreq) / 16000.0;
      if (phase >= 2.0 * M_PI) phase -= 2.0 * M_PI;
    }

    i2s_write(I2S_NUM_0, buf, chunk * sizeof(int16_t), &written, portMAX_DELAY);
    sampleIdx += chunk;
  }

  free(buf);
}

// ---------------- LED HELPERS ----------------
void fillColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n=============================================");
  Serial.println("  SAFE AUDIO + 4 MODE MULTI SYSTEM");
  Serial.println("=============================================");

  pinMode(BTN_MEGAPHONE, INPUT_PULLUP);
  pinMode(BTN_GYRO, INPUT_PULLUP);
  pinMode(BTN_POTATO, INPUT_PULLUP);
  pinMode(BTN_SPECTRUM, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(40);
  fillColor(0, 0, 0);

  Wire.begin(6, 7);
  mpuOK = mpu.begin();

  setupI2S();

  // Startup sound
  playAdvancedTone(150, 300, 400, 15000.0);
}

// ---------------- MAIN LOOP ----------------
void loop() {
  unsigned long currentMillis = millis();

  // -------- BUTTON HANDLING (DEBOUNCED) --------
  if (currentMillis - lastDebounceTime > debounceDelay) {

    if (digitalRead(BTN_MEGAPHONE) == LOW) {
      activeMode = (activeMode == 1) ? 0 : 1;
      playAdvancedTone(400, 800, 150, 15000);
      lastDebounceTime = currentMillis;
    }

    else if (digitalRead(BTN_GYRO) == LOW) {
      activeMode = (activeMode == 2) ? 0 : 2;
      playAdvancedTone(600, 900, 150, 15000);
      lastDebounceTime = currentMillis;
    }

    else if (digitalRead(BTN_POTATO) == LOW) {
      activeMode = (activeMode == 3) ? 0 : 3;
      potatoInitialized = false;
      playAdvancedTone(800, 1100, 150, 15000);
      lastDebounceTime = currentMillis;
    }

    else if (digitalRead(BTN_SPECTRUM) == LOW) {
      activeMode = (activeMode == 4) ? 0 : 4;
      playAdvancedTone(1000, 500, 150, 15000);
      lastDebounceTime = currentMillis;
    }
  }

  // ---------------- MODE SYSTEM ----------------
  switch (activeMode) {

    // =====================================================
    // MODE 1: SAFE MEGAPHONE (Noise-Gated Amplifier)
    // =====================================================
    case 1: {
      size_t bytes_read, bytes_written;
      i2s_read(I2S_NUM_0, audio_buffer, sizeof(audio_buffer), &bytes_read, portMAX_DELAY);

      int samples = bytes_read / 2;

      long sum = 0;
      for (int i = 0; i < samples; i++) sum += abs(audio_buffer[i]);

      int level = (samples > 0) ? sum / samples : 0;

      // Noise gate prevents echo / feedback
      if (level > 3800) {
        for (int i = 0; i < samples; i++) {
          int32_t amplified = (int32_t)audio_buffer[i] * 4;
          audio_buffer[i] = (int16_t)constrain(amplified, -28000, 28000);
        }

        i2s_write(I2S_NUM_0, audio_buffer, bytes_read, &bytes_written, portMAX_DELAY);
      } else {
        memset(audio_buffer, 0, bytes_read);
      }

      int leds = constrain(map(level, 3500, 18000, 0, NUM_LEDS), 0, NUM_LEDS);

      pixels.clear();
      for (int i = 0; i < leds; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      }
      pixels.show();
      break;
    }

    // =====================================================
    // MODE 2: GYRO LASER SYNTH
    // =====================================================
    case 2: {
      if (mpuOK) {
        sensors_event_t a, g, t;
        mpu.getEvent(&a, &g, &t);

        float motion = abs(a.acceleration.x) + abs(a.acceleration.y) + abs(a.acceleration.z);

        if (motion > 18) {
          int intensity = constrain(map(motion, 18, 45, 0, 255), 0, 255);

          fillColor(intensity, 0, 255 - intensity);

          int startFreq = 2200 - (intensity * 3);
          int endFreq = 400 + (intensity * 2);

          playAdvancedTone(startFreq, endFreq, 40, 20000.0);
        } else {
          pixels.clear();
          pixels.show();
        }
      }
      break;
    }

    // =====================================================
    // MODE 3: HOT POTATO GAME
    // =====================================================
    case 3: {
      if (!potatoInitialized) {
        potatoExplodeTime = millis() + random(4000, 9000);
        potatoCurrentLed = 0;
        potatoInitialized = true;
      }

      if (millis() < potatoExplodeTime) {

        pixels.clear();

        int timeLeft = potatoExplodeTime - millis();
        int speedDelay = constrain(map(timeLeft, 0, 7000, 30, 200), 30, 200);

        uint8_t red = map(timeLeft, 0, 7000, 255, 0);
        uint8_t green = map(timeLeft, 0, 7000, 0, 255);

        pixels.setPixelColor(potatoCurrentLed, pixels.Color(red, green, 0));
        pixels.show();

        int clickFreq = 1800 - (speedDelay * 5);
        playAdvancedTone(clickFreq, clickFreq - 30, 12, 8000.0);

        delay(speedDelay);

        potatoCurrentLed = (potatoCurrentLed + 1) % NUM_LEDS;
      }
      else {
        fillColor(255, 0, 0);
        playAdvancedTone(300, 40, 800, 30000.0);
        fillColor(0, 0, 0);
        delay(500);
        potatoInitialized = false;
      }
      break;
    }

    // =====================================================
    // MODE 4: AUDIO SPECTRUM VISUALIZER (VISUAL ONLY)
    // =====================================================
    case 4: {
      size_t bytes_read;
      i2s_read(I2S_NUM_0, audio_buffer, sizeof(audio_buffer), &bytes_read, portMAX_DELAY);

      int samples = bytes_read / 2;

      long sum = 0;
      for (int i = 0; i < samples; i++) sum += abs(audio_buffer[i]);

      int level = (samples > 0) ? sum / samples : 0;

      int leds = constrain(map(level, 500, 12000, 0, NUM_LEDS), 0, NUM_LEDS);

      pixels.clear();

      for (int i = 0; i < leds; i++) {
        uint8_t r = map(i, 0, NUM_LEDS, 0, 255);
        uint8_t b = map(i, 0, NUM_LEDS, 255, 0);
        pixels.setPixelColor(i, pixels.Color(r, 0, b));
      }

      pixels.show();
      break;
    }

    // =====================================================
    // MODE OFF
    // =====================================================
    default: {
      pixels.clear();
      pixels.show();
      break;
    }
  }
}
