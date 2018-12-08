#!/usr/bin/env python
# coding=utf-8

from setuptools import setup,find_packages

setup(name="blockbuster",
      version="0.1",
      author='nunum',
      author_email='ntmg.22@gmail.com',
      url='https://github.com/NunuM/movies_command',
      description='Search for your favourite movies',
      packages=find_packages(),
      python_requires='~=3.4',
      install_requires=[
          'configparser', 'requests'
      ],
      entry_points={
        'console_scripts': [
            'blockbuster = command.pirate:main'
        ]
    })
