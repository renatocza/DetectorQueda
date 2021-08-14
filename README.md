# DetectorQueda
Detector de queda para idosos utilizando ESP-32 (compatível com ESP-8266) e acelerômetro MPU-6050.
Ao detectar uma queda o aparelho envia uma mensagem via **TELEGRAM** diretamente ao usuário informando uma possível queda.

## Hardware utilizado

- ESP32 DevKitC
- MPU-6050

## Bibliotecas utilizadas

- CTBot
- Adafruit_MPU6050

## Criando Telegram Token

- Inicie uma conversa com @BotFather
- /newbot
- Siga os passos para criar um bot
- /setprivacy
- Selecione o Bot
- Disable

Caso precise novamente do token digite /token


## Ligação MPU-6050 -> ESP32

- Através da placa adaptadora fornecida no projeto (recomendado) conecte o MPU-6050
- Na interface de conexão para o ESP (4 pinos) conecte VCC no pino V5 caso esteja utilizando uma fonte de energia 5v (4 pilhas) ou ligue diretamente no pino 3v3 caso esteja utilizando duas pilhas. **ATENÇÃO: O pino 3v3 não possui regulador de tensão e uma corrente maior que 3,3v pode queimar o ESP-32**
- Ligue GND ao GND do ESP-32
- Ligue o pino SCL do adaptador ao pino 22 do ESP
- Ligue o pino SDA do adaptador ao pino 21 do ESP


## Usando o bot

- Após iniciar o ESP-32 digite alguma mensagem para o bot
- O bot responderá a mensagem com o texto "Monitorando"
- Se uma queda for detectada o bot enviará uma mensagem de aviso



**Este é um software/hardware livre**
