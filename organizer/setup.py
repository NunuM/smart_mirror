#!/usr/bin/env python
# coding=utf-8

from setuptools import setup,find_packages

setup(name="organizer",
      version="0.1",
      author='nunum',
      author_email='ntmg.22@gmail.com',
      url='https://github.com/NunuM/movies_command',
      description='Organize you life, create notes and be notified',
      packages=find_packages(),
      python_requires='~=3.4',
      install_requires=[
          'configparser', 'requests', 'pytz'
      ],
      entry_points={
        'console_scripts': [
            'organizer = command.todo:main',
            'organizerd = daemon.daemon:main'
        ]
    })
