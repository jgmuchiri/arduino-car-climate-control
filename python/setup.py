from setuptools import setup, find_packages

setup(
    name='CarDash',
    version='1.0',
    description='Cardash',
    long_description='Car Dashboard Interface to control climate',
    url='http://github.com/jgmuchiri',
    license='MIT',
    author='John Muchiri',
    author_email='jgmuchiri@gmail.com',
    packages=find_packages(),    
    dependency_links=['http://pypi.python.org/pypi/pyserial'],
    install_requires=[
        "Flask>=0.10.1",
        "pyserial>=3.0.1"
    ],
    include_package_data=True,
    package_data={
        'static': 'cardash/static/*',
        'templates': 'cardash/templates/*'},
    classifiers=[
        "Private :: Do Not Upload"
    ],
)
