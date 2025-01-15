# Pomodoro Timer para M5StickC Plus 2

Este projeto implementa um temporizador Pomodoro no dispositivo M5StickC Plus 2, projetado para ajudar no gerenciamento de tarefas e melhorar a produtividade. Com funcionalidades visuais e interativas, ele é ideal para estudantes, profissionais e qualquer pessoa que queira organizar melhor seu tempo.

## Funcionalidades

- **Ciclos de Trabalho e Pausa:** Alterna automaticamente entre períodos de trabalho (25 minutos) e descanso (5 minutos).
- **Barra de Progresso:** Exibe o progresso do ciclo atual em tempo real.
- **Gráfico de Ciclos:** Mostra os ciclos concluídos com barras crescentes.
- **Ajustes Dinâmicos:** Permite aumentar ou reduzir os tempos de trabalho e pausa com pressionamentos curtos ou longos do botão.
- **Feedback Visual e Sonoro:** Utiliza cores para diferenciar os modos (vermelho para trabalho, verde para pausa) e emite alertas sonoros ao final de cada ciclo.

## Hardware Necessário

- [M5StickC Plus 2](https://shop.m5stack.com/collections/m5stick-series)

## Como Usar

1. **Configuração Inicial:**
   - Clone este repositório ou copie o código para a IDE Arduino.
   - Certifique-se de que as bibliotecas do M5StickC Plus 2 estão instaladas.

2. **Carregando o Código:**
   - Conecte o M5StickC Plus 2 ao computador via cabo USB.
   - Compile e faça o upload do código para o dispositivo.

3. **Controles:**
   - **Botão A:** Inicia ou pausa o temporizador.
   - **Botão PWR:** Reseta o temporizador para o início do ciclo atual.
   - **Botão B:** Ajusta o tempo (pressionamento curto para aumentar, longo para reduzir).

## Exemplo de Funcionamento

1. Ao iniciar, o dispositivo exibirá o modo atual (Trabalho ou Pausa), o tempo restante e o número de ciclos concluídos.
2. Durante o ciclo, uma barra de progresso será preenchida gradualmente.
3. Após completar um ciclo de trabalho, um gráfico de barras será atualizado para mostrar os ciclos concluídos.

## Personalização

- **Alterar Tempos Padrão:**
  - Modifique as variáveis `workTime` e `breakTime` no início do código para ajustar os tempos padrão.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests com melhorias e novas funcionalidades.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
