#!/usr/bin/env python
# coding=utf-8

from setuptools import setup,find_packages

setup(name="gcalendarevents",
      version="0.1",
      author='rui',
      author_email='1140475@isep.ipp.pt',
      packages=find_packages(),
      python_requires='~=2.7',
      install_requires=['google-api-python-client','oauth2client'],
      entry_points={
        'console_scripts': [
            'gcalendarevents = command.gcalander_events:main'
        ]
    }
)
