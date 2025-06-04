#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio

#define NUM_PIXELS 25
#define OUT_PIN 7
const uint button_0 = 3;
const uint button_1 = 4;
const uint button_2 = 5;
const uint button_3 = 6;
const uint button_4 = 8;
const uint button_5 = 9;
const uint button_6 = 10;

uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R = r * 255;
  unsigned char G = g * 255;
  unsigned char B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

void desenho_pio(double *desenho, PIO pio, uint sm, double r, double g, double b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    double intensidade = desenho[24 - i];
    uint32_t cor = matrix_rgb(b * intensidade, r * intensidade, g * intensidade);
    pio_sm_put_blocking(pio, sm, cor);
  }
}

void limpar_matriz(PIO pio, uint sm) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pio_sm_put_blocking(pio, sm, matrix_rgb(0, 0, 0));
  }
}

void animar_seta(PIO pio, uint sm, double r, double g, double b) {
  double frames[19][25] = {
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
     {
      0, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      1, 0, 0, 0, 0,
      1, 1, 0, 0, 0,
      1, 1, 1, 0, 0,
      1, 1, 0, 0, 0,
      1, 0, 0, 0, 0
    },
    {
      0, 1, 0, 0, 0,
      0, 1, 1, 0, 0,
      1, 1, 1, 1, 0,
      0, 1, 1, 0, 0,
      0, 1, 0, 0, 0
    },
    {
      0, 0, 1, 0, 0,
      0, 0, 1, 1, 0,
      1, 1, 1, 1, 1,
      0, 0, 1, 1, 0,
      0, 0, 1, 0, 0
    },
    {
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 1,
      0, 1, 1, 1, 1,
      0, 0, 0, 1, 1,
      0, 0, 0, 1, 0
    },
    {
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 1,
      0, 0, 1, 1, 1,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 1
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 1, 1,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },//9
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 1,
      0, 0, 0, 1, 1,
      0, 0, 0, 0, 1,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 1,
      0, 0, 0, 1, 1,
      0, 0, 1, 1, 1,
      0, 0, 0, 1, 1,
      0, 0, 0, 0, 1
    },
    {
      0, 0, 0, 1, 0,
      0, 0, 1, 1, 0,
      0, 1, 1, 1, 1,
      0, 0, 1, 1, 0,
      0, 0, 0, 1, 0
    },
    {
      0, 0, 1, 0, 0,
      0, 1, 1, 0, 0,
      1, 1, 1, 1, 1,
      0, 1, 1, 0, 0,
      0, 0, 1, 0, 0
    },
    {
      0, 1, 0, 0, 0,
      1, 1, 0, 0, 0,
      1, 1, 1, 1, 0,
      1, 1, 0, 0, 0,
      0, 1, 0, 0, 0
    },
    {
      1, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      1, 1, 1, 0, 0,
      1, 0, 0, 0, 0,
      1, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      1, 1, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      1, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
  };

  for (int i = 0; i < 18; i++) {
    desenho_pio(frames[i], pio, sm, r, g, b);
    sleep_ms(250);
  }
  
}

void animar_fogos(PIO pio, uint sm, double r, double g, double b) {
  double frames[9][25] = {
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0
    },
     {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 1, 1, 1, 0,
      0, 0, 1, 0, 0,
      0, 0, 0, 0, 0
    },
    {
      0, 0, 1, 0, 0,
      0, 1, 1, 1, 0,
      1, 1, 1, 1, 1,
      0, 1, 1, 1, 0,
      0, 0, 1, 0, 0
    },
    {
      0, 1, 0, 1, 0,
      1, 1, 0, 1, 1,
      0, 0, 0, 0, 0,
      1, 1, 0, 1, 1,
      0, 1, 0, 1, 0
    },
    {
      1, 0, 0, 0, 1,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      1, 0, 0, 0, 1
    },//9
    
  };

  for (int i = 0; i < 9; i++) {
    desenho_pio(frames[i], pio, sm, r, g, b);
    sleep_ms(250);
  }
  
}

static void gpio_irq_handler(uint gpio, uint32_t events) {
  printf("Interrupção ocorreu no pino %d\n", gpio);
  reset_usb_boot(0, 0);
}

int main() {
  stdio_init_all();

  PIO pio = pio0;
  uint offset = pio_add_program(pio, &pio_matrix_program);
  uint sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, OUT_PIN);

  gpio_init(button_0);
  gpio_set_dir(button_0, GPIO_IN);
  gpio_pull_up(button_0);

  gpio_init(button_1);
  gpio_set_dir(button_1, GPIO_IN);
  gpio_pull_up(button_1);

  gpio_init(button_2);
  gpio_set_dir(button_2, GPIO_IN);
  gpio_pull_up(button_2);

  gpio_init(button_3);
  gpio_set_dir(button_3, GPIO_IN);
  gpio_pull_up(button_3);

  gpio_init(button_4);
  gpio_set_dir(button_4, GPIO_IN);
  gpio_pull_up(button_4);

  gpio_init(button_5);
  gpio_set_dir(button_5, GPIO_IN);
  gpio_pull_up(button_5);

  gpio_init(button_6);
  gpio_set_dir(button_6, GPIO_IN);
  gpio_pull_up(button_6);

  gpio_set_irq_enabled_with_callback(button_0, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

  printf("Sistema iniciado. Pressione o botão para animação\n");

  while (true) {
    if (!gpio_get(button_1)) {  // Botão pressionado (nível baixo)
      animar_seta(pio, sm, 0.0, 0.0, 1.0);  // Vermelho
      limpar_matriz(pio, sm);
    }
    if (!gpio_get(button_2)) {  // Botão pressionado (nível baixo)
      animar_seta(pio, sm, 0.0, 1.0, 0.0);  // Verde
      limpar_matriz(pio, sm);
    }
    if (!gpio_get(button_3)) {  // Botão pressionado (nível baixo)
      animar_seta(pio, sm, 1.0, 0.0, 0.0);  // Azul
      limpar_matriz(pio, sm);
    }
    if (!gpio_get(button_4)) {  // Botão pressionado (nível baixo)
      animar_fogos(pio, sm, 1.0, 0.0, 0.0);  // Vermelho
      limpar_matriz(pio, sm);
    }
    if (!gpio_get(button_5)) {  // Botão pressionado (nível baixo)
      animar_fogos(pio, sm, 0.0, 1.0, 0.0);  // Verde
      limpar_matriz(pio, sm);
    }
    if (!gpio_get(button_6)) {  // Botão pressionado (nível baixo)
      animar_fogos(pio, sm, 0.0, 0.0, 1.0);  // Azul
      limpar_matriz(pio, sm);
    }

     else {
      limpar_matriz(pio, sm);
    }
    sleep_ms(100);
   }
}
