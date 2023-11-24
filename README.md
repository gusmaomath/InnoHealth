# InnoHealth: Sistema de Prevenção de Epilepsia com IoT e IA Métis

## Visão Geral

O InnoHealth é um sistema integrado de Internet das Coisas (IoT) e Inteligência Artificial (IA) projetado para prevenir ataques epiléticos e monitorar convulsões. Utilizando sensores para medir condições ambientais e movimento, juntamente com um sistema de IA chamado "Métis", este sistema oferece uma abordagem abrangente para melhorar a qualidade de vida de pacientes com epilepsia.

<p align="center">
  <img src="https://github.com/gusmaomath/InnoHealth/assets/104039223/35a806fe-0c6a-474e-8d20-675be01c52ca">
</p>

**Projeto em execução:** [InnoHealth Wokwi](https://wokwi.com/projects/382256974583652353)

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
   - DHT22 mede temperatura corporal e umidade.
   - MPU6050 mede dados de aceleração e giroscópio.

2. **Botão de Pânico:**
   - Ativado por uma entrada digital, aciona a sinalização de emergência no tópico MQTT "panico".

3. **Monitoramento Ambiental:**
   - Alertas publicados no tópico MQTT "alerta" se a temperatura ou umidade excederem limites predefinidos.

4. **Monitoramento de Movimento:**
   - Detecta possível convulsão se os valores de aceleração ou giroscópio excederem limites predefinidos.
   - Publica mensagem no tópico MQTT "lidarComAtaqueEpiletico" para tomar medidas preventivas.

5. **Comunicação MQTT:**
   - Dispositivo se comunica com servidor MQTT central especificado por `mqtt_server` e `mqtt_port`.
   - Inscreve-se no tópico "panico" para sinais de emergência.

6. **Integração com IA (Métis):**
   - Sistema de IA "Métis" deve ser integrado separadamente.
   - Métis aprende com dados históricos para prever e prevenir convulsões.
   - Inicialize o sistema Métis com um conjunto de dados históricos que inclua leituras dos sensores durante convulsões e períodos normais.
   - Carregue o modelo treinado do Métis no código Arduino ou em um servidor que processa os dados MQTT recebidos.
   - Ao receber leituras de sensores em tempo real, pré-processe os dados conforme necessário e use o modelo Métis para prever a probabilidade de uma convulsão.
   - Com base na probabilidade prevista, tome medidas adequadas, como enviar alertas, acionar medidas preventivas ou notificar profissionais de saúde
   - A eficácia do Métis depende fortemente da qualidade dos dados de treinamento e da capacidade contínua de adaptação.
   - Certifique-se de ajustar os parâmetros do modelo e a arquitetura da rede neural de acordo com as características dos seus dados.

## Configuração

1. **Conectar Hardware:**
   - Conecte DHT22, MPU6050 e botão de pânico aos pinos apropriados no Arduino.

2. **Configuração WiFi:**
   - Configure credenciais do WiFi (SSID e senha) no código.

3. **Configuração MQTT:**
   - Configure detalhes do servidor MQTT (IP e porta) e ID do cliente MQTT.

4. **Limites e Thresholds:**
   - Ajuste limites para temperatura, umidade, aceleração e giroscópio de acordo com requisitos.

5. **Integração com IA:**
   - Sistema de IA Métis precisa ser integrado para aprendizado e previsão de padrões de convulsões.

## Uso

- Faça upload do código para a placa Arduino.
- Certifique-se de que o dispositivo IoT está conectado à rede WiFi.
- Monitore tópicos MQTT para sinais de emergência, alertas e medidas preventivas.
- Integre Métis para previsão personalizada de convulsões.

## Nota Importante

Este código é um framework para prevenção de epilepsia. A eficácia depende da precisão do sistema Métis e do ajuste contínuo com dados reais e feedback do usuário.

## Autor

Matheus Gusmão & Júlia Neves

## Agradecimentos

- Inspirado pela necessidade de soluções eficazes de prevenção de epilepsia.
- Agradecimentos à comunidade de código aberto pelas bibliotecas utilizadas neste projeto.
