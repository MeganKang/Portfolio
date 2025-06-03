# AquaGrowth Plant Care App

## 📌 Project Overview
This project is an IOS App paired with a physical device that tracks moisture, temperature, and humidity of various plants. It demonstrates business planning by researching potential market, gaining user insights by conducting interviews, and analyzing competitors, features, budget and profits. It also showcases skills in building mobile apps using **Swift**, creating an account database using **Firebase**, and designing user interface using **Figma**.

## 📊 Tools Used
- `Swift`: Programming mobile app, and building screens.
- `Firebase`: Building a database of accounts for logins.
- `Figma`: Designing the user interface, creating color schemes, and user flow.
- `Trello`: Utilizing an agile project management methodology, scrum process and sprint management.
- `Google Workspace`: Create documents for user research and general project documents and presentations.

## 🛠️ Skills Demonstrated
## 1️ Business Planning, Business Analysis
- `df`, `pandas` for loading the csv file into a dataframe, reading the dataset
- Removing unnecessary symbols such as `astericks` and `whitespaces`
- Changing `obj type` to `string type`, 
- **One-hot Encoding**
  - Encoding symptoms categories (str to float)

## 2️ UI/UX Design
- **Principal Component Analysis (PCA)**:
  - Purpose: Narrowing symptoms to balance features and targets.
  - Found: The symptoms were very similar and had little to no variation according to the PCA map. We had trouble finding the categories to differentiate and identify any clusters.
- **T-SNE**
  - Purpose: Due to lack of information using PCA, T-SNE can be used to visualize high-dimensional data into a 2 or 3d plane. In order to narrow our symptoms, we used this method to see how related some symptoms were to each other.
  - Found: The number of symptoms that were being faced by clients were forming clusters on the map, this means that certain symptoms were being seen together. This can be used to help focus our data onto similar symptoms.
- **Association Rule Learning**
  - Purpose: Mapping the symptoms into pairs using Apriori Algorithm
  - Found: ‘Trouble finding the right word’ and ‘Brain Fog’ are symptoms that may fall under the same type of mold (Confidence: 0.944751) 

## 3 Mobile App Development
- **Support Vector Model (SVM)**
  - Supervised machine learning algorithm used for classification and regression tasks. It works by finding a hyperplane that best separates data points into different classes.
  - Result: Over 60% accuarcy on 3 mold species

## 4 Database Building/Management
-
---

## 📈 Contribution Overview

To show communication and presentation skills, here is a video of a presentation of our findings:


## 📈 App Launch, Insights, Key Takeaways
> [**“Device and App Presentation”**](https://youtu.be/y4WGKv_AzPw?si=svRGplgeaZi754XN)
- **Results**: Our main objective was to see if it was possible to predict the type of mold species from the clients symptoms. We were able to find some correlations between symptoms and attempted to focus our model on a narrow feature set. Although prediction accuracies were not above 70%, we found that during our time, there was potential to learn and build more. Our code and data was used for the early stages of incorporating machine learning into their business and was a stepping stone for the usage of AI at We Inspect.

---

💡 **Developed by:** Megan Kang, Alex Vega, Noah Jacinto, Jaxon Brown, Jeet Patel, Daniel Vasquez   
🔗 **Connect with me:** [LinkedIn](https://www.linkedin.com/in/megan-kang-195b70165/)

---

