# IoT SRAM PUF Security

This repository contains the code and resources for the research paper on using SRAM PUFs for security in IoT devices. The study demonstrates the implementation of SRAM PUFs on an STM32F407ZGT6 microcontroller and evaluates their reliability, uniqueness, and compliance with security standards.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Results](#results)


## Introduction

The Internet of Things (IoT) faces significant security challenges. This project explores Physical Unclonable Functions (PUFs) as a low-cost, hardware-based security solution for resource-constrained IoT devices. By leveraging inherent fabrication variances, PUFs provide unique, non-replicable identities for devices.

## Project Structure

The project is organized into the following directories:

- `code`: Contains the source code for data acquisition and data processing.
  - `data acquisition`: Contains the Keil software project for reading SRAM power-up values.
    - `puf test/one/Projects/MDK-ARM/atk_f407.uvprojx`: Main project file to start the data acquisition process.
  - `data processing`: Contains Jupyter notebooks for processing the acquired data.
    - `3 voting standard file.ipynb`: Standard file calculation using 3 voting.
    - `5 voting standard file.ipynb`: Standard file calculation using 5 voting.
    - `7 voting standard file.ipynb`: Standard file calculation using 7 voting.
    - `reliability of 3 voting.ipynb`: Reliability analysis of the PUF data.
    - `uniformity.ipynb`: Uniformity analysis of the PUF data.
    - `uniqueness.ipynb`: Uniqueness analysis of the PUF data.
    - `Authentication false rate (theoretical and practical).ipynb`: Authentication false rate analysis and EER calculation.
- `data`: Contains the SRAM power-up values and processed data.
  - `biaozhun.txt`: Standard file calculated using 3 voting.
  - `biaozhunAtB.txt`: Files where `A` represents the number of votes and `B` is just a differentiator.
  - `*.txt`: 35 files, each containing 64KB SRAM power-up values.

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/smallsmallsnake/IoT-SRAM-PUF-Security.git
    cd IoT-SRAM-PUF-Security
    ```

2. Set up the environment:
    - Ensure you have Python and the required libraries installed. You can install the required libraries using:
      ```sh
      pip install -r requirements.txt
      ```

3. Additional steps for setting up the STM32F407ZGT6 microcontroller:
    - Follow the instructions in the `code/data acquisition` folder to set up and program the microcontroller.

## Usage

### Data Acquisition

1. Open the Keil project:
    - Navigate to `IoT-SRAM-PUF-Security/code/data acquisition/puf test/one/Projects/MDK-ARM/atk_f407.uvprojx` and open it with Keil uVision.
    - Build and run the project to collect SRAM power-up values.

### Data Processing

1. Run the Jupyter notebooks to process the acquired data:
    - `3 voting standard file.ipynb`: Calculate the standard file using 3 voting.
    - `5 voting standard file.ipynb`: Calculate the standard file using 5 voting.
    - `7 voting standard file.ipynb`: Calculate the standard file using 7 voting.
    - `reliability of 3 voting.ipynb`: Analyze the reliability of the PUF data.
    - `uniformity.ipynb`: Analyze the uniformity of the PUF data.
    - `uniqueness.ipynb`: Analyze the uniqueness of the PUF data.
    - `Authentication false rate (theoretical and practical).ipynb`: Analyze the authentication false rate and calculate the EER.

## Results

The results of the experiments demonstrate that microcontroller-based SRAM PUFs can achieve similar performance in terms of reliability and security compared to other SRAM PUFs, including those based on ASICs or FPGAs.


