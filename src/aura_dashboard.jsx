import { useState, useEffect, useRef, useCallback } from "react";

/* ═══════════════════════════════════════════════════════════════════════════
   A.U.R.A. TACTICAL OPERATIONS DASHBOARD
   Autonomous Urban Rescue Array — Real-time Swarm Monitoring
   ═══════════════════════════════════════════════════════════════════════════ */

// ─── ROSBRIDGE CLIENT ──────────────────────────────────────────────────────
class RosBridge {
  constructor(url = "ws://localhost:9090") {
    this.url = url; this.ws = null; this.subs = {}; this.id = 0;
    this.connected = false; this.onStatus = null; this.rt = null;
  }
  connect() {
    try {
      this.ws = new WebSocket(this.url);
      this.ws.onopen = () => { this.connected = true; this.onStatus?.("connected"); Object.entries(this.subs).forEach(([t, s]) => this._wire(t, s.type)); };
      this.ws.onmessage = (e) => { try { const d = JSON.parse(e.data); if (d.op === "publish" && this.subs[d.topic]) this.subs[d.topic].cb(d.msg); if (d.op === "service_response") this._svcRes?.(d); } catch {} };
      this.ws.onclose = () => { this.connected = false; this.onStatus?.("disconnected"); this.rt = setTimeout(() => this.connect(), 3000); };
      this.ws.onerror = () => { this.connected = false; this.onStatus?.("error"); };
    } catch { this.onStatus?.("error"); }
  }
  subscribe(topic, type, cb) { this.subs[topic] = { type, cb }; if (this.connected) this._wire(topic, type); }
  _wire(topic, type) { this.ws?.send(JSON.stringify({ op: "subscribe", id: `s${this.id++}`, topic, type, throttle_rate: 200 })); }
  callService(svc, type, req = {}) {
    return new Promise((res, rej) => {
      const id = `v${this.id++}`;
      const h = (e) => { try { const d = JSON.parse(e.data); if (d.op === "service_response" && d.id === id) { this.ws.removeEventListener("message", h); res(d.values); } } catch {} };
      this.ws?.addEventListener("message", h);
      this.ws?.send(JSON.stringify({ op: "call_service", id, service: svc, type, args: req }));
      setTimeout(() => { this.ws?.removeEventListener("message", h); rej("timeout"); }, 5000);
    });
  }
  disconnect() { clearTimeout(this.rt); this.ws?.close(); }
}

// ─── CONSTANTS ─────────────────────────────────────────────────────────────
const PHASES = ["IDLE","PREFLIGHT","TAKEOFF","TRANSIT","FORMATION","OPERATIONS","RTL","LANDED","ABORT"];
const PHASE_COLORS = {
  IDLE: "#64748b", PREFLIGHT: "#f59e0b", TAKEOFF: "#3b82f6", TRANSIT: "#8b5cf6",
  FORMATION: "#06b6d4", OPERATIONS: "#10b981", RTL: "#f97316", LANDED: "#6b7280", ABORT: "#ef4444"
};
const FLIGHT_MODES = { 0:"IDLE", 1:"TAKEOFF", 2:"LOITER", 3:"MISSION", 4:"RTL", 5:"LAND" };

// ─── THEME ─────────────────────────────────────────────────────────────────
const T = {
  bg: "#0a0e14", panel: "#111820", border: "#1e2a38", accent: "#f59e0b",
  green: "#10b981", red: "#ef4444", blue: "#3b82f6", cyan: "#06b6d4",
  text: "#e2e8f0", dim: "#64748b", glow: (c, s = 8) => `0 0 ${s}px ${c}40`,
};

// ─── LARGE METRIC CARD ─────────────────────────────────────────────────────
function MetricCard({ label, value, unit, color = T.accent, icon, alert, sub }) {
  const c = alert ? T.red : color;
  return (
    <div style={{
      background: `linear-gradient(135deg, ${c}08, ${c}03)`,
      border: `1px solid ${c}30`, borderRadius: 8, padding: "14px 16px",
      position: "relative", overflow: "hidden", minWidth: 0,
    }}>
      <div style={{ position: "absolute", top: 0, left: 0, right: 0, height: 2, background: `linear-gradient(90deg, transparent, ${c}60, transparent)` }} />
      <div style={{ display: "flex", alignItems: "center", gap: 6, marginBottom: 6 }}>
        {icon && <span style={{ fontSize: 16 }}>{icon}</span>}
        <span style={{ fontSize: 11, fontWeight: 600, color: T.dim, textTransform: "uppercase", letterSpacing: "0.1em" }}>{label}</span>
      </div>
      <div style={{ display: "flex", alignItems: "baseline", gap: 4 }}>
        <span style={{ fontSize: 36, fontWeight: 800, color: c, fontFamily: "'JetBrains Mono', 'Fira Code', monospace", lineHeight: 1, textShadow: T.glow(c, 12) }}>
          {value}
        </span>
        {unit && <span style={{ fontSize: 14, color: T.dim, fontWeight: 600 }}>{unit}</span>}
      </div>
      {sub && <div style={{ fontSize: 10, color: T.dim, marginTop: 4 }}>{sub}</div>}
    </div>
  );
}

// ─── PHASE BADGE ───────────────────────────────────────────────────────────
function PhaseBadge({ phase }) {
  const name = PHASES[phase] || "UNKNOWN";
  const c = PHASE_COLORS[name] || T.dim;
  return (
    <div style={{
      display: "inline-flex", alignItems: "center", gap: 8, padding: "8px 16px",
      background: `${c}18`, border: `2px solid ${c}`, borderRadius: 6,
      boxShadow: T.glow(c, 16),
    }}>
      <div style={{
        width: 10, height: 10, borderRadius: "50%", background: c,
        boxShadow: `0 0 8px ${c}`, animation: name === "OPERATIONS" ? "pulse 2s ease infinite" : "none",
      }} />
      <span style={{ fontSize: 18, fontWeight: 800, color: c, letterSpacing: "0.15em", fontFamily: "'JetBrains Mono', monospace" }}>{name}</span>
    </div>
  );
}

// ─── DRONE ROW ─────────────────────────────────────────────────────────────
function DroneRow({ drone, index }) {
  const bat = drone.battery_percent ?? 100;
  const batColor = bat > 60 ? T.green : bat > 30 ? T.accent : T.red;
  const mode = FLIGHT_MODES[drone.flight_mode] || "UNK";
  return (
    <div style={{
      display: "grid", gridTemplateColumns: "32px 1fr 70px 90px 64px", gap: 8, alignItems: "center",
      padding: "8px 10px", background: index % 2 === 0 ? "#ffffff04" : "transparent", borderRadius: 4,
    }}>
      <div style={{
        width: 28, height: 28, borderRadius: "50%",
        background: drone.role === 1 ? `${T.cyan}30` : `${T.accent}20`,
        border: `2px solid ${drone.role === 1 ? T.cyan : T.accent}`,
        display: "flex", alignItems: "center", justifyContent: "center",
        fontSize: 12, fontWeight: 800, color: drone.role === 1 ? T.cyan : T.accent,
      }}>
        {drone.role === 1 ? "H" : drone.drone_id}
      </div>
      <div style={{ fontSize: 11, color: T.dim, fontFamily: "monospace" }}>
        ({drone.position?.x?.toFixed(0) ?? 0}, {drone.position?.y?.toFixed(0) ?? 0}, {drone.position?.z?.toFixed(0) ?? 0})
      </div>
      <div style={{ fontSize: 12, fontWeight: 700, color: T.blue, fontFamily: "monospace" }}>{mode}</div>
      <div style={{ display: "flex", alignItems: "center", gap: 4 }}>
        <div style={{ flex: 1, height: 6, background: "#1e293b", borderRadius: 3, overflow: "hidden" }}>
          <div style={{ width: `${bat}%`, height: "100%", background: batColor, borderRadius: 3, transition: "width 0.5s" }} />
        </div>
        <span style={{ fontSize: 11, fontWeight: 700, color: batColor, fontFamily: "monospace", minWidth: 28 }}>{bat.toFixed(0)}%</span>
      </div>
      <div style={{ fontSize: 11, color: T.dim, fontFamily: "monospace" }}>
        {(drone.signal_strength_dbm ?? -80).toFixed(0)} dBm
      </div>
    </div>
  );
}

// ─── DEAD ZONE PANEL ───────────────────────────────────────────────────────
function DeadZonePanel({ zones, onAdd, onClear }) {
  return (
    <div>
      <div style={{ display: "flex", gap: 6, marginBottom: 10 }}>
        <button onClick={onAdd} style={{
          flex: 1, padding: "8px 0", background: `${T.red}20`, border: `1px solid ${T.red}50`,
          borderRadius: 4, color: T.red, fontWeight: 700, fontSize: 12, cursor: "pointer",
          fontFamily: "'JetBrains Mono', monospace",
        }}>+ ADD ZONE</button>
        <button onClick={onClear} style={{
          flex: 1, padding: "8px 0", background: `${T.green}15`, border: `1px solid ${T.green}40`,
          borderRadius: 4, color: T.green, fontWeight: 700, fontSize: 12, cursor: "pointer",
          fontFamily: "'JetBrains Mono', monospace",
        }}>CLEAR ALL</button>
      </div>
      {zones.length === 0 ? (
        <div style={{ textAlign: "center", color: T.dim, fontSize: 12, padding: 16 }}>No active dead zones</div>
      ) : (
        <div style={{ display: "flex", flexDirection: "column", gap: 4, maxHeight: 150, overflowY: "auto" }}>
          {zones.map((z, i) => (
            <div key={i} style={{
              display: "flex", alignItems: "center", gap: 8, padding: "6px 8px",
              background: `${T.red}10`, border: `1px solid ${T.red}25`, borderRadius: 4,
            }}>
              <div style={{ width: 8, height: 8, borderRadius: "50%", background: T.red, boxShadow: `0 0 6px ${T.red}` }} />
              <span style={{ fontSize: 11, color: T.text, flex: 1, fontFamily: "monospace" }}>
                ({z.cx?.toFixed(0)}, {z.cy?.toFixed(0)}) r={z.radius?.toFixed(0)}m
              </span>
              <span style={{ fontSize: 10, color: T.red, fontWeight: 700 }}>-{z.attenuation_db?.toFixed(0)}dB</span>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

// ─── TACTICAL MAP ──────────────────────────────────────────────────────────
function TacticalMap({ drones, deadZones, coverage }) {
  const ref = useRef(null);

  useEffect(() => {
    const c = ref.current; if (!c) return;
    const dpr = window.devicePixelRatio || 2;
    const rect = c.getBoundingClientRect();
    c.width = rect.width * dpr; c.height = rect.height * dpr;
    const ctx = c.getContext("2d"); ctx.scale(dpr, dpr);
    const w = rect.width, h = rect.height, cx = w / 2, cy = h / 2;
    const R = Math.min(cx, cy) - 12;
    const AREA = 200;
    const toScreen = (wx, wy) => [cx + (wx / AREA) * R, cy - (wy / AREA) * R];

    // Background
    ctx.fillStyle = "#060a10"; ctx.fillRect(0, 0, w, h);

    // Grid
    ctx.strokeStyle = "#1a2430"; ctx.lineWidth = 0.5;
    for (let i = -200; i <= 200; i += 50) {
      const [x1, y1] = toScreen(i, -200);
      const [x2, y2] = toScreen(i, 200);
      ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke();
      const [x3, y3] = toScreen(-200, i);
      const [x4, y4] = toScreen(200, i);
      ctx.beginPath(); ctx.moveTo(x3, y3); ctx.lineTo(x4, y4); ctx.stroke();
    }

    // Range rings
    ctx.strokeStyle = "#1e2a3820"; ctx.lineWidth = 1;
    [50, 100, 150, 200].forEach(r => {
      ctx.beginPath(); ctx.arc(cx, cy, (r / AREA) * R, 0, Math.PI * 2); ctx.stroke();
    });

    // Axis labels
    ctx.fillStyle = "#475569"; ctx.font = "10px monospace"; ctx.textAlign = "center";
    [-200, -100, 0, 100, 200].forEach(v => {
      const [x] = toScreen(v, -200);
      ctx.fillText(`${v}m`, x, cy + R + 10);
    });

    // Dead zones (draw BEFORE drones)
    deadZones.forEach(z => {
      const [zx, zy] = toScreen(z.cx || 0, z.cy || 0);
      const zr = ((z.radius || 30) / AREA) * R;
      // Fill
      const grad = ctx.createRadialGradient(zx, zy, 0, zx, zy, zr);
      grad.addColorStop(0, "rgba(239, 68, 68, 0.25)");
      grad.addColorStop(0.7, "rgba(239, 68, 68, 0.10)");
      grad.addColorStop(1, "rgba(239, 68, 68, 0.02)");
      ctx.fillStyle = grad; ctx.beginPath(); ctx.arc(zx, zy, zr, 0, Math.PI * 2); ctx.fill();
      // Border
      ctx.strokeStyle = "#ef444480"; ctx.lineWidth = 2; ctx.setLineDash([4, 4]);
      ctx.beginPath(); ctx.arc(zx, zy, zr, 0, Math.PI * 2); ctx.stroke();
      ctx.setLineDash([]);
      // Label
      ctx.fillStyle = "#ef4444"; ctx.font = "bold 10px monospace"; ctx.textAlign = "center";
      ctx.fillText(`-${(z.attenuation_db || 0).toFixed(0)}dB`, zx, zy + 4);
    });

    // Mesh links
    if (drones.length > 1) {
      ctx.strokeStyle = "#10b98130"; ctx.lineWidth = 1;
      for (let i = 0; i < drones.length; i++) {
        for (let j = i + 1; j < drones.length; j++) {
          const dx = (drones[i].x || 0) - (drones[j].x || 0);
          const dy = (drones[i].y || 0) - (drones[j].y || 0);
          const dist = Math.sqrt(dx * dx + dy * dy);
          if (dist < 150) {
            const [x1, y1] = toScreen(drones[i].x || 0, drones[i].y || 0);
            const [x2, y2] = toScreen(drones[j].x || 0, drones[j].y || 0);
            ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke();
          }
        }
      }
    }

    // Drones
    drones.forEach((d, i) => {
      const [dx, dy] = toScreen(d.x || 0, d.y || 0);
      const isHub = d.role === 1;
      const dc = isHub ? T.cyan : T.accent;

      // Coverage circle (faint)
      const covR = ((d.z || 25) * 1.5 / AREA) * R;
      ctx.fillStyle = `${dc}08`; ctx.beginPath(); ctx.arc(dx, dy, covR, 0, Math.PI * 2); ctx.fill();

      // Drone marker
      ctx.fillStyle = dc; ctx.strokeStyle = dc; ctx.lineWidth = 2;
      if (isHub) {
        // Diamond for hub
        ctx.beginPath(); ctx.moveTo(dx, dy - 8); ctx.lineTo(dx + 8, dy); ctx.lineTo(dx, dy + 8); ctx.lineTo(dx - 8, dy); ctx.closePath(); ctx.fill();
      } else {
        ctx.beginPath(); ctx.arc(dx, dy, 6, 0, Math.PI * 2); ctx.fill();
      }

      // Label
      ctx.fillStyle = "#000"; ctx.font = "bold 9px monospace"; ctx.textAlign = "center"; ctx.textBaseline = "middle";
      ctx.fillText(isHub ? "H" : `${d.id ?? i}`, dx, dy);

      // Altitude label
      ctx.fillStyle = T.dim; ctx.font = "9px monospace"; ctx.textBaseline = "top";
      ctx.fillText(`${(d.z || 0).toFixed(0)}m`, dx, dy + 10);
    });

    // Crosshair at origin
    ctx.strokeStyle = "#334155"; ctx.lineWidth = 1;
    ctx.beginPath(); ctx.moveTo(cx - 8, cy); ctx.lineTo(cx + 8, cy); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(cx, cy - 8); ctx.lineTo(cx, cy + 8); ctx.stroke();

  }, [drones, deadZones, coverage]);

  return <canvas ref={ref} style={{ width: "100%", height: "100%", borderRadius: 6 }} />;
}

// ─── COVERAGE BAR ──────────────────────────────────────────────────────────
function CoverageBar({ value, target = 80, label }) {
  const c = value >= target ? T.green : value >= 60 ? T.accent : T.red;
  return (
    <div style={{ marginBottom: 6 }}>
      {label && <div style={{ fontSize: 10, color: T.dim, marginBottom: 3, fontWeight: 600 }}>{label}</div>}
      <div style={{ position: "relative", height: 10, background: "#1e293b", borderRadius: 5, overflow: "hidden" }}>
        <div style={{ width: `${Math.min(value, 100)}%`, height: "100%", background: c, borderRadius: 5, transition: "width 0.5s, background 0.3s", boxShadow: `0 0 8px ${c}40` }} />
        <div style={{ position: "absolute", left: `${target}%`, top: 0, bottom: 0, width: 2, background: "#ffffff30" }} />
      </div>
    </div>
  );
}

// ─── EVENT LOG ─────────────────────────────────────────────────────────────
function EventLog({ events }) {
  const ref = useRef(null);
  useEffect(() => { ref.current?.scrollTo(0, ref.current.scrollHeight); }, [events]);
  return (
    <div ref={ref} style={{ maxHeight: 130, overflowY: "auto", fontSize: 10, fontFamily: "monospace", color: T.dim }}>
      {events.slice(-20).map((e, i) => (
        <div key={i} style={{ padding: "2px 0", borderBottom: `1px solid ${T.border}` }}>
          <span style={{ color: e.color || T.dim }}>{e.time}</span>
          <span style={{ marginLeft: 6, color: e.color || T.text }}>{e.msg}</span>
        </div>
      ))}
    </div>
  );
}

// ─── MAIN DASHBOARD ────────────────────────────────────────────────────────
export default function AURADashboard() {
  const [rosStatus, setRosStatus] = useState("disconnected");
  const [phase, setPhase] = useState(0);
  const [coverage, setCoverage] = useState(0);
  const [drones, setDrones] = useState([]);
  const [droneData, setDroneData] = useState([]);
  const [network, setNetwork] = useState({});
  const [deadZones, setDeadZones] = useState([]);
  const [events, setEvents] = useState([{ time: "00:00", msg: "Dashboard initialized", color: T.dim }]);
  const [tick, setTick] = useState(0);
  const [simMode, setSimMode] = useState(true);
  const bridge = useRef(null);
  const startTime = useRef(Date.now());

  const logEvent = useCallback((msg, color) => {
    const t = ((Date.now() - startTime.current) / 1000).toFixed(0);
    const m = Math.floor(t / 60); const s = t % 60;
    setEvents(prev => [...prev.slice(-50), { time: `${String(m).padStart(2,"0")}:${String(s).padStart(2,"0")}`, msg, color }]);
  }, []);

  // Rosbridge connection
  useEffect(() => {
    const b = new RosBridge("ws://localhost:9090");
    bridge.current = b;
    b.onStatus = (s) => {
      setRosStatus(s);
      if (s === "connected") {
        setSimMode(false);
        logEvent("Rosbridge connected", T.green);
        b.subscribe("/mission/status", "aura_msgs/msg/MissionStatus", (msg) => {
          setPhase(msg.phase ?? 0);
          setCoverage(msg.coverage_achieved ?? 0);
        });
        b.subscribe("/swarm/state", "aura_msgs/msg/SwarmState", (msg) => {
          const dd = (msg.drones || []).map(d => ({
            id: d.drone_id, x: d.position?.x || 0, y: d.position?.y || 0, z: d.position?.z || 0,
            battery_percent: d.battery_percent, flight_mode: d.flight_mode,
            signal_strength_dbm: d.signal_strength_dbm, role: d.role,
            throughput_mbps: d.throughput_mbps, latency_ms: d.latency_ms,
            connected_neighbors: d.connected_neighbors, position: d.position,
            velocity: d.velocity, drone_id: d.drone_id,
          }));
          setDrones(dd);
          setDroneData(msg.drones || []);
        });
        b.subscribe("/network/metrics", "aura_msgs/msg/NetworkMetrics", (msg) => {
          setNetwork({
            coverage: msg.total_coverage_percent, signal: msg.avg_signal_strength_dbm,
            throughput: msg.avg_throughput_mbps, latency: msg.avg_latency_ms,
            links: msg.link_from_drone?.length || 0, mesh: msg.mesh_connected,
          });
        });
        b.subscribe("/weather/zones", "aura_msgs/msg/WeatherZone", (msg) => {
          if (!msg.is_active) {
            setDeadZones(prev => prev.filter(z => !(Math.abs(z.cx - (msg.center?.x||0)) < 1 && Math.abs(z.cy - (msg.center?.y||0)) < 1)));
          } else {
            setDeadZones(prev => {
              const existing = prev.findIndex(z => Math.abs(z.cx - (msg.center?.x||0)) < 1 && Math.abs(z.cy - (msg.center?.y||0)) < 1);
              const zone = { cx: msg.center?.x || 0, cy: msg.center?.y || 0, radius: msg.radius_meters, attenuation_db: msg.signal_attenuation_db };
              if (existing >= 0) { const n = [...prev]; n[existing] = zone; return n; }
              return [...prev, zone];
            });
          }
        });
      }
    };
    b.connect();
    return () => b.disconnect();
  }, [logEvent]);

  // Simulation mode (demo data when no rosbridge)
  useEffect(() => {
    if (!simMode) return;
    const iv = setInterval(() => {
      setTick(t => t + 1);
      setPhase(5); // OPERATIONS
      setCoverage(prev => Math.min(100, prev + (prev < 95 ? 2 : 0.1)));
      setDrones([
        { id: 0, x: 40, y: 0, z: 25, battery_percent: 92, flight_mode: 3, signal_strength_dbm: -68, role: 1, position: { x: 40, y: 0, z: 25 }, drone_id: 0 },
        { id: 1, x: 12, y: 38, z: 15, battery_percent: 88, flight_mode: 3, signal_strength_dbm: -72, role: 0, position: { x: 12, y: 38, z: 15 }, drone_id: 1 },
        { id: 2, x: -32, y: 23, z: 15, battery_percent: 91, flight_mode: 3, signal_strength_dbm: -71, role: 0, position: { x: -32, y: 23, z: 15 }, drone_id: 2 },
        { id: 3, x: -32, y: -24, z: 15, battery_percent: 85, flight_mode: 3, signal_strength_dbm: -73, role: 0, position: { x: -32, y: -24, z: 15 }, drone_id: 3 },
        { id: 4, x: 12, y: -38, z: 15, battery_percent: 89, flight_mode: 3, signal_strength_dbm: -70, role: 0, position: { x: 12, y: -38, z: 15 }, drone_id: 4 },
      ]);
      setNetwork({ coverage: 100, signal: -73.9, throughput: 103.8, latency: 6.0, links: 10, mesh: true });
    }, 1000);
    return () => clearInterval(iv);
  }, [simMode]);

  const handleAddZone = async () => {
    try {
      if (bridge.current?.connected) {
        await bridge.current.callService("/dead_zone_publisher/add_random_zone", "std_srvs/srv/Trigger");
        logEvent("Dead zone injected", T.red);
      } else {
        // Demo mode
        const cx = (Math.random() - 0.5) * 200;
        const cy = (Math.random() - 0.5) * 200;
        setDeadZones(prev => [...prev, { cx, cy, radius: 20 + Math.random() * 30, attenuation_db: 12 + Math.random() * 18 }]);
        setCoverage(prev => Math.max(50, prev - 5 - Math.random() * 10));
        logEvent(`Dead zone at (${cx.toFixed(0)}, ${cy.toFixed(0)})`, T.red);
      }
    } catch { logEvent("Failed to inject zone", T.red); }
  };

  const handleClearZones = async () => {
    try {
      if (bridge.current?.connected) {
        await bridge.current.callService("/dead_zone_publisher/clear_zones", "std_srvs/srv/Trigger");
      }
      setDeadZones([]);
      logEvent("Dead zones cleared", T.green);
    } catch { logEvent("Failed to clear zones", T.red); }
  };

  const phaseName = PHASES[phase] || "UNKNOWN";
  const phaseColor = PHASE_COLORS[phaseName] || T.dim;
  const covColor = coverage >= 80 ? T.green : coverage >= 60 ? T.accent : T.red;
  const avgBat = drones.length > 0 ? drones.reduce((s, d) => s + (d.battery_percent || 0), 0) / drones.length : 0;

  return (
    <div style={{
      minHeight: "100vh", background: T.bg, color: T.text, padding: 16,
      fontFamily: "'JetBrains Mono', 'Fira Code', 'Cascadia Code', monospace",
    }}>
      <style>{`
        @import url('https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;600;700;800&display=swap');
        @keyframes pulse { 0%, 100% { opacity: 1; } 50% { opacity: 0.5; } }
        * { box-sizing: border-box; }
        ::-webkit-scrollbar { width: 4px; } ::-webkit-scrollbar-thumb { background: ${T.border}; border-radius: 2px; }
      `}</style>

      {/* HEADER */}
      <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", marginBottom: 16, padding: "8px 0", borderBottom: `1px solid ${T.border}` }}>
        <div style={{ display: "flex", alignItems: "center", gap: 12 }}>
          <div style={{ fontSize: 24, fontWeight: 800, color: T.accent, letterSpacing: "0.1em" }}>A.U.R.A.</div>
          <div style={{ fontSize: 11, color: T.dim, maxWidth: 200 }}>Autonomous Urban Rescue Array</div>
        </div>
        <div style={{ display: "flex", alignItems: "center", gap: 16 }}>
          <PhaseBadge phase={phase} />
          <div style={{ display: "flex", alignItems: "center", gap: 6 }}>
            <div style={{ width: 8, height: 8, borderRadius: "50%", background: rosStatus === "connected" ? T.green : T.red, boxShadow: `0 0 6px ${rosStatus === "connected" ? T.green : T.red}` }} />
            <span style={{ fontSize: 11, color: rosStatus === "connected" ? T.green : T.dim }}>
              {rosStatus === "connected" ? "LIVE" : simMode ? "DEMO" : "OFFLINE"}
            </span>
          </div>
        </div>
      </div>

      {/* TOP METRICS ROW — large, visible from distance */}
      <div style={{ display: "grid", gridTemplateColumns: "repeat(6, 1fr)", gap: 10, marginBottom: 16 }}>
        <MetricCard label="Coverage" value={coverage.toFixed(1)} unit="%" color={covColor} icon="📡"
          alert={coverage < 80} sub={coverage < 80 ? "Below target!" : "Target: 80%"} />
        <MetricCard label="Signal" value={(network.signal || -80).toFixed(1)} unit="dBm" color={T.blue} icon="📶" />
        <MetricCard label="Throughput" value={(network.throughput || 0).toFixed(0)} unit="Mbps" color={T.cyan} icon="⚡" />
        <MetricCard label="Latency" value={(network.latency || 0).toFixed(1)} unit="ms" color={T.accent} icon="⏱" />
        <MetricCard label="Mesh Links" value={network.links || 0} unit="" color={network.mesh ? T.green : T.red} icon="🔗"
          alert={!network.mesh} sub={network.mesh ? "Fully connected" : "DISCONNECTED"} />
        <MetricCard label="Avg Battery" value={avgBat.toFixed(0)} unit="%" color={avgBat > 60 ? T.green : avgBat > 30 ? T.accent : T.red} icon="🔋" />
      </div>

      {/* MAIN CONTENT — 3 columns */}
      <div style={{ display: "grid", gridTemplateColumns: "280px 1fr 280px", gap: 12, height: "calc(100vh - 220px)", minHeight: 400 }}>

        {/* LEFT COLUMN — Drones + Dead Zones */}
        <div style={{ display: "flex", flexDirection: "column", gap: 12 }}>
          {/* Drones */}
          <div style={{ background: T.panel, border: `1px solid ${T.border}`, borderRadius: 8, padding: 12, flex: 1 }}>
            <div style={{ fontSize: 11, fontWeight: 700, color: T.accent, letterSpacing: "0.12em", textTransform: "uppercase", marginBottom: 8, paddingBottom: 6, borderBottom: `1px solid ${T.border}` }}>
              SWARM STATUS ({drones.length} drones)
            </div>
            <div style={{ display: "flex", flexDirection: "column", gap: 2 }}>
              {drones.map((d, i) => <DroneRow key={d.id ?? i} drone={d} index={i} />)}
            </div>
          </div>

          {/* Dead Zones */}
          <div style={{ background: T.panel, border: `1px solid ${T.border}`, borderRadius: 8, padding: 12 }}>
            <div style={{ fontSize: 11, fontWeight: 700, color: T.red, letterSpacing: "0.12em", textTransform: "uppercase", marginBottom: 8, paddingBottom: 6, borderBottom: `1px solid ${T.border}` }}>
              DEAD ZONES ({deadZones.length})
            </div>
            <DeadZonePanel zones={deadZones} onAdd={handleAddZone} onClear={handleClearZones} />
          </div>
        </div>

        {/* CENTER — Tactical Map */}
        <div style={{ background: T.panel, border: `1px solid ${T.border}`, borderRadius: 8, padding: 8, position: "relative" }}>
          <div style={{ position: "absolute", top: 8, left: 12, fontSize: 10, fontWeight: 700, color: T.dim, letterSpacing: "0.12em", textTransform: "uppercase", zIndex: 1 }}>
            TACTICAL MAP
          </div>
          <TacticalMap drones={drones} deadZones={deadZones} coverage={coverage} />
        </div>

        {/* RIGHT COLUMN — Coverage + Events */}
        <div style={{ display: "flex", flexDirection: "column", gap: 12 }}>
          {/* Coverage Details */}
          <div style={{ background: T.panel, border: `1px solid ${T.border}`, borderRadius: 8, padding: 12 }}>
            <div style={{ fontSize: 11, fontWeight: 700, color: T.green, letterSpacing: "0.12em", textTransform: "uppercase", marginBottom: 10, paddingBottom: 6, borderBottom: `1px solid ${T.border}` }}>
              COVERAGE ANALYSIS
            </div>
            <CoverageBar value={coverage} target={80} label="Total Coverage" />
            <div style={{ display: "grid", gridTemplateColumns: "1fr 1fr", gap: 8, marginTop: 10 }}>
              <div style={{ background: `${T.blue}10`, border: `1px solid ${T.blue}20`, borderRadius: 4, padding: 8, textAlign: "center" }}>
                <div style={{ fontSize: 9, color: T.dim, marginBottom: 2 }}>DRONES UP</div>
                <div style={{ fontSize: 22, fontWeight: 800, color: T.blue }}>{drones.length}</div>
              </div>
              <div style={{ background: `${T.red}10`, border: `1px solid ${T.red}20`, borderRadius: 4, padding: 8, textAlign: "center" }}>
                <div style={{ fontSize: 9, color: T.dim, marginBottom: 2 }}>DEAD ZONES</div>
                <div style={{ fontSize: 22, fontWeight: 800, color: deadZones.length > 0 ? T.red : T.dim }}>{deadZones.length}</div>
              </div>
            </div>
            {/* Network health indicator */}
            <div style={{ marginTop: 12, padding: 8, background: network.mesh ? `${T.green}08` : `${T.red}12`, border: `1px solid ${network.mesh ? T.green : T.red}30`, borderRadius: 4 }}>
              <div style={{ display: "flex", alignItems: "center", gap: 6 }}>
                <div style={{ width: 8, height: 8, borderRadius: "50%", background: network.mesh ? T.green : T.red, animation: "pulse 2s ease infinite" }} />
                <span style={{ fontSize: 12, fontWeight: 700, color: network.mesh ? T.green : T.red }}>
                  {network.mesh ? "MESH CONNECTED" : "MESH BROKEN"}
                </span>
              </div>
            </div>
          </div>

          {/* Event Log */}
          <div style={{ background: T.panel, border: `1px solid ${T.border}`, borderRadius: 8, padding: 12, flex: 1 }}>
            <div style={{ fontSize: 11, fontWeight: 700, color: T.dim, letterSpacing: "0.12em", textTransform: "uppercase", marginBottom: 8, paddingBottom: 6, borderBottom: `1px solid ${T.border}` }}>
              EVENT LOG
            </div>
            <EventLog events={events} />
          </div>
        </div>
      </div>
    </div>
  );
}
