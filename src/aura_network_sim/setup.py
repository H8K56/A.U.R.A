from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'aura_network_sim'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools', 'numpy'],
    zip_safe=True,
    maintainer='Hussein Khadra',
    maintainer_email='khadrahussein4@gmail.com',
    description='Network simulation for A.U.R.A. UAV swarm',
    license='MIT',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'network_sim_node = aura_network_sim.network_sim_node:main',
            'coverage_calculator_node = aura_network_sim.coverage_calculator_node:main',
            'mesh_visualizer_node = aura_network_sim.mesh_visualizer_node:main',
        ],
    },
)
