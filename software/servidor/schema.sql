-- Tabla de lecturas de COStop (PostgreSQL / Aiven)
-- Una fila por sensor y por envío: el ESP32 manda "co", "temperatura" y "humedad" cada INTERVALO_LOG.
CREATE TABLE IF NOT EXISTS lecturas (
  id           BIGSERIAL PRIMARY KEY,
  dispositivo  VARCHAR(50)  NOT NULL,
  sensor       VARCHAR(20)  NOT NULL CHECK (sensor IN ('co', 'temperatura', 'humedad')),
  valor        DOUBLE PRECISION NOT NULL,
  creado_en    TIMESTAMPTZ  NOT NULL DEFAULT NOW()
);

CREATE INDEX IF NOT EXISTS idx_lecturas_disp_sensor_fecha
  ON lecturas (dispositivo, sensor, creado_en DESC);
