// Copiar este archivo como "secrets.h" (misma carpeta) y completar.
// secrets.h está en .gitignore: NUNCA subirlo a GitHub.
#pragma once

// WiFi (red de 2,4 GHz)
const char* WIFI_SSID = "NOMBRE_DE_TU_RED";
const char* WIFI_PASS = "CLAVE_DE_TU_RED";

// Telegram: token entregado por @BotFather y chat_id de quien recibe las alertas
// (un grupo tiene chat_id negativo, ej: "-1001234567890")
const char* TG_TOKEN = "TOKEN_DEL_BOT";
const char* TG_CHAT  = "CHAT_ID";

// Nube (servidor de software/servidor desplegado en Railway)
const char* SERVER_URL = "https://TU-APP.up.railway.app/api/lecturas";
const char* API_KEY    = "LA_MISMA_API_KEY_QUE_EN_RAILWAY";
