# Sistema de Prevenção de Epilepsia com IoT e IA (InnoHealth)

## Visão Geral

Este código implementa um sistema IoT (Internet das Coisas) projetado para prevenção de epilepsia e monitoramento de convulsões. O sistema utiliza sensores para medir condições ambientais e movimento, e se comunica com um servidor central usando o protocolo MQTT (Message Queuing Telemetry Transport). Além disso, ele integra um sistema de IA chamado "Métis" para aprender e prever padrões de convulsões.

<p align="center">
  <img src="(https://github.com/gusmaomath/InnoHealth/assets/104039223/35a806fe-0c6a-474e-8d20-675be01c52ca)" alt="Descrição da Imagem">
</p>

## Componentes

### Hardware

- **Sensor DHT22:** Mede temperatura e umidade corporal.
- **Sensor MPU6050:** Mede dados de aceleração e giroscópio.
- **Botão:** Botão de pânico para sinalização de emergência.
- **Módulo WiFi:** Permite a comunicação com um servidor MQTT central.

### Software

- **Código Arduino:** Implementa leituras dos sensores, detecção do botão de pânico e comunicação com o servidor central.
- **Protocolo MQTT:** Facilita a comunicação entre o dispositivo e o servidor central.
- **Sistema de IA Métis:** Um sistema separado para aprender e prever padrões de convulsões.

## Como Funciona

1. **Leituras dos Sensores:**
   - O sensor DHT22 mede temperatura corporal e umidade.
   - O sensor MPU6050 mede dados de aceleração e giroscópio.

2. **Botão de Pânico:**
   - Um botão de pânico é implementado usando uma entrada digital. Quando pressionado, aciona a sinalização de emergência publicando uma mensagem no tópico MQTT "panico".

3. **Monitoramento Ambiental:**
   - Leituras de temperatura e umidade corporal são monitoradas. Se os valores excederem limites predefinidos, uma mensagem de alerta é publicada no tópico MQTT "alerta".

4. **Monitoramento de Movimento:**
   - Dados de aceleração e giroscópio são monitorados. Se os valores excederem limites predefinidos, indicando um movimento incomum, é detectada uma possível convulsão. O sistema toma medidas preventivas, como publicar uma mensagem no tópico MQTT "lidarComAtaqueEpiletico".

5. **Comunicação MQTT:**
   - O dispositivo se comunica com um servidor MQTT central, especificado por `mqtt_server` e `mqtt_port`.
   - Ele se inscreve no tópico "panico" para sinais de emergência.

6. **Integração com IA (Métis):**
   - O sistema de IA "Métis" deve ser integrado separadamente.
   - Métis aprende com dados históricos e padrões específicos do usuário para prever e prevenir convulsões.

## Configuração

1. **Conectar Hardware:**
   - Conecte o DHT22, MPU6050 e botão de pânico aos pinos apropriados no Arduino.

2. **Configuração WiFi:**
   - Configure as credenciais do WiFi (SSID e senha) no código.

3. **Configuração MQTT:**
   - Configure os detalhes do servidor MQTT (IP do servidor, porta) e o ID do cliente MQTT.

4. **Limites e Thresholds:**
   - Ajuste os limites e thresholds predefinidos para temperatura, umidade corporal, aceleração e valores do giroscópio de acordo com requisitos específicos.

5. **Integração com IA:**
   - O sistema de IA Métis precisa ser integrado separadamente para aprendizado e previsão de padrões de convulsões personalizados.

## Uso

- Faça o upload do código para a placa Arduino.
- Certifique-se de que o dispositivo IoT está conectado à rede WiFi.
- Monitore os tópicos MQTT para sinais de emergência, alertas e medidas preventivas contra convulsões.
- Integre o sistema de IA Métis para previsão personalizada de convulsões.

## Nota Importante

Este código serve como um framework fundamental para um sistema de prevenção de epilepsia. A eficácia da previsão de convulsões depende principalmente da precisão e capacidade de aprendizado do sistema de IA Métis. É essencial atualizar continuamente e aprimorar o Métis com base em dados do mundo real e feedback do usuário para melhorar suas capacidades preditivas.

## Autor

Matheus Gusmão & Júlia Neves

## Agradecimentos

- Este projeto foi inspirado pela necessidade de soluções eficazes de prevenção de epilepsia.
- Agradecimentos especiais à comunidade de código aberto pelas bibliotecas utilizadas neste projeto.
