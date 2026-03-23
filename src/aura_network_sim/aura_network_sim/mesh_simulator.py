"""
WiFi Mesh Network Simulator for A.U.R.A.

Simulates drone-to-drone mesh network connectivity:
- Computes pairwise link quality
- Determines mesh connectivity (graph analysis)
- Calculates per-drone network metrics
"""

import numpy as np
from dataclasses import dataclass, field
from typing import Dict, List, Tuple, Optional
from collections import deque

from .propagation import PropagationModel, D2D_CONFIG, RadioConfig


@dataclass
class DroneNetworkState:
    """Network state for a single drone"""
    drone_id: int
    position: np.ndarray  # [x, y, z] in meters
    is_hub: bool = False
    tx_power_dbm: float = 20.0
    
    # Computed metrics
    neighbors: List[int] = field(default_factory=list)
    neighbor_rssi: Dict[int, float] = field(default_factory=dict)
    best_rssi_dbm: float = -200.0
    throughput_mbps: float = 0.0
    latency_ms: float = 0.0
    hops_to_hub: int = -1  # -1 = no path


class MeshSimulator:
    """
    Simulates WiFi mesh network between drones.
    
    Computes:
    - Pairwise connectivity matrix
    - RSSI and throughput for each link
    - Mesh graph connectivity
    - Routing paths to hub
    """
    
    def __init__(self, config: Optional[RadioConfig] = None, seed: int = 42):
        self.config = config or D2D_CONFIG
        self.propagation = PropagationModel(self.config, seed)
        
        # Drone states
        self.drones: Dict[int, DroneNetworkState] = {}
        
        # Computed matrices (indexed by sorted drone_id order)
        self.connectivity: Optional[np.ndarray] = None
        self.rssi_matrix: Optional[np.ndarray] = None
        self.rate_matrix: Optional[np.ndarray] = None
        
        # Ordered list of drone IDs
        self._drone_ids: List[int] = []
        self._id_to_idx: Dict[int, int] = {}
    
    def update_drone(self, drone_id: int, position: np.ndarray, 
                     is_hub: bool = False, tx_power_dbm: float = 20.0):
        """Add or update drone in simulation"""
        if drone_id not in self.drones:
            self.drones[drone_id] = DroneNetworkState(
                drone_id=drone_id,
                position=position.copy(),
                is_hub=is_hub,
                tx_power_dbm=tx_power_dbm,
            )
        else:
            self.drones[drone_id].position = position.copy()
            self.drones[drone_id].is_hub = is_hub
            self.drones[drone_id].tx_power_dbm = tx_power_dbm
        
        # Rebuild index mapping
        self._rebuild_index()
    
    def remove_drone(self, drone_id: int):
        """Remove drone safely"""

        if drone_id not in self.drones:
            return

        del self.drones[drone_id]

        # remove references from neighbors
        for drone in self.drones.values():
            drone.neighbors = [n for n in drone.neighbors if n != drone_id]
            drone.neighbor_rssi.pop(drone_id, None)

        self._rebuild_index()
    
    def _rebuild_index(self):
        """Rebuild drone ID to index mapping"""
        self._drone_ids = sorted(self.drones.keys())
        self._id_to_idx = {did: i for i, did in enumerate(self._drone_ids)}
    
    def compute_connectivity(self) -> Tuple[np.ndarray, np.ndarray, np.ndarray]:
        """
        Compute mesh connectivity between all drones.
        
        Returns:
            connectivity: Boolean matrix of connected links
            rssi_matrix: RSSI values for each link (dBm)
            rate_matrix: Data rate for each link (Mbps)
        """
        self._rebuild_index()
        n = len(self.drones)
        if n == 0:
            self.connectivity = np.array([])
            self.rssi_matrix = np.array([])
            self.rate_matrix = np.array([])
            return self.connectivity, self.rssi_matrix, self.rate_matrix
        
        self.connectivity = np.zeros((n, n), dtype=bool)
        self.rssi_matrix = np.full((n, n), -200.0)
        self.rate_matrix = np.zeros((n, n))

        for drone in self.drones.values():
            drone.neighbors.clear()
            drone.best_rssi_dbm = -200
            drone.throughput_mbps = 0
            drone.hops_to_hub = None
        
        for i, id_i in enumerate(self._drone_ids):
            drone_i = self.drones.get(id_i)
            if drone_i is None:
                continue
            
            for j, id_j in enumerate(self._drone_ids):
                if j <= i:
                    continue
                
                drone_j = self.drones[id_j]
                if drone_j is None:
                    continue
                # Compute distance
                distance = np.linalg.norm(drone_i.position - drone_j.position)
                
                # Compute link metrics
                link_id = (min(id_i, id_j), max(id_i, id_j))
                metrics = self.propagation.compute_link_metrics(distance, link_id)
                
                # Store results (symmetric)
                self.rssi_matrix[i, j] = metrics['rssi_dbm']
                self.rssi_matrix[j, i] = metrics['rssi_dbm']
                
                if metrics['connected']:
                    self.connectivity[i, j] = True
                    self.connectivity[j, i] = True
                    self.rate_matrix[i, j] = metrics['rate_mbps']
                    self.rate_matrix[j, i] = metrics['rate_mbps']
        
        # Update drone states with neighbor info
        self._update_drone_neighbors()
        
        return self.connectivity, self.rssi_matrix, self.rate_matrix
    
    def _update_drone_neighbors(self):
        """Update each drone's neighbor list and metrics"""
        if self.connectivity is None or len(self.connectivity) == 0:
            return
        
        for i, drone_id in enumerate(self._drone_ids):
            drone = self.drones[drone_id]
            
            # Find connected neighbors
            drone.neighbors = []
            drone.neighbor_rssi = {}
            drone.best_rssi_dbm = -200.0
            
            for j, other_id in enumerate(self._drone_ids):
                if i != j and self.connectivity[i, j]:
                    drone.neighbors.append(other_id)
                    drone.neighbor_rssi[other_id] = self.rssi_matrix[i, j]
                    
                    if self.rssi_matrix[i, j] > drone.best_rssi_dbm:
                        drone.best_rssi_dbm = self.rssi_matrix[i, j]
            
            # Compute throughput (average of neighbor links)
            if drone.neighbors:
                rates = [
                    self.rate_matrix[i, self._id_to_idx[n]]
                    for n in drone.neighbors
                        if n in self._id_to_idx
                ]
                drone.throughput_mbps = np.mean(rates)
            else:
                drone.throughput_mbps = 0.0
        
        # Compute hops to hub
        self._compute_hops_to_hub()
    
    def _compute_hops_to_hub(self):
        """Compute number of hops to nearest hub for each drone"""
        if self.connectivity is None or len(self.connectivity) == 0:
            return
        
        # Find hub drones
        hub_indices = [self._id_to_idx[did] for did, d in self.drones.items() 
                       if d.is_hub]
        
        if not hub_indices:
            # No hub, all drones have no path
            for drone in self.drones.values():
                drone.hops_to_hub = -1
                drone.latency_ms = 999.0
            return
        
        # BFS from all hubs simultaneously
        n = len(self._drone_ids)
        hops = np.full(n, -1)
        
        queue = deque()
        for hub_idx in hub_indices:
            hops[hub_idx] = 0
            queue.append(hub_idx)
        
        while queue:
            current = queue.popleft()
            
            for neighbor in range(n):
                if self.connectivity[current, neighbor] and hops[neighbor] == -1:
                    hops[neighbor] = hops[current] + 1
                    queue.append(neighbor)
        
        # Update drone states
        base_latency_ms = 2.0  # Processing latency
        hop_latency_ms = 5.0   # Per-hop latency
        
        for i, drone_id in enumerate(self._drone_ids):
            self.drones[drone_id].hops_to_hub = int(hops[i])
            
            if hops[i] >= 0:
                self.drones[drone_id].latency_ms = base_latency_ms + hops[i] * hop_latency_ms
            else:
                self.drones[drone_id].latency_ms = 999.0
    
    def is_mesh_connected(self) -> bool:
        """Check if all drones form a single connected component"""
        if len(self.drones) <= 1:
            return True
        
        if self.connectivity is None or len(self.connectivity) == 0:
            return False
        
        n = len(self._drone_ids)
        visited = np.zeros(n, dtype=bool)
        visited[0] = True
        queue = deque([0])
        
        while queue:
            current = queue.popleft()
            for neighbor in range(n):
                if self.connectivity[current, neighbor] and not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)
        
        return np.all(visited)
    
    def find_path(self, source_id: int, dest_id: int) -> Optional[List[int]]:
        """Find shortest path between two drones using BFS"""
        if source_id not in self._id_to_idx or dest_id not in self._id_to_idx:
            return None
        
        if source_id == dest_id:
            return [source_id]
        
        if self.connectivity is None:
            return None
        
        source_idx = self._id_to_idx[source_id]
        dest_idx = self._id_to_idx[dest_id]
        
        n = len(self._drone_ids)
        visited = np.zeros(n, dtype=bool)
        parent = np.full(n, -1)
        
        visited[source_idx] = True
        queue = deque([source_idx])
        
        while queue:
            current = queue.popleft()
            
            if current == dest_idx:
                # Reconstruct path
                path = []
                idx = dest_idx
                while idx != -1:
                    path.append(self._drone_ids[idx])
                    idx = parent[idx]
                return list(reversed(path))
            
            for neighbor in range(n):
                if self.connectivity[current, neighbor] and not visited[neighbor]:
                    visited[neighbor] = True
                    parent[neighbor] = current
                    queue.append(neighbor)
        
        return None  # No path exists
    
    def get_link_info(self) -> List[Dict]:
        """Get information about all active links"""
        links = []
        
        if self.connectivity is None:
            return links
        
        for i, id_i in enumerate(self._drone_ids):
            for j, id_j in enumerate(self._drone_ids):
                if j <= i:
                    continue
                
                if self.connectivity[i, j]:
                    links.append({
                        'from_id': id_i,
                        'to_id': id_j,
                        'rssi_dbm': float(self.rssi_matrix[i, j]),
                        'rate_mbps': float(self.rate_matrix[i, j]),
                        'distance_m': float(np.linalg.norm(
                            self.drones[id_i].position - self.drones[id_j].position
                        )),
                    })
        
        return links
    
    def get_mesh_stats(self) -> Dict:
        """Get overall mesh network statistics"""
        if not self.drones:
            return {
                'num_drones': 0,
                'num_links': 0,
                'is_connected': False,
                'avg_neighbors': 0.0,
                'avg_rssi_dbm': -200.0,
                'avg_throughput_mbps': 0.0,
                'avg_latency_ms': 999.0,
            }
        
        links = self.get_link_info()
        
        neighbors = [len(d.neighbors) for d in self.drones.values()]
        rssi_values = [d.best_rssi_dbm for d in self.drones.values() if d.best_rssi_dbm > -200]
        throughputs = [d.throughput_mbps for d in self.drones.values()]
        latencies = [d.latency_ms for d in self.drones.values() if d.latency_ms < 999]
        
        return {
            'num_drones': len(self.drones),
            'num_links': len(links),
            'is_connected': self.is_mesh_connected(),
            'avg_neighbors': float(np.mean(neighbors)) if neighbors else 0.0,
            'avg_rssi_dbm': float(np.mean(rssi_values)) if rssi_values else -200.0,
            'avg_throughput_mbps': float(np.mean(throughputs)) if throughputs else 0.0,
            'avg_latency_ms': float(np.mean(latencies)) if latencies else 999.0,
        }
