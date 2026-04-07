from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'aura_simulation'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        (os.path.join('share', package_name, 'worlds'), glob('worlds/*.sdf')),
    ],
    install_requires=['setuptools', 'numpy'],
    zip_safe=True,
    maintainer='Hussein Khadra',
    maintainer_email='khadrahussein4@gmail.com',
    description='Simulation environment for A.U.R.A. disaster relief UAV swarm',
    license='MIT',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'sim_swarm_driver = aura_simulation.sim_swarm_driver:main',
            'dead_zone_publisher = aura_simulation.dead_zone_publisher:main',
            'scenario_runner = aura_simulation.scenario_runner:main',
        ],
    },
)
