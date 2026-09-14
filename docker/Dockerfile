# ==============================================================================
# A.U.R.A. Development Container
# Ubuntu 22.04 + ROS 2 Humble + Gazebo Classic 11 + PX4 SITL + NS-3 + PufferLib
#
# Every external source is pinned to an exact revision from versions.env. It
# used to clone default branches with --depth 1, so two builds of this same
# file produced different stacks — see roadmap 0.2.
#
# GPU: the pinned torch is a cu124 build, which carries kernels for sm_50-sm_90.
# On an sm_120 (Blackwell) card such as the RTX 5050, torch.cuda.is_available()
# returns True and kernels then fail to launch; train_policy's resolve_device()
# detects that and falls back to CPU. Overriding TORCH_CUDA_CHANNEL to cu128 is
# the modernization step (roadmap 0.6), deliberately NOT done on the frozen
# baseline.
# ==============================================================================

FROM ubuntu:22.04

# ── Pinned revisions (defaults mirror versions.env) ──────────────────────────
ARG PX4_AUTOPILOT_REV=7b7233587665c93fb6eb7e68d3d43035293d8af4
ARG PX4_MSGS_REV=31147daec8fae45e0cfe265d9dfe426e7d6fcf86
ARG PX4_ROS_COM_REV=86e9aeb20e55a4673fa8a9f1c29ea06a6c5ad1af
ARG NS3_VERSION=3.40
ARG TORCH_VERSION=2.6.0
ARG TORCHVISION_VERSION=0.21.0
ARG TORCHAUDIO_VERSION=2.6.0
ARG TORCH_CUDA_CHANNEL=cu124

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Locale setup
RUN apt-get update && apt-get install -y locales \
    && locale-gen en_US en_US.UTF-8 \
    && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8

# ==============================================================================
# BASE DEPENDENCIES
# ==============================================================================
RUN apt-get update && apt-get install -y \
    curl \
    gnupg2 \
    lsb-release \
    wget \
    git \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    python3 \
    python3-pip \
    python3-dev \
    python3-venv \
    software-properties-common \
    sudo \
    vim \
    nano \
    htop \
    tmux \
    net-tools \
    iputils-ping \
    gdb \
    valgrind \
    mesa-utils \
    && rm -rf /var/lib/apt/lists/*

# ==============================================================================
# ROS 2 HUMBLE
# ==============================================================================
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key \
    -o /usr/share/keyrings/ros-archive-keyring.gpg

RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] \
    http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" \
    | tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN apt-get update && apt-get install -y \
    ros-humble-desktop \
    ros-humble-ros-base \
    ros-humble-ament-cmake \
    ros-humble-rclcpp \
    ros-humble-rclpy \
    ros-humble-std-msgs \
    ros-humble-geometry-msgs \
    ros-humble-sensor-msgs \
    ros-humble-nav-msgs \
    ros-humble-tf2 \
    ros-humble-tf2-ros \
    ros-humble-tf2-geometry-msgs \
    ros-humble-image-transport \
    ros-humble-cv-bridge \
    ros-humble-vision-opencv \
    ros-humble-diagnostic-updater \
    ros-humble-launch-testing \
    ros-humble-launch-testing-ament-cmake \
    ros-dev-tools \
    python3-rosdep \
    python3-colcon-common-extensions \
    && rm -rf /var/lib/apt/lists/*

RUN rosdep init || true && rosdep update --rosdistro=humble

# ==============================================================================
# GAZEBO CLASSIC 11
# ==============================================================================
RUN apt-get update && apt-get install -y \
    gazebo \
    libgazebo-dev \
    ros-humble-gazebo-ros-pkgs \
    ros-humble-gazebo-ros \
    ros-humble-gazebo-plugins \
    ros-humble-gazebo-msgs \
    && rm -rf /var/lib/apt/lists/*

# ==============================================================================
# PX4 DEPENDENCIES
# ==============================================================================
RUN apt-get update && apt-get install -y \
    astyle \
    genromfs \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    libopencv-dev \
    libeigen3-dev \
    libxml2-dev \
    libxslt1-dev \
    openjdk-11-jdk \
    protobuf-compiler \
    libprotobuf-dev \
    libprotoc-dev \
    unzip \
    zip \
    && rm -rf /var/lib/apt/lists/*

# ==============================================================================
# PX4 ROS 2 INTERFACE (from source - main branch)
# ==============================================================================
WORKDIR /opt/px4_ros/src
# Pinned to exact revisions. A shallow fetch of a specific SHA keeps this as
# fast as --depth 1 while making the result reproducible.
RUN for repo in "px4_msgs:${PX4_MSGS_REV}" "px4_ros_com:${PX4_ROS_COM_REV}"; do \
        name="${repo%%:*}"; rev="${repo##*:}"; \
        mkdir -p "$name" && cd "$name" \
        && git init -q . \
        && git remote add origin "https://github.com/PX4/${name}.git" \
        && git fetch -q --depth 1 origin "$rev" \
        && git checkout -q FETCH_HEAD \
        && cd ..; \
    done

SHELL ["/bin/bash", "-c"]
WORKDIR /opt/px4_ros
RUN source /opt/ros/humble/setup.bash \
    && colcon build --symlink-install

# ==============================================================================
# NS-3 NETWORK SIMULATOR
# ==============================================================================
RUN apt-get update && apt-get install -y \
    g++ \
    python3-setuptools \
    qt5-qmake \
    qtbase5-dev \
    qtchooser \
    libsqlite3-dev \
    gsl-bin \
    libgsl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt
RUN wget https://www.nsnam.org/releases/ns-allinone-${NS3_VERSION}.tar.bz2 \
    && tar xjf ns-allinone-${NS3_VERSION}.tar.bz2 \
    && rm ns-allinone-${NS3_VERSION}.tar.bz2 \
    && cd ns-allinone-${NS3_VERSION} \
    && ./build.py --enable-examples --enable-tests

ENV NS3_HOME=/opt/ns-allinone-${NS3_VERSION}/ns-${NS3_VERSION}
ENV PYTHONPATH=${NS3_HOME}/build/bindings/python:${PYTHONPATH}
ENV LD_LIBRARY_PATH=${NS3_HOME}/build/lib:${LD_LIBRARY_PATH}

# ==============================================================================
# PYTHON ML/RL STACK
# ==============================================================================
RUN pip3 install --upgrade pip setuptools wheel

# apt's python3-sympy shadows the version the PX4 build needs
RUN apt-get update && apt-get remove -y python3-sympy || true \
    && rm -rf /usr/lib/python3/dist-packages/sympy* || true \
    && rm -rf /var/lib/apt/lists/*

# PyTorch first, from the CUDA channel (needs its own index URL, so it cannot
# live in requirements.txt). It bundles its own CUDA runtime.
RUN pip3 install --ignore-installed \
    torch==${TORCH_VERSION} \
    torchvision==${TORCHVISION_VERSION} \
    torchaudio==${TORCHAUDIO_VERSION} \
    --index-url https://download.pytorch.org/whl/${TORCH_CUDA_CHANNEL}

# Everything else pinned together. Installing as one resolve is what prevents a
# later package silently upgrading an earlier pin, which is how the old
# numpy==1.24.3 pin ended up as 1.26.4 at runtime.
COPY requirements.txt requirements-baseline-extra.txt /tmp/
RUN pip3 install --ignore-installed \
        -r /tmp/requirements.txt \
        -r /tmp/requirements-baseline-extra.txt \
    && rm /tmp/requirements.txt /tmp/requirements-baseline-extra.txt

# ==============================================================================
# C++ LIBRARIES FOR MINCO
# ==============================================================================
RUN apt-get update && apt-get install -y \
    libeigen3-dev \
    libceres-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libatlas-base-dev \
    libsuitesparse-dev \
    && rm -rf /var/lib/apt/lists/*

# Header-only; upstream publishes no tags, so this tracks the default branch.
# If MINCO results ever shift unexpectedly, pin this to a SHA first.
RUN git clone https://github.com/ZJU-FAST-Lab/LBFGS-Lite.git /opt/LBFGS-Lite

# ==============================================================================
# CREATE USER
# ==============================================================================
ARG USER_ID=1000
ARG GROUP_ID=1000

RUN groupadd -g ${GROUP_ID} aura || true \
    && useradd -m -u ${USER_ID} -g ${GROUP_ID} -s /bin/bash aura || true \
    && echo "aura ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN chown -R ${USER_ID}:${GROUP_ID} /opt/px4_ros

USER aura
WORKDIR /home/aura

# Set HOME explicitly for PX4 setup script
ENV HOME=/home/aura

# ==============================================================================
# PX4 AUTOPILOT
# PX4 setup script needs HOME set properly, and we skip its bashrc modifications
# ==============================================================================
# Pinned. This is PX4 *main* on the v1.16.0-rc line, NOT the v1.14 that
# CLAUDE.md and the roadmap describe — the previous unpinned clone of the
# default branch is how they drifted apart. Documentation follows the running
# system, not the other way round (roadmap 0.5).
RUN mkdir -p /home/aura/PX4-Autopilot && cd /home/aura/PX4-Autopilot \
    && git init -q . \
    && git remote add origin https://github.com/PX4/PX4-Autopilot.git \
    && git fetch -q --depth 1 origin ${PX4_AUTOPILOT_REV} \
    && git checkout -q FETCH_HEAD \
    && git submodule update --init --recursive --depth 1

# Run PX4 dependencies installer with HOME explicitly set
# The script tries to modify .bashrc, so we ensure it exists and is writable
RUN touch /home/aura/.bashrc \
    && cd /home/aura/PX4-Autopilot \
    && HOME=/home/aura bash ./Tools/setup/ubuntu.sh --no-sim-tools || true

# Build PX4 SITL
RUN cd /home/aura/PX4-Autopilot \
    && make px4_sitl_default

ENV PX4_HOME=/home/aura/PX4-Autopilot

# ==============================================================================
# ENVIRONMENT SETUP
# ==============================================================================
RUN echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc \
    && echo 'source /opt/px4_ros/install/setup.bash' >> ~/.bashrc \
    && echo '[ -f /home/aura/ws/install/setup.bash ] && source /home/aura/ws/install/setup.bash' >> ~/.bashrc \
    && echo 'export PX4_HOME=/home/aura/PX4-Autopilot' >> ~/.bashrc \
    && echo 'source $PX4_HOME/Tools/simulation/gazebo-classic/setup_gazebo.bash $PX4_HOME $PX4_HOME/build/px4_sitl_default' >> ~/.bashrc \
    && echo "export NS3_HOME=${NS3_HOME}" >> ~/.bashrc \
    && echo 'export PYTHONPATH=$NS3_HOME/build/bindings/python:$PYTHONPATH' >> ~/.bashrc \
    && echo 'export GAZEBO_MODEL_PATH=/home/aura/ws/models:$GAZEBO_MODEL_PATH' >> ~/.bashrc \
    && echo 'alias cb="cd /home/aura/ws && colcon build --symlink-install"' >> ~/.bashrc \
    && echo 'alias cbp="cd /home/aura/ws && colcon build --symlink-install --packages-select"' >> ~/.bashrc \
    && echo 'alias ws="cd /home/aura/ws"' >> ~/.bashrc \
    && echo 'alias src="cd /home/aura/ws/src"' >> ~/.bashrc \
    && echo 'alias gpu-test="python3 -c \"import torch; print(f\\\"CUDA: {torch.cuda.is_available()}, GPU: {torch.cuda.get_device_name(0) if torch.cuda.is_available() else None}\\\")\""' >> ~/.bashrc \
    && echo 'echo ""' >> ~/.bashrc \
    && echo 'echo "  A.U.R.A. Development Environment"' >> ~/.bashrc \
    && echo 'echo "  Commands: cb (build), ws (workspace), gpu-test (verify GPU)"' >> ~/.bashrc \
    && echo 'echo ""' >> ~/.bashrc

RUN mkdir -p /home/aura/ws/src

WORKDIR /home/aura/ws
CMD ["/bin/bash"]
