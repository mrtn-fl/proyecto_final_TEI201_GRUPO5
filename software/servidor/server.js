// =====================================================================
//  COStop - Servidor API (Railway) -> PostgreSQL (Aiven)
//  POST /api/lecturas       guarda una lectura (requiere header x-api-key)
//  GET  /api/lecturas       últimas lecturas (?dispositivo=&sensor=&limite=)
//  GET  /api/lecturas.csv   exporta lecturas en CSV (mismos filtros)
//  GET  /api/resumen        última lectura y promedio/máx de las últimas 24 h por sensor
//  GET  /salud              verifica que el servidor y la base respondan
// =====================================================================
const express = require("express");
const fs = require("fs");
const path = require("path");
const { Pool } = require("pg");

const { DATABASE_URL, API_KEY, PORT = 3000 } = process.env;
if (!DATABASE_URL || !API_KEY) {
  console.error("Faltan variables de entorno DATABASE_URL y/o API_KEY");
  process.exit(1);
}

// Aiven exige SSL. rejectUnauthorized:false evita tener que subir el certificado CA;
// para mayor seguridad se puede usar ssl: { ca: <contenido de ca.pem> }.
const pool = new Pool({
  connectionString: DATABASE_URL.replace(/[?&]sslmode=[^&]*/, ""),
  ssl: { rejectUnauthorized: false },
});

const SENSORES = ["co", "temperatura", "humedad"];
const app = express();
app.use(express.json({ limit: "2kb" }));

// Filtros comunes para GET
function filtros(q) {
  const cond = [], params = [];
  if (q.dispositivo) { params.push(String(q.dispositivo)); cond.push(`dispositivo = $${params.length}`); }
  if (q.sensor)      { params.push(String(q.sensor));      cond.push(`sensor = $${params.length}`); }
  const limite = Math.min(Math.max(parseInt(q.limite, 10) || 100, 1), 5000);
  return { where: cond.length ? "WHERE " + cond.join(" AND ") : "", params, limite };
}

app.post("/api/lecturas", async (req, res) => {
  if (req.get("x-api-key") !== API_KEY) return res.status(401).json({ error: "API key inválida" });
  const { dispositivo, sensor, valor } = req.body || {};
  if (typeof dispositivo !== "string" || !dispositivo || dispositivo.length > 50)
    return res.status(400).json({ error: "dispositivo inválido" });
  if (!SENSORES.includes(sensor)) return res.status(400).json({ error: "sensor inválido" });
  if (typeof valor !== "number" || !Number.isFinite(valor)) return res.status(400).json({ error: "valor inválido" });
  try {
    const r = await pool.query(
      "INSERT INTO lecturas (dispositivo, sensor, valor) VALUES ($1, $2, $3) RETURNING id, creado_en",
      [dispositivo, sensor, valor]
    );
    res.status(201).json(r.rows[0]);
  } catch (e) {
    console.error(e);
    res.status(500).json({ error: "error de base de datos" });
  }
});

app.get("/api/lecturas", async (req, res) => {
  const { where, params, limite } = filtros(req.query);
  try {
    const r = await pool.query(
      `SELECT id, dispositivo, sensor, valor, creado_en FROM lecturas ${where} ORDER BY creado_en DESC LIMIT ${limite}`,
      params
    );
    res.json(r.rows);
  } catch (e) {
    console.error(e);
    res.status(500).json({ error: "error de base de datos" });
  }
});

app.get("/api/lecturas.csv", async (req, res) => {
  const { where, params, limite } = filtros(req.query);
  try {
    const r = await pool.query(
      `SELECT id, dispositivo, sensor, valor, creado_en FROM lecturas ${where} ORDER BY creado_en DESC LIMIT ${limite}`,
      params
    );
    const filas = r.rows.map(x => [x.id, x.dispositivo, x.sensor, x.valor, x.creado_en.toISOString()].join(","));
    res.type("text/csv").attachment("lecturas_costop.csv")
       .send("id,dispositivo,sensor,valor,creado_en\n" + filas.join("\n") + "\n");
  } catch (e) {
    console.error(e);
    res.status(500).json({ error: "error de base de datos" });
  }
});

app.get("/api/resumen", async (req, res) => {
  try {
    const r = await pool.query(`
      SELECT dispositivo, sensor,
             (ARRAY_AGG(valor ORDER BY creado_en DESC))[1] AS ultimo,
             MAX(creado_en) AS ultima_fecha,
             ROUND(AVG(valor)::numeric, 2) AS promedio_24h,
             MAX(valor) AS maximo_24h,
             COUNT(*) AS n_24h
      FROM lecturas
      WHERE creado_en > NOW() - INTERVAL '24 hours'
      GROUP BY dispositivo, sensor
      ORDER BY dispositivo, sensor`);
    res.json(r.rows);
  } catch (e) {
    console.error(e);
    res.status(500).json({ error: "error de base de datos" });
  }
});

app.get("/salud", async (_req, res) => {
  try { await pool.query("SELECT 1"); res.json({ ok: true }); }
  catch { res.status(503).json({ ok: false }); }
});

// Crea la tabla al iniciar (idempotente) y levanta el servidor
(async () => {
  try {
    await pool.query(fs.readFileSync(path.join(__dirname, "schema.sql"), "utf8"));
    console.log("[db] tabla lecturas lista");
  } catch (e) {
    console.error("[db] no se pudo crear la tabla:", e.message);
  }
  app.listen(PORT, () => console.log(`[api] escuchando en puerto ${PORT}`));
})();
