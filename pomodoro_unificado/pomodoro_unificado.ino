/**
 * @file pomodoro_unificado.ino
 * @author LucasIneth (https://github.com/lucasineth)
 * @brief Pomodoro Timer com barra de progresso e gráfico para M5StickC Plus 2
 * @version 1.0
 * @date 2024-01-15
 *
 * @Hardware: M5StickC Plus 2
 * @Platform Version: Arduino M5Stack Board Manager v2.1.3
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5StickCPlus2: https://github.com/m5stack/M5StickCPlus2
 */

#include <M5StickCPlus2.h>

// Configurações iniciais
int workTime = 25 * 60;  // 25 minutos (em segundos)
int breakTime = 5 * 60;  // 5 minutos (em segundos)
int timer = workTime;    // Tempo atual
bool isWorking = true;   // Indica se está no ciclo de trabalho
bool isRunning = false;  // Indica se o timer está rodando
int completedCycles = 0; // Contador de ciclos concluídos

// Configurações da barra de progresso
const int barWidth = 200;
const int barHeight = 20;
const int barX = 10;
const int barY = 140;

// Função para exibir o tempo restante na tela
void displayTime() {
  int minutes = timer / 60;
  int seconds = timer % 60;

  // Calcula a porcentagem de progresso
  int maxTime = isWorking ? workTime : breakTime;
  float progress = 1.0 - ((float)timer / maxTime);
  int progressWidth = progress * barWidth;

  // Define a cor de fundo com base no modo
  M5.Lcd.fillScreen(isWorking ? RED : GREEN);

  // Exibe as informações
  M5.Lcd.setTextColor(WHITE, isWorking ? RED : GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.printf("Modo: %s", isWorking ? "Trabalho" : "Pausa");

  M5.Lcd.setCursor(10, 60);
  M5.Lcd.printf("Tempo: %02d:%02d", minutes, seconds);

  M5.Lcd.setCursor(10, 100);
  M5.Lcd.printf("Ciclos: %d", completedCycles);

  // Desenha a barra de progresso
  M5.Lcd.fillRect(barX, barY, barWidth, barHeight, DARKGREY); // Fundo da barra
  M5.Lcd.fillRect(barX, barY, progressWidth, barHeight, WHITE); // Progresso atual
}

// Função para desenhar o gráfico de barras dos ciclos concluídos
void drawGraph() {
  const int graphBarWidth = 15; // Largura de cada barra
  const int graphBarSpacing = 5; // Espaçamento entre barras
  const int graphBarHeightMax = 60; // Altura máxima da barra
  const int graphXStart = 10; // Início do gráfico no eixo X
  const int graphYStart = 120; // Base do gráfico no eixo Y

  // Limpa a área do gráfico
  M5.Lcd.fillRect(0, graphYStart - graphBarHeightMax - 10, 240, graphBarHeightMax + 20, BLACK);

  // Desenha as barras
  for (int i = 0; i < completedCycles && i < 10; i++) {
    int barHeight = map(i + 1, 1, 10, 10, graphBarHeightMax); // Altura proporcional
    int barX = graphXStart + i * (graphBarWidth + graphBarSpacing);
    int barY = graphYStart - barHeight;
    M5.Lcd.fillRect(barX, barY, graphBarWidth, barHeight, BLUE);
  }
}

// Alterna entre iniciar e pausar o timer
void toggleTimer() {
  isRunning = !isRunning;
}

// Reseta o timer para o início do ciclo atual
void resetTimer() {
  isRunning = false;
  timer = isWorking ? workTime : breakTime;
  displayTime();
}

// Ajusta o tempo de trabalho ou pausa
void adjustTime(bool increase) {
  int adjustment = 60; // Ajuste em segundos (1 minuto)
  if (isWorking) {
    workTime = max(60, workTime + (increase ? adjustment : -adjustment));
    timer = workTime;
  } else {
    breakTime = max(60, breakTime + (increase ? adjustment : -adjustment));
    timer = breakTime;
  }
  displayTime();
}

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  displayTime();
}

void loop() {
  M5.update();

  // Botão A: Inicia ou pausa o timer
  if (M5.BtnA.wasPressed()) {
    toggleTimer();
  }

  // Botão PWR: Reseta o timer
  if (M5.BtnPWR.wasPressed()) {
    resetTimer();
  }

  // Botão B: Ajuste dinâmico (pressiona curto para aumentar, longo para reduzir)
  if (M5.BtnB.wasPressed()) {
    adjustTime(true); // Aumenta o tempo
  }
  if (M5.BtnB.pressedFor(1000)) { // Reduz o tempo ao segurar
    adjustTime(false);
  }

  // Atualiza o timer se estiver rodando
  if (isRunning) {
    delay(1000); // Espera 1 segundo
    timer--;

    // Verifica se o tempo acabou
    if (timer <= 0) {
      isWorking = !isWorking; // Alterna entre trabalho e pausa
      timer = isWorking ? workTime : breakTime;

      // Incrementa o contador de ciclos ao final de um ciclo de trabalho
      if (!isWorking) {
        completedCycles++;
        drawGraph(); // Atualiza o gráfico
      }

      // Alerta sonoro
      M5.Speaker.tone(1000, 200);
      delay(300);
      M5.Speaker.tone(1000, 200);
    }

    displayTime();
  }
}
