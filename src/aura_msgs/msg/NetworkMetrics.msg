# NetworkMetrics.msg
# Network simulation metrics from NS-3 bridge
std_msgs/Header header
builtin_interfaces/Time timestamp

# Grid-based coverage map
uint32 grid_size_x               # Number of cells in X
uint32 grid_size_y               # Number of cells in Y
float32 cell_size_meters         # Size of each cell
geometry_msgs/Point origin       # World position of grid origin

# Coverage data (flattened grid_size_x * grid_size_y arrays)
# Access with: data[y * grid_size_x + x]
float32[] signal_strength_dbm    # Signal strength at each cell
float32[] throughput_mbps        # Available throughput at each cell
float32[] latency_ms             # Expected latency at each cell
bool[] coverage_mask             # True if cell has usable coverage

# Aggregate metrics
float32 total_coverage_percent   # Percent of target area covered
float32 avg_signal_strength_dbm
float32 avg_throughput_mbps
float32 avg_latency_ms
float32 packet_loss_percent

# Per-link metrics (between drones)
uint8[] link_from_drone          # Source drone ID
uint8[] link_to_drone            # Destination drone ID
float32[] link_throughput_mbps   # Throughput on this link
float32[] link_latency_ms        # Latency on this link
float32[] link_rssi_dbm          # Signal strength on this link

# Backhaul status (Hub to command post)
bool backhaul_active
float32 backhaul_throughput_mbps
float32 backhaul_latency_ms
