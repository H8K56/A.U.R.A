import { useState, useEffect, useRef, useCallback } from "react";

// ─── rosbridge ─────────────────────────────────────────────────────────────
class RosBridge {
  constructor(url = "ws://localhost:9090") {
    this.url = url; this.ws = null; this.subs = {}; this.idCounter = 0;
    this.connected = false; this.onStatusChange = null; this.reconnectTimer = null;
  }
  connect() {
    try {
      this.ws = new WebSocket(this.url);
      this.ws.onopen = () => { this.connected = true; this.onStatusChange?.("connected"); Object.entries(this.subs).forEach(([t, s]) => this._sub(t, s.type)); };
      this.ws.onmessage = (e) => { try { const d = JSON.parse(e.data); if (d.op === "publish" && this.subs[d.topic]) this.subs[d.topic].cb(d.msg); } catch {} };
      this.ws.onclose = () => { this.connected = false; this.onStatusChange?.("disconnected"); this.reconnectTimer = setTimeout(() => this.connect(), 3000); };
      this.ws.onerror = () => { this.connected = false; this.onStatusChange?.("error"); };
    } catch { this.onStatusChange?.("error"); }
  }
  subscribe(topic, type, cb) { this.subs[topic] = { type, cb }; if (this.connected) this._sub(topic, type); }
  _sub(topic, type) { this.ws?.send(JSON.stringify({ op: "subscribe", id: `s${this.idCounter++}`, topic, type, throttle_rate: 150 })); }
  callService(svc, type, req = {}) {
    return new Promise((res, rej) => {
      const id = `v${this.idCounter++}`;
      const h = (e) => { try { const d = JSON.parse(e.data); if (d.op === "service_response" && d.id === id) { this.ws.removeEventListener("message", h); res(d.values); } } catch {} };
      this.ws?.addEventListener("message", h);
      this.ws?.send(JSON.stringify({ op: "call_service", id, service: svc, type, args: req }));
      setTimeout(() => { this.ws?.removeEventListener("message", h); rej("timeout"); }, 5000);
    });
  }
  publish(topic, type, msg) { this.ws?.send(JSON.stringify({ op: "publish", topic, type, msg })); }
  disconnect() { clearTimeout(this.reconnectTimer); this.ws?.close(); }
}

const PHASES = ["IDLE","PREFLIGHT","TAKEOFF","TRANSIT","FORMATION","OPERATIONS","RTL","LANDED"];
const PC = { IDLE:"#475569",PREFLIGHT:"#d97706",TAKEOFF:"#2563eb",TRANSIT:"#7c3aed",FORMATION:"#0891b2",OPERATIONS:"#059669",RTL:"#ea580c",LANDED:"#64748b" };
const FM = { 0:"IDLE",1:"TKOFF",2:"LOITER",3:"MSN",4:"RTL",5:"LAND" };

// ─── HEX FRAME ─────────────────────────────────────────────────────────────
function HexFrame({ title, children, color = "#f59e0b", alert, style = {} }) {
  const c = alert ? "#dc2626" : color;
  return (
    <div style={{ position: "relative", border: `1px solid ${c}30`, background: `${c}06`, ...style }}>
      {/* Corner cuts */}
      <div style={{ position: "absolute", top: -1, left: -1, width: 12, height: 12, borderTop: `2px solid ${c}60`, borderLeft: `2px solid ${c}60` }} />
      <div style={{ position: "absolute", top: -1, right: -1, width: 12, height: 12, borderTop: `2px solid ${c}60`, borderRight: `2px solid ${c}60` }} />
      <div style={{ position: "absolute", bottom: -1, left: -1, width: 8, height: 8, borderBottom: `1px solid ${c}30`, borderLeft: `1px solid ${c}30` }} />
      <div style={{ position: "absolute", bottom: -1, right: -1, width: 8, height: 8, borderBottom: `1px solid ${c}30`, borderRight: `1px solid ${c}30` }} />
      {title && (
        <div style={{ position: "absolute", top: -8, left: 16, background: "#080c10", padding: "0 6px", fontSize: 8, fontWeight: 700, color: c, letterSpacing: "0.15em", textTransform: "uppercase" }}>
          {alert && <span style={{ marginRight: 4, animation: "blink 0.8s ease infinite" }}>⚠</span>}{title}
        </div>
      )}
      <div style={{ padding: "12px 10px 8px" }}>{children}</div>
    </div>
  );
}

// ─── RADAR ──────────────────────────────────────────────────────────────────
function TacticalRadar({ drones, deadZones, coverage, tick, actionVectors }) {
  const ref = useRef(null);
  const trails = useRef({});
  const sweep = useRef(0);

  useEffect(() => {
    const c = ref.current; if (!c) return;
    const dpr = window.devicePixelRatio || 2;
    const rect = c.getBoundingClientRect();
    c.width = rect.width * dpr; c.height = rect.height * dpr;
    const ctx = c.getContext("2d"); ctx.scale(dpr, dpr);
    const w = rect.width, h = rect.height, cx = w / 2, cy = h / 2;
    const R = Math.min(cx, cy) - 6;

    const xs = drones.map(d => d.x), ys = drones.map(d => d.y);
    const span = drones.length > 0 ? Math.max(Math.max(...xs) - Math.min(...xs), Math.max(...ys) - Math.min(...ys), 40) / 2 + 25 : 60;
    const oxW = drones.length > 0 ? (Math.min(...xs) + Math.max(...xs)) / 2 : 0;
    const oyW = drones.length > 0 ? (Math.min(...ys) + Math.max(...ys)) / 2 : 0;
    const toR = (wx, wy) => [cx + ((wx - oxW) / span) * R * 0.85, cy - ((wy - oyW) / span) * R * 0.85];

    // BG
    ctx.fillStyle = "#060a10"; ctx.fillRect(0, 0, w, h);

    // Hex grid pattern (subtle)
    ctx.strokeStyle = "rgba(245, 158, 11, 0.03)";
    ctx.lineWidth = 0.3;
    const hexR = 20;
    for (let hx = 0; hx < w; hx += hexR * 1.73) {
      for (let hy = 0; hy < h; hy += hexR * 1.5) {
        const offsetX = (Math.floor(hy / (hexR * 1.5)) % 2) * hexR * 0.866;
        const px = hx + offsetX, py = hy;
        if (Math.hypot(px - cx, py - cy) < R + 10) {
          ctx.beginPath();
          for (let i = 0; i < 6; i++) {
            const a = Math.PI / 3 * i - Math.PI / 6;
            const vx = px + hexR * 0.4 * Math.cos(a), vy = py + hexR * 0.4 * Math.sin(a);
            i === 0 ? ctx.moveTo(vx, vy) : ctx.lineTo(vx, vy);
          }
          ctx.closePath(); ctx.stroke();
        }
      }
    }

    // Range rings
    for (let i = 1; i <= 3; i++) {
      const r = (R * i) / 3;
      ctx.beginPath(); ctx.arc(cx, cy, r, 0, Math.PI * 2);
      ctx.strokeStyle = `rgba(245, 158, 11, ${i === 3 ? 0.15 : 0.05})`;
      ctx.lineWidth = i === 3 ? 1 : 0.5; ctx.stroke();
    }
    // Cross
    ctx.strokeStyle = "rgba(245, 158, 11, 0.06)"; ctx.lineWidth = 0.5;
    ctx.beginPath(); ctx.moveTo(cx - R, cy); ctx.lineTo(cx + R, cy); ctx.stroke();
    ctx.beginPath(); ctx.moveTo(cx, cy - R); ctx.lineTo(cx, cy + R); ctx.stroke();

    // Sweep
    sweep.current = (sweep.current + 0.025) % (Math.PI * 2);
    const sa = sweep.current;
    ctx.beginPath(); ctx.moveTo(cx, cy);
    ctx.lineTo(cx + Math.cos(sa) * R, cy + Math.sin(sa) * R);
    ctx.strokeStyle = "rgba(245, 158, 11, 0.25)"; ctx.lineWidth = 1; ctx.stroke();

    // Coverage heatmap
    if (coverage?.data?.length > 0) {
      const cols = coverage.width || 20, rows = coverage.height || 20;
      for (let r = 0; r < rows; r++) for (let c2 = 0; c2 < cols; c2++) {
        const v = coverage.data[r * cols + c2] || 0;
        if (v > 0.05) {
          const wx = oxW - span + (c2 / cols) * span * 2, wy = oyW - span + (r / rows) * span * 2;
          const [sx, sy] = toR(wx, wy);
          if (Math.hypot(sx - cx, sy - cy) < R) {
            const cr = (R * 0.85 / cols) * 1.2;
            ctx.fillStyle = v > 0.7 ? `rgba(16,185,129,${v * 0.1})` : v > 0.4 ? `rgba(245,158,11,${v * 0.08})` : `rgba(220,38,38,${v * 0.06})`;
            ctx.fillRect(sx - cr / 2, sy - cr / 2, cr, cr);
          }
        }
      }
    }

    // Dead zones
    deadZones.forEach(dz => {
      const [dx2, dy2] = toR(dz.x, dz.y);
      const dr = (dz.radius / span) * R * 0.85;
      ctx.save(); ctx.beginPath(); ctx.arc(dx2, dy2, dr, 0, Math.PI * 2); ctx.clip();
      ctx.strokeStyle = "rgba(220,38,38,0.15)"; ctx.lineWidth = 0.5;
      for (let l = -dr * 2; l < dr * 2; l += 5) { ctx.beginPath(); ctx.moveTo(dx2 + l, dy2 - dr); ctx.lineTo(dx2 + l + dr, dy2 + dr); ctx.stroke(); }
      ctx.restore();
      ctx.beginPath(); ctx.arc(dx2, dy2, dr, 0, Math.PI * 2);
      ctx.strokeStyle = `rgba(220,38,38,${0.4 + Math.sin(tick * 0.15) * 0.2})`;
      ctx.lineWidth = 1.5; ctx.setLineDash([3, 3]); ctx.stroke(); ctx.setLineDash([]);
      ctx.fillStyle = `rgba(220,38,38,${0.5 + Math.sin(tick * 0.15) * 0.2})`;
      ctx.font = "bold 7px monospace"; ctx.textAlign = "center";
      ctx.fillText("DEAD ZONE", dx2, dy2 - dr - 4);
    });

    // Mesh links + particles
    if (drones.length > 1) for (let i = 0; i < drones.length; i++) for (let j = i + 1; j < drones.length; j++) {
      const dist = Math.hypot(drones[i].x - drones[j].x, drones[i].y - drones[j].y);
      if (dist < 150) {
        const [x1, y1] = toR(drones[i].x, drones[i].y), [x2, y2] = toR(drones[j].x, drones[j].y);
        const str = Math.max(0, 1 - dist / 150);
        ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2);
        ctx.strokeStyle = `rgba(245,158,11,${str * 0.2})`; ctx.lineWidth = str * 1.5; ctx.stroke();
        const pp = ((tick * 0.02 + i * 0.3 + j * 0.7) % 1);
        ctx.fillStyle = `rgba(245,158,11,${str * 0.5})`;
        ctx.beginPath(); ctx.arc(x1 + (x2 - x1) * pp, y1 + (y2 - y1) * pp, 1.5, 0, Math.PI * 2); ctx.fill();
      }
    }

    // Trails
    drones.forEach(d => {
      if (!trails.current[d.id]) trails.current[d.id] = [];
      const t = trails.current[d.id]; t.push({ x: d.x, y: d.y }); if (t.length > 35) t.shift();
      if (t.length > 1) {
        ctx.beginPath(); t.forEach((p, i) => { const [sx, sy] = toR(p.x, p.y); i === 0 ? ctx.moveTo(sx, sy) : ctx.lineTo(sx, sy); });
        ctx.strokeStyle = d.role === 1 ? "rgba(245,158,11,0.12)" : "rgba(52,211,153,0.08)"; ctx.lineWidth = 1; ctx.stroke();
      }
    });

    // ACTION VECTORS — the RL's intended moves
    if (actionVectors && actionVectors.length === drones.length) {
      drones.forEach((d, i) => {
        const [sx, sy] = toR(d.x, d.y);
        const av = actionVectors[i];
        if (av) {
          const scale = 3;
          const ex = sx + av.dx * scale, ey = sy - av.dy * scale;
          // Chevron arrow
          ctx.beginPath(); ctx.moveTo(sx, sy); ctx.lineTo(ex, ey);
          ctx.strokeStyle = "rgba(56,189,248,0.7)"; ctx.lineWidth = 2; ctx.stroke();
          // Arrowhead
          const angle = Math.atan2(ey - sy, ex - sx);
          ctx.beginPath();
          ctx.moveTo(ex, ey);
          ctx.lineTo(ex - 6 * Math.cos(angle - 0.4), ey - 6 * Math.sin(angle - 0.4));
          ctx.moveTo(ex, ey);
          ctx.lineTo(ex - 6 * Math.cos(angle + 0.4), ey - 6 * Math.sin(angle + 0.4));
          ctx.strokeStyle = "rgba(56,189,248,0.8)"; ctx.lineWidth = 1.5; ctx.stroke();
        }
      });
    }

    // Drones
    drones.forEach(d => {
      const [sx, sy] = toR(d.x, d.y);
      const hub = d.role === 1; const col = hub ? "#f59e0b" : "#34d399";
      const low = d.battery < 25;

      // Targeting reticle
      const rr = 14 + Math.sin(tick * 0.08 + d.id) * 2;
      ctx.strokeStyle = low ? `rgba(220,38,38,${0.3 + Math.sin(tick * 0.3) * 0.2})` : `${col}25`;
      ctx.lineWidth = 1;
      // Top-left bracket
      ctx.beginPath(); ctx.moveTo(sx - rr, sy - rr + 4); ctx.lineTo(sx - rr, sy - rr); ctx.lineTo(sx - rr + 4, sy - rr); ctx.stroke();
      // Top-right
      ctx.beginPath(); ctx.moveTo(sx + rr - 4, sy - rr); ctx.lineTo(sx + rr, sy - rr); ctx.lineTo(sx + rr, sy - rr + 4); ctx.stroke();
      // Bottom-left
      ctx.beginPath(); ctx.moveTo(sx - rr, sy + rr - 4); ctx.lineTo(sx - rr, sy + rr); ctx.lineTo(sx - rr + 4, sy + rr); ctx.stroke();
      // Bottom-right
      ctx.beginPath(); ctx.moveTo(sx + rr - 4, sy + rr); ctx.lineTo(sx + rr, sy + rr); ctx.lineTo(sx + rr, sy + rr - 4); ctx.stroke();

      // Blip
      ctx.fillStyle = col;
      if (hub) { ctx.save(); ctx.translate(sx, sy); ctx.rotate(Math.PI / 4); ctx.fillRect(-4.5, -4.5, 9, 9); ctx.restore(); }
      else { ctx.beginPath(); ctx.arc(sx, sy, 3.5, 0, Math.PI * 2); ctx.fill(); }

      // Glow
      const g = ctx.createRadialGradient(sx, sy, 0, sx, sy, 10);
      g.addColorStop(0, `${col}25`); g.addColorStop(1, "transparent");
      ctx.fillStyle = g; ctx.beginPath(); ctx.arc(sx, sy, 10, 0, Math.PI * 2); ctx.fill();

      // Label
      ctx.fillStyle = col; ctx.font = "bold 8px monospace"; ctx.textAlign = "left";
      ctx.fillText(hub ? "HUB" : `U${d.id}`, sx + 16, sy - 8);
      ctx.fillStyle = "rgba(255,255,255,0.3)"; ctx.font = "7px monospace";
      ctx.fillText(`${d.z.toFixed(0)}m ${d.battery.toFixed(0)}%`, sx + 16, sy + 1);
    });

  }, [drones, deadZones, coverage, tick, actionVectors]);

  return <canvas ref={ref} style={{ width: "100%", height: "100%", display: "block" }} />;
}

// ─── REWARD BAR ─────────────────────────────────────────────────────────────
function RewardBar({ label, value, maxVal = 2, color, negative }) {
  const pct = Math.min(100, Math.abs(value) / maxVal * 100);
  return (
    <div style={{ display: "flex", alignItems: "center", gap: 6, marginBottom: 3 }}>
      <span style={{ fontSize: 7, color: "rgba(255,255,255,0.3)", width: 52, textAlign: "right", letterSpacing: "0.03em" }}>{label}</span>
      <div style={{ flex: 1, height: 6, background: "rgba(255,255,255,0.04)", borderRadius: 1, overflow: "hidden", position: "relative" }}>
        <div style={{
          position: "absolute", [negative ? "right" : "left"]: 0, top: 0, bottom: 0,
          width: `${pct}%`, background: color, opacity: 0.7,
          borderRadius: 1, transition: "width 0.3s ease",
        }} />
      </div>
      <span style={{ fontSize: 8, color, fontWeight: 700, minWidth: 32, textAlign: "right" }}>{negative ? "-" : "+"}{Math.abs(value).toFixed(2)}</span>
    </div>
  );
}

// ─── NEURAL PULSE (fake activation viz) ─────────────────────────────────────
function NeuralPulse({ tick, confidence }) {
  const ref = useRef(null);
  useEffect(() => {
    const c = ref.current; if (!c) return;
    const dpr = 2; const rect = c.getBoundingClientRect();
    c.width = rect.width * dpr; c.height = rect.height * dpr;
    const ctx = c.getContext("2d"); ctx.scale(dpr, dpr);
    const w = rect.width, h = rect.height;

    ctx.fillStyle = "#060a10"; ctx.fillRect(0, 0, w, h);

    // Network layers: 184 -> 256 -> 256 -> 15
    const layers = [184, 256, 256, 15];
    const layerX = layers.map((_, i) => 20 + (i / (layers.length - 1)) * (w - 40));
    const maxNodes = 12; // visual cap

    layers.forEach((size, li) => {
      const displayN = Math.min(size, maxNodes);
      const spacing = Math.min(14, (h - 20) / displayN);
      const startY = h / 2 - (displayN * spacing) / 2;

      for (let ni = 0; ni < displayN; ni++) {
        const nx = layerX[li];
        const ny = startY + ni * spacing + spacing / 2;

        // Activation level (simulated)
        const activation = 0.2 + 0.8 * Math.abs(Math.sin(tick * 0.07 + li * 1.3 + ni * 0.8));
        const isHot = activation > 0.7;

        // Connections to next layer
        if (li < layers.length - 1) {
          const nextN = Math.min(layers[li + 1], maxNodes);
          const nextSpacing = Math.min(14, (h - 20) / nextN);
          const nextStartY = h / 2 - (nextN * nextSpacing) / 2;
          for (let nj = 0; nj < nextN; nj += 2) { // sparse for perf
            const nnx = layerX[li + 1];
            const nny = nextStartY + nj * nextSpacing + nextSpacing / 2;
            const connStrength = Math.abs(Math.sin(tick * 0.04 + ni * 0.5 + nj * 0.3 + li * 2));
            if (connStrength > 0.4) {
              ctx.beginPath(); ctx.moveTo(nx, ny); ctx.lineTo(nnx, nny);
              ctx.strokeStyle = `rgba(245,158,11,${connStrength * 0.08})`;
              ctx.lineWidth = 0.5; ctx.stroke();
            }
          }
        }

        // Node
        ctx.fillStyle = isHot ? `rgba(245,158,11,${activation * 0.8})` : `rgba(245,158,11,${activation * 0.25})`;
        ctx.beginPath(); ctx.arc(nx, ny, isHot ? 3 : 2, 0, Math.PI * 2); ctx.fill();
        if (isHot) {
          const g = ctx.createRadialGradient(nx, ny, 0, nx, ny, 6);
          g.addColorStop(0, "rgba(245,158,11,0.2)"); g.addColorStop(1, "transparent");
          ctx.fillStyle = g; ctx.beginPath(); ctx.arc(nx, ny, 6, 0, Math.PI * 2); ctx.fill();
        }
      }

      // Layer label
      ctx.fillStyle = "rgba(245,158,11,0.3)"; ctx.font = "bold 7px monospace"; ctx.textAlign = "center";
      ctx.fillText(size.toString(), layerX[li], h - 3);
    });

    // Layer names
    ctx.fillStyle = "rgba(255,255,255,0.15)"; ctx.font = "6px monospace"; ctx.textAlign = "center";
    ["OBS", "HIDDEN", "HIDDEN", "ACT"].forEach((name, i) => ctx.fillText(name, layerX[i], 8));

    // Confidence bar at bottom
    ctx.fillStyle = "rgba(245,158,11,0.08)";
    ctx.fillRect(10, h - 12, w - 20, 5);
    const confCol = confidence > 0.7 ? "#10b981" : confidence > 0.4 ? "#f59e0b" : "#dc2626";
    ctx.fillStyle = confCol;
    ctx.fillRect(10, h - 12, (w - 20) * confidence, 5);

  }, [tick, confidence]);

  return <canvas ref={ref} style={{ width: "100%", height: "100%", display: "block" }} />;
}

// ─── SPARKLINE ──────────────────────────────────────────────────────────────
function Spark({ data, color, h = 20, w = 70 }) {
  if (!data || data.length < 2) return null;
  const mn = Math.min(...data), mx = Math.max(...data), rg = mx - mn || 1;
  const pts = data.map((v, i) => `${(i / (data.length - 1)) * w},${h - ((v - mn) / rg) * (h - 2) - 1}`).join(" ");
  return <svg width={w} height={h} style={{ display: "block", opacity: 0.6 }}><polyline points={pts} fill="none" stroke={color} strokeWidth="1" /></svg>;
}

// ─── DEMO DATA ──────────────────────────────────────────────────────────────
function useDemoMode() {
  const [tick, setTick] = useState(0);
  const phaseRef = useRef(0), ptRef = useRef(0);
  const histRef = useRef({ signal: [], throughput: [], latency: [], coverage: [], reward: [] });

  useEffect(() => { const iv = setInterval(() => setTick(t => t + 1), 380); return () => clearInterval(iv); }, []);
  useEffect(() => { ptRef.current++; const th = [5, 10, 16, 25, 36, 240, 250, 260]; if (ptRef.current >= th[phaseRef.current] && phaseRef.current < PHASES.length - 1) phaseRef.current++; }, [tick]);

  const phase = PHASES[phaseRef.current];
  const t = tick * 0.4, inOps = phase === "OPERATIONS", inForm = phase === "FORMATION";

  const drones = Array.from({ length: 5 }, (_, i) => {
    const angle = (2 * Math.PI * i) / 5 + t * 0.015;
    const baseR = inOps ? 38 + i * 14 : inForm ? 18 + i * 6 : phase === "TRANSIT" ? 10 + t * 0.5 : 3;
    const w2 = Math.sin(t * 0.25 + i * 1.7) * 3;
    const bat = Math.max(15, 100 - t * 0.12 - i * 3 + Math.sin(t * 0.05 + i) * 2);
    return {
      id: i, role: i === 0 ? 1 : 0,
      x: Math.cos(angle) * (baseR + w2) + (inOps ? Math.sin(t * 0.08 + i * 2) * 5 : 0),
      y: Math.sin(angle) * (baseR + w2) + (inOps ? Math.cos(t * 0.06 + i * 3) * 4 : 0),
      z: phase === "IDLE" ? 0.5 : phase === "TAKEOFF" ? Math.min(15, t) : 15 + Math.sin(t * 0.08 + i) * 0.5,
      battery: bat, voltage: 14.8 * bat / 100,
      flightMode: phase === "IDLE" ? 0 : phase === "TAKEOFF" ? 1 : phase === "RTL" ? 4 : 3,
      signal: -62 - i * 4 + Math.sin(t * 0.15 + i) * 3,
      throughput: inOps ? 85 + Math.random() * 35 : inForm ? 40 : 0,
      latency: inOps ? 4 + Math.random() * 5 : inForm ? 12 : 0,
    };
  });

  const deadZones = inOps && t > 30 ? [{ x: 35, y: -15, radius: 22, attenuation: 30 }] : [];

  const cov = (() => {
    const sz = 20, data = new Array(sz * sz).fill(0);
    if (inForm || inOps) for (let r = 0; r < sz; r++) for (let c2 = 0; c2 < sz; c2++) {
      const wx = -70 + (c2 / sz) * 140, wy = -70 + (r / sz) * 140;
      let sig = 0; drones.forEach(d => { sig = Math.max(sig, Math.max(0, 1 - Math.hypot(d.x - wx, d.y - wy) / 55)); });
      deadZones.forEach(dz => { if (Math.hypot(dz.x - wx, dz.y - wy) < dz.radius) sig *= 0.15; });
      data[r * sz + c2] = sig;
    }
    return { data, width: sz, height: sz };
  })();

  const sig = -72 + Math.sin(t * 0.08) * 4;
  const thr = inOps ? 105 + Math.random() * 15 : 0;
  const lat = inOps ? 5.5 + Math.random() * 3 : 0;
  const covP = inOps ? 93 + Math.random() * 6 : inForm ? 55 : 0;

  // Simulated RL brain
  const rewardComponents = inOps ? {
    coverage: 0.93 + Math.sin(t * 0.05) * 0.05,
    connectivity: 2.0,
    signal: 0.15 + Math.sin(t * 0.08) * 0.03,
    throughput: 0.25 + Math.random() * 0.05,
    latency: 0.08 + Math.random() * 0.02,
    movement: 0.02 + Math.random() * 0.03,
    safety: deadZones.length > 0 ? 0.1 + Math.random() * 0.05 : 0,
    improvement: Math.max(0, Math.sin(t * 0.03) * 0.15),
    priority: 1.2 + Math.sin(t * 0.04) * 0.2,
  } : null;

  const totalReward = rewardComponents ? Object.entries(rewardComponents).reduce((s, [k, v]) => s + (["movement", "safety"].includes(k) ? -v : v), 0) : 0;

  const actionVectors = inOps ? drones.map((d, i) => ({
    dx: Math.sin(t * 0.06 + i * 1.5) * (3 + Math.random() * 2) * (deadZones.length > 0 && Math.hypot(d.x - 35, d.y + 15) < 40 ? 2 : 1),
    dy: Math.cos(t * 0.05 + i * 2.1) * (3 + Math.random() * 2),
    dz: Math.sin(t * 0.03 + i) * 0.5,
    confidence: 0.6 + Math.sin(t * 0.04 + i) * 0.3,
  })) : null;

  const policyConfidence = inOps ? 0.65 + Math.sin(t * 0.03) * 0.25 : 0;

  const h = histRef.current;
  h.signal.push(sig); h.throughput.push(thr); h.latency.push(lat); h.coverage.push(covP); h.reward.push(totalReward);
  if (h.signal.length > 40) { h.signal.shift(); h.throughput.shift(); h.latency.shift(); h.coverage.shift(); h.reward.shift(); }

  return { drones, deadZones, coverage: cov, phase, tick, actionVectors, rewardComponents, totalReward, policyConfidence,
    metrics: { signal: sig, throughput: thr, latency: lat, meshConnected: inForm || inOps, linkCount: inOps ? 10 : inForm ? 6 : 0, coveragePercent: covP },
    history: { ...h } };
}

// ─── MAIN ───────────────────────────────────────────────────────────────────
export default function AuraGundamHUD() {
  const [mode, setMode] = useState("demo");
  const [rosUrl] = useState("ws://localhost:9090");
  const [connStatus, setConnStatus] = useState("disconnected");
  const [events, setEvents] = useState([]);
  const [liveDrones, setLiveDrones] = useState([]);
  const [liveMetrics, setLiveMetrics] = useState({});
  const [livePhase, setLivePhase] = useState("IDLE");
  const [liveCov, setLiveCov] = useState({ data: [], width: 0, height: 0 });
  const [liveDZ, setLiveDZ] = useState([]);
  const [liveTick, setLiveTick] = useState(0);
  const [liveHist, setLiveHist] = useState({ signal: [], throughput: [], latency: [], coverage: [], reward: [] });
  const [abortConfirm, setAbortConfirm] = useState(false);
  const bridgeRef = useRef(null), logRef = useRef(null);
  const demo = useDemoMode();

  useEffect(() => { const iv = setInterval(() => setLiveTick(t => t + 1), 380); return () => clearInterval(iv); }, []);

  const addEvent = useCallback((text, color) => {
    const ts = new Date().toTimeString().slice(0, 8);
    setEvents(p => [...p.slice(-60), { ts, text, color }]);
  }, []);

  const connectRos = useCallback(() => {
    if (bridgeRef.current) bridgeRef.current.disconnect();
    const b = new RosBridge(rosUrl); bridgeRef.current = b;
    b.onStatusChange = s => { setConnStatus(s); if (s === "connected") { addEvent("DATALINK ESTABLISHED", "#10b981"); setMode("live"); } else if (s === "disconnected") addEvent("DATALINK LOST", "#dc2626"); };
    b.subscribe("/swarm/state", "aura_msgs/msg/SwarmState", msg => setLiveDrones((msg.drones || []).map(d => ({ id: d.drone_id, role: d.role, x: d.position?.x || 0, y: d.position?.y || 0, z: d.position?.z || 0, battery: d.battery_percent || 0, voltage: d.battery_voltage || 0, flightMode: d.flight_mode || 0, signal: d.signal_strength_dbm, throughput: d.throughput_mbps, latency: d.latency_ms }))));
    b.subscribe("/network/metrics", "aura_msgs/msg/NetworkMetrics", msg => { const m = { signal: msg.avg_signal_strength_dbm, throughput: msg.total_throughput_mbps, latency: msg.avg_latency_ms, meshConnected: msg.mesh_connected, linkCount: msg.active_links, coveragePercent: msg.coverage_percent }; setLiveMetrics(m); setLiveHist(h => ({ signal: [...h.signal, m.signal].slice(-40), throughput: [...h.throughput, m.throughput].slice(-40), latency: [...h.latency, m.latency].slice(-40), coverage: [...h.coverage, m.coveragePercent].slice(-40), reward: h.reward })); });
    b.subscribe("/mission/status", "aura_msgs/msg/MissionStatus", msg => setLivePhase(p => { if (p !== msg.current_phase) addEvent(`PHASE → ${msg.current_phase}`, PC[msg.current_phase]); return msg.current_phase; }));
    b.subscribe("/network/coverage_map", "aura_msgs/msg/CoverageMap", msg => setLiveCov({ data: msg.data || [], width: msg.width || 20, height: msg.height || 20 }));
    b.subscribe("/network/dead_zones", "aura_msgs/msg/WeatherZone", msg => { if (msg.zones) setLiveDZ(msg.zones.map(z => ({ x: z.center?.x || 0, y: z.center?.y || 0, radius: z.radius || 20, attenuation: z.attenuation_db || 20 }))); });
    b.connect();
  }, [rosUrl, addEvent]);

  useEffect(() => () => bridgeRef.current?.disconnect(), []);

  const d = mode === "live" ? liveDrones : demo.drones;
  const m = mode === "live" ? liveMetrics : demo.metrics;
  const phase = mode === "live" ? livePhase : demo.phase;
  const cov = mode === "live" ? liveCov : demo.coverage;
  const dz = mode === "live" ? liveDZ : demo.deadZones;
  const tick = mode === "live" ? liveTick : demo.tick;
  const hist = mode === "live" ? liveHist : demo.history;
  const rc = demo.rewardComponents;
  const av = demo.actionVectors;
  const pc = demo.policyConfidence;
  const tr = demo.totalReward;
  const isOps = phase === "OPERATIONS";
  const isActive = !["IDLE", "LANDED"].includes(phase);
  const avgBat = d.length ? d.reduce((s, x) => s + x.battery, 0) / d.length : 0;
  const minBat = d.length ? Math.min(...d.map(x => x.battery)) : 0;

  const handleAbort = () => { if (!abortConfirm) { setAbortConfirm(true); setTimeout(() => setAbortConfirm(false), 3000); return; } if (mode === "live" && bridgeRef.current?.connected) { bridgeRef.current.callService("/mission/abort", "std_srvs/srv/Trigger", {}).catch(() => bridgeRef.current.publish("/mission/command", "std_msgs/msg/String", { data: "ABORT" })); } addEvent("■ ABORT EXECUTED", "#dc2626"); setAbortConfirm(false); };

  useEffect(() => { if (logRef.current) logRef.current.scrollTop = logRef.current.scrollHeight; }, [events]);

  const css = `
    @keyframes blink { 0%,100%{opacity:1} 50%{opacity:0.3} }
    @keyframes pulse { 0%,100%{opacity:0.6} 50%{opacity:1} }
    @keyframes scan { from{top:-2px} to{top:100%} }
    @import url('https://fonts.googleapis.com/css2?family=Rajdhani:wght@400;600;700&family=Orbitron:wght@400;700;900&display=swap');
    ::-webkit-scrollbar { width: 3px; } ::-webkit-scrollbar-track { background: transparent; } ::-webkit-scrollbar-thumb { background: rgba(245,158,11,0.15); }
  `;

  return (
    <div style={{ height: "100vh", background: "#080c10", color: "#fef3c7", fontFamily: "'Rajdhani', sans-serif", overflow: "hidden", position: "relative", display: "flex", flexDirection: "column" }}>
      <style>{css}</style>

      {/* Scan line */}
      <div style={{ position: "absolute", inset: 0, pointerEvents: "none", overflow: "hidden", zIndex: 50, opacity: 0.04 }}>
        <div style={{ position: "absolute", left: 0, right: 0, height: 1, background: "linear-gradient(90deg, transparent, #f59e0b, transparent)", animation: "scan 3s linear infinite" }} />
      </div>

      {/* ═══ TOP BAR ═══ */}
      <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", padding: "5px 12px", borderBottom: "1px solid rgba(245,158,11,0.15)", background: "linear-gradient(180deg, rgba(245,158,11,0.04) 0%, transparent 100%)", flexShrink: 0 }}>
        <div style={{ display: "flex", alignItems: "baseline", gap: 8 }}>
          <span style={{ fontFamily: "'Orbitron'", fontWeight: 900, fontSize: 16, color: "#f59e0b", letterSpacing: "0.12em" }}>A.U.R.A.</span>
          <span style={{ fontSize: 10, color: "rgba(245,158,11,0.35)", fontWeight: 600, letterSpacing: "0.08em" }}>AUTONOMOUS URBAN RESCUE ARRAY</span>
        </div>
        <div style={{ display: "flex", alignItems: "center", gap: 8 }}>
          <div style={{ padding: "2px 10px", background: `${PC[phase]}18`, border: `1px solid ${PC[phase]}50`, display: "flex", alignItems: "center", gap: 5 }}>
            <div style={{ width: 5, height: 5, background: PC[phase], animation: isActive ? "pulse 1.2s ease infinite" : "none" }} />
            <span style={{ fontSize: 11, color: PC[phase], fontWeight: 700, fontFamily: "'Orbitron'", letterSpacing: "0.06em" }}>{phase}</span>
          </div>
          <div style={{ fontSize: 9, color: "rgba(255,255,255,0.25)", display: "flex", alignItems: "center", gap: 4 }}>
            <div style={{ width: 4, height: 4, borderRadius: "50%", background: mode === "live" ? "#10b981" : "#d97706" }} />
            {mode === "demo" ? "SIM" : "LIVE"}
          </div>
          <button onClick={mode === "demo" ? connectRos : () => { bridgeRef.current?.disconnect(); setMode("demo"); }} style={{ background: "none", border: "1px solid rgba(245,158,11,0.25)", color: "#f59e0b", padding: "2px 8px", fontSize: 9, cursor: "pointer", fontFamily: "'Rajdhani'" }}>{mode === "demo" ? "LINK" : "UNLINK"}</button>
        </div>
      </div>

      {/* ═══ PHASE BAR ═══ */}
      <div style={{ display: "flex", padding: "3px 12px", borderBottom: "1px solid rgba(245,158,11,0.08)", flexShrink: 0 }}>
        {PHASES.map((p, i) => {
          const a = p === phase, past = i < PHASES.indexOf(phase);
          return (
            <div key={p} style={{ display: "flex", alignItems: "center", flex: 1 }}>
              <div style={{ display: "flex", flexDirection: "column", alignItems: "center", flex: 1 }}>
                <div style={{ width: a ? 8 : 4, height: a ? 8 : 4, transform: a ? "rotate(45deg)" : "none", background: a ? PC[p] : past ? `${PC[p]}80` : "rgba(255,255,255,0.06)", boxShadow: a ? `0 0 8px ${PC[p]}60` : "none", transition: "all 0.3s" }} />
                <span style={{ fontSize: 6, marginTop: 1, color: a ? PC[p] : past ? "rgba(255,255,255,0.25)" : "rgba(255,255,255,0.08)", fontWeight: a ? 700 : 400 }}>{p}</span>
              </div>
              {i < PHASES.length - 1 && <div style={{ height: 1, flex: 1, minWidth: 3, background: past ? `${PC[PHASES[i + 1]]}35` : "rgba(255,255,255,0.03)" }} />}
            </div>
          );
        })}
      </div>

      {/* ═══ MAIN GRID ═══ */}
      <div style={{ flex: 1, display: "grid", gridTemplateColumns: "180px 1fr 200px", gridTemplateRows: "1fr auto", overflow: "hidden", gap: 0 }}>

        {/* ─── LEFT: FLEET + TELEMETRY ─── */}
        <div style={{ borderRight: "1px solid rgba(245,158,11,0.08)", display: "flex", flexDirection: "column", overflow: "hidden", padding: "6px 8px", gap: 6 }}>
          {/* Network */}
          <HexFrame title="Network">
            {[
              { l: "SIG", v: m.signal, u: "dBm", f: v => v?.toFixed(1), c: "#10b981", d: hist.signal },
              { l: "THR", v: m.throughput, u: "Mbps", f: v => v?.toFixed(0), c: "#38bdf8", d: hist.throughput },
              { l: "LAT", v: m.latency, u: "ms", f: v => v?.toFixed(1), c: "#f59e0b", d: hist.latency },
              { l: "COV", v: m.coveragePercent, u: "%", f: v => v?.toFixed(0), c: "#a78bfa", d: hist.coverage },
            ].map(x => (
              <div key={x.l} style={{ display: "flex", alignItems: "center", justifyContent: "space-between", padding: "2px 0" }}>
                <div>
                  <div style={{ fontSize: 7, color: "rgba(255,255,255,0.2)" }}>{x.l}</div>
                  <div style={{ fontSize: 14, fontWeight: 700, color: x.c, lineHeight: 1 }}>{x.f(x.v || 0)}<span style={{ fontSize: 7, opacity: 0.4, marginLeft: 2 }}>{x.u}</span></div>
                </div>
                <Spark data={x.d} color={x.c} h={18} w={55} />
              </div>
            ))}
            <div style={{ display: "flex", gap: 10, fontSize: 9, color: "rgba(255,255,255,0.3)", marginTop: 2, borderTop: "1px solid rgba(245,158,11,0.06)", paddingTop: 3 }}>
              <span>MESH <span style={{ color: m.meshConnected ? "#10b981" : "#dc2626", fontWeight: 700 }}>{m.meshConnected ? "UP" : "DN"}</span></span>
              <span>LNK <span style={{ fontWeight: 700 }}>{m.linkCount || 0}</span></span>
            </div>
          </HexFrame>

          {/* Fleet */}
          <HexFrame title="Fleet" alert={minBat < 20} style={{ flex: 1, overflow: "hidden", display: "flex", flexDirection: "column" }}>
            <div style={{ flex: 1, overflow: "auto" }}>
              {d.map(dr => {
                const hub = dr.role === 1, col = hub ? "#f59e0b" : "#34d399";
                const bc = dr.battery > 50 ? "#10b981" : dr.battery > 25 ? "#d97706" : "#dc2626";
                return (
                  <div key={dr.id} style={{ padding: "3px 4px", marginBottom: 2, borderLeft: `2px solid ${col}`, background: "rgba(255,255,255,0.01)" }}>
                    <div style={{ display: "flex", justifyContent: "space-between", fontSize: 9 }}>
                      <span style={{ fontWeight: 700, color: col }}>{hub ? "HUB" : `U${dr.id}`}</span>
                      <span style={{ color: "rgba(255,255,255,0.2)", fontSize: 8 }}>{FM[dr.flightMode]}</span>
                    </div>
                    <div style={{ display: "flex", alignItems: "center", gap: 3, marginTop: 1 }}>
                      <div style={{ flex: 1, height: 4, background: "rgba(255,255,255,0.04)", borderRadius: 1 }}>
                        <div style={{ width: `${dr.battery}%`, height: "100%", background: `linear-gradient(90deg, ${bc}aa, ${bc})`, borderRadius: 1, transition: "width 0.8s" }} />
                      </div>
                      <span style={{ fontSize: 8, color: bc, fontWeight: 700, minWidth: 24 }}>{dr.battery.toFixed(0)}%</span>
                      <span style={{ fontSize: 7, color: "rgba(255,255,255,0.2)" }}>{(dr.voltage || 0).toFixed(1)}V</span>
                    </div>
                  </div>
                );
              })}
            </div>
            <div style={{ borderTop: "1px solid rgba(245,158,11,0.06)", paddingTop: 3, marginTop: 3, fontSize: 8, color: "rgba(255,255,255,0.25)" }}>
              <div style={{ display: "flex", justifyContent: "space-between" }}><span>AVG</span><span style={{ color: avgBat > 50 ? "#10b981" : "#d97706", fontWeight: 700 }}>{avgBat.toFixed(0)}%</span></div>
              <div style={{ display: "flex", justifyContent: "space-between" }}><span>MIN</span><span style={{ color: minBat > 50 ? "#10b981" : minBat > 25 ? "#d97706" : "#dc2626", fontWeight: 700 }}>{minBat.toFixed(0)}%</span></div>
              <div style={{ display: "flex", justifyContent: "space-between" }}><span>ENDURANCE</span><span style={{ fontWeight: 700 }}>{Math.max(0, ((minBat - 15) / 1.5)).toFixed(0)}m</span></div>
            </div>
          </HexFrame>
        </div>

        {/* ─── CENTER: RADAR ─── */}
        <div style={{ position: "relative" }}>
          <TacticalRadar drones={d} deadZones={dz} coverage={cov} tick={tick} actionVectors={av} />
          {/* Top-left overlay */}
          <div style={{ position: "absolute", top: 6, left: 6, fontSize: 9, color: "rgba(245,158,11,0.45)" }}>
            <div>UNITS: <span style={{ color: "#f59e0b", fontWeight: 700 }}>{d.length}</span></div>
            <div>DZ: <span style={{ color: dz.length > 0 ? "#dc2626" : "rgba(245,158,11,0.5)", fontWeight: 700 }}>{dz.length}</span></div>
          </div>
          {/* Top-right */}
          <div style={{ position: "absolute", top: 6, right: 6, fontSize: 8, color: "rgba(255,255,255,0.15)", textAlign: "right" }}>
            {new Date().toISOString().replace("T", " ").slice(0, 19)} UTC
          </div>
          {/* Bottom-center: RL mode indicator */}
          {isOps && (
            <div style={{ position: "absolute", bottom: 8, left: "50%", transform: "translateX(-50%)", display: "flex", alignItems: "center", gap: 6, padding: "3px 12px", background: "rgba(56,189,248,0.08)", border: "1px solid rgba(56,189,248,0.25)" }}>
              <div style={{ width: 5, height: 5, background: "#38bdf8", animation: "pulse 1s ease infinite" }} />
              <span style={{ fontSize: 9, color: "#38bdf8", fontWeight: 700, fontFamily: "'Orbitron'", letterSpacing: "0.1em" }}>RL POLICY ACTIVE</span>
            </div>
          )}
        </div>

        {/* ─── RIGHT: RL BRAIN ─── */}
        <div style={{ borderLeft: "1px solid rgba(245,158,11,0.08)", display: "flex", flexDirection: "column", overflow: "hidden", padding: "6px 8px", gap: 6 }}>
          {isOps ? (
            <>
              {/* Neural network visualization */}
              <HexFrame title="Policy Network" color="#38bdf8">
                <div style={{ height: 100 }}>
                  <NeuralPulse tick={tick} confidence={pc} />
                </div>
                <div style={{ display: "flex", justifyContent: "space-between", fontSize: 8, color: "rgba(255,255,255,0.3)", marginTop: 2 }}>
                  <span>184→256→256→15</span>
                  <span>CONF: <span style={{ color: pc > 0.7 ? "#10b981" : pc > 0.4 ? "#f59e0b" : "#dc2626", fontWeight: 700 }}>{(pc * 100).toFixed(0)}%</span></span>
                </div>
              </HexFrame>

              {/* Reward decomposition */}
              <HexFrame title="Reward Signal" color="#10b981" style={{ flex: 1 }}>
                <div style={{ marginBottom: 4 }}>
                  <div style={{ display: "flex", justifyContent: "space-between", fontSize: 8, marginBottom: 4 }}>
                    <span style={{ color: "rgba(255,255,255,0.3)" }}>TOTAL</span>
                    <span style={{ fontSize: 14, fontWeight: 700, color: tr > 3 ? "#10b981" : tr > 1.5 ? "#f59e0b" : "#dc2626", fontFamily: "'Orbitron'" }}>{tr.toFixed(2)}</span>
                  </div>
                  <Spark data={hist.reward} color="#10b981" h={20} w={170} />
                </div>
                {rc && (
                  <>
                    <RewardBar label="COVERAGE" value={rc.coverage} color="#10b981" maxVal={1.5} />
                    <RewardBar label="CONNECT" value={rc.connectivity} color="#38bdf8" maxVal={2.5} />
                    <RewardBar label="SIGNAL" value={rc.signal} color="#a78bfa" maxVal={0.3} />
                    <RewardBar label="THRUPUT" value={rc.throughput} color="#2dd4bf" maxVal={0.4} />
                    <RewardBar label="PRIORITY" value={rc.priority} color="#f59e0b" maxVal={2} />
                    <RewardBar label="IMPROVE" value={rc.improvement} color="#34d399" maxVal={0.5} />
                    <RewardBar label="MOVE" value={rc.movement} color="#dc2626" maxVal={0.1} negative />
                    <RewardBar label="SAFETY" value={rc.safety} color="#dc2626" maxVal={0.3} negative />
                  </>
                )}
              </HexFrame>

              {/* Action output */}
              <HexFrame title="Action Vectors" color="#38bdf8">
                <div style={{ display: "grid", gridTemplateColumns: "repeat(5, 1fr)", gap: 3 }}>
                  {(av || []).map((a, i) => (
                    <div key={i} style={{ textAlign: "center" }}>
                      <div style={{ fontSize: 7, color: d[i]?.role === 1 ? "#f59e0b" : "#34d399", fontWeight: 700 }}>{d[i]?.role === 1 ? "HUB" : `U${i}`}</div>
                      <svg width="28" height="28" viewBox="-14 -14 28 28">
                        <circle cx="0" cy="0" r="12" fill="none" stroke="rgba(56,189,248,0.1)" strokeWidth="0.5" />
                        <line x1="0" y1="0" x2={a.dx * 1.5} y2={-a.dy * 1.5} stroke="#38bdf8" strokeWidth="1.5" />
                        <circle cx="0" cy="0" r="1.5" fill="rgba(56,189,248,0.6)" />
                      </svg>
                      <div style={{ fontSize: 6, color: "rgba(255,255,255,0.2)" }}>{a.confidence ? `${(a.confidence * 100).toFixed(0)}%` : ""}</div>
                    </div>
                  ))}
                </div>
              </HexFrame>
            </>
          ) : (
            <HexFrame title="RL Brain" color="rgba(255,255,255,0.15)" style={{ flex: 1, display: "flex", alignItems: "center", justifyContent: "center" }}>
              <div style={{ textAlign: "center", color: "rgba(255,255,255,0.12)" }}>
                <div style={{ fontFamily: "'Orbitron'", fontSize: 11, letterSpacing: "0.1em", marginBottom: 4 }}>STANDBY</div>
                <div style={{ fontSize: 8 }}>RL activates in OPERATIONS</div>
                <div style={{ fontSize: 8, marginTop: 2 }}>Current: {phase}</div>
              </div>
            </HexFrame>
          )}
        </div>

        {/* ═══ BOTTOM BAR ═══ */}
        <div style={{ gridColumn: "1 / -1", display: "flex", borderTop: "1px solid rgba(245,158,11,0.1)", background: "rgba(0,0,0,0.4)" }}>
          <div ref={logRef} style={{ flex: 1, padding: "3px 10px", maxHeight: 56, overflowY: "auto", fontSize: 9 }}>
            {events.length === 0 && <span style={{ color: "rgba(255,255,255,0.08)" }}>SYSTEM READY...</span>}
            {events.map((e, i) => (
              <div key={i} style={{ display: "flex", gap: 8, lineHeight: 1.3 }}>
                <span style={{ color: "rgba(245,158,11,0.15)", minWidth: 52 }}>{e.ts}</span>
                <span style={{ color: e.color || "rgba(255,255,255,0.35)" }}>{e.text}</span>
              </div>
            ))}
          </div>
          <div style={{ display: "flex", alignItems: "center", padding: "0 10px", borderLeft: "1px solid rgba(245,158,11,0.08)" }}>
            <button onClick={handleAbort} disabled={!isActive} style={{
              background: !isActive ? "rgba(255,255,255,0.02)" : abortConfirm ? "#dc2626" : "rgba(220,38,38,0.06)",
              border: `1px solid ${!isActive ? "rgba(255,255,255,0.03)" : abortConfirm ? "#dc2626" : "rgba(220,38,38,0.3)"}`,
              color: !isActive ? "rgba(255,255,255,0.08)" : abortConfirm ? "#fff" : "#dc2626",
              padding: "5px 14px", fontSize: 10, cursor: isActive ? "pointer" : "not-allowed",
              fontFamily: "'Orbitron'", fontWeight: 700, letterSpacing: "0.08em",
              animation: abortConfirm ? "blink 0.5s ease infinite" : "none",
            }}>
              {abortConfirm ? "CONFIRM" : "■ ABORT"}
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}
