# RISC Zero Rust SmartCore Machine Learning Template

This template is intended to give you a framework for using the RISC Zero ZKVM to perform verifiable inference using machine learning models from the Rust SmartCore library.  The following models are currently supported:

Classifiers: Logistic Regression, Decision Trees, Random Forests, K Nearest Neighbors, Naive Bayes, and Support Vector Machines.  (Support Vector Machine and Support Vector Regression are supported using a forked version of SmartCore.)

Regression:  Linear Regression, Lasso, Ridge, and Elastic Net.

Clutering:  K-Means, DBSCAN.

Dimensionality Reduction:  PCA.

Matrix Decomposition:  SVD, Eigenvalue Decomposition, QR, LU.

The following folders are not part of the standard RISC Zero starter template and should be added if the user wishes to replicate the layout of this template:  res/ml-model, res/input-data, and train-model.  ml-model contains a json file of a trained decision tree model and input-data contains a json file of sample input data.  You can train and export your model along with any sample data in train-model/src/main.rs (note that this is excluded from the zkvm workspace).  

res/ml-model and res/input-data come preloaded with a trained decision tree classifier.  You can replace the code in train-model to train and export any of the supported models listed above.

## Model Types

It is important to specificy the generic types for each model so that they can be succesfully deserialized.  The input data for a trained model is typically formatted as a DenseMatrix, so be sure to add the following import: 
`use smartcore::linalg::basic::matrix::DenseMatrix;`
when using KNN, be sure to add the following import:
`use smartcore::metrics::distance::euclidian::Euclidian;`
A list of the supported models with definitions for their respective types can be found below.  Note that {float} is a placeholder for either f32 or f64:

```
let model: DecisionTreeClassifier<{float}, u32, DenseMatrix<{float}>, Vec<u32>> = trained_model;
```

```
let model: RandomForestClassifier<{float}, u8, DenseMatrix<{float}>, Vec<u8>> = trained_model;
```

```
let model: GaussianNB<{float}, _, DenseMatrix<{float}>, _> = trained_model;
```

```
let model: LogisticRegression<{flaot}, u32, DenseMatrix<{float}>, Vec<u32>> = trained_model;
```

```
let model: LinearRegression< {float}, {float}, DenseMatrix<{float}>, Vec<{float}>> = trained_model;
```

```
let model: KNNClassifier< {float}, u32, DenseMatrix<{float}>, Vec<u32>, Euclidian<{float}>> = trained_model;
```

```
let model: KMeans<{float}, u8, DenseMatrix<{float}>, Vec<u8>> = trained_model;
```

```
let model: PCA<{float}, DenseMatrix<{float}>> = trained_model;
```

NOTE:  For Support Vector Machine classifiers and regression models, you MUST use the following smartcore fork and import into you cargo.toml file:

smartcore = { git = "https://github.com/Roee-87/smartcore.git", features = ["serde"]}

Deserialization of SVC and SVR does not includes that SVCParametersmake field.  It must be added back into the model struct manually after deserialization.  The SVC and SVR fork have ammended the visbility of the model struct, making the parameters field public and thereby allowing the parameters field to be directly inserted into the model struct after dserialization.  You must insert the same parameters that were used when training the model.
```
let mut model: SVC<{float}, i32, DenseMatrix<{float}>, Vec<i32>> = deserialized_svc_trained;
let params = &SVCParameters::default().with_c(200.0).with_kernel(Kernels::linear());
model.parameters = Some(params);
```

```
let mut model: SVR< '_, {float}, DenseMatrix<{float}>, Vec<{float}>> = deserialized_model;
//make sure to use the same SVRParameters used to train the model
let params = &SVRParameters::default().with_eps(2.0).with_c(10.0).with_kernel(Kernels::linear());
model.parameters = params;
```

SVM models support four kernels:  Gaussian (rbf), Linear, Polynomial, and Sigmoid.  Kernels are selected within the .with_kernel() function in the SVCParameters or SVRParameters.
Kernel::linear()
Kernel::rbf()
Kernel::polynomial()
Kernel::sigmoid()

## Quick Start

First, [install](https://dev.risczero.com/zkvm/install) RISC Zero's zkVM tools if you don't already have them.

To build all methods and execute the method within the zkVM, run the following command:

```
cargo run
```
### Running proofs remotely on Bonsai

*Note: The Bonsai proving service is still in early Alpha; an API key is required for access. [Click here to request access].*

If you have access to the URL and API key to Bonsai you can run your proofs
remotely. To prove in Bonsai mode, invoke `cargo run` with two additional
environment variables:

```
BONSAI_API_KEY="YOUR_API_KEY" BONSAI_API_URL="BONSAI_URL" cargo run
```

[Click here to request access]: https://bonsai.xyz/apply

## How to create a project based on this template




## Contributor's Guide
We welcome contributions to documentation and code via PRs and GitHub Issues on our [main repository](http://www.github.com/risc0) or any of our other repositories.

## Video Tutorial

## Questions, Feedback, and Collaborations
We'd love to hear from you on [Discord](https://discord.gg/risczero) or [Twitter](https://twitter.com/risczero).

[Structure of a zkVM Application]: https://dev.risczero.com/zkvm/developer-guide/zkvm-app-structure
