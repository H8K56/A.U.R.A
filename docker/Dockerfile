# ==============================================================================
# A.U.R.A. Development Container
# Ubuntu 22.04 + ROS 2 Humble + Gazebo Classic + PX4 SITL + NS-3 + PufferLib
# 
# GPU: RTX 5050 / CUDA 13.0 / Driver 580.x supported via nvidia-container-toolkit
# ==============================================================================

FROM ubuntu:22.04

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
# Clone PX4 ROS message and ROS communication packages (shallow)
RUN git clone --depth 1 https://github.com/PX4/px4_msgs.git \
    && git clone --depth 1 https://github.com/PX4/px4_ros_com.git

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
RUN wget https://www.nsnam.org/releases/ns-allinone-3.40.tar.bz2 \
    && tar xjf ns-allinone-3.40.tar.bz2 \
    && rm ns-allinone-3.40.tar.bz2 \
    && cd ns-allinone-3.40 \
    && ./build.py --enable-examples --enable-tests

ENV NS3_HOME=/opt/ns-allinone-3.40/ns-3.40
ENV PYTHONPATH=${NS3_HOME}/build/bindings/python:${PYTHONPATH}
ENV LD_LIBRARY_PATH=${NS3_HOME}/build/lib:${LD_LIBRARY_PATH}

# ==============================================================================
# PYTHON ML/RL STACK
# ==============================================================================
RUN pip3 install --upgrade pip setuptools wheel

RUN pip3 install \
    numpy==1.24.3 \
    scipy==1.11.4 \
    pandas==2.0.3 \
    matplotlib==3.7.5 \
    seaborn==0.13.0 \
    scikit-learn==1.3.2

RUN apt-get update && apt-get remove -y python3-sympy || true \
    && rm -rf /usr/lib/python3/dist-packages/sympy* || true \
    && pip3 install --ignore-installed sympy mpmath \
    && rm -rf /var/lib/apt/lists/*
# PyTorch with CUDA (bundles own CUDA runtime - works with any driver)
RUN pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu124

RUN pip3 install \
    pufferlib \
    gymnasium==0.29.1 \
    stable-baselines3==2.2.1 \
    tensorboard==2.15.1 \
    wandb==0.16.1

RUN pip3 install \
    pyyaml==6.0.1 \
    rich==13.7.0 \
    typer==0.9.0 \
    pytest==7.4.3 \
    black==23.12.1 \
    ruff==0.1.8

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
RUN git clone https://github.com/PX4/PX4-Autopilot.git --depth 1 --recursive /home/aura/PX4-Autopilot

# Run PX4 dependencies installer with HOME explicitly set
# The script tries to modify .bashrc, so we ensure it exists and is writable
RUN touch /home/aura/.bashrc \
    && cd /home/aura/PX4-Autopilot \
    && HOME=/home/aura bash ./Tools/setup/ubuntu.sh --no-sim-tools || true

# Build PX4 SITL
RUN cd /home/aura/PX4-Autopilot \
    && make px4_sitl_default

ENV PX4_HOME=/home/aura/PX4-Autopilot #==============================================================================
# ENVIRONMENT SETUP
# ==============================================================================
RUN echo 'source /opt/ros/humble/setup.bash' >> ~/.bashrc \
    && echo 'source /opt/px4_ros/install/setup.bash' >> ~/.bashrc \
    && echo '[ -f /home/aura/ws/install/setup.bash ] && source /home/aura/ws/install/setup.bash' >> ~/.bashrc \
    && echo 'export PX4_HOME=/home/aura/PX4-Autopilot' >> ~/.bashrc \
    && echo 'source $PX4_HOME/Tools/simulation/gazebo-classic/setup_gazebo.bash $PX4_HOME $PX4_HOME/build/px4_sitl_default' >> ~/.bashrc \
    && echo 'export NS3_HOME=/opt/ns-allinone-3.40/ns-3.40' >> ~/.bashrc \
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
