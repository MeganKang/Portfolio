# We Inspect Machine Learning Studio Project

## 📌 Project Overview
This project analyzes symptoms and mold species in order to find patterns to be able to predict one from the other. It demonstrates data cleaning, preprocessing, and visualization using **Python** and model building using **Sci-kitlearn**, **Matplotlib**, **Numpy** and **Pandas**.

## 📊 Datasets and Tools Used
- `WeInspectData` - Contains client survey information from location, mold species found in their homes, illness diagnoses, symptoms categorized by area of affect.
  - Data source: Provided by We Inspect

## 🛠️ Machine Learning Skills Demonstrated
## 1️ Data Cleaning
- `df`, `pandas` for loading the csv file into a dataframe, reading the dataset
- Removing unnecessary symbols such as `astericks` and `whitespaces`
- Changing `obj type` to `string type`, 
- **One-hot Encoding**
  - Encoding symptoms categories (str to float)

## 2️ Data Preprocessing and Data Visualization
- **Principal Component Analysis (PCA)**:
  - Purpose: Narrowing symptoms to balance features and targets.
  - Found: The symptoms were very similar and had little to no variation according to the PCA map. We had trouble finding the categories to differentiate and identify any clusters.
- **T-SNE**
  - Purpose: Due to lack of information using PCA, T-SNE can be used to visualize high-dimensional data into a 2 or 3d plane. In order to narrow our symptoms, we used this method to see how related some symptoms were to each other.
  - Found: The number of symptoms that were being faced by clients were forming clusters on the map, this means that certain symptoms were being seen together. This can be used to help focus our data onto similar symptoms.
- **Association Rule Learning**
  - Purpose: Mapping the symptoms into pairs using Apriori Algorithm
  - Found: ‘Trouble finding the right word’ and ‘Brain Fog’ are symptoms that may fall under the same type of mold (Confidence: 0.944751) 

## 3 Model Building
- **Support Vector Model (SVM)**
  - Supervised machine learning algorithm used for classification and regression tasks. It works by finding a hyperplane that best separates data points into different classes.
  - Result: Over 60% accuarcy on 3 mold species

---

## 📈 Presentation to Technical and Non-technical Stakeholders

To show communication and presentation skills, here is a video of a presentation of our findings:

> [**“We Inspect Studio Project Presentation”**](https://drive.google.com/file/d/1ChykVVNbSp47HiVQ6Q3BocyXlcNovsdb/view?usp=drive_link)

## 📈 Insights & Key Findings
- **Results**: Our main objective was to see if it was possible to predict the type of mold species from the clients symptoms. We were able to find some correlations between symptoms and attempted to focus our model on a narrow feature set. Although prediction accuracies were not above 70%, we found that during our time, there was potential to learn and build more. Our code and data was used for the early stages of incorporating machine learning into their business and was a stepping stone for the usage of AI at We Inspect.
- **What would I do differently**: Spend more time analyzing and breaking down the data. We were given many data points with many features and it would have been beneficial to narrow our search to certain categories of symptoms like "respiratory" instead of taking on all of the symptoms at once.

---

💡 **Developed by:** Megan Kang, Tiffany Truong, Max Ju, Ilda Martinez, Ayelet Kleinerman   
🔗 **Connect with me:** [LinkedIn](https://www.linkedin.com/in/megan-kang-195b70165/)

---
