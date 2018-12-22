#!/usr/bin/env python
# coding=utf-8

from setuptools import setup,find_packages

setup(name="weather",
      version="0.1",
      author='rui',
      author_email='',
      packages=find_packages(),
      python_requires='~=3.4',
      install_requires=['requests'],
      entry_points={
        'console_scripts': [
            'weather = command.weather:main'
        ]
    })
