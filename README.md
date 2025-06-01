# Geração de Animações em Matriz de LEDs 5x5

## Objetivo
Desenvolver duas animações em uma matriz de LEDs 5x5 (WS2812), controladas via botões A e B da placa BitDogLab, utilizando o microcontrolador Raspberry Pi Pico W e o simulador Wokwi. Implementar debounce por software nos botões.

---

## Descrição das Animações

### Animação 1 — Desenho de Seta 
Animação representando uma seta, que se forma gradualmente, acionada pelo botão **B** (GPIO 6).

### Animação 2 — Fogos
Animação representando uma explosão de fogos, acionada pelo botão **A** (GPIO 5).

---

## Especificações Técnicas
- Microcontrolador: Raspberry Pi Pico W
- Matriz de LEDs: 5x5 WS2812
- Botões: GPIO 5 (B) e GPIO 6 (A)
- Linguagem: C
- Ambiente: VS Code + Pico SDK + simulador Wokwi
- Debounce por software implementado

---

## Como Executar
1. Clone este repositório:
    ```bash
    git clone https://github.com/ryanfvieira1/Matriz_LEDS---RP2040.git
    ```

2. Compile o projeto com o **Pico SDK**.
3. Execute a simulação no **Wokwi** ou grave o firmware no Raspberry Pi Pico W.
4. Pressione o botão **B** para executar a animação do coração.
5. Pressione o botão **A** para executar a animação do fogo de artifício.

---

## Organização da Equipe
- **Líder de Projeto:** RYAN FARIAS — responsável pelo gerenciamento do repositório e revisão dos pull requests.
- **Desenvolvedor 1:** JOÃO VICTOR GUIMARÃES — responsável pela animação.
- **Desenvolvedor 2:** JOÃO VICTOR TEIXEIRA — responsável pela animação.

---

## Demonstração em Vídeo
Assista ao vídeo demonstrando o funcionamento das animações:

 [Link para o vídeo]

---

## Conclusão
A atividade foi concluída com sucesso, implementando as animações propostas.

---
