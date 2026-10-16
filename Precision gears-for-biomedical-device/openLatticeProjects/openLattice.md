# Medical Engineering, Computational Architecture & Biometrics

**Open-source research and engineering portfolio**

A collection of experimental projects exploring medical engineering, parametric architecture, computational modeling, biometric authentication, and AI-assisted healthcare technologies.

The central project is **BoneScaffoldAI**, a parametric 3D porous scaffold generator built with OpenSCAD. The broader goal is to connect geometric design, medical imaging, simulation, and secure biometric systems through reproducible software engineering.

> **Disclaimer:** These projects are for education, research, and engineering prototyping. They are not medical devices, diagnostic systems, or clinically validated implants. Any medical application requires appropriate independent validation, qualified professional oversight, and applicable regulatory review.

## Table of Contents

- [1. Featured Project: BoneScaffoldAI](#1-featured-project-bonescaffoldai)
- [2. Medical Engineering Projects](#2-medical-engineering-projects)
- [3. Computational Architecture](#3-computational-architecture)
- [4. Biometric Systems](#4-biometric-systems)
- [5. System Architecture](#5-system-architecture)
- [6. Technology Stack](#6-technology-stack)
- [7. Repository Structure](#7-repository-structure)
- [8. Installation and Usage](#8-installation-and-usage)
- [9. Validation and Testing](#9-validation-and-testing)
- [10. Privacy, Safety and Ethics](#10-privacy-safety-and-ethics)
- [11. Development Roadmap](#11-development-roadmap)
- [12. Open-Source Resources](#12-open-source-resources)
- [13. Contributing](#13-contributing)
- [14. License](#14-license)

---

## 1. Featured Project: BoneScaffoldAI

**BoneScaffoldAI** is a parametric computer-aided design prototype for generating porous cylindrical scaffold geometries.

The initial implementation uses OpenSCAD to construct a lattice from interconnected rounded struts, with optional end plates and an axial mounting hole. It also supports importing an externally generated STL mesh.

### Current capabilities

- Parametric specimen diameter and height.
- Adjustable lattice cell spacing and strut radius.
- Three-dimensional vertical and horizontal lattice members.
- Cylindrical boundary clipping.
- Optional top and bottom plates.
- Optional central mounting hole.
- STL mesh import and scaling.
- Script-based, reproducible geometry generation.

### Example configuration

```scad
model_mode = "lattice";

scaffold_diameter = 12;
scaffold_height = 20;

cell_size = 4;
strut_radius = 0.55;

stl_scale = 1.0;
stl_file = "../meshes/scaffold.stl";

add_end_plates = false;
plate_thickness = 1.0;
plate_extra_radius = 0.5;

add_center_hole = false;
center_hole_diameter = 2.0;

$fn = 32;
```

The dimensions are expressed in millimetres by convention. OpenSCAD itself does not enforce physical units.

### How it works

1. Define the overall specimen dimensions.
2. Generate vertical struts on a regular grid.
3. Add horizontal members along the X and Y axes.
4. Intersect the resulting lattice with a cylindrical boundary.
5. Optionally add end plates or subtract a central hole.
6. Render the geometry and export an STL for further inspection.

### Potential extensions

| Extension | Objective |
|---|---|
| Gyroid structures | Generate continuous triply periodic porous surfaces |
| Graded porosity | Vary geometric density across a specimen |
| Image-derived geometry | Explore geometry informed by medical image segmentation |
| Mesh analysis | Measure connected components, defects and surface quality |
| Finite element analysis | Investigate mechanical response under defined loading assumptions |
| Design optimization | Compare candidate geometries against predefined engineering objectives |
| Visualization dashboard | Display parameters, mesh statistics and simulation results |

**Important limitation:** the existing lattice is a simplified geometric model. It does not automatically provide controlled porosity, interconnected pore sizes, validated mechanical performance, or biological suitability. Those properties must be measured or established separately.

---

## 2. Medical Engineering Projects

### 2.1 Medical Image Segmentation

Build a research pipeline that converts anonymized medical images into segmented anatomical models.

**Suggested technologies**
- Python
- [Project MONAI](https://github.com/Project-MONAI/MONAI)
- [3D Slicer](https://github.com/Slicer/Slicer)
- NumPy and SimpleITK

**Workflow**

`Medical images → preprocessing → segmentation → 3D surface → mesh inspection`

Possible experiments include bone segmentation, anatomical surface reconstruction, and comparison between manually annotated and model-generated masks.

### 2.2 Patient-Specific Geometry Research

Explore how segmented anatomical surfaces can be transformed into parametric geometry for engineering studies.

Potential features:
- Surface smoothing and mesh repair.
- Landmark-based alignment.
- Coordinate system transformations.
- Anatomical measurements.
- Export to STL or other supported mesh formats.
- Comparison between original and reconstructed surfaces.

This project should use authorized datasets and preserve the distinction between an anatomical reconstruction and a clinically approved device design.

### 2.3 Computational Biomechanics

Develop a simulation pipeline for studying simplified mechanical structures.

Possible tools:
- [Gmsh](https://github.com/live-clones/gmsh) for mesh generation.
- [CalculiX](https://github.com/Dhondtguido/CalculiX) for finite element analysis.
- Python for preprocessing and results analysis.

Potential outputs include displacement fields, stress distributions, mesh convergence plots, and comparisons between lattice configurations.

Simulation results depend on the geometry, material model, boundary conditions, loads, and numerical assumptions. They should not be interpreted as evidence of clinical performance without appropriate verification and validation.

### 2.4 Medical Data Visualization

Create a dashboard for displaying engineering and research measurements.

Example metrics:
- Specimen dimensions.
- Estimated solid volume and porosity.
- Mesh triangle count.
- Connected-component count.
- Simulation displacement and stress statistics.
- Image segmentation overlap metrics.

Use synthetic or appropriately authorized data for demonstrations.

---

## 3. Computational Architecture

This section focuses on architectural systems, parametric modeling, and the design of reproducible engineering workflows.

### 3.1 Parametric Design Engine

Create a reusable geometry generator that accepts a parameter configuration and produces a 3D model.

Potential inputs:
- Overall dimensions.
- Lattice topology.
- Cell spacing.
- Beam or strut dimensions.
- Boundary shape.
- Optional mounting features.

Potential outputs:
- OpenSCAD source.
- STL mesh.
- JSON parameter manifest.
- Geometry validation report.

A future version could support multiple topologies through a common interface instead of relying on a single hard-coded lattice.

### 3.2 Generative and Bio-Inspired Structures

Investigate cellular materials, periodic lattices, and surface-based geometries.

Candidate design families include:
- Cubic lattices.
- Octet-truss lattices.
- Voronoi structures.
- Gyroid surfaces.
- Functionally graded structures.

The objective is to compare geometry, connectivity, manufacturability, and computational cost rather than assume that one structure is universally superior.

### 3.3 Digital Twin Research

Build a prototype that links a geometric model with simulated or measured data.

A simple architecture could contain:

- **Geometry layer:** parametric CAD and mesh assets.
- **Data layer:** configuration files and experimental results.
- **Simulation layer:** numerical models and solver outputs.
- **Visualization layer:** 3D viewer and engineering dashboard.
- **Reporting layer:** reproducible summaries and plots.

Initially, the system can operate entirely on simulated data. Real sensor or laboratory integrations can be added when suitable hardware and validated data sources are available.

### 3.4 Automated CAD Pipeline

A useful engineering automation project would:

1. Read a version-controlled parameter file.
2. Generate a model using OpenSCAD.
3. Export the resulting geometry.
4. Run mesh and dimensional checks.
5. Save a report with the model and software versions.
6. Store artifacts alongside the corresponding source revision.

This makes experiments easier to reproduce and compare.

---

## 4. Biometric Systems

Biometric projects should be developed as independent security and privacy research modules. They should not require medical imaging or patient identifiers unless a clearly justified, authorized use case requires them.

### 4.1 Face Detection and Image Analysis

Build a computer vision demonstration that detects faces in consented or synthetic images.

Suggested technology: [OpenCV](https://github.com/opencv/opencv).

Possible functionality:
- Face detection.
- Image quality assessment.
- Lighting and pose analysis.
- Detection performance evaluation.
- Comparison of false-positive and false-negative rates.

Face detection identifies the presence or location of a face; it does not, by itself, establish a person's identity.

### 4.2 Fingerprint Image Processing

Develop a research tool for exploring fingerprint image quality and feature extraction using authorized sample images.

Possible functionality:
- Image normalization.
- Ridge enhancement.
- Orientation-field visualization.
- Quality scoring.
- Synthetic sample generation.
- Evaluation using documented benchmark datasets.

Do not store raw fingerprint images or reusable biometric templates unnecessarily.

### 4.3 Secure Biometric Authentication

Design a demonstration authentication system that combines an application with a device-supported authenticator.

Suggested standard: [W3C WebAuthn](https://github.com/w3c/webauthn).

WebAuthn allows applications to use public-key credentials. A device may use a fingerprint, face recognition, a PIN, or another local mechanism to authorize credential use, depending on the authenticator and its configuration.

A prototype could implement:

- User registration.
- Challenge generation.
- Public-key credential registration.
- Authentication challenge verification.
- Session management.
- Rate limiting and audit events.

**Security principle:** the application should not need to collect or centrally store raw fingerprints or face images to use WebAuthn. Biometric verification is typically performed locally by the authenticator.

### 4.4 Biometric Performance Evaluation

Measure system behavior using a documented evaluation procedure.

Useful metrics include:

- False Acceptance Rate (FAR).
- False Rejection Rate (FRR).
- Equal Error Rate (EER), where appropriate.
- Authentication latency.
- Failure-to-acquire rate.
- Performance across relevant test conditions.

These metrics are not interchangeable. Report the dataset, operating threshold, sample sizes, and test protocol alongside each result. Avoid claiming demographic fairness or production-grade security from small demonstrations.

---

## 5. System Architecture

A possible long-term architecture connects the projects through shared interfaces without coupling their sensitive data.

```text
                    ENGINEERING WORKSPACE
                             |
               +-------------+-------------+
               |             |             |
          Medical AI    Parametric CAD   Biometrics
               |             |             |
          Segmentation   OpenSCAD / STL  WebAuthn
               |             |             |
               +-------------+-------------+
                             |
                     Validation Layer
                             |
              +--------------+--------------+
              |              |              |
          Data Checks    Mesh Checks    Security Tests
              |              |              |
              +--------------+--------------+
                             |
                  Reports and Visualization
```

### Architectural principles

- Keep each project modular and independently testable.
- Use explicit interfaces between geometry, simulation, and visualization.
- Separate authentication credentials from engineering datasets.
- Avoid storing sensitive medical or biometric information in Git.
- Version configuration files and document model assumptions.
- Maintain reproducible environments and automated tests.
- Treat generated models and simulation results as research artifacts, not clinical evidence.

---

## 6. Technology Stack

| Area | Recommended technologies |
|---|---|
| Parametric CAD | OpenSCAD |
| Programming | Python, C++, JavaScript or TypeScript |
| Medical AI | MONAI, PyTorch |
| Medical imaging | 3D Slicer, SimpleITK |
| Mesh generation | Gmsh |
| Numerical simulation | CalculiX |
| Computer vision | OpenCV |
| Authentication | WebAuthn, FIDO-compatible authenticators |
| Visualization | Matplotlib, Plotly, a suitable 3D viewer |
| Data exchange | STL, JSON, CSV, NIfTI or DICOM where appropriate |
| Version control | Git and GitHub |
| Testing | pytest, automated geometry checks, CI workflows |
| Documentation | Markdown and reproducible notebooks |

Select dependencies based on the requirements of each module, and verify their licenses and compatibility before distribution.

---

## 7. Repository Structure

A possible monorepository layout is:

```text
medical-engineering-lab/
├── README.md
├── LICENSE
├── CONTRIBUTING.md
├── SECURITY.md
├── .gitignore
│
├── projects/
│   ├── BoneScaffoldAI/
│   │   ├── README.md
│   │   ├── openscad/
│   │   │   └── scaffold.scad
│   │   ├── meshes/
│   │   │   └── .gitkeep
│   │   ├── configs/
│   │   │   └── default.json
│   │   └── tests/
│   │
│   ├── medical-imaging/
│   │   ├── README.md
│   │   ├── src/
│   │   └── tests/
│   │
│   ├── computational-architecture/
│   │   ├── README.md
│   │   ├── models/
│   │   └── simulations/
│   │
│   └── biometric-authentication/
│       ├── README.md
│       ├── backend/
│       ├── frontend/
│       └── tests/
│
├── shared/
│   ├── validation/
│   └── visualization/
│
├── docs/
│   ├── architecture.md
│   ├── validation-plan.md
│   └── threat-model.md
│
└── .github/
    └── workflows/
        └── tests.yml
```

This is a proposed structure, not a description of files already present in the current prototype.

---

## 8. Installation and Usage

### Prerequisites

- Git.
- OpenSCAD.
- Python, if using the optional analysis tools.
- A mesh inspection tool for reviewing exported geometry.

### Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/medical-engineering-lab.git
cd medical-engineering-lab
```

Replace `YOUR_USERNAME` with your GitHub username after creating the repository.

### Run the scaffold prototype

1. Open `projects/BoneScaffoldAI/openscad/scaffold.scad` in OpenSCAD.
2. Set `model_mode = "lattice"`.
3. Adjust the dimensions and lattice parameters.
4. Preview the geometry.
5. Run a full render.
6. Export the model as STL.
7. Inspect the mesh independently before using it in downstream engineering workflows.

For imported geometry, set `model_mode = "import"` and ensure the configured STL path points to an existing file.

### Reproducibility

Record the parameter values, software versions, mesh export settings, and validation results for every experiment. Keep large generated files and all sensitive source data out of Git unless there is a clear, appropriate reason to include them.

---

## 9. Validation and Testing

Validation should be specific to each project's intended purpose.

### BoneScaffoldAI

- [ ] Confirm that dimensions match the configured values.
- [ ] Check for disconnected components and unintended gaps.
- [ ] Inspect mesh watertightness and surface normals.
- [ ] Measure porosity and pore-size distributions using a documented method.
- [ ] Check how parameter changes affect geometry.
- [ ] Compare mesh quality across export settings.
- [ ] Define appropriate mechanical simulation assumptions before interpreting results.
- [ ] Document limitations and unresolved defects.

### Medical imaging

- [ ] Use appropriately licensed, authorized datasets.
- [ ] Verify image orientation, spacing, and coordinate transforms.
- [ ] Document preprocessing and segmentation methods.
- [ ] Evaluate against independent reference annotations where available.
- [ ] Report uncertainty and limitations.

### Biometric authentication

- [ ] Test valid and invalid authentication attempts.
- [ ] Validate challenge handling and session expiration.
- [ ] Check replay resistance and rate limiting.
- [ ] Assess credential recovery and account deletion.
- [ ] Minimize sensitive data collection.
- [ ] Document the threat model and test conditions.

Passing software tests does not establish clinical validity, material safety, biometric fairness, or resistance to every security attack.

---

## 10. Privacy, Safety and Ethics

Medical and biometric systems require particular care because their data can be sensitive and difficult to replace.

- Do not commit identifiable patient data, raw biometric samples, private keys, credentials, or access tokens.
- Use synthetic data or appropriately authorized datasets for public demonstrations.
- Document dataset provenance, licenses, and permitted uses.
- Minimize data collection and define retention and deletion procedures.
- Apply access controls and encryption where appropriate.
- Evaluate bias, accessibility, security, and failure modes.
- Do not use experimental outputs to make clinical decisions.
- Obtain appropriate specialist review before considering real-world medical deployment.

For European deployments, assess the applicability of GDPR and other relevant requirements. Medical-device and AI obligations depend on the system's intended purpose, design, and deployment context.

---

## 11. Development Roadmap

### Phase 1 — Geometry prototype

- [x] Implement a basic parametric lattice.
- [x] Support optional end plates and a central hole.
- [x] Support importing an STL mesh.
- [ ] Add automated geometry validation.
- [ ] Document export and inspection procedures.

### Phase 2 — Engineering analysis

- [ ] Generate alternative lattice topologies.
- [ ] Add geometric measurements and porosity estimation.
- [ ] Create a repeatable mesh-generation pipeline.
- [ ] Run controlled numerical experiments.
- [ ] Generate comparative engineering reports.

### Phase 3 — Medical imaging integration

- [ ] Add a small, authorized example dataset.
- [ ] Explore image segmentation using MONAI.
- [ ] Reconstruct surfaces from segmentation masks.
- [ ] Document coordinate systems and geometry transformations.

### Phase 4 — Biometric security prototype

- [ ] Implement WebAuthn registration and authentication.
- [ ] Add automated authentication tests.
- [ ] Define a threat model.
- [ ] Document privacy and credential lifecycle management.

### Phase 5 — Integrated research platform

- [ ] Create a unified dashboard.
- [ ] Add experiment and configuration tracking.
- [ ] Automate testing through GitHub Actions.
- [ ] Publish reproducible demonstrations and technical documentation.

---

## 12. Open-Source Resources

The following repositories are useful starting points for building these projects. Review their current documentation, licenses, and dependency requirements before integrating them.

| Resource | What it offers |
|---|---|
| [OpenSCAD](https://github.com/openscad/openscad) | Script-based parametric CAD and solid geometry |
| [MONAI](https://github.com/Project-MONAI/MONAI) | Deep learning tools for medical imaging |
| [3D Slicer](https://github.com/Slicer/Slicer) | Medical image visualization and analysis |
| [Gmsh](https://github.com/live-clones/gmsh) | Mesh generation and finite element preprocessing |
| [CalculiX](https://github.com/Dhondtguido/CalculiX) | Finite element analysis |
| [OpenCV](https://github.com/opencv/opencv) | Computer vision and image processing |
| [W3C WebAuthn](https://github.com/w3c/webauthn) | Web authentication standard development |

These are external projects, not components already integrated into BoneScaffoldAI. See the [MONAI documentation](https://project-monai.github.io/) for medical AI guidance and the [WebAuthn specification](https://www.w3.org/TR/webauthn/) for authentication protocol details.

---

## 13. Contributing

Contributions are welcome for engineering experiments, geometry improvements, reproducibility, documentation, testing, and privacy-conscious security demonstrations.

Suggested workflow:

1. Open an issue describing the proposed change.
2. Explain the intended purpose and relevant assumptions.
3. Include tests or reproducible examples.
4. Document known limitations.
5. Submit a pull request for review.

Contributions must respect the licensing terms of dependencies and datasets and must not introduce private medical or biometric data.

---

## 14. License

Choose a license appropriate to the project and its dependencies before publishing.

For example, the MIT License may suit some general-purpose software components, while other licenses may be more appropriate for specific datasets, research assets, or dependencies. A software license does not establish clinical approval or authorize uses prohibited by other applicable requirements.

---

**Project vision:** Build an open, modular research environment that connects parametric geometry, medical engineering, computational simulation, and privacy-conscious biometric authentication through reproducible and testable software.

*BoneScaffoldAI is the initial engineering prototype. Medical imaging, simulation, and biometric modules are proposed extensions and should be described as implemented only after their functionality has been developed and tested.*

