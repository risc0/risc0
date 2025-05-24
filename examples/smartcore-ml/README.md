# RISC Zero Rust SmartCore Machine Learning Template

This template is intended to give you a framework for using the RISC Zero ZKVM to perform verifiable inference using machine learning models from the Rust SmartCore library.  The following models are currently supported:

Classifiers: Logistic Regression, Decision Trees, Random Forests, K Nearest Neighbors, Naive Bayes, and Support Vector Machines.  (Support Vector Machine and Support Vector Regression are supported using a forked version of SmartCore.)

Regression:  Linear Regression, Lasso, Ridge, and Elastic Net.

Clustering:  K-Means, DBSCAN.

Dimensionality Reduction:  PCA.

Matrix Decomposition:  SVD, Eigenvalue Decomposition, QR, LU.

The following folders are not part of the standard RISC Zero starter template and should be added if the user wishes to replicate the layout of this template:  res/ml-model, res/input-data, the SmartCore Jupyter notebook, and the iris input data and classes CSV files.  The ml-model folder contains a json file of a trained decision tree model and input-data contains a json file of sample input data.  You can train and export your model along with any sample data in the Jupyter notebook.

res/ml-model and res/input-data come preloaded with a trained decision tree classifier.  You can replace the code in the Jupyter notebook to train and export any of the supported models listed above.

## Model Types

It is important to specify the generic types for each model so that they can be successfully deserialized.  The input data for a trained model is typically formatted as a DenseMatrix, so be sure to add the following import:
`use smartcore::linalg::basic::matrix::DenseMatrix;`
when using KNN, be sure to add the following import:
`use smartcore::metrics::distance::euclidean::Euclidean;`
A list of the supported models with definitions for their respective types can be found below.  Note that {float} is a placeholder for either f32 or f64:

```rust
let model: DecisionTreeClassifier<{float}, u32, DenseMatrix<{float}>, Vec<u32>> = trained_model;
```

```rust
let model: RandomForestClassifier<{float}, u8, DenseMatrix<{float}>, Vec<u8>> = trained_model;
```

```rust
let model: GaussianNB<{float}, _, DenseMatrix<{float}>, _> = trained_model;
```

```rust
let model: LogisticRegression<{float}, u32, DenseMatrix<{float}>, Vec<u32>> = trained_model;
```

```rust
let model: LinearRegression< {float}, {float}, DenseMatrix<{float}>, Vec<{float}>> = trained_model;
```

```rust
let model: KNNClassifier< {float}, u32, DenseMatrix<{float}>, Vec<u32>, Euclidean<{float}>> = trained_model;
```

```rust
let model: KMeans<{float}, u8, DenseMatrix<{float}>, Vec<u8>> = trained_model;
```

```rust
let model: PCA<{float}, DenseMatrix<{float}>> = trained_model;
```

NOTE:  Deserialization of SVC and SVR does not include that `SVCParametersmake` field.  It must be added back into the model struct manually after deserialization.  The RISC Zero SmartCore fork has amended the visibility of the model `struct`, making the parameters field public and thereby allowing the parameters field to be directly inserted into the model struct after deserialization.  You must insert the same parameters that were used when training the model.

```rust
let mut model: SVC<{float}, i32, DenseMatrix<{float}>, Vec<i32>> = deserialized_svc_trained;
let params = &SVCParameters::default().with_c(200.0).with_kernel(Kernels::linear());
model.parameters = Some(params);
```

```rust
let mut model: SVR< '_, {float}, DenseMatrix<{float}>, Vec<{float}>> = deserialized_model;
//make sure to use the same SVRParameters used to train the model
let params = &SVRParameters::default().with_eps(2.0).with_c(10.0).with_kernel(Kernels::linear());
model.parameters = params;
```

SVM models support four kernels:  Gaussian (rbf), Linear, Polynomial, and Sigmoid.  Kernels are selected within the `.with_kernel()` function in the `SVCParameters` or `SVRParameters`.  Specify the desired kernel as follows:

- Kernel::linear()
- Kernel::rbf()
- Kernel::polynomial()
- Kernel::sigmoid()

## SmartCore

The source code for SmartCore can be found here:  [https://github.com/smartcorelib/smartcore](https://github.com/smartcorelib/smartcore)

You can find other model implementations and additional SmartCore features here:  [https://github.com/smartcorelib/smartcore-jupyter/tree/main/notebooks](https://github.com/smartcorelib/smartcore-jupyter/tree/main/notebooks)

## Jupyter notebook

In order to run Rust code from a Jupyter notebook, you will need to have the Rust kernel installed.  Installation instructions for the kernel and for Jupyter can be found here:
[https://github.com/evcxr/evcxr/blob/main/evcxr\_jupyter/README.md](https://github.com/evcxr/evcxr/blob/main/evcxr_jupyter/README.md)
