from setuptools import setup, find_packages
import os
from glob import glob

package_name = 'aura_strategic_rl'

setup(
    name=package_name,
    version='0.1.0',

    packages=find_packages(exclude=['test']),

    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
            glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'),
            glob('config/*.yaml')),
    ],

    install_requires=[
        'setuptools',
        'numpy',
        'torch',
        'gymnasium',
    ],

    extras_require={
        'test': ['pytest'],
    },

    zip_safe=True,

    maintainer='Hussein Khadra',
    maintainer_email='khadrahussein4@gmail.com',

    description='Strategic RL policy for A.U.R.A. UAV swarm positioning',
    license='MIT',

    entry_points={
        'console_scripts': [
            'strategic_rl_node = aura_strategic_rl.strategic_rl_node:main',
            'baseline_hho = aura_strategic_rl.baseline_hho:main',
            'train_policy = aura_strategic_rl.train_policy:main',
        ],
    },
)