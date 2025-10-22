# 🛰️ AURA — Autonomous UAV Relay Architecture

## Overview
**AURA (Autonomous UAV Relay Architecture)** is a multi-drone, AI-driven communication network designed for **disaster response and resilient connectivity**.  
When ground infrastructure fails — due to wildfires, earthquakes, or other crises — AURA enables drones to **form an adaptive aerial network** that restores coverage and data links between emergency teams, civilians, and command centers.

AURA integrates **AirSim** for flight simulation and **ns-3** for network-level modeling, creating a unified environment that captures both **physical flight dynamics** and **communication behavior**.  
This dual-simulation approach allows the system to learn and optimize for real-world conditions such as weather impairments, node failure, and interference.

---

## 🚨 Problem Statement
In disaster-affected areas, **ground-based communication networks often collapse**, leaving emergency responders and survivors disconnected.  
Traditional satellite links are costly, power-intensive, and not scalable for local high-throughput operations.

There is a critical need for a **rapidly deployable, autonomous aerial communication mesh** that can self-organize, recover from failures, and sustain connectivity under harsh conditions.

---

## 🎯 Project Goal
AURA aims to:
- Design and simulate a **multi-drone ad-hoc communication network** capable of maintaining high reliability and low latency under dynamic conditions.  
- Integrate **AI-based (RL) optimization** for drone positioning and network routing to improve coverage and reduce energy usage.  
- Validate system performance through **AirSim + ns-3 co-simulation**, ensuring realistic physical and network behavior.
- Demonstrate **self-healing mesh properties** that can recover from drone failure or signal loss.

---

## 🧠 Tech Stack
- **AirSim** – For realistic UAV flight dynamics and environmental physics.
- **ns-3** – For simulating communication networks (Wi-Fi, LTE, LoRa).
- **Python / C++** – For RL, system integration, and data logging.
- **Grafana + Prometheus** – For live metrics visualization and analysis.
- **Dockerized Simulation Environment** – Ensures reproducible, modular deployments.

---

## ✈️ Architecture
AURA consists of multiple autonomous UAV nodes acting as **relay stations** that form a **self-organizing mesh network**.  
Each drone:
- Learns optimal placement and routing policies.
- Adapts to weather, interference, and node failures.
- Contributes to network resilience and recovery through decentralized coordination.

AURA’s modular design ensures seamless transition from **simulation to real-world deployment**, allowing for ground-mast fallback prototypes or partial hardware validation.

---

## ⚙️ Core Features
*(To be filled in as development progresses)*  
- [ ] Flight simulation integration with AirSim  
- [ ] Network topology via ns-3  
- [ ] Reinforcement Learning (RL) module  
- [ ] KPI dashboard for latency, coverage, recovery  
- [ ] Failure injection and reroute handling  
- [ ] Hardware validation path (optional tethered drone)  
- [ ] ... *(add more here)*  

---

## 🧩 Future Work
- Expand to **multi-agent RL coordination** for dynamic mesh formation.
- Implement **LTE/5G** extensions for high-bandwidth relay nodes.
- Deploy on low-power **Jetson or RB5 hardware** for field testing.
- Explore **AI-driven impairment adaptation** (wind, smoke, rain).

---

## 📅 Project Timeline (Aug 2025 – Jun 2026)
- **Aug–Sep 2025:** Setup AirSim + ns-3 environment and define KPIs  
- **Oct–Dec 2025:** Implement impairment models and RL baseline  
- **Jan–Mar 2026:** Run training experiments and integrate metrics dashboards  
- **Apr–Jun 2026:** Finalize MVP, demo, and documentation for Springer publication  

---

## 👨‍💻 Author
**Hussein Khadra (U224N1877)**  
University of Nicosia — Department of Computer Science  
Supervised by **Prof. Mavromoustakis**  

---

## 🧾 License
This project is distributed under the **MIT License** — open for academic and research collaboration.

---

> *AURA: Restoring connectivity, one autonomous link at a time.*
