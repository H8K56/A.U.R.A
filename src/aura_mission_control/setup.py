from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'aura_mission_control'

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
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Hussein Khadra',
    maintainer_email='khadrahussein4@gmail.com',
    description='Mission state machine and swarm orchestration for A.U.R.A.',
    license='MIT',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'mission_control_node = aura_mission_control.mission_control_node:main',
            'mission_monitor = aura_mission_control.mission_monitor:main',
        ],
    },
)
